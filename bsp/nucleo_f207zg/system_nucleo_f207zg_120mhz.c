// system_nucleo_f207zg_120mhz.c
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

#include "stm32f2xx.h"
#include "system_stm32f2xx.h"

#define RCC_PLLCFGR_PLLR_Pos  28


#define PLL_M              4
#define PLL_N            120
#define PLL_P              2
#define PLL_Q              5
#define PLL_R              2 // reserved bits must be kept at this value

#define FLASH_WAIT_STATES  FLASH_ACR_LATENCY_3WS


uint32_t SystemCoreClock = (120u * 1000 * 1000);


void SystemInit(void)
{
  // disable clock interrupts
  RCC->CIR = 0;

  // HSI on, CSS off
  RCC->CR = ((RCC->CR & ~RCC_CR_CSSON) | RCC_CR_HSION);

  // wait until HSI ready
  while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

  // SYSCLK from HSI
  RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_HSI);

  // wait until SYSCLK from HSI
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

  // PLLs off
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_PLLI2SON);

  // wait until PLLs stopped
  while ((RCC->CR & (RCC_CR_PLLRDY | RCC_CR_PLLI2SRDY)) != 0);

  // HSE off
  RCC->CR &= ~RCC_CR_HSEON;

  // wait until HSE stopped
  while ((RCC->CR & RCC_CR_HSERDY) != 0);

  // HSE on with bypass
  RCC->CR |= (RCC_CR_HSEON | RCC_CR_HSEBYP);

  // wait until HSE ready
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

  // configure PLL
  RCC->PLLCFGR = (RCC_PLLCFGR_PLLSRC_HSE
    |   (PLL_M           << RCC_PLLCFGR_PLLM_Pos)
    |   (PLL_N           << RCC_PLLCFGR_PLLN_Pos)
    | (((PLL_P / 2) - 1) << RCC_PLLCFGR_PLLP_Pos)
    |   (PLL_Q           << RCC_PLLCFGR_PLLQ_Pos)
    |   (PLL_R           << RCC_PLLCFGR_PLLR_Pos));

  // disable spread-spectrum
  RCC->SSCGR = 0;

  // PLL and CSS on, keep HSI and HSE on, default HSITRIM
  RCC->CR = (RCC_CR_PLLON
           | RCC_CR_CSSON
           | RCC_CR_HSEON
           | RCC_CR_HSITRIM_4
           | RCC_CR_HSION);

  // wait until PLL ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

  // configure flash prefetch, instruction cache, data cache and wait state
  FLASH->ACR = (FLASH_ACR_PRFTEN
              | FLASH_ACR_ICEN
              | FLASH_ACR_DCEN
              | FLASH_WAIT_STATES);

  // default clock outputs, set bus divisors, SYSCLK from PLL
  RCC->CFGR = ((RCC_CFGR_RTCPRE_0 * 8)
             |  RCC_CFGR_PPRE2_DIV2
             |  RCC_CFGR_PPRE1_DIV4
             |  RCC_CFGR_HPRE_DIV1
             |  RCC_CFGR_SW_PLL);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // enable system configuration interface
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  (void)RCC->APB2ENR;

  // enable IO compensation cell
  SYSCFG->CMPCR = SYSCFG_CMPCR_CMP_PD;

  // wait until IO compensation cell is ready
  while ((SYSCFG->CMPCR & SYSCFG_CMPCR_READY) != SYSCFG_CMPCR_READY);

  // enable faults
  SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk);

  // trap divide by zero
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;

  // SysTick on with no interrupt
  SysTick->LOAD = -1;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

  // cycle counter on
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT       = 0;
}
