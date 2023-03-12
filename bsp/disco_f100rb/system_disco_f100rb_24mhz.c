/* system_stm32f1xx.c */

#include "stm32f1xx.h"

uint32_t SystemCoreClock = (24u * 1000 * 1000);

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
  RCC->CR = (0x00000080u | RCC_CR_HSION);

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
  SysTick->LOAD = -1;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
}
