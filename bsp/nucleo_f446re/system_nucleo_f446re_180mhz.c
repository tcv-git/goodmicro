// system_nucleo_f446re_180mhz.c
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
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "system_nucleo_f446re_180mhz.h"

// default value of register field:
#define RCC_CR_HSITRIM_Default      RCC_CR_HSITRIM_4

// location of field which is reserved but must still set:
#define RCC_PLLSAICFGR_PLLSAIR_Pos  RCC_PLLI2SCFGR_PLLI2SR_Pos

// main PLL parameters:
#define PLL_M             4
#define PLL_N           180
#define PLL_P             2
#define PLL_Q             8
#define PLL_R             3

// I2S PLL parameters (NB: PLLI2S is not started below)
#define PLLI2S_M          4
#define PLLI2S_N        120
#define PLLI2S_P          2
#define PLLI2S_Q          2
#define PLLI2S_R          2
#define PLLI2SDIVQ        1

// SAI PLL parameters (NB: PLLSAI is not started below)
#define PLLSAI_M          4
#define PLLSAI_N         96
#define PLLSAI_P          4
#define PLLSAI_Q          4
#define PLLSAI_R          4 // reserved bits must be kept at this value
#define PLLSAIDIVQ        1

#define FLASH_WAIT_STATES  FLASH_ACR_LATENCY_5WS


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = HCLK;

/* System interrupt vector
 */
extern uint32_t g_pfnVectors[];


/* System initialization
 */
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
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_PLLI2SON | RCC_CR_PLLSAION);

  // wait until PLLs stopped
  while ((RCC->CR & (RCC_CR_PLLRDY | RCC_CR_PLLI2SRDY | RCC_CR_PLLSAIRDY)) != 0);

  // HSE off
  RCC->CR &= ~RCC_CR_HSEON;

  // wait until HSE stopped
  while ((RCC->CR & RCC_CR_HSERDY) != 0);

  // enable power management interface
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  (void)RCC->APB1ENR;

  // select regulator voltage output scale 1 (maximum power)
  PWR->CR |= PWR_CR_VOS;

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

  // configure I2S PLL
  RCC->PLLI2SCFGR = (
        (PLLI2S_M           << RCC_PLLI2SCFGR_PLLI2SM_Pos)
    |   (PLLI2S_N           << RCC_PLLI2SCFGR_PLLI2SN_Pos)
    | (((PLLI2S_P / 2) - 1) << RCC_PLLI2SCFGR_PLLI2SP_Pos)
    |   (PLLI2S_Q           << RCC_PLLI2SCFGR_PLLI2SQ_Pos)
    |   (PLLI2S_R           << RCC_PLLI2SCFGR_PLLI2SR_Pos));

  // configure SAI PLL
  RCC->PLLSAICFGR = (
        (PLLSAI_M           << RCC_PLLSAICFGR_PLLSAIM_Pos)
    |   (PLLSAI_N           << RCC_PLLSAICFGR_PLLSAIN_Pos)
    | (((PLLSAI_P / 2) - 1) << RCC_PLLSAICFGR_PLLSAIP_Pos)
    |   (PLLSAI_Q           << RCC_PLLSAICFGR_PLLSAIQ_Pos)
    |   (PLLSAI_R           << RCC_PLLSAICFGR_PLLSAIR_Pos));

  // set dedicated clock sources and dividers
  RCC->DCKCFGR = (RCC_DCKCFGR_TIMPRE
                | ((PLLSAIDIVQ - 1) << RCC_DCKCFGR_PLLSAIDIVQ_Pos)
                | ((PLLI2SDIVQ - 1) << RCC_DCKCFGR_PLLI2SDIVQ_Pos));

  // main PLL (only) on, CSS on, keep HSI and HSE on, default HSITRIM
  RCC->CR = (RCC_CR_PLLON
           | RCC_CR_CSSON
           | RCC_CR_HSEON
           | RCC_CR_HSITRIM_Default
           | RCC_CR_HSION);

  // enable over-drive
  PWR->CR |= PWR_CR_ODEN;

  // wait for over-drive enable
  while ((PWR->CSR & PWR_CSR_ODRDY) != PWR_CSR_ODRDY);

  // enable over-drive switching
  PWR->CR |= PWR_CR_ODSWEN;

  // wait for over-drive switching
  while ((PWR->CSR & PWR_CSR_ODSWRDY) != PWR_CSR_ODSWRDY);

  // wait until PLL ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

  // configure flash prefetch, instruction cache, data cache and wait states
  FLASH->ACR = (FLASH_ACR_PRFTEN
              | FLASH_ACR_ICEN
              | FLASH_ACR_DCEN
              | FLASH_WAIT_STATES);

  // wait for wait-states to be applied
  while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_WAIT_STATES);

  // default clock outputs, set bus divisors, SYSCLK from PLL
  RCC->CFGR = ((RCC_CFGR_RTCPRE_0 * (HSE_VALUE / 1000000))
             |  RCC_CFGR_PPRE2_DIV2
             |  RCC_CFGR_PPRE1_DIV4
             |  RCC_CFGR_HPRE_DIV1
             |  RCC_CFGR_SW_PLL);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // HSI off
  RCC->CR = (RCC_CR_PLLON
           | RCC_CR_CSSON
           | RCC_CR_HSEON
           | RCC_CR_HSITRIM_Default);

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

  // enable IO compensation cell
  SYSCFG->CMPCR = SYSCFG_CMPCR_CMP_PD;

  // wait until IO compensation cell is ready
  while ((SYSCFG->CMPCR & SYSCFG_CMPCR_READY) != SYSCFG_CMPCR_READY);
}
