// system_nucleo_l073rz_32mhz.c
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
#include "stm32l0xx.h"
#include "system_stm32l0xx.h"


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (32u * 1000 * 1000);

/* System interrupt vector
 */
extern uint32_t g_pfnVectors[];


/* System initialization
 */
void SystemInit(void)
{
  // disable clock interrupts
  RCC->CIER = 0;

  // MSI on
  RCC->CR |= RCC_CR_MSION;

  // wait until MSI ready
  while ((RCC->CR & RCC_CR_MSIRDY) != RCC_CR_MSIRDY);

  // MCO off, STOPWUCK=MSI, HPRE=1, PPRE2=1, PPRE1=1, SYSCLK from MSI
  RCC->CFGR = ((RCC->CFGR & ~(RCC_CFGR_MCOPRE | RCC_CFGR_MCOSEL | RCC_CFGR_STOPWUCK | RCC_CFGR_HPRE | RCC_CFGR_PPRE2 | RCC_CFGR_PPRE1 | RCC_CFGR_SW)) | RCC_CFGR_SW_MSI);

  // wait until SYSCLK from MSI
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_MSI);

  // PLL and CSS off
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_CSSHSEON);

  // wait until PLL stopped
  while ((RCC->CR & RCC_CR_PLLRDY) != 0);

  // HSE and HSI off, RTCPRE=2, keep MSI on
  RCC->CR = RCC_CR_MSION;

  // wait until HSE and HSI stopped
  while ((RCC->CR & (RCC_CR_HSIRDY | RCC_CR_HSERDY)) != 0);

  // enable power interface
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  (void)RCC->APB1ENR;

  // wait until ready to change VOS
  while ((PWR->CSR & PWR_CSR_VOSF) != 0);

  // disable programmable voltage detector, regulator range 1 (highest performance)
  PWR->CR = ((PWR->CR & ~(PWR_CR_PVDE | PWR_CR_VOS)) | PWR_CR_VOS_0);

  // wait until VOS changed
  while ((PWR->CSR & PWR_CSR_VOSF) != 0);

  // HSE on with bypass
  RCC->CR = (RCC_CR_MSION | RCC_CR_HSEON | RCC_CR_HSEBYP);

  // wait until HSE ready
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

  // keep MCO off, PLLDIV=2, PLLMUL=8, PLLSRC=HSE, PPRE2=1, PPRE1=1, HPRE=1, keep SYSCLK from MSI
  RCC->CFGR = (RCC_CFGR_PLLDIV2 | RCC_CFGR_PLLMUL8 | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_SW_MSI);

  // PLL and CSS on
  RCC->CR = (RCC_CR_MSION | RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_PLLON | RCC_CR_CSSHSEON);

  // wait until PLL ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

  // enable flash pre-read data, prefetch instructions, one wait-state
  FLASH->ACR = (FLASH_ACR_PRE_READ | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY);

  // wait for wait-states to be applied
  while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY);

  // SYSCLK from PLL
  RCC->CFGR = (RCC_CFGR_PLLDIV2 | RCC_CFGR_PLLMUL4 | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_SW_PLL);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // peripheral clocks to default sources
  RCC->CCIPR = 0;

  // HSI48 off
  RCC->CRRCR = 0;

  // wait until HSI48 stopped
  while ((RCC->CRRCR & RCC_CRRCR_HSI48RDY) != 0);

  // MSI off
  RCC->CR = (RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_PLLON | RCC_CR_CSSHSEON);

  // wait until MSI stopped
  while ((RCC->CR & RCC_CR_MSIRDY) != 0);

  // SysTick on with no interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

  // set vector address
  SCB->VTOR = (uint32_t)&g_pfnVectors[0];
}
