// Hardware CRC calculator driver
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include "stm32l0xx.h"
#include "hw_crc.h"

void crc_init(void)
{
  RCC->AHBENR |= RCC_AHBENR_CRCEN;
  (void)RCC->AHBENR;

  CRC->CR   = (CRC_CR_REV_OUT | CRC_CR_REV_IN | CRC_CR_POLYSIZE_0); // 16-bit
  CRC->INIT = 0;
  CRC->POL  = 0x8005; // 0xA001 reversed
}

uint16_t crc_calc(const uint8_t *data, uint32_t count)
{
  CRC->CR |= CRC_CR_RESET;

  if ((1u & (uintptr_t)data) && (count >= 1))
  {
    *(volatile uint8_t*)&CRC->DR = *data;
    data++;
    count--;
  }

  if ((2u & (uintptr_t)data) && (count >= 2))
  {
    *(volatile uint16_t*)&CRC->DR = *(const uint16_t*)data;
    data  += 2;
    count -= 2;
  }

  while (((3u & (uintptr_t)data) == 0) && (count >= 4))
  {
    *(volatile uint32_t*)&CRC->DR = *(const uint32_t*)data;
    data  += 4;
    count -= 4;
  }

  if (count >= 2)
  {
    *(volatile uint16_t*)&CRC->DR = *(const uint16_t*)data;
    data  += 2;
    count -= 2;
  }

  if (count >= 1)
  {
    *(volatile uint8_t*)&CRC->DR = *data;
  }

  return *(volatile uint16_t*)&CRC->DR;
}
