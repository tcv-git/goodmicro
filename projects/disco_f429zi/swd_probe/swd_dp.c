
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "peripheral_enable.h"
#include "stm32f4xx_simple_gpio.h"
#include "delay.h"
#include "swd_dp.h"

#define CLOCK_GPIO  GPIOE
#define CLOCK_PIN   PIN2
#define DATA_GPIO   GPIOE
#define DATA_PIN    PIN6

#define LINE_RESET 1
#define LINE_IDLE  0

#define START_BIT  1
#define STOP_BIT   0
#define PARK_BIT   1

enum rw
{
  RW_WRITE = 0,
  RW_READ  = 1,
};

enum port
{
  PORT_DP = 0,
  PORT_AP = 1,
};

enum address
{
  ADDR_DP_R_DPIDR     = 0,
  ADDR_DP_W_ABORT     = 0,
  ADDR_DP_RW_CTRLSTAT = 1,
  ADDR_DP_R_RESEND    = 2,
  ADDR_DP_W_SELECT    = 2,
  ADDR_DP_R_RDBUFF    = 3,
};

static inline void delay(void)
{
  DELAY_US(1);
}

static inline void set_clock_hi(void)
{
  GPIO_set_reset(CLOCK_GPIO, HI(CLOCK_PIN));
}

static inline void set_clock_lo(void)
{
  GPIO_set_reset(CLOCK_GPIO, LO(CLOCK_PIN));
}

static inline void set_data(bool level)
{
  GPIO_set_reset(DATA_GPIO, (level ? HI(DATA_PIN) : LO(DATA_PIN)));
}

static inline void setup_clock(void)
{
  peripheral_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);

  set_clock_lo();

  GPIO_output_push_pull_slow(CLOCK_GPIO, CLOCK_PIN);
}

static inline void setup_data_output(bool level)
{
  peripheral_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);

  set_data(level);

  GPIO_output_push_pull_slow(DATA_GPIO, DATA_PIN);
}

static inline void setup_data_input(void)
{
  peripheral_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);

  GPIO_input_pull_up(DATA_GPIO, DATA_PIN);
}

static inline bool get_data(void)
{
  return ((DATA_GPIO->IDR & DATA_PIN) != 0);
}

static void write_bit(bool bit)
{
  set_data(bit);

  delay();
  set_clock_hi();

  delay();
  set_clock_lo();
}

static bool read_bit(void)
{
  delay();
  bool bit = get_data();

  set_clock_hi();
  delay();
  set_clock_lo();

  return bit;
}

void reset_sequence(void)
{
  setup_clock();
  setup_data_output(LINE_RESET);

  for (uint_fast8_t i = 0; i < 50; i++)
  {
    write_bit(LINE_RESET);
  }

#if 0
  // old JTAG to SWD switching sequence
  // 0 11 0 11 0 11 0 11 0 111
  write_bit(0);
  write_bit(1);
  write_bit(1);
  write_bit(0);
  write_bit(1);
  write_bit(1);
  write_bit(0);
  write_bit(1);
  write_bit(1);
  write_bit(0);
  write_bit(1);
  write_bit(1);
  write_bit(0);
  write_bit(1);
  write_bit(1);
  write_bit(1);
#endif

#if 0
  // new JTAG to SWD switching sequence
  // 0 1111 00 1111 00 111
  write_bit(0);
  write_bit(1);
  write_bit(1);
  write_bit(1);
  write_bit(1);
  write_bit(0);
  write_bit(0);
  write_bit(1);
  write_bit(1);
  write_bit(1);
  write_bit(1);
  write_bit(0);
  write_bit(0);
  write_bit(1);
  write_bit(1);
  write_bit(1);
#endif

#if 0
  // re-reset after switching sequence
  for (uint_fast8_t i = 0; i < 50; i++)
  {
    write_bit(LINE_RESET);
  }
#endif

  // idle so first start bit can be detected
  for (uint_fast8_t i = 0; i < 2; i++)
  {
    write_bit(LINE_IDLE);
  }
}

static void send_request(enum rw rw, enum port port, enum address address)
{
  bool addr_lo = ((address >> 0) & 1);
  bool addr_hi = ((address >> 1) & 1);

  bool parity = ((port + rw + addr_lo + addr_hi) & 1);

  write_bit(START_BIT);
  write_bit(port);
  write_bit(rw);
  write_bit(addr_lo);
  write_bit(addr_hi);
  write_bit(parity);
  write_bit(STOP_BIT);
  write_bit(PARK_BIT);
}

static enum result read_ack(void)
{
  setup_data_input();
  (void)read_bit(); // turnaround

  bool ack_ok   = read_bit();
  bool ack_wait = read_bit();
  bool ack_err  = read_bit();

  if (ack_ok && (!ack_wait) && (!ack_err))
  {
    return OK;
  }
  else if ((!ack_ok) && ack_wait && (!ack_err))
  {
    return WAIT_RESPONSE;
  }
  else if ((!ack_ok) && (!ack_wait) && ack_err)
  {
    return ERROR_RESPONSE;
  }
  else
  {
    return PROTOCOL_ERROR;
  }
}

static enum result write_word(enum port port, enum address address, uint32_t data)
{
  send_request(RW_WRITE, port, address);

  enum result result = read_ack();

  (void)read_bit(); // turnaround

  if (result == OK)
  {
    setup_data_output(data & 1);

    bool parity = 0;

    for (uint_fast8_t i = 0; i < 32; i++)
    {
      bool bit = ((data >> i) & 1);

      parity ^= bit;

      write_bit(bit);
    }

    write_bit(parity);
  }
  else
  {
    setup_data_output(LINE_IDLE);
  }

  for (uint_fast8_t i = 0; i < 8; i++)
  {
    write_bit(LINE_IDLE);
  }

  return result;
}

static enum result read_word(enum port port, enum address address, uint32_t *p_data)
{
  send_request(RW_READ, port, address);

  enum result result = read_ack();

  if (result == OK)
  {
    uint32_t data = 0;

    bool parity = 0;

    for (uint_fast8_t i = 0; i < 32; i++)
    {
      bool bit = read_bit();

      parity ^= bit;

      data |= (bit << i);
    }

    parity ^= read_bit();

    if (parity == 0)
    {
      if (p_data)
      {
        *p_data = data;
      }
    }
    else
    {
      result = PARITY_ERROR;
    }
  }

  (void)read_bit(); // turnaround

  setup_data_output(LINE_IDLE);

  for (uint_fast8_t i = 0; i < 8; i++)
  {
    write_bit(LINE_IDLE);
  }

  return result;
}

enum result read_dpidr(uint32_t *p_data)
{
  return read_word(PORT_DP, ADDR_DP_R_DPIDR, p_data);
}

enum result read_resend(uint32_t *p_data)
{
  return read_word(PORT_DP, ADDR_DP_R_RESEND, p_data);
}

enum result read_rdbuff(uint32_t *p_data)
{
  return read_word(PORT_DP, ADDR_DP_R_RDBUFF, p_data);
}

enum result write_abort(uint32_t data)
{
  return write_word(PORT_DP, ADDR_DP_W_ABORT, data);
}

enum result write_select(uint32_t data)
{
  return write_word(PORT_DP, ADDR_DP_W_SELECT, data);
}

static uint32_t previous_select = UINT32_MAX;

enum result set_apsel(uint8_t apsel)
{
  uint32_t data;

  if (previous_select == UINT32_MAX)
  {
    data = (apsel << 24);
  }
  else
  {
    data = ((apsel << 24) | (previous_select & 0xFF));
  }

  if (data == previous_select)
  {
    return OK;
  }

  enum result result = write_select(data);

  if (result == OK)
  {
    previous_select = data;
  }
  else
  {
    previous_select = UINT32_MAX;
  }

  return result;
}

enum result set_apbank(uint8_t apbank)
{
  if (apbank > 0xF)
  {
    return INVALID_ARG;
  }

  uint32_t data;

  if (previous_select == UINT32_MAX)
  {
    data = (apbank << 4);
  }
  else
  {
    data = ((apbank << 4) | (previous_select & 0xFF00000FuL));
  }

  if (data == previous_select)
  {
    return OK;
  }

  enum result result = write_select(data);

  if (result == OK)
  {
    previous_select = data;
  }
  else
  {
    previous_select = UINT32_MAX;
  }

  return result;
}

enum result set_dpbank(uint8_t dpbank)
{
  if (dpbank > 0xF)
  {
    return INVALID_ARG;
  }

  uint32_t data;

  if (previous_select == UINT32_MAX)
  {
    data = dpbank;
  }
  else
  {
    data = (dpbank | (previous_select & 0xFF0000F0uL));
  }

  if (data == previous_select)
  {
    return OK;
  }

  enum result result = write_select(data);

  if (result == OK)
  {
    previous_select = data;
  }
  else
  {
    previous_select = UINT32_MAX;
  }

  return result;
}

enum result set_apsel_apbank(uint8_t apsel, uint8_t apbank)
{
  if (apbank > 0xF)
  {
    return INVALID_ARG;
  }

  uint32_t data;

  if (previous_select == UINT32_MAX)
  {
    data = ((apsel << 24) | (apbank << 4));
  }
  else
  {
    data = ((apsel << 24) | (apbank << 4) | (previous_select & 0x0000000FuL));
  }

  if (data == previous_select)
  {
    return OK;
  }

  enum result result = write_select(data);

  if (result == OK)
  {
    previous_select = data;
  }
  else
  {
    previous_select = UINT32_MAX;
  }

  return result;
}

enum result set_apsel_apbank_dbank(uint8_t apsel, uint8_t apbank, uint8_t dpbank)
{
  if ((apbank > 0xF) || (dpbank > 0xF))
  {
    return INVALID_ARG;
  }

  uint32_t data = ((apsel << 24) | (apbank << 4) | dpbank);

  if (data == previous_select)
  {
    return OK;
  }

  enum result result = write_select(data);

  if (result == OK)
  {
    previous_select = data;
  }
  else
  {
    previous_select = UINT32_MAX;
  }

  return result;
}

enum result read_ctrlstat(uint32_t *p_data)
{
  enum result result = set_dpbank(0);

  if (result == OK)
  {
    result = read_word(PORT_DP, ADDR_DP_RW_CTRLSTAT, p_data);
  }

  return result;
}

enum result read_dlcr(uint32_t *p_data)
{
  enum result result = set_dpbank(1);

  if (result == OK)
  {
    result = read_word(PORT_DP, ADDR_DP_RW_CTRLSTAT, p_data);
  }

  return result;
}

enum result write_ctrlstat(uint32_t data)
{
  enum result result = set_dpbank(0);

  if (result == OK)
  {
    result = write_word(PORT_DP, ADDR_DP_RW_CTRLSTAT, data);
  }

  return result;
}

enum result write_dlcr(uint32_t data)
{
  enum result result = set_dpbank(1);

  if (result == OK)
  {
    result = write_word(PORT_DP, ADDR_DP_RW_CTRLSTAT, data);
  }

  return result;
}

enum result read_ap(uint8_t apsel, uint8_t address, uint32_t *p_data)
{
  if ((address & 3) != 0)
  {
    return INVALID_ARG;
  }

  enum result result = set_apsel_apbank(apsel, (address >> 4));

  if (result == OK)
  {
    result = read_word(PORT_AP, ((address >> 2) & 3), NULL);
  }

  if (result == OK)
  {
    result = read_word(PORT_DP, ADDR_DP_R_RDBUFF, p_data);
  }

  return result;
}
