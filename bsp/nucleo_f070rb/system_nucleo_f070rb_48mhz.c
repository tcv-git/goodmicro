// system_nucleo_f070rb_48mhz.c
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
#include "stm32f0xx.h"
#include "system_stm32f0xx.h"

// default value of register field:
#define RCC_CR_HSITRIM_Default      RCC_CR_HSITRIM_4


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (48u * 1000 * 1000);


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

  // MCO off, HPRE=1, PPRE=1, ADCPRE=2, SYSCLK from HSI
  RCC->CFGR = ((RCC->CFGR & ~(RCC_CFGR_MCO
                            | RCC_CFGR_HPRE
                            | RCC_CFGR_PPRE
                            | RCC_CFGR_ADCPRE
                            | RCC_CFGR_SW)) | RCC_CFGR_SW_HSI);

  // wait until SYSCLK from HSI
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

  // PLL and CSS off
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_CSSON);

  // wait until PLL stopped
  while ((RCC->CR & RCC_CR_PLLRDY) != 0);

  // HSE off, default HSI trim, keep HSI on
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSION);

  // wait until HSE stopped
  while ((RCC->CR & RCC_CR_HSERDY) != 0);

  // HSE on with bypass, keep HSI on
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSION | RCC_CR_HSEON | RCC_CR_HSEBYP);

  // wait until HSE ready
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

  // configure PLL, clock output and clock dividers
  RCC->CFGR = (RCC_CFGR_MCO_NOCLOCK
             | RCC_CFGR_PLLMUL12
             | RCC_CFGR_PLLSRC_HSE_PREDIV
             | RCC_CFGR_ADCPRE_DIV2
             | RCC_CFGR_PPRE_DIV1
             | RCC_CFGR_HPRE_DIV1
             | RCC_CFGR_SW_HSI);

  // set PREDIV (also sets RCC_CFGR_PLLXTPRE)
  RCC->CFGR2 = RCC_CFGR2_PREDIV_DIV2;

  // PLL and CSS on
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSION | RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_PLLON | RCC_CR_CSSON);

  // wait until PLL ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

  // enable flash prefetch, one wait-state
  FLASH->ACR = (FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY);

  // wait for wait-states to be applied
  while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY);

  // SYSCLK from PLL
  RCC->CFGR = (RCC_CFGR_MCO_NOCLOCK
             | RCC_CFGR_PLLMUL12
             | RCC_CFGR_PLLSRC_HSE_PREDIV
             | RCC_CFGR_ADCPRE_DIV2
             | RCC_CFGR_PPRE_DIV1
             | RCC_CFGR_HPRE_DIV1
             | RCC_CFGR_SW_PLL);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // HSI off
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_PLLON | RCC_CR_CSSON);

  // wait until HSI stopped
  while ((RCC->CR & RCC_CR_HSIRDY) != 0);

  // SysTick on with no interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
}
