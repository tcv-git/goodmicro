// system_stm32f0xx_pll.c
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
#include "stm32f0xx_missing.h"
#include "clock_config.h"
#include "stm32f0xx_simple_clocks.h"

// default value of register field:
#define RCC_CR_HSITRIM_Default      RCC_CR_HSITRIM_4


// calculated register values:
#if   (HPRE ==   1)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV1
#elif (HPRE ==   2)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV2
#elif (HPRE ==   4)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV4
#elif (HPRE ==   8)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV8
#elif (HPRE ==  16)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV16
#elif (HPRE ==  64)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV64
#elif (HPRE == 128)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV128
#elif (HPRE == 256)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV256
#elif (HPRE == 512)
#define RCC_CFGR_HPRE_DIV   RCC_CFGR_HPRE_DIV512
#endif

#if   (PPRE ==   1)
#define RCC_CFGR_PPRE_DIV   RCC_CFGR_PPRE_DIV1
#elif (PPRE ==   2)
#define RCC_CFGR_PPRE_DIV   RCC_CFGR_PPRE_DIV2
#elif (PPRE ==   4)
#define RCC_CFGR_PPRE_DIV   RCC_CFGR_PPRE_DIV4
#elif (PPRE ==   8)
#define RCC_CFGR_PPRE_DIV   RCC_CFGR_PPRE_DIV8
#elif (PPRE ==  16)
#define RCC_CFGR_PPRE_DIV   RCC_CFGR_PPRE_DIV16
#endif


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = HCLK;


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

#if defined (HSEBYP) && (HSEBYP != 0)
  // HSE bypass on
  RCC->CR |= RCC_CR_HSEBYP;
#endif

#if PLLSRC == RCC_CFGR_PLLSRC_HSE_PREDIV
  // HSE on
  RCC->CR |= RCC_CR_HSEON;

  // wait until HSE ready
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);
#endif

#if defined(RCC_CFGR_PLLSRC_HSI48_PREDIV) && (PLLSRC == RCC_CFGR_PLLSRC_HSI48_PREDIV)

  // HSI48 on, HSI14 off and cannot be turned on by ADC
  RCC->CR2 = (RCC_CR2_HSI48ON | RCC_CR2_HSI14DIS);

  // wait until HSI48 ready and HSI14 stopped
  while ((RCC->CR2 & (RCC_CR2_HSI14RDY | RCC_CR2_HSI48RDY)) != RCC_CR2_HSI48RDY);

#elif defined(RCC_CR_HSI48RDY)

  // HSI48 off, HSI14 off and cannot be turned on by ADC
  RCC->CR2 = RCC_CR2_HSI14DIS;

  // wait until HSI14 and HSI48 stopped
  while ((RCC->CR2 & (RCC_CR2_HSI14RDY | RCC_CR2_HSI48RDY)) != 0);

#else
  // HSI14 off and cannot be turned on by ADC
  RCC->CR2 = RCC_CR2_HSI14DIS;

  // wait until HSI14 stopped
  while ((RCC->CR2 & RCC_CR2_HSI14RDY) != 0);
#endif

  // configure PLL, clock output and clock dividers
  RCC->CFGR = (RCC_CFGR_MCO_NOCLOCK
             | ((PLLMUL - 2u) << 18)
             | PLLSRC
             | RCC_CFGR_PPRE_DIV
             | RCC_CFGR_HPRE_DIV
             | RCC_CFGR_SW_HSI);

  // set PREDIV (also sets RCC_CFGR_PLLXTPRE)
  RCC->CFGR2 = (PREDIV - 1u);

  // PLL and CSS on
  RCC->CR |= (RCC_CR_CSSON | RCC_CR_PLLON);

  // wait until PLL ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

#if SYSCLK > 24000000
  // flash 1 wait state, enable prefetch buffer
  FLASH->ACR = (FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY);

  // wait for wait-states to be applied
  while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY);
#else
  // flash zero wait states, prefetch off (no advantage at 0WS)
  FLASH->ACR = 0;
#endif

  // SYSCLK from PLL
  RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // various peripheral clocks to default
  RCC->CFGR3 = 0;

#if (PLLSRC == RCC_CFGR_PLLSRC_HSE_PREDIV) || (defined(RCC_CFGR_PLLSRC_HSI48_PREDIV) && (PLLSRC == RCC_CFGR_PLLSRC_HSI48_PREDIV))
  // HSI off
  RCC->CR &= ~RCC_CR_HSION;

  // wait until HSI stopped
  while ((RCC->CR & RCC_CR_HSIRDY) != 0);
#endif

  // SysTick on with no interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
}
