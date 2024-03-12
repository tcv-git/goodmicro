
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "peripheral_enable.h"
#include "stm32f4xx_simple_gpio.h"
#include "delay.h"
#include "swd.h"

#define CLOCK_GPIO  GPIOE
#define CLOCK_PIN   PIN2
#define DATA_GPIO   GPIOE
#define DATA_PIN    PIN6

#define START_BIT 1
#define STOP_BIT  0
#define PARK_BIT  1

#define RW_READ   1
#define RW_WRITE  0


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
  set_clock_hi();

  bool bit = get_data();

  delay();
  set_clock_lo();

  return bit;
}

void reset_sequence(void)
{
  setup_clock();
  setup_data_output(1);

  for (uint_fast8_t i = 0; i < 50; i++)
  {
    write_bit(1);
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
    write_bit(1);
  }
#endif
}

enum result write_word(enum port port, enum address address, uint32_t data)
{
  setup_data_output(0);

  for (uint_fast8_t i = 0; i < 16; i++)
  {
    write_bit(0);
  }

  bool addr_lo = ((address >> 0) & 1);
  bool addr_hi = ((address >> 1) & 1);

  bool parity = ((port + RW_WRITE + addr_lo + addr_hi) & 1);

  write_bit(START_BIT);
  write_bit(port);
  write_bit(RW_WRITE);
  write_bit(addr_lo);
  write_bit(addr_hi);
  write_bit(parity);
  write_bit(STOP_BIT);
  write_bit(PARK_BIT);

  setup_data_input();
  (void)read_bit(); // turnaround

  bool ack_ok   = read_bit();
  bool ack_wait = read_bit();
  bool ack_err  = read_bit();

  (void)read_bit(); // turnaround
  setup_data_output(0);

  if ((ack_ok + ack_wait + ack_err) != 1)
  {
    return PROTOCOL_ERROR;
  }

  if (ack_err)
  {
    return ERROR_RESPONSE;
  }

  if (ack_wait)
  {
    return WAIT_RESPONSE;
  }

  parity = 0;

  for (uint_fast8_t i = 0; i < 32; i++)
  {
    bool bit = ((data >> i) & 1);

    parity = ((parity + bit) & 1);

    write_bit(bit);
  }

  write_bit(parity);

  return OK;
}

enum result read_word(enum port port, enum address address, uint32_t *p_data)
{
  setup_data_output(0);

  for (uint_fast8_t i = 0; i < 16; i++)
  {
    write_bit(0);
  }

  bool addr_lo = ((address >> 0) & 1);
  bool addr_hi = ((address >> 1) & 1);

  bool parity = ((port + RW_READ + addr_lo + addr_hi) & 1);

  write_bit(START_BIT);
  write_bit(port);
  write_bit(RW_READ);
  write_bit(addr_lo);
  write_bit(addr_hi);
  write_bit(parity);
  write_bit(STOP_BIT);
  write_bit(PARK_BIT);

  setup_data_input();
  (void)read_bit(); // turnaround

  bool ack_ok   = read_bit();
  bool ack_wait = read_bit();
  bool ack_err  = read_bit();

  if ((ack_ok + ack_wait + ack_err) != 1)
  {
    return PROTOCOL_ERROR;
  }

  if (ack_err)
  {
    return ERROR_RESPONSE;
  }

  if (ack_wait)
  {
    return WAIT_RESPONSE;
  }

  uint32_t data = 0;

  parity = 0;

  for (uint_fast8_t i = 0; i < 32; i++)
  {
    bool bit = read_bit();

    data |= (bit << i);

    parity = ((parity + bit) & 1);
  }

  parity = ((parity + read_bit()) & 1);

  if (parity)
  {
    return PARITY_ERROR;
  }

  if (p_data)
  {
    *p_data = data;
  }

  return OK;
}

enum result read_register_via_buffer(enum port port, enum address address, uint32_t *p_data)
{
  enum result result = read_word(port, address, NULL);

  if (result == OK)
  {
    result = read_word(DP, ADDR_DP_R_RDBUFF, p_data);
  }

  return result;
}
