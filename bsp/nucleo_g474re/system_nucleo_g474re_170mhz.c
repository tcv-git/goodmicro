// system_nucleo_g474re_170mhz.c
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
#include "stm32g4xx.h"
#include "system_stm32g4xx.h"

// main PLL parameters:
#define PLL_M             6
#define PLL_N            85
#define PLL_P            12
#define PLL_Q             8
#define PLL_R             2

// flash wait states:
#define FLASH_ACR_LATENCY_Value     FLASH_ACR_LATENCY_4WS


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (170u * 1000 * 1000);

/* System interrupt vector
 */
extern uint32_t g_pfnVectors[];


/* System initialization
 */
void SystemInit(void)
{
  // disable clock interrupts
  RCC->CIER = 0;

  // HSI on
  RCC->CR |= RCC_CR_HSION;

  // wait until HSI ready
  while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

  // MCO off, HPRE=2, PPRE2=1, PPRE1=1, SYSCLK from HSI
  RCC->CFGR = (RCC_CFGR_HPRE_DIV2 | RCC_CFGR_SW_HSI);

  // wait until SYSCLK from HSI
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

  // PLL and CSS off
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_CSSON);

  // wait until PLL stopped
  while ((RCC->CR & RCC_CR_PLLRDY) != 0);

  // HSE off, keep HSI on
  RCC->CR = RCC_CR_HSION;

  // wait until HSE stopped
  while ((RCC->CR & RCC_CR_HSERDY) != 0);

  // enable power management interface
  RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
  (void)RCC->APB1ENR1;

  // disable low power run, select regulator voltage output scale 1 (maximum power)
  PWR->CR1 = ((PWR->CR1 & ~(PWR_CR1_LPR | PWR_CR1_VOS)) | PWR_CR1_VOS_0);

  // wait until VOS changed
  while ((PWR->SR2 & PWR_SR2_VOSF) != 0);

  // enable regulator boost mode
  PWR->CR5 = 0; // sic

  // HSE on (without bypass)
  RCC->CR = (RCC_CR_HSION | RCC_CR_HSEON);

  // wait until HSE ready
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

  // configure PLL
  RCC->PLLCFGR = (RCC_PLLCFGR_PLLSRC_HSE
                | RCC_PLLCFGR_PLLPEN
                | RCC_PLLCFGR_PLLQEN
                | RCC_PLLCFGR_PLLREN
                | ( (PLL_M - 1)      << RCC_PLLCFGR_PLLM_Pos    )
                |   (PLL_N           << RCC_PLLCFGR_PLLN_Pos    )
                | (  PLL_P           << RCC_PLLCFGR_PLLPDIV_Pos )
                | (((PLL_Q / 2) - 1) << RCC_PLLCFGR_PLLQ_Pos    )
                | (((PLL_R / 2) - 1) << RCC_PLLCFGR_PLLR_Pos    ));

  // PLL and CSS on
  RCC->CR = (RCC_CR_HSION | RCC_CR_HSEON | RCC_CR_PLLON | RCC_CR_CSSON);

  // wait until PLL ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

  // configure flash prefetch, instruction cache, data cache and wait states
  FLASH->ACR = ((FLASH->ACR & ~FLASH_ACR_LATENCY)
               | FLASH_ACR_PRFTEN
               | FLASH_ACR_ICEN
               | FLASH_ACR_DCEN
               | FLASH_ACR_LATENCY_Value);

  // wait for wait-states to be applied
  while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_Value);

  // HPRE=2, PPRE2=1, PPRE1=1, SYSCLK from PLL
  RCC->CFGR = (RCC_CFGR_HPRE_DIV2 | RCC_CFGR_SW_PLL);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // wait at least 1 microsecond before setting HPRE
  for (unsigned int i = 0; i < 256; i++)
  {
    __NOP();
  }

  // HPRE=1, PPRE2=1, PPRE1=1, SYSCLK from PLL
  RCC->CFGR = RCC_CFGR_SW_PLL;

  // CLK48 from PLLR, ADC clocks from PLLP, all other peripheral clocks from HCLK/PCLK
  RCC->CCIPR  = (RCC_CCIPR_CLK48SEL_1 | RCC_CCIPR_ADC12SEL_0 | RCC_CCIPR_CLK48SEL_0 | RCC_CCIPR_FDCANSEL_1);
  RCC->CCIPR2 = 0;

  // HSI48 off
  RCC->CRRCR = 0;

  // wait until HSI48 stopped
  while ((RCC->CRRCR & RCC_CRRCR_HSI48RDY) != 0);

  // HSI off
  RCC->CR = (RCC_CR_HSEON | RCC_CR_PLLON | RCC_CR_CSSON);

  // wait until HSI stopped
  while ((RCC->CR & RCC_CR_HSIRDY) != 0);

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

  // enable FPU (set CP10 and CP11 full access)
  SCB->CPACR |= ((3u << (10 * 2)) | (3u << (11 * 2)));

  // enable system configuration interface
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  (void)RCC->APB2ENR;

  // disable I2C FM+, disable analog switch boost, disable analog switch VDDA supply
  // disable FPU interrupts except invalid operation and divide by zero
  SYSCFG->CFGR1 = (SYSCFG_CFGR1_FPU_IE_0 | SYSCFG_CFGR1_FPU_IE_1);
}
