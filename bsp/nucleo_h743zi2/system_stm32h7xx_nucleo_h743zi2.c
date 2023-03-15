// system_stm32h7xx_nucleo_h743zi2.c
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
#include "stm32h7xx.h"
#include "system_stm32h7xx.h"


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (64u * 1000 * 1000);


/* System initialization
 */
void SystemInit(void)
{
  // SysTick on with no interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

  // debug cycle counter on
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->LAR          = 0xC5ACCE55u;
  DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT       = 0;
}
