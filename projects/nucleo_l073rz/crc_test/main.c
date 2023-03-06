// main.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all intellectual property rights in them, including
  copyright, trademarks, design rights, database right, patents, and the right
  to be identified as the author.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  You are free to use, modify and distribute this software as you please, but
  you do so at your own risk.  If you do not pass on this warning then you may
  be responsible for any problems encountered by those who obtain the software
  through you.
*/

#include <string.h>
#include "stm32l0xx.h"
#include "debug_printf.h"
#include "sw_crc.h"
#include "hw_crc.h"

static void test(const uint8_t *data, uint32_t count)
{
  uint16_t soft = crc_CalcCrc(data, count);
  uint16_t hard = crc_calc   (data, count);

  debug_printf("%04X %04X %s\n", soft, hard, (soft==hard?"***":""));
}

int main(void)
{
  debug_uart_init();
  debug_printf("\f");

  crc_init();

  uint8_t data[] = "xdfgncxdtn rt ghjgf mctuh";

  test(&data[0], ((sizeof data) - 0));
  test(&data[1], ((sizeof data) - 1));
  test(&data[2], ((sizeof data) - 2));
  test(&data[3], ((sizeof data) - 3));

  test(&data[0], ((sizeof data) - 1));
  test(&data[1], ((sizeof data) - 2));
  test(&data[2], ((sizeof data) - 3));
  test(&data[3], ((sizeof data) - 4));

  test(&data[0], ((sizeof data) - 2));
  test(&data[1], ((sizeof data) - 3));
  test(&data[2], ((sizeof data) - 4));
  test(&data[3], ((sizeof data) - 5));

  test(&data[0], ((sizeof data) - 3));
  test(&data[1], ((sizeof data) - 4));
  test(&data[2], ((sizeof data) - 5));
  test(&data[3], ((sizeof data) - 6));

  debug_printf("done\n");

  for (;;);
}
