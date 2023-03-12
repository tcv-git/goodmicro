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

#include "stm32l0xx.h"
#include "system_stm32l0xx.h"

/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (2u * 1024 * 1024);


/* System initialization
 */
void SystemInit(void)
{
  // set VTOR
  SCB->VTOR = FLASH_BASE;

  // disable clock interrupts
  RCC->CIER = 0;

  // disable MCO
  RCC->CFGR &= ~RCC_CFGR_MCOSEL;

  // set MSI range and MSI/HSI16 trim to zero
  RCC->ICSCR = RCC_ICSCR_MSIRANGE_5;

  // enable MSI
  RCC->CR |= RCC_CR_MSION;

  // wait until MSI ready
  while ((RCC->CR & RCC_CR_MSIRDY) != RCC_CR_MSIRDY);

  // sysclk from MSI
  RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_MSI);

  // wait until sysclk from MSI
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_MSI);

  // AHB and APB dividers to one
  RCC->CFGR = RCC_CFGR_SW_MSI;

  // peripheral clocks to default sources
  RCC->CCIPR = 0;

  // disable flash pre-read/prefetch/cache, zero-wait states
  FLASH->ACR = FLASH_ACR_DISAB_BUF;

  // PLL and CSS off
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_CSSHSEON);

  // wait until PLL stopped
  while ((RCC->CR & RCC_CR_PLLRDY) != 0);

  // HSE, HSI16, HSI16OUT off
  RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_HSIOUTEN | RCC_CR_HSIKERON | RCC_CR_HSION);

  // wait until HSE, HSI16 off
  while ((RCC->CR & (RCC_CR_HSIRDY | RCC_CR_HSERDY)) != 0);

  // HSI48 off
  RCC->CRRCR = 0;

  // wait until HSI48 off
  while ((RCC->CRRCR & RCC_CRRCR_HSI48RDY) != 0);

  // enable power interface
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;

  // disable programmable voltage detector, regulator range 3 (lowest power)
  PWR->CR = ((PWR->CR & ~PWR_CR_PVDE) | PWR_CR_VOS);

  // enable systick without interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
}
