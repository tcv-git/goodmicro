// system_stm32l0xx_msi_2mhz.c
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
uint32_t SystemCoreClock = (2u * 1024 * 1024);

/* System interrupt vector
 */
extern uint32_t g_pfnVectors[];


/* System initialization
 */
void SystemInit(void)
{
  // disable clock interrupts
  RCC->CIER = 0;

  // MCO off
  RCC->CFGR &= ~(RCC_CFGR_MCOPRE | RCC_CFGR_MCOSEL);

  // set MSI range and MSI/HSI16 trim to zero
  RCC->ICSCR = RCC_ICSCR_MSIRANGE_5;

  // MSI on
  RCC->CR |= RCC_CR_MSION;

  // wait until MSI ready
  while ((RCC->CR & RCC_CR_MSIRDY) != RCC_CR_MSIRDY);

  // MCO off, STOPWUCK=MSI, HPRE=1, PPRE2=1, PPRE1=1, SYSCLK from MSI
  RCC->CFGR = ((RCC->CFGR & ~(RCC_CFGR_MCOPRE | RCC_CFGR_MCOSEL | RCC_CFGR_STOPWUCK | RCC_CFGR_HPRE | RCC_CFGR_PPRE2 | RCC_CFGR_PPRE1 | RCC_CFGR_SW)) | RCC_CFGR_SW_MSI);

  // wait until SYSCLK from MSI
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_MSI);

  // peripheral clocks to default sources
  RCC->CCIPR = 0;

  // PLL and CSS off
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_CSSHSEON);

  // wait until PLL stopped
  while ((RCC->CR & RCC_CR_PLLRDY) != 0);

  // HSE and HSI off, RTCPRE=2, keep MSI on
  RCC->CR = RCC_CR_MSION;

  // wait until HSE and HSI stopped
  while ((RCC->CR & (RCC_CR_HSIRDY | RCC_CR_HSERDY)) != 0);

  // HSI48 off
  RCC->CRRCR = 0;

  // wait until HSI48 stopped
  while ((RCC->CRRCR & RCC_CRRCR_HSI48RDY) != 0);

  // disable flash pre-read/prefetch/cache, zero-wait states
  FLASH->ACR = FLASH_ACR_DISAB_BUF;

  // enable power interface
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  (void)RCC->APB1ENR;

  // wait until ready to change VOS
  while ((PWR->CSR & PWR_CSR_VOSF) != 0);

  // disable programmable voltage detector, regulator range 3 (lowest power)
  PWR->CR = ((PWR->CR & ~PWR_CR_PVDE) | PWR_CR_VOS);

  // wait until VOS changed
  while ((PWR->CSR & PWR_CSR_VOSF) != 0);

  // SysTick on with no interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

  // set vector address
  SCB->VTOR = (uint32_t)&g_pfnVectors[0];
}
