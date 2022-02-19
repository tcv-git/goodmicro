// main.c
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
#include "i2c_master.h"
#include "lcd.h"
#include "lcd_text.h"
#include "delay.h"

#define BUS_ADDRESS 0x70

#define REG_READ_DATA 0x00

static int gpiox_write(uint8_t reg, uint8_t data)
{
  uint8_t transfer[2];

  transfer[0] = reg;
  transfer[1] = data;

  return i2cm_write(BUS_ADDRESS, transfer, sizeof transfer);
}

static int gpiox_read(uint8_t reg)
{
  int status = i2cm_start_write(BUS_ADDRESS);

  if (status < 0)
  {
    return status;
  }

  status = i2cm_write_data(&reg, sizeof reg, false);

  if (status < 0)
  {
    return status;
  }

  status = i2cm_start_read(BUS_ADDRESS);

  if (status < 0)
  {
    return status;
  }

  uint8_t data;

  status = i2cm_read_data(&data, sizeof data, true, true);

  if (status < 0)
  {
    return status;
  }

  return data;
}

int main(void)
{
  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  int result = i2cm_init();

  if (result != 0)
  {
    lcd_printf("i2c init status %d\n", result);
    for (;;);
  }

  result = gpiox_write(0x03, 0xCF);

  if (result != 0)
  {
    lcd_printf("i2c write status %d\n", result);
    for (;;);
  }

  unsigned int i;

  for (i = 0;; i++)
  {
    result = gpiox_read(REG_READ_DATA);

    if (result < 0)
    {
      lcd_printf("i2c init status %d\n", result);
      for (;;);
    }

    lcd_printf("%02X\n", result);

    uint8_t output = 0x30;

    if ((result & 0x80) == 0)
    {
      output ^= 0x20;
    }

    if ((result & 0x40) == 0)
    {
      output ^= 0x10;
    }

    result = gpiox_write(0x01, output);

    if (result != 0)
    {
      lcd_printf("i2c write status %d\n", result);
      for (;;);
    }

    DELAY_MS(100);
  }
}
