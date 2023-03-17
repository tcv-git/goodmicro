// main.c
// Copyright Green Energy Options Ltd.

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
