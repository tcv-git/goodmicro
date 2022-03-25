// system_stm32f405-439.c
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
#include "stm32f4xx_missing.h"
#include "system_stm32f4xx.h"
#include "system_stm32f405-439.h"


// #############################################################################
//
//      System clock source set/ready register values
//
// #############################################################################

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSE) || ((RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL) && (RCC_PLLCFGR_PLLSRC_Value == RCC_PLLCFGR_PLLSRC_HSE))

#define RCC_CR_CSSON_Value  RCC_CR_CSSON
#else
#define RCC_CR_CSSON_Value  0
#endif

#define RCC_CFGR_SWS_Value  ((RCC_CFGR_SW_Value >> RCC_CFGR_SW_Pos) << RCC_CFGR_SWS_Pos)


// #############################################################################
//
//      Oscilator enable register values
//
// #############################################################################

#define RCC_CR_HSION_Value  (HSION << RCC_CR_HSION_Pos)
#define RCC_CR_HSEON_Value  (HSEON << RCC_CR_HSEON_Pos)


// #############################################################################
//
//      PLL enable/ready register values
//
// #############################################################################

#ifdef RCC_CR_PLLSAION_Pos

#define RCC_CR_ALL_PLLs_ON    (RCC_CR_PLLON  | RCC_CR_PLLI2SON  | RCC_CR_PLLSAION )
#define RCC_CR_ALL_PLLs_RDY   (RCC_CR_PLLRDY | RCC_CR_PLLI2SRDY | RCC_CR_PLLSAIRDY)
#define RCC_CR_PLLs_ON        ((PLLON << RCC_CR_PLLON_Pos ) | (PLLI2SON << RCC_CR_PLLI2SON_Pos ) | (PLLSAION << RCC_CR_PLLSAION_Pos ))
#define RCC_CR_PLLs_RDY       ((PLLON << RCC_CR_PLLRDY_Pos) | (PLLI2SON << RCC_CR_PLLI2SRDY_Pos) | (PLLSAION << RCC_CR_PLLSAIRDY_Pos))

#else // RCC_CR_PLLSAION

#define RCC_CR_ALL_PLLs_ON    (RCC_CR_PLLON  | RCC_CR_PLLI2SON )
#define RCC_CR_ALL_PLLs_RDY   (RCC_CR_PLLRDY | RCC_CR_PLLI2SRDY)
#define RCC_CR_PLLs_ON        ((PLLON << RCC_CR_PLLON_Pos ) | (PLLI2SON << RCC_CR_PLLI2SON_Pos ))
#define RCC_CR_PLLs_RDY       ((PLLON << RCC_CR_PLLRDY_Pos) | (PLLI2SON << RCC_CR_PLLI2SRDY_Pos))

#endif // RCC_CR_PLLSAION


// #############################################################################
//
//      main PLL configuration register values
//
// #############################################################################

// because main PLL doesn't have an R output, keep the PLLCFGR reset value where the PLLI2SCFGR has PLLI2SR
#define RCC_PLLCFGR_Reserved_Value   (RCC_PLLCFGR_RST_VALUE & RCC_PLLI2SCFGR_PLLI2SR_Msk)

#define RCC_PLLCFGR_PLLM_Value       (PLL_M           << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLN_Value       (PLL_N           << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLP_Value     (((PLL_P / 2) - 1) << RCC_PLLCFGR_PLLP_Pos)
#define RCC_PLLCFGR_PLLQ_Value       (PLL_Q           << RCC_PLLCFGR_PLLQ_Pos)

#define RCC_SSCGR_SSCGEN_Value       (SSCGEN    << RCC_SSCGR_SSCGEN_Pos    )
#define RCC_SSCGR_SPREADSEL_Value    (SPREADSEL << RCC_SSCGR_SPREADSEL_Pos )
#define RCC_SSCGR_INCSTEP_Value      (INCSTEP   << RCC_SSCGR_INCSTEP_Pos   )
#define RCC_SSCGR_MODPER_Value       (MODPER    << RCC_SSCGR_MODPER_Pos    )


// #############################################################################
//
//      I2S PLL configuration register values
//
// #############################################################################

#define RCC_PLLI2SCFGR_PLLI2SN_Value  (PLLI2S_N << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SR_Value  (PLLI2S_R << RCC_PLLI2SCFGR_PLLI2SR_Pos)

#ifdef  RCC_PLLI2SCFGR_PLLI2SQ_Pos
#define RCC_PLLI2SCFGR_PLLI2SQ_Value  (PLLI2S_Q << RCC_PLLI2SCFGR_PLLI2SQ_Pos)

// if PLLI2S doesn't have a Q output, keep the PLLI2SCFGR reset value where the main PLLCFGR has PLLQ
#else
#define RCC_PLLI2SCFGR_PLLI2SQ_Value  (RCC_PLLI2SCFGR_RST_VALUE & RCC_PLLCFGR_PLLQ_Msk)
#endif

#ifdef  RCC_DCKCFGR_PLLI2SDIVQ_Pos
#define RCC_DCKCFGR_PLLI2SDIVQ_Value  ((PLLI2SDIVQ - 1) << RCC_DCKCFGR_PLLI2SDIVQ_Pos)
#endif


// #############################################################################
//
//      SAI PLL configuration register values
//
// #############################################################################

#ifdef  RCC_PLLSAICFGR_PLLSAIN_Pos
#define RCC_PLLSAICFGR_PLLSAIN_Value  (PLLSAI_N << RCC_PLLSAICFGR_PLLSAIN_Pos)
#define RCC_PLLSAICFGR_PLLSAIR_Value  (PLLSAI_R << RCC_PLLSAICFGR_PLLSAIR_Pos)
#define RCC_PLLSAICFGR_PLLSAIQ_Value  (PLLSAI_Q << RCC_PLLSAICFGR_PLLSAIQ_Pos)

#if   (PLLSAIDIVR ==  2)
#define                  RCC_DCKCFGR_PLLSAIDIVR_Value  RCC_DCKCFGR_PLLSAIDIVR_DIV2
#elif (PLLSAIDIVR ==  4)
#define                  RCC_DCKCFGR_PLLSAIDIVR_Value  RCC_DCKCFGR_PLLSAIDIVR_DIV4
#elif (PLLSAIDIVR ==  8)
#define                  RCC_DCKCFGR_PLLSAIDIVR_Value  RCC_DCKCFGR_PLLSAIDIVR_DIV8
#elif (PLLSAIDIVR == 16)
#define                  RCC_DCKCFGR_PLLSAIDIVR_Value  RCC_DCKCFGR_PLLSAIDIVR_DIV16
#endif

#define RCC_DCKCFGR_PLLSAIDIVQ_Value  ((PLLSAIDIVQ - 1) << RCC_DCKCFGR_PLLSAIDIVQ_Pos)
#endif // RCC_PLLSAICFGR_PLLSAIN_Pos


// #############################################################################
//
//      clock divider register values
//
// #############################################################################

#if   (HPRE ==   1)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV1
#elif (HPRE ==   2)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV2
#elif (HPRE ==   4)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV4
#elif (HPRE ==   8)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV8
#elif (HPRE ==  16)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV16
#elif (HPRE ==  64)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV64
#elif (HPRE == 128)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV128
#elif (HPRE == 256)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV256
#elif (HPRE == 512)
#define                  RCC_CFGR_HPRE_Value     RCC_CFGR_HPRE_DIV512
#endif

#if   (PPRE1 ==   1)
#define                  RCC_CFGR_PPRE1_Value    RCC_CFGR_PPRE1_DIV1
#elif (PPRE1 ==   2)
#define                  RCC_CFGR_PPRE1_Value    RCC_CFGR_PPRE1_DIV2
#elif (PPRE1 ==   4)
#define                  RCC_CFGR_PPRE1_Value    RCC_CFGR_PPRE1_DIV4
#elif (PPRE1 ==   8)
#define                  RCC_CFGR_PPRE1_Value    RCC_CFGR_PPRE1_DIV8
#elif (PPRE1 ==  16)
#define                  RCC_CFGR_PPRE1_Value    RCC_CFGR_PPRE1_DIV16
#endif

#if   (PPRE2 ==   1)
#define                  RCC_CFGR_PPRE2_Value    RCC_CFGR_PPRE2_DIV1
#elif (PPRE2 ==   2)
#define                  RCC_CFGR_PPRE2_Value    RCC_CFGR_PPRE2_DIV2
#elif (PPRE2 ==   4)
#define                  RCC_CFGR_PPRE2_Value    RCC_CFGR_PPRE2_DIV4
#elif (PPRE2 ==   8)
#define                  RCC_CFGR_PPRE2_Value    RCC_CFGR_PPRE2_DIV8
#elif (PPRE2 ==  16)
#define                  RCC_CFGR_PPRE2_Value    RCC_CFGR_PPRE2_DIV16
#endif

#if   (MCO1PRE == 1)
#define                  RCC_CFGR_MCO1PRE_Value  RCC_CFGR_MCO1PRE_DIV1
#elif (MCO1PRE == 2)
#define                  RCC_CFGR_MCO1PRE_Value  RCC_CFGR_MCO1PRE_DIV2
#elif (MCO1PRE == 3)
#define                  RCC_CFGR_MCO1PRE_Value  RCC_CFGR_MCO1PRE_DIV3
#elif (MCO1PRE == 4)
#define                  RCC_CFGR_MCO1PRE_Value  RCC_CFGR_MCO1PRE_DIV4
#elif (MCO1PRE == 5)
#define                  RCC_CFGR_MCO1PRE_Value  RCC_CFGR_MCO1PRE_DIV5
#endif

#if   (MCO2PRE == 1)
#define                  RCC_CFGR_MCO2PRE_Value  RCC_CFGR_MCO2PRE_DIV1
#elif (MCO2PRE == 2)
#define                  RCC_CFGR_MCO2PRE_Value  RCC_CFGR_MCO2PRE_DIV2
#elif (MCO2PRE == 3)
#define                  RCC_CFGR_MCO2PRE_Value  RCC_CFGR_MCO2PRE_DIV3
#elif (MCO2PRE == 4)
#define                  RCC_CFGR_MCO2PRE_Value  RCC_CFGR_MCO2PRE_DIV4
#elif (MCO2PRE == 5)
#define                  RCC_CFGR_MCO2PRE_Value  RCC_CFGR_MCO2PRE_DIV5
#endif

#define RCC_CFGR_RTCPRE_Value     (RTCPRE << RCC_CFGR_RTCPRE_Pos)

#ifdef  RCC_DCKCFGR_TIMPRE_Pos
#define RCC_DCKCFGR_TIMPRE_Value  (TIMPRE << RCC_DCKCFGR_TIMPRE_Pos)
#endif


// #############################################################################
//
//      flash register values
//
// #############################################################################

#define FLASH_ACR_LATENCY_Value   (FLASH_LATENCY << FLASH_ACR_LATENCY_Pos)

#if (defined(VDD_mV) && (VDD_mV < 2100)) || (FLASH_LATENCY == 0)

#define FLASH_ACR_PRFTEN_Value  0
#else
#define FLASH_ACR_PRFTEN_Value  FLASH_ACR_PRFTEN
#endif

#if (FLASH_LATENCY == 0)
#define FLASH_ACR_ICEN_Value  0
#define FLASH_ACR_DCEN_Value  0
#else
#define FLASH_ACR_ICEN_Value  FLASH_ACR_ICEN
#define FLASH_ACR_DCEN_Value  FLASH_ACR_DCEN
#endif


// #############################################################################
//
//      SystemCoreClock variable, SystemInit and SystemCoreClockUpdate
//
// #############################################################################

uint32_t SystemCoreClock = SYSTEM_CORE_CLOCK;


// #############################################################################
//
//      SystemInit function
//
// #############################################################################

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
  RCC->CR &= ~RCC_CR_ALL_PLLs_ON;

  // wait until PLLs stopped
  while ((RCC->CR & RCC_CR_ALL_PLLs_RDY) != 0);

  // HSE off
  RCC->CR &= ~RCC_CR_HSEON;

  // wait until HSE stopped
  while ((RCC->CR & RCC_CR_HSERDY) != 0);

  // HSE on with HSE bypass if required
  RCC->CR = ((RCC->CR & ~RCC_CR_HSEBYP) | RCC_CR_HSEON_Value | RCC_CR_HSEBYP_Value);

  // wait until HSE ready if required
#if HSEON
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);
#endif

  // enable power management interface
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
  (void)RCC->APB1ENR;

  // select regulator voltage output scale
  PWR->CR = ((PWR->CR & ~PWR_CR_VOS) | PWR_CR_VOS_Value);

  // configure PLL
  RCC->PLLCFGR = (RCC_PLLCFGR_Reserved_Value
                | RCC_PLLCFGR_PLLSRC_Value
                | RCC_PLLCFGR_PLLM_Value
                | RCC_PLLCFGR_PLLN_Value
                | RCC_PLLCFGR_PLLP_Value
                | RCC_PLLCFGR_PLLQ_Value);

  // configure spread-spectrum
  RCC->SSCGR = (RCC_SSCGR_SSCGEN_Value
              | RCC_SSCGR_SPREADSEL_Value
              | RCC_SSCGR_INCSTEP_Value
              | RCC_SSCGR_MODPER_Value);

  // configure I2S PLL
  RCC->PLLI2SCFGR = (RCC_PLLI2SCFGR_PLLI2SN_Value
                   | RCC_PLLI2SCFGR_PLLI2SQ_Value
                   | RCC_PLLI2SCFGR_PLLI2SR_Value);

  // configure SAI PLL if present
#ifdef RCC_PLLSAICFGR_PLLSAIN_Pos
  RCC->PLLSAICFGR = ((RCC_PLLSAICFGR_PLLSAIR_Value)
                  |  (RCC_PLLSAICFGR_PLLSAIQ_Value)
                  |  (RCC_PLLSAICFGR_PLLSAIN_Value));
#endif

  // set dedicated clock dividers
#ifdef RCC_DCKCFGR_TIMPRE_Pos
  RCC->DCKCFGR = (RCC_DCKCFGR_TIMPRE_Value
                | RCC_DCKCFGR_PLLSAIDIVR_Value
                | RCC_DCKCFGR_PLLSAIDIVQ_Value
                | RCC_DCKCFGR_PLLI2SDIVQ_Value);
#endif

  // PLLs and CSS on, keep HSI and HSE on, default HSITRIM
  RCC->CR = (RCC_CR_PLLs_ON
           | RCC_CR_CSSON_Value
           | RCC_CR_HSEON_Value
           | RCC_CR_HSITRIM_4
           | RCC_CR_HSION);

#if defined(PWR_CR_ODEN_Pos) && (PWR_CR_ODEN_Value == PWR_CR_ODEN_ENABLE)
  // enable over-drive
  PWR->CR |= PWR_CR_ODEN;

  // wait for over-drive enable
  while ((PWR->CSR & PWR_CSR_ODRDY) != PWR_CSR_ODRDY);

  // enable over-drive switching
  PWR->CR |= PWR_CR_ODSWEN;

  // wait for over-drive switching
  while ((PWR->CSR & PWR_CSR_ODSWRDY) != PWR_CSR_ODSWRDY);

#endif // PWR_CR_ODEN_Pos

  // wait until PLLs ready
  while ((RCC->CR & RCC_CR_PLLs_RDY) != RCC_CR_PLLs_RDY);

  // configure flash prefetch, instruction cache, data cache and wait state
  FLASH->ACR = (FLASH_ACR_PRFTEN_Value
              | FLASH_ACR_ICEN_Value
              | FLASH_ACR_DCEN_Value
              | FLASH_ACR_LATENCY_Value);

  // set clock outputs, clock divisors and SYSCLK source
  RCC->CFGR = (RCC_CFGR_MCO2_Value
             | RCC_CFGR_MCO2PRE_Value
             | RCC_CFGR_MCO1PRE_Value
             | RCC_CFGR_MCO1_Value
             | RCC_CFGR_RTCPRE_Value
             | RCC_CFGR_PPRE2_Value
             | RCC_CFGR_PPRE1_Value
             | RCC_CFGR_HPRE_Value
             | RCC_CFGR_SW_Value);

  // wait until SYSCLK from selected source
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_Value);

  // HSI off if no longer required
#if !HSION
  RCC->CR = (RCC_CR_PLLs_ON
           | RCC_CR_CSSON_Value
           | RCC_CR_HSEON_Value
           | RCC_CR_HSITRIM_4
           | RCC_CR_HSION_Value);
#endif

  // enable system configuration interface
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  (void)RCC->APB2ENR;

  // enable IO compensation cell
  SYSCFG->CMPCR = SYSCFG_CMPCR_CMP_PD_Value;

#if (SYSCFG_CMPCR_CMP_PD_Value == SYSCFG_CMPCR_CMP_PD_ENABLE)
  // wait until IO compensation cell is ready
  while ((SYSCFG->CMPCR & SYSCFG_CMPCR_READY) != SYSCFG_CMPCR_READY);
#endif

  // enable faults
  SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk);

  // trap divide by zero
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;

  // enable FPU (set CP10 and CP11 full access)
  SCB->CPACR |= ((3u << (10 * 2)) | (3u << (11 * 2)));

  // SysTick on with no interrupt
  SysTick->LOAD = -1;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

  // debug cycle counter on
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT       = 0;
}


// #############################################################################
//
//      SystemCoreClockUpdate function
//
// #############################################################################

void SystemCoreClockUpdate(void)
{
  SystemCoreClock = SYSTEM_CORE_CLOCK;
}
