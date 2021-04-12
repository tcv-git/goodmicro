// i2c_master.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all copyright and other intellectual property rights
  in them.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  If you use, modify or distribute this software then you do so at your own
  risk.  If you do not pass on this warning then you may be responsible for any
  problems encountered by those who obtain the software through you.
*/

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_missing.h"
#include "stm32f4xx_simple_gpio.h"
#include "system_stm32f405-439.h"
#include "delay.h"
#include "uptime.h"
#include "i2c_master.h"

#define I2CM_SCL_PORT           GPIOB
#define I2CM_SCL_PORT_ENR       RCC->AHB1ENR
#define I2CM_SCL_PORT_ENR_BIT   RCC_AHB1ENR_GPIOBEN
#define I2CM_SCL_PINMASK        PIN6
#define I2CM_SCL_AFn            AF4
#define I2CM_SDA_PORT           GPIOB
#define I2CM_SDA_PORT_ENR       RCC->AHB1ENR
#define I2CM_SDA_PORT_ENR_BIT   RCC_AHB1ENR_GPIOBEN
#define I2CM_SDA_PINMASK        PIN7
#define I2CM_SDA_AFn            AF4
#define I2CM_ENR                RCC->APB1ENR
#define I2CM_ENR_BIT            RCC_APB1ENR_I2C1EN
#define I2CM_RSTR               RCC->APB1RSTR
#define I2CM_RSTR_BIT           RCC_APB1RSTR_I2C1RST
#define I2CM                    I2C1
#define I2CM_APB_CLK            APB1_CLK

#define I2CM_CLK   100000u  // required I2C clock speed: 100kHz

#define CR2_FREQ  ((unsigned int)I2CM_APB_CLK / 1000000u)
#define CCR_CCR   ((unsigned int)I2CM_APB_CLK / (2 * I2CM_CLK))


static void i2cm_init_peripheral(void)
{{{
/*  Register bits:

  CR1:
    SWRST      x  software reset
    ALERT      0  not SMB
    PEC        0  no CRC
    POS        0  no CRC
    ACK        x  varies
    STOP       x  varies
    START      x  varies
    NOSTRETCH  0  use stretching
    ENGC       0  no general call
    ENPEC      0  no CRC
    ENARP      0  no ARP
    SMBTYPE    0  not SMB
    SMBUS      0  not SMB
    PE         1  enable

  CR2:
    LAST       0  not using DMA
    DMAEN      0  not using DMA
    ITBUFEN    0  not using interrupts
    ITEVTEN    0  not using interrupts
    ITERREN    0  not using interrupts
    FREQ      xx  peripheral clock in MHz, eg: if APBxCLK = 42MHz set FREQ = 42

  OAR1:        0  not a slave
  OAR2:        0  not a slave

  CCR:
    FS:        0  standard mode
    DUTY:      0  not in fast mode
    CCR:      xx  ((xx periods high + xx period low) * (1/APBCLK)) must equal (1/ desired I2C clock frequency)

  TRISE:      xx  (in standard mode, this is 1 more than FREQ)

  FLTR:      N/A on stm32f40x
    (FIXME if running on STM32F42x set ANOFF=0, DNF=0xF as long as PCLK >= 40MHz)

  SR1:
    ALERT:    won't happen, not SMB
    TIMEOUT:  won't happen, not SMB
    PECERR:   won't happen, CRC not enabled
    OVR:      won't happen, stretching enabled
    AF:       got a nack need to clear by writing zero and sending stop
    ARLO:     some other master has the bus, we are waiting
    BERR:     set at random by hardware, master will carry on regardless
    TxE       time to send
    RxNE      time to read
    STOPF     someone sent a stop, write to CR1 to clear
    ADD10:    won't happen, not using 10 bit mode
    BTF:      we are stretching, check TxE or RxNE
    ADDR:     sent address acked (or recieved address matched, since slave mode cannot be disabled)
              clear by read SR1 SR2
    SB:       start was sent, write address to DR

  SR2: don't care, except:
    BUSY:     something ongoing
    MSL:      we are the master
*/

  I2CM->CR1   = 0;
  I2CM->CR2   = CR2_FREQ;
  I2CM->OAR1  = 0;
  I2CM->OAR2  = 0;
  I2CM->CCR   = CCR_CCR;
  I2CM->TRISE = (CR2_FREQ + 1);
}}}


int i2cm_init(void)
{{{
  I2CM_RSTR |= I2CM_RSTR_BIT;
  I2CM_ENR  |= I2CM_ENR_BIT;
  (void)I2CM_ENR;
  I2CM_RSTR &= ~I2CM_RSTR_BIT;
  (void)I2CM_RSTR;

  I2CM_SCL_PORT_ENR |= I2CM_SCL_PORT_ENR_BIT;
  (void)I2CM_SCL_PORT_ENR;
  I2CM_SDA_PORT_ENR |= I2CM_SDA_PORT_ENR_BIT;
  (void)I2CM_SDA_PORT_ENR;

  GPIO_alternate_open_drain_pull_up_slow(I2CM_SCL_PORT, I2CM_SCL_PINMASK, I2CM_SCL_AFn);
  GPIO_alternate_open_drain_pull_up_slow(I2CM_SDA_PORT, I2CM_SDA_PINMASK, I2CM_SDA_AFn);

  GPIO_lock(I2CM_SCL_PORT, I2CM_SCL_PINMASK);
  GPIO_lock(I2CM_SDA_PORT, I2CM_SDA_PINMASK);

  i2cm_init_peripheral();

  return I2CM_SUCCESS;
}}}


static int i2cm_stop_reset(int status)
{{{
  // send stop if we are master
  if ((I2CM->SR2 & I2C_SR2_MSL) != 0)
  {
    I2CM->CR1 |= I2C_CR1_STOP;
  }

  // poll until stop is sent
  uint64_t timeout = (uptime_ms() + 25);

  for (;;)
  {
    uint32_t sr1 = I2CM->SR1;

    if ((sr1 & I2C_SR1_ARLO) != 0)
    {
      // another master has the bus
      if (status == I2CM_SUCCESS){ status = I2CM_ERROR_ARLO; }
    }

    if ((sr1 & I2C_SR1_AF) != 0)
    {
      // we got leftover nack
      if (status == I2CM_SUCCESS){ status = I2CM_ERROR_NACK; }
    }

    uint32_t sr2 = I2CM->SR2;

    if ((sr2 & I2C_SR2_MSL) == 0)
    {
      // we are no longer master
      break;
    }

    if (uptime_ms() > timeout)
    {
      if (status == I2CM_SUCCESS){ status = I2CM_ERROR_TIMEOUT; }
      break;
    }
  }

  // because the BERR flag doesn't work (see errata) we reset the peripheral after every transmission
  I2CM->CR1 = I2C_CR1_SWRST;

  DELAY_US(50);

  // rewrite all registers that get cleared by SWRST
  i2cm_init_peripheral();

  // even when PE is 0 the peripheral starts updating BUSY, which we will check before we next start

  return status;
}}}


static int i2cm_start(uint8_t address_byte)
{{{
  uint32_t sr2 = I2CM->SR2;

  if (((sr2 & I2C_SR2_BUSY) != 0) && ((sr2 & I2C_SR2_MSL) == 0))
  {
    // busy but we are not master
    return I2CM_ERROR_BUSY;
  }

  // clear SWRESET, START, STOP, ACK in CR1 and STOPF in SR1
  I2CM->CR1 = I2C_CR1_PE;

  // clear any leftover unread data
  (void)I2CM->DR;
  (void)I2CM->DR;

  // clear previous TIMEOUT, AF, ARLO, BERR
  I2CM->SR1 = 0;

  // clear previous ADDR
  (void)I2CM->SR1;
  (void)I2CM->SR2;

  // request to send start
  I2CM->CR1 = (I2C_CR1_PE | I2C_CR1_START);

  // poll for start sent
  uint64_t timeout = (uptime_ms() + 25);

  for (;;)
  {
    uint32_t sr1 = I2CM->SR1;

    if ((sr1 & I2C_SR1_ARLO) != 0)
    {
      // another master has the bus
      return i2cm_stop_reset(I2CM_ERROR_ARLO);
    }

    if ((sr1 & I2C_SR1_SB) != 0)
    {
      // start sent, ready for address
      break;
    }

    if (uptime_ms() > timeout)
    {
      // someone over-stretched the bus
      return i2cm_stop_reset(I2CM_ERROR_TIMEOUT);
    }
  }

  I2CM->DR = address_byte;

  for (;;)
  {
    uint32_t sr1 = I2CM->SR1;

    if ((sr1 & I2C_SR1_ARLO) != 0)
    {
      // another master has the bus
      return i2cm_stop_reset(I2CM_ERROR_ARLO);
    }

    if ((sr1 & I2C_SR1_AF) != 0)
    {
      // we got nack
      return i2cm_stop_reset(I2CM_ERROR_NACK);
    }

    if ((sr1 & I2C_SR1_ADDR) != 0)
    {
      // address sent, ready for data
      break;
    }

    if (uptime_ms() > timeout)
    {
      // someone over-stretched the bus
      return i2cm_stop_reset(I2CM_ERROR_TIMEOUT);
    }
  }

  (void)I2CM->SR2;  // read to clear ADDR

  return I2CM_SUCCESS;
}}}


int i2cm_start_write(uint8_t slave_address)
{{{
  if (slave_address > 0x7F)
  {
    return I2CM_ERROR_USAGE;
  }

  return i2cm_start(slave_address << 1);
}}}


int i2cm_start_read(uint8_t slave_address)
{{{
  if (slave_address > 0x7F)
  {
    return I2CM_ERROR_USAGE;
  }

  int status = i2cm_start(((slave_address << 1) | 1));

  if (status == I2CM_SUCCESS)
  {
    // NB: if we are about to read a single byte, we shouldn't set ACK at all
    // (manual says clear it before reading ADDR) but as long as we call
    // i2cm_read_last_byte straight away it will get cleared again before it is sent

    I2CM->CR1 = (I2C_CR1_PE | I2C_CR1_ACK);
  }

  return status;
}}}


static int i2cm_write_byte(uint8_t data)
{{{
  uint64_t timeout = (uptime_ms() + 25);

  for (;;)
  {
    uint32_t sr1 = I2CM->SR1;

    if ((sr1 & I2C_SR1_AF) != 0)
    {
      // we got nack
      return i2cm_stop_reset(I2CM_ERROR_NACK);
    }

    if ((sr1 & I2C_SR1_ARLO) != 0)
    {
      // another master has the bus
      return i2cm_stop_reset(I2CM_ERROR_ARLO);
    }

    if ((sr1 & I2C_SR1_TXE) != 0)
    {
      // ready for data
      break;
    }

    if (uptime_ms() > timeout)
    {
      // someone over-stretched the bus
      return i2cm_stop_reset(I2CM_ERROR_TIMEOUT);
    }
  }

  I2CM->DR = data;

  return I2CM_SUCCESS;
}}}


static int i2cm_read_byte(uint8_t *data)
{{{
  uint64_t timeout = (uptime_ms() + 25);

  for (;;)
  {
    uint32_t sr1 = I2CM->SR1;

    if ((sr1 & I2C_SR1_AF) != 0)
    {
      // we got nack (leftover from when we transmitted)
      return i2cm_stop_reset(I2CM_ERROR_NACK);
    }

    if ((sr1 & I2C_SR1_ARLO) != 0)
    {
      // another master has the bus
      return i2cm_stop_reset(I2CM_ERROR_ARLO);
    }

    if ((sr1 & I2C_SR1_RXNE) != 0)
    {
      // data ready
      break;
    }

    if (uptime_ms() > timeout)
    {
      // someone over-stretched the bus
      return i2cm_stop_reset(I2CM_ERROR_TIMEOUT);
    }
  }

  *data = I2CM->DR;

  return I2CM_SUCCESS;
}}}


static int i2cm_read_last_byte(uint8_t *data, bool send_stop, bool nack_last_byte)
{{{
  if (nack_last_byte)
  {
    I2CM->CR1 = I2C_CR1_PE; // clear I2C_CR1_ACK;
  }

  if (send_stop)
  {
    DELAY_US(12); // let the byte start before setting stop (12us = 1.2 bit times at 100kHz or 4.8 bits at 400kHz)

    I2CM->CR1 |= (I2C_CR1_PE | I2C_CR1_STOP); // set stop (also clear ack - we ignore nack_last_byte if sending stop)
  }

  bool status = i2cm_read_byte(data);

  if (status != I2CM_SUCCESS)
  {
    // read_byte has already called stop_reset
    return status;
  }

  if (!send_stop)
  {
    return I2CM_SUCCESS;
  }

  return i2cm_stop_reset(I2CM_SUCCESS);
}}}


int i2cm_write_data(const uint8_t *data, uint32_t data_length, bool send_stop)
{{{
  for (uint32_t i = 0; i < data_length; i++)
  {
    int status = i2cm_write_byte(data[i]);

    if (status != I2CM_SUCCESS)
    {
      return status;
    }
  }

  if (data_length > 0)
  {
    // poll for transfer complete
    uint64_t timeout = (uptime_ms() + 30);

    for (;;)
    {
      uint32_t sr1 = I2CM->SR1;

      if ((sr1 & I2C_SR1_AF) != 0)
      {
        // we got nack
        return i2cm_stop_reset(I2CM_ERROR_NACK);
      }

      if ((sr1 & I2C_SR1_ARLO) != 0)
      {
        // another master has the bus
        return i2cm_stop_reset(I2CM_ERROR_ARLO);
      }

      if ((sr1 & I2C_SR1_BTF) != 0)
      {
        // byte transfter finished
        break;
      }

      if (uptime_ms() > timeout)
      {
        // someone over-stretched the bus
        return i2cm_stop_reset(I2CM_ERROR_TIMEOUT);
      }
    }
  }

  if (!send_stop)
  {
    return I2CM_SUCCESS;
  }

  return i2cm_stop_reset(I2CM_SUCCESS);
}}}


int i2cm_read_data(uint8_t *data, uint32_t data_length, bool send_stop, bool nack_last_byte)
{{{
  if (data_length > 0)
  {
    uint32_t i;

    for (i = 0; i < (data_length - 1); i++)
    {
      int status = i2cm_read_byte(&data[i]);

      if (status != I2CM_SUCCESS)
      {
        return status;
      }
    }

    int status = i2cm_read_last_byte(&data[i], send_stop, nack_last_byte);

    if (status != I2CM_SUCCESS)
    {
      return status;
    }
  }
  else
  {
    if (nack_last_byte)
    {
      // it is too late to nack the last byte
      // and in fact we may clock in an extra byte that we didn't want
      return I2CM_ERROR_USAGE;
    }
  }

  if (!send_stop)
  {
    return I2CM_SUCCESS;
  }

  return i2cm_stop_reset(I2CM_SUCCESS);
}}}


int i2cm_write(uint8_t slave_address, const uint8_t *data, uint32_t data_length)
{{{
  int status = i2cm_start_write(slave_address);

  if (status == I2CM_SUCCESS)
  {
    status = i2cm_write_data(data, data_length, true); // send_stop = true
  }

  return status;
}}}


int i2cm_read(uint8_t slave_address, uint8_t *data, uint32_t data_length)
{{{
  int status = i2cm_start_read(slave_address);

  if (status == I2CM_SUCCESS)
  {
    status = i2cm_read_data(data, data_length, true, true); // send_stop = true, nack_last_byte = true
  }

  return status;
}}}
