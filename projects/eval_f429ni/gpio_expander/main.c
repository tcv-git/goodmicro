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
#include "stm32f4xx_simple_gpio.h"
#include "debug_printf.h"
#include "i2c_master.h"

#define GREEN_ON   PIN6_LO
#define GREEN_OFF  PIN6_HI
#define ORANGE_ON  PIN7_LO
#define ORANGE_OFF PIN7_HI
#define RED_ON     PIN10_LO
#define RED_OFF    PIN10_HI
#define BLUE_ON    PIN12_LO
#define BLUE_OFF   PIN12_HI

#define JOY_UP     (1u << 2)
#define JOY_RIGHT  (1u << 3)
#define JOY_LEFT   (1u << 4)
#define JOY_DOWN   (1u << 5)

static inline void try_i2cm(int status)
{
  switch (status)
  {
    case I2CM_SUCCESS       : return;
    case I2CM_ERROR_USAGE   : debug_printf("I2CM_ERROR_USAGE"   "\n");  for (;;);
    case I2CM_ERROR_BUSY    : debug_printf("I2CM_ERROR_BUSY"    "\n");  for (;;);
    case I2CM_ERROR_ARLO    : debug_printf("I2CM_ERROR_ARLO"    "\n");  for (;;);
    case I2CM_ERROR_NACK    : debug_printf("I2CM_ERROR_NACK"    "\n");  for (;;);
    case I2CM_ERROR_TIMEOUT : debug_printf("I2CM_ERROR_TIMEOUT" "\n");  for (;;);
    default                 : debug_printf("unkown i2cm status" "\n");  for (;;);
  }
}

int main(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_slow(GPIOG, (PIN6 | PIN7 | PIN10 | PIN12));

  debug_uart_init();

  try_i2cm(i2cm_init());

  try_i2cm(i2cm_start_write(0x42));

  try_i2cm(i2cm_write_data((const uint8_t*)"\x00", 1, false));

  try_i2cm(i2cm_start_read(0x42));

  uint8_t readback[2];

  try_i2cm(i2cm_read_data(readback, sizeof readback, true, true));

  if ((readback[0] != 0x00) || (readback[1] != 0x16))
  {
    debug_printf("ID %02X,%02X expected 00,16\n", readback[0], readback[1]);
    for (;;);
  }

  for (;;)
  {
    try_i2cm(i2cm_start_write(0x42));

    try_i2cm(i2cm_write_data((const uint8_t*)"\x11", 1, false));

    try_i2cm(i2cm_start_read(0x42));

    try_i2cm(i2cm_read_data(readback, 1, true, true));

    uint32_t leds = 0;

    if ((readback[0] & JOY_UP   ) == 0){ leds |= GREEN_ON  ; }else{ leds |= GREEN_OFF  ; }
    if ((readback[0] & JOY_RIGHT) == 0){ leds |= ORANGE_ON ; }else{ leds |= ORANGE_OFF ; }
    if ((readback[0] & JOY_LEFT ) == 0){ leds |= RED_ON    ; }else{ leds |= RED_OFF    ; }
    if ((readback[0] & JOY_DOWN ) == 0){ leds |= BLUE_ON   ; }else{ leds |= BLUE_OFF   ; }

    GPIO_set_reset(GPIOG, leds);
  }
}
