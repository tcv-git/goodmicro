// system_disco_f100rb_24mhz.c
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
#include "stm32f1xx.h"
#include "system_stm32f1xx.h"

// default value of register field:
#define RCC_CR_HSITRIM_Default      (16 << RCC_CR_HSITRIM_Pos)


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (24u * 1000 * 1000);

/* System interrupt vector
 */
extern uint32_t g_pfnVectors[];


/* System initialization
 */
void SystemInit(void)
{
  // disable clock interrupts
  RCC->CIR = 0;

  // HSI on
  RCC->CR |= RCC_CR_HSION;

  // wait until HSI ready
  while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

  // SYSCLK from HSI
  RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_HSI);

  // wait until SYSCLK from HSI
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

  // PLL and CSS off
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_CSSON);

  // wait until PLL stopped
  while ((RCC->CR & RCC_CR_PLLRDY) != 0);

  // HSE off
  RCC->CR &= ~RCC_CR_HSEON;

  // wait until HSE stopped
  while ((RCC->CR & RCC_CR_HSERDY) != 0);

  // default HSI trim, HSE bypass off
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSION);

  // configure PLL, clock output and clock dividers
  RCC->CFGR = (RCC_CFGR_MCO_NOCLOCK
            | RCC_CFGR_PLLMULL6
            | RCC_CFGR_PLLSRC
            | RCC_CFGR_ADCPRE_DIV2
            | RCC_CFGR_PPRE2_DIV1
            | RCC_CFGR_PPRE1_DIV1
            | RCC_CFGR_HPRE_DIV1
            | RCC_CFGR_SW_HSI);

  // set PREDIV (also sets RCC_CFGR_PLLXTPRE)
  RCC->CFGR2 = RCC_CFGR2_PREDIV1_DIV2;

  // HSE and CSS on
  RCC->CR |= (RCC_CR_CSSON | RCC_CR_HSEON);

  // wait until HSE ready
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

  // PLL on
  RCC->CR |= RCC_CR_PLLON;

  // wait until PLL ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

  // flash zero wait states, single cycle access
  FLASH->ACR = 0;

  // SYSCLK from PLL
  RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // HSI off
  RCC->CR &= ~RCC_CR_HSION;

  // SysTick on with no interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

  // debug cycle counter on
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT       = 0;

  // set vector address
  SCB->VTOR = (uint32_t)&g_pfnVectors[0];

  // enable faults
  SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk);

  // trap integer divide by zero
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
}
