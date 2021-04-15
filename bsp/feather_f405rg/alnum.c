// alnum.c
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
#include "alnum.h"

#define I2C_ADDRESS  0x70

const uint16_t ALNUM_DIGITS[10] =
{
  SEGMENTS_0,
  SEGMENTS_1,
  SEGMENTS_2,
  SEGMENTS_3,
  SEGMENTS_4,
  SEGMENTS_5,
  SEGMENTS_6,
  SEGMENTS_7,
  SEGMENTS_8,
  SEGMENTS_9
};

void alnum_init(void)
{
  uint8_t message1[1] = {0x21};
  uint8_t message2[1] = {0x81};

  i2cm_write(I2C_ADDRESS, message1, sizeof message1);
  i2cm_write(I2C_ADDRESS, message2, sizeof message2);
}

void alnum_write(uint16_t d1, uint16_t d2, uint16_t d3, uint16_t d4)
{
  uint8_t message[17] = {0};

  message[1] = ((d1 >> 0) & 0xFF);
  message[2] = ((d1 >> 8) & 0xFF);
  message[3] = ((d2 >> 0) & 0xFF);
  message[4] = ((d2 >> 8) & 0xFF);
  message[5] = ((d3 >> 0) & 0xFF);
  message[6] = ((d3 >> 8) & 0xFF);
  message[7] = ((d4 >> 0) & 0xFF);
  message[8] = ((d4 >> 8) & 0xFF);

  i2cm_write(I2C_ADDRESS, message, sizeof message);
}

void alnum_red(unsigned int x)
{
  if (x < 10)
  {
    alnum_write(0, ALNUM_DIGITS[x % 10], 0, 0);
  }
  else
  {
    alnum_write(ALNUM_DIGITS[(x / 10) % 10], ALNUM_DIGITS[x % 10], 0, 0);
  }
}

void alnum_green(unsigned int x)
{
  if (x < 10)
  {
    alnum_write(0, 0, 0, ALNUM_DIGITS[x % 10]);
  }
  else
  {
    alnum_write(0, 0, ALNUM_DIGITS[(x / 10) % 10], ALNUM_DIGITS[x % 10]);
  }
}

void alnum_lim(unsigned int x)
{
  alnum_write(SEGMENTS_LI, SEGMENTS_M, ALNUM_DIGITS[(x / 10) % 10], ALNUM_DIGITS[x % 10]);
}
