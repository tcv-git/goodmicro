// system_stm32f7xx_disco_f746ng.c
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
/*

The STM32Cube template project startup does:

  Reset_Handler:
    fill bss
    copy data
    SystemInit:
      enable FPU
      system and bus clock sources to default
      configure external DRAM
      set vector address to constant
    main:
      setup MPU
      enable I cache
      enable D cache
      HAL_Init:
        flash accelerator enable
        flash prefetch enable
        set priority grouping
        init systick (inc set priority)
      setup oscilators and PLL
      enable regulator overdrive
      setup bus dividers, system clock source, flash wait states

This project uses this arrangement:

  Reset_Handler:
    configure external DRAM
    fill bss
    copy data
    SystemInit:
      system clock source to default
      set regulator scale
      setup oscilators and PLLs
      enable regulator overdrive
      flash accelerator enable
      flash prefetch enable
      flash wait states
      setup bus dividers and system clock source
      set dedicated clock sources
      enable systick counter without interrupt
      enable debug cycle counter
      set vector address using symbol
      enable fault interrupts
      enable FPU
      enable I cache
      enable D cache
      enable IO compensation cell
    main:
      set priority grouping
      enable systick interrupt if required
*/

#include <stdint.h>
#include "stm32f7xx.h"
#include "system_stm32f7xx.h"

// default value of register field:
#define RCC_CR_HSITRIM_Default      RCC_CR_HSITRIM_4

// location of field which is reserved but must still set:
#define RCC_PLLCFGR_PLLR_Pos        RCC_PLLI2SCFGR_PLLI2SR_Pos

// crystal/clock input frequency in Hz:
#define HSE_VALUE       (25u * 1000 * 1000)

// main PLL parameters:
#define PLL_M            25
#define PLL_N           432
#define PLL_P             2
#define PLL_Q             9
#define PLL_R             2 // reserved bits must be kept at this value

// flash wait states:
#define FLASH_ACR_LATENCY_Value     FLASH_ACR_LATENCY_7WS


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (216u * 1000 * 1000);

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

  // PLLs and CSS off
  RCC->CR &= ~(RCC_CR_PLLON | RCC_CR_PLLI2SON | RCC_CR_PLLSAION | RCC_CR_CSSON);

  // wait until PLLs stopped
  while ((RCC->CR & (RCC_CR_PLLRDY | RCC_CR_PLLI2SRDY | RCC_CR_PLLSAIRDY)) != 0);

  // HSE off, default HSI trim, keep HSI on
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSION);

  // wait until HSE stopped
  while ((RCC->CR & RCC_CR_HSERDY) != 0);

  // enable power management interface
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  (void)RCC->APB1ENR;

  // select regulator voltage output scale 1 (maximum power)
  PWR->CR1 |= PWR_CR1_VOS;

  // HSE on (without bypass)
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSION | RCC_CR_HSEON);

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

  // PLL and CSS on
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSION | RCC_CR_HSEON | RCC_CR_PLLON | RCC_CR_CSSON);

  // enable over-drive
  PWR->CR1 |= PWR_CR1_ODEN;

  // wait for over-drive enable
  while ((PWR->CSR1 & PWR_CSR1_ODRDY) != PWR_CSR1_ODRDY);

  // enable over-drive switching
  PWR->CR1 |= PWR_CR1_ODSWEN;

  // wait for over-drive switching
  while ((PWR->CSR1 & PWR_CSR1_ODSWRDY) != PWR_CSR1_ODSWRDY);

  // wait until PLL ready
  while ((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

  // configure flash prefetch, instruction cache, data cache and wait states
  FLASH->ACR = (FLASH_ACR_ARTEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_Value);

  // wait for wait-states to be applied
  while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_Value);

  // default clock outputs, set bus divisors, SYSCLK from PLL
  RCC->CFGR = ((RCC_CFGR_RTCPRE_0 * (HSE_VALUE / 1000000))
             |  RCC_CFGR_PPRE2_DIV2
             |  RCC_CFGR_PPRE1_DIV4
             |  RCC_CFGR_HPRE_DIV1
             |  RCC_CFGR_SW_PLL);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // set dedicated clock sources and dividers
  RCC->DCKCFGR1 = RCC_DCKCFGR1_TIMPRE;
  RCC->DCKCFGR2 = 0;

  // HSI off
  RCC->CR = (RCC_CR_HSITRIM_Default | RCC_CR_HSEON | RCC_CR_PLLON | RCC_CR_CSSON);

  // wait until HSI stopped
  while ((RCC->CR & RCC_CR_HSIRDY) != 0);

  // SysTick on with no interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

  // debug cycle counter on
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->LAR          = 0xC5ACCE55u;
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

  // enable instruction and data cache
  SCB_EnableICache();
  SCB_EnableDCache();

  // enable system configuration interface
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  (void)RCC->APB2ENR;

  // enable IO compensation cell
  SYSCFG->CMPCR = SYSCFG_CMPCR_CMP_PD;

  // wait until IO compensation cell is ready
  while ((SYSCFG->CMPCR & SYSCFG_CMPCR_READY) != SYSCFG_CMPCR_READY);
}
