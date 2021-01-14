// system_stm32f405-439.h
// PUBLIC DOMAIN
// http:///www.purposeful.co.uk/software/goodmicro

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

#ifndef SYSTEM_STM32F405_439_H_INCLUDED
#define SYSTEM_STM32F405_439_H_INCLUDED

#include "stm32f4xx.h"
#include "stm32f4xx_missing.h"
#include "system_config.h"


// #############################################################################
//
//      check part number
//
// #############################################################################

#if !(defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) \
   || defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx))

#error No compatible stm32f4xx part number macro defined
#endif


// #############################################################################
//
//      power settings
//
// #############################################################################

// -----------------------------------------------------------------------------
//  PWR_CR_VOS_Value
// -----------------------------------------------------------------------------

#ifndef PWR_CR_VOS_Value
#define PWR_CR_VOS_Value  PWR_CR_VOS_SCALE1
#endif

#ifdef PWR_CR_VOS_SCALE3

#if (PWR_CR_VOS_Value != PWR_CR_VOS_SCALE1) && (PWR_CR_VOS_Value != PWR_CR_VOS_SCALE2) && (PWR_CR_VOS_Value != PWR_CR_VOS_SCALE3)
#error Invalid definition of PWR_CR_VOS_Value (must be PWR_CR_VOS_SCALE1, PWR_CR_VOS_SCALE2 or PWR_CR_VOS_SCALE3 on this part)
#endif

#else  // PWR_CR_VOS_SCALE3

#if (PWR_CR_VOS_Value != PWR_CR_VOS_SCALE1) && (PWR_CR_VOS_Value != PWR_CR_VOS_SCALE2)
#error Invalid definition of PWR_CR_VOS_Value (must be PWR_CR_VOS_SCALE1 or PWR_CR_VOS_SCALE2 on this part)
#endif

#endif // PWR_CR_VOS_SCALE3

// -----------------------------------------------------------------------------
//  PWR_CR_ODEN_Value
// -----------------------------------------------------------------------------

#ifdef PWR_CR_ODEN_Pos

#ifndef PWR_CR_ODEN_Value

#if (PWR_CR_VOS_Value == PWR_CR_VOS_SCALE3) || (defined(VDD_mV) && (VDD_mV < 2100))

#define PWR_CR_ODEN_Value  PWR_CR_ODEN_DISABLE
#else
#define PWR_CR_ODEN_Value  PWR_CR_ODEN_ENABLE
#endif

#endif // PWR_CR_ODEN_Value

#if (PWR_CR_ODEN_Value != PWR_CR_ODEN_DISABLE) && (PWR_CR_ODEN_Value != PWR_CR_ODEN_ENABLE)
#error Invalid definition of PWR_CR_ODEN_Value (must be PWR_CR_ODEN_DISABLE or PWR_CR_ODEN_ENABLE)
#endif

#if (PWR_CR_VOS_Value == PWR_CR_VOS_SCALE3) && (PWR_CR_ODEN_Value != PWR_CR_ODEN_DISABLE)
#error PWR_CR_VOS_Value is PWR_CR_VOS_SCALE3 but PWR_CR_ODEN_Value is not PWR_CR_ODEN_DISABLE
#endif

#if defined(VDD_mV) && (VDD_mV < 2100) && (PWR_CR_ODEN_Value != PWR_CR_ODEN_DISABLE)
#error VDD_mV is less than 2100 but PWR_CR_ODEN_Value is not PWR_CR_ODEN_DISABLE
#endif

#else  // PWR_CR_ODEN_Pos

#ifdef PWR_CR_ODEN_Value
#error PWR_CR_ODEN_Value is defined but is not available on selected part
#endif

#endif // PWR_CR_ODEN_Pos

// -----------------------------------------------------------------------------
//  SYSCFG_CMPCR_CMP_PD_Value
// -----------------------------------------------------------------------------

#ifndef SYSCFG_CMPCR_CMP_PD_Value

#if defined(VDD_mV) && (VDD_mV < 2400)
#define SYSCFG_CMPCR_CMP_PD_Value  SYSCFG_CMPCR_CMP_PD_DISABLE
#else
#define SYSCFG_CMPCR_CMP_PD_Value  SYSCFG_CMPCR_CMP_PD_ENABLE
#endif

#endif // SYSCFG_CMPCR_CMP_PD_Value

#if (SYSCFG_CMPCR_CMP_PD_Value != SYSCFG_CMPCR_CMP_PD_DISABLE) && (SYSCFG_CMPCR_CMP_PD_Value != SYSCFG_CMPCR_CMP_PD_ENABLE)
#error Invalid definition of SYSCFG_CMPCR_CMP_PD_Value (must be SYSCFG_CMPCR_CMP_PD_DISABLE or SYSCFG_CMPCR_CMP_PD_ENABLE)
#endif

#if defined(VDD_mV) && (VDD_mV < 2400) && (SYSCFG_CMPCR_CMP_PD_Value != SYSCFG_CMPCR_CMP_PD_DISABLE)
#error VDD_mV is less than 2400 but SYSCFG_CMPCR_CMP_PD_Value is not SYSCFG_CMPCR_CMP_PD_DISABLE
#endif


// #############################################################################
//
//      check host bus divider (required to calculate maximum clocks)
//
// #############################################################################

#ifndef HPRE
#define HPRE  1
#endif

#if (HPRE != 1) && (HPRE != 2) && (HPRE != 4) && (HPRE != 8) && (HPRE != 16) && (HPRE != 64) && (HPRE != 128) && (HPRE != 256) && (HPRE != 512)
#error Invalid definition of HPRE (must be one of 1,2,4,8,16,64,128,256,512)
#endif


// #############################################################################
//
//      maximum clocks (depending on power settings)
//
// #############################################################################

// -----------------------------------------------------------------------------
//  SYSCLK_MAX depending on regulator settings
// -----------------------------------------------------------------------------

#if (PWR_CR_VOS_Value == PWR_CR_VOS_SCALE1)

#if defined(PWR_CR_ODEN_Pos) && (PWR_CR_ODEN_Value == PWR_CR_ODEN_ENABLE)
#define SYSCLK_MAX  180000000
#else
#define SYSCLK_MAX  168000000
#endif

#elif (PWR_CR_VOS_Value == PWR_CR_VOS_SCALE2)

#if defined(PWR_CR_ODEN_Pos) && (PWR_CR_ODEN_Value == PWR_CR_ODEN_ENABLE)
#define SYSCLK_MAX  168000000
#else
#define SYSCLK_MAX  144000000
#endif

#else  // PWR_CR_VOS_Value must be PWR_CR_VOS_SCALE3
#define SYSCLK_MAX  120000000
#endif

// -----------------------------------------------------------------------------
//  FLASH_LATENCY_STEP depending on supply voltage
// -----------------------------------------------------------------------------

#ifndef VDD_mV  // if no VDD_mV, assume Vdd >= 2.7 V
#define                 FLASH_LATENCY_STEP  30000000
#elif (VDD_mV >= 2700)
#define                 FLASH_LATENCY_STEP  30000000   // BOR threshold should be set to level 3
#elif (VDD_mV >= 2400)
#define                 FLASH_LATENCY_STEP  24000000   // BOR threshold should be set to level 2
#elif (VDD_mV >= 2100)
#define                 FLASH_LATENCY_STEP  22000000   // BOR threshold should be set to level 1
#else
#define                 FLASH_LATENCY_STEP  20000000   // BOR should be off
#endif

// -----------------------------------------------------------------------------
//  HCLK_MAX depending on maximum flash latency
// -----------------------------------------------------------------------------

#define HCLK_MAX   (((FLASH_ACR_LATENCY_Msk >> FLASH_ACR_LATENCY_Pos) + 1) * FLASH_LATENCY_STEP)

#if    (SYSCLK_MAX > (HCLK_MAX * HPRE))
#undef  SYSCLK_MAX
#define SYSCLK_MAX   (HCLK_MAX * HPRE)
#endif

// -----------------------------------------------------------------------------
//  APBnCLK_MAX depending on regulator settings
// -----------------------------------------------------------------------------

#if defined(PWR_CR_ODEN_Pos) && (PWR_CR_ODEN_Value == PWR_CR_ODEN_ENABLE)

#define APB1CLK_MAX  45000000
#define APB2CLK_MAX  90000000
#else
#define APB1CLK_MAX  42000000
#define APB2CLK_MAX  84000000
#endif

// -----------------------------------------------------------------------------
//  OUTPUT_FREQUENCY_MAX depending on compensation cell
// -----------------------------------------------------------------------------

#if (SYSCFG_CMPCR_CMP_PD_Value == SYSCFG_CMPCR_CMP_PD_ENABLE)

#define OUTPUT_FREQUENCY_MAX  100000000
#else
#define OUTPUT_FREQUENCY_MAX   50000000
#endif


// #############################################################################
//
//      high-speed external clock settings
//
// #############################################################################

#ifndef RCC_CR_HSEBYP_Value
#define RCC_CR_HSEBYP_Value  RCC_CR_HSEBYP_DISABLE
#endif

#if (RCC_CR_HSEBYP_Value != RCC_CR_HSEBYP_DISABLE) && (RCC_CR_HSEBYP_Value != RCC_CR_HSEBYP_ENABLE)
#error Invalid definition of RCC_CR_HSEBYP_Value (must be RCC_CR_HSEBYP_DISABLE or RCC_CR_HSEBYP_ENABLE)
#endif

#if (RCC_CR_HSEBYP_Value != RCC_CR_HSEBYP_ENABLE)
#define HSE_VALUE_MIN    4000000
#define HSE_VALUE_MAX   26000000
#else
#define HSE_VALUE_MIN    1000000
#define HSE_VALUE_MAX   50000000
#endif

// IMPORTANT: no default definition of HSE_VALUE

#if defined(HSE_VALUE) && ((HSE_VALUE < HSE_VALUE_MIN) || (HSE_VALUE > HSE_VALUE_MAX))
#error Definition of HSE_VALUE out of range
#endif


// #############################################################################
//
//      identify clock source
//
// #############################################################################

#if !defined(RCC_CFGR_SW_Value) && (!defined(HSEON) || (HSEON == 1)) && defined(HSE_VALUE)

#if defined(SYSCLK) && (SYSCLK == HSE_VALUE)
#define                                      RCC_CFGR_SW_Value  RCC_CFGR_SW_HSE
#endif

#if defined(PLLON) && (PLLON == 0) && !defined(SYSCLK)
#define                                      RCC_CFGR_SW_Value  RCC_CFGR_SW_HSE
#endif

#endif // !defined(RCC_CFGR_SW_Value) && (!defined(HSEON) || (HSEON != 0)) && defined(HSE_VALUE)

#if !defined(RCC_CFGR_SW_Value) && (!defined(HISON) || (HSION == 1))

#if defined(SYSCLK) && (SYSCLK == HSI_VALUE)
#define                                      RCC_CFGR_SW_Value  RCC_CFGR_SW_HSI
#endif

#if defined(PLLON) && (PLLON == 0) && !defined(SYSCLK)
#define                                      RCC_CFGR_SW_Value  RCC_CFGR_SW_HSI
#endif

#endif // !defined(RCC_CFGR_SW_Value) && (!defined(HISON) || (HSION != 0))

#ifndef RCC_CFGR_SW_Value
#define RCC_CFGR_SW_Value  RCC_CFGR_SW_PLL
#endif

#if (RCC_CFGR_SW_Value != RCC_CFGR_SW_HSE) && (RCC_CFGR_SW_Value != RCC_CFGR_SW_HSI) && (RCC_CFGR_SW_Value != RCC_CFGR_SW_PLL)
#error Invalid definition of RCC_CFGR_SW_Value
#endif


// #############################################################################
//
//      check clock source (HSI)
//
// #############################################################################

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSI)

#ifndef SYSCLK
#define SYSCLK  HSI_VALUE
#endif

#if (SYSCLK != HSI_VALUE)
#error RCC_CFGR_SW_Value is RCC_CFGR_SW_HSI but SYSCLK does not match HSI_VALUE
#endif

#ifndef HSION
#define HSION  1
#endif

#if (HSION != 1)
#error RCC_CFGR_SW_Value is RCC_CFGR_SW_HSI but HSION is not 1
#endif

#ifndef PLLON
#define PLLON  0
#endif

#endif // (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSI)


// #############################################################################
//
//      check clock source (HSE)
//
// #############################################################################

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSE)

#ifndef HSE_VALUE
#error RCC_CFGR_SW_Value is RCC_CFGR_SW_HSE but HSE_VALUE is undefined
#endif

#ifndef SYSCLK
#define SYSCLK  HSE_VALUE
#endif

#if (SYSCLK != HSE_VALUE)
#error RCC_CFGR_SW_Value is RCC_CFGR_SW_HSE but SYSCLK does not match HSE_VALUE
#endif

#ifndef HSEON
#define HSEON  1
#endif

#if (HSEON != 1)
#error RCC_CFGR_SW_Value is RCC_CFGR_SW_HSE but HSEON is not 1
#endif

#ifndef PLLON
#define PLLON  0
#endif

#endif // (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSE)


// #############################################################################
//
//      check PLL input
//
// #############################################################################

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL)

#ifndef PLLON
#define PLLON  1
#endif

#if (PLLON != 1)
#error RCC_CFGR_SW_Value is RCC_CFGR_SW_PLL but PLLON is not 1
#endif

#endif // (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL)

#if defined(HSE_VALUE) && (!defined(HSEON) || (HSEON == 1)) && !defined(RCC_PLLCFGR_PLLSRC_Value)
#define RCC_PLLCFGR_PLLSRC_Value  RCC_PLLCFGR_PLLSRC_HSE
#endif

#ifndef RCC_PLLCFGR_PLLSRC_Value
#define RCC_PLLCFGR_PLLSRC_Value  RCC_PLLCFGR_PLLSRC_HSI
#endif

#if (RCC_PLLCFGR_PLLSRC_Value != RCC_PLLCFGR_PLLSRC_HSE) && (RCC_PLLCFGR_PLLSRC_Value != RCC_PLLCFGR_PLLSRC_HSI)
#error Invalid definition of RCC_PLLCFGR_PLLSRC_Value
#endif

#if (RCC_PLLCFGR_PLLSRC_Value == RCC_PLLCFGR_PLLSRC_HSE) && !defined(HSE_VALUE)
#error RCC_PLLCFGR_PLLSRC_Value is RCC_PLLCFGR_PLLSRC_HSE but HSE_VALUE is not defined
#endif

#if (RCC_PLLCFGR_PLLSRC_Value == RCC_PLLCFGR_PLLSRC_HSE) && !defined(HSEON)
#define HSEON  1
#endif

#if (RCC_PLLCFGR_PLLSRC_Value == RCC_PLLCFGR_PLLSRC_HSI) && !defined(HSION)
#define HSION  1
#endif

#if (RCC_PLLCFGR_PLLSRC_Value == RCC_PLLCFGR_PLLSRC_HSE) && (HSEON != 1)
#error RCC_PLLCFGR_PLLSRC_Value is RCC_PLLCFGR_PLLSRC_HSE but HSEON is not 1
#endif

#if (RCC_PLLCFGR_PLLSRC_Value == RCC_PLLCFGR_PLLSRC_HSI) && (HSION != 1)
#error RCC_PLLCFGR_PLLSRC_Value is RCC_PLLCFGR_PLLSRC_HSI but HSION is not 1
#endif

#if (RCC_PLLCFGR_PLLSRC_Value == RCC_PLLCFGR_PLLSRC_HSE)
#define PLL_INPUT  HSE_VALUE
#endif

#if (RCC_PLLCFGR_PLLSRC_Value == RCC_PLLCFGR_PLLSRC_HSI)
#define PLL_INPUT  HSI_VALUE
#endif


// #############################################################################
//
//      check SYSCLK configuration
//
// #############################################################################

// IMPORTANT: no default definition of SYSCLK

#if defined(SYSCLK) && (SYSCLK > SYSCLK_MAX)
#error Definition of SYSCLK exceeds maximum possible
#endif

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSE) && defined(HSE_VALUE) && defined(SYSCLK) && (SYSCLK != HSE_VALUE)
#error RCC_CFGR_SW_Value is RCC_CFGR_SW_HSE but SYSCLK is not equal to HSE_VALUE
#endif

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSI) && defined(SYSCLK) && (SYSCLK != HSI_VALUE)
#error RCC_CFGR_SW_Value is RCC_CFGR_SW_HSI but SYSCLK is not equal to HSI_VALUE
#endif

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL) && defined(SYSCLK) \
  && defined(PLL_M) && defined(PLL_N) && defined(PLL_P) \
  && ((SYSCLK * PLL_M * PLL_P) != (PLL_INPUT * PLL_N))

#error Defined SYSCLK does not agree with defined PLL_M, PLL_N and PLL_P
#endif



// #############################################################################
//
//      PLL configuration requirements
//
// #############################################################################

/*
  External crystal:                           4000000 <=          HSE         <=  26000000
  Integer M:          2 <= M <= 63             950000 <=       (HSE / M)      <=   2100000
  Integer N:         50 <= N <= 432         100000000 <=    ((HSE / M) * N)   <= 432000000
  Integer P:       P = (2 or 4 or 6 or 8)               (((HSE / M) * N) / P) <= 168000000 or 180000000
  Integer Q:          2 <= Q <= 15                      (((HSE / M) * N) / Q) <=  48000000 (exactly 48000000 for USB)
*/

#define VALID_PLL_M(m)        (((m) >= RCC_PLLM_MIN_VALUE) && ((m) <= RCC_PLLM_MAX_VALUE))
#define VALID_PLL_N(n)        (((n) >= RCC_PLLN_MIN_VALUE) && ((n) <= RCC_PLLN_MAX_VALUE))
#define VALID_PLL_P(p)        (((p) == 2) || ((p) == 4) || ((p) == 6) || ((p) == 8))
#define VALID_PLL_Q(q)        (((q) >= RCC_PLLQ_MIN_VALUE) && ((q) <= RCC_PLLQ_MAX_VALUE))


// #############################################################################
//
//      calculate PLL configuration if not defined
//
// #############################################################################

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL) && !(defined(PLL_M) && defined(PLL_N) && defined(PLL_P))

#ifdef PLL_M
#error PLL_M defined without PLL_N and PLL_P
#endif

#ifdef PLL_N
#error PLL_N defined without PLL_M and PLL_P
#endif

#ifdef PLL_P
#error PLL_P defined without PLL_M and PLL_N
#endif

/*
  PLL configuration will be generated according to the following rules:

  - If HSE_VALUE is defined use HSE for PLL input.
  - If HSE_VALUE is not defined use HSI for PLL input.
  - If SYSCLK is defined provide it exactly or else fail.
  - If SYSCLK is not defined get as close as possible to the maximum allowed frequency.
  - Make the 48MHz clock available for USB if possible.
  - Use even PLL_M if possible.
  - Use the smallest possible PLL_M (highest allowed VCO input).
  - Use the smallest possible PLL_N and PLL_P (lowest allowed VCO output).
  - Use the smallest possible PLL_Q (highest allowed PLL48CLK).
*/

#ifdef SYSCLK

#define N(m,p)                  ((1uLL * SYSCLK * (m) * (p)) / PLL_INPUT)
#define MP_OK_FOR_SYSCLK(m,p)   ((PLL_INPUT * N((m),(p))) == (SYSCLK * (m) * (p)))

#else  // SYSCLK

#define N(m,p)                  ((1uLL * SYSCLK_MAX * (m) * (p)) / PLL_INPUT)
#define MP_OK_FOR_SYSCLK(m,p)   (1)

#endif // SYSCLK

#define VCO_INPUT_IN_RANGE(m)       ((PLL_INPUT >= (RCC_PLLVCO_INPUT_MIN * (m))) && (PLL_INPUT <= (RCC_PLLVCO_INPUT_MAX * (m))))
#define VCO_OUTPUT_IN_RANGE(m,p)    (((PLL_INPUT * N((m),(p))) >= (RCC_PLLVCO_OUTPUT_MIN * (m))) && ((PLL_INPUT * N((m),(p))) <= (RCC_PLLVCO_OUTPUT_MAX * (m))))
#define MP_OK_FOR_VCO(m,p)          (VCO_INPUT_IN_RANGE(m) && VCO_OUTPUT_IN_RANGE((m),(p)))
#define Q(m,n)                      (((PLL_INPUT * (n)) + ((USBCLK_MAX * (m)) - 1)) / (USBCLK_MAX * (m)))
#define MP_OK_FOR_NQ(m,p)           (VALID_PLL_N(N((m),(p))) && VALID_PLL_Q(Q((m),N((m),(p)))))
#define MP_OK(m,p)                  (MP_OK_FOR_VCO((m),(p)) && MP_OK_FOR_NQ((m),(p)) && MP_OK_FOR_SYSCLK((m),(p)))
#define M_OK(m)                     (MP_OK((m),2) || MP_OK((m),4) || MP_OK((m),6) || MP_OK((m),8))
#define USB_POSSIBLE(m,p)           ((PLL_INPUT * N((m),(p))) == (USBCLK_MAX * (m) * Q((m),N((m),(p)))))
#define MP_OK_USB(m,p)              (MP_OK((m),(p)) && USB_POSSIBLE((m),(p)))
#define M_OK_USB(m)                 (MP_OK_USB((m),2) || MP_OK_USB((m),4) || MP_OK_USB((m),6) || MP_OK_USB((m),8))


#if      M_OK_USB( 2)
#define               PLL_M   2
#elif    M_OK_USB( 4)
#define               PLL_M   4
#elif    M_OK_USB( 6)
#define               PLL_M   6
#elif    M_OK_USB( 8)
#define               PLL_M   8
#elif    M_OK_USB(10)
#define               PLL_M  10
#elif    M_OK_USB(12)
#define               PLL_M  12
#elif    M_OK_USB(14)
#define               PLL_M  14
#elif    M_OK_USB(16)
#define               PLL_M  16
#elif    M_OK_USB(18)
#define               PLL_M  18
#elif    M_OK_USB(20)
#define               PLL_M  20
#elif    M_OK_USB(22)
#define               PLL_M  22
#elif    M_OK_USB(24)
#define               PLL_M  24
#elif    M_OK_USB(26)
#define               PLL_M  26
#elif    M_OK_USB( 3)
#define               PLL_M   3
#elif    M_OK_USB( 5)
#define               PLL_M   5
#elif    M_OK_USB( 7)
#define               PLL_M   7
#elif    M_OK_USB( 9)
#define               PLL_M   9
#elif    M_OK_USB(11)
#define               PLL_M  11
#elif    M_OK_USB(13)
#define               PLL_M  13
#elif    M_OK_USB(15)
#define               PLL_M  15
#elif    M_OK_USB(17)
#define               PLL_M  17
#elif    M_OK_USB(19)
#define               PLL_M  19
#elif    M_OK_USB(21)
#define               PLL_M  21
#elif    M_OK_USB(23)
#define               PLL_M  23
#elif    M_OK_USB(25)
#define               PLL_M  25
#elif    M_OK( 2)
#define               PLL_M   2
#elif    M_OK( 4)
#define               PLL_M   4
#elif    M_OK( 6)
#define               PLL_M   6
#elif    M_OK( 8)
#define               PLL_M   8
#elif    M_OK(10)
#define               PLL_M  10
#elif    M_OK(12)
#define               PLL_M  12
#elif    M_OK(14)
#define               PLL_M  14
#elif    M_OK(16)
#define               PLL_M  16
#elif    M_OK(18)
#define               PLL_M  18
#elif    M_OK(20)
#define               PLL_M  20
#elif    M_OK(22)
#define               PLL_M  22
#elif    M_OK(24)
#define               PLL_M  24
#elif    M_OK(26)
#define               PLL_M  26
#elif    M_OK( 3)
#define               PLL_M   3
#elif    M_OK( 5)
#define               PLL_M   5
#elif    M_OK( 7)
#define               PLL_M   7
#elif    M_OK( 9)
#define               PLL_M   9
#elif    M_OK(11)
#define               PLL_M  11
#elif    M_OK(13)
#define               PLL_M  13
#elif    M_OK(15)
#define               PLL_M  15
#elif    M_OK(17)
#define               PLL_M  17
#elif    M_OK(19)
#define               PLL_M  19
#elif    M_OK(21)
#define               PLL_M  21
#elif    M_OK(23)
#define               PLL_M  23
#elif    M_OK(25)
#define               PLL_M  25
#else
#error Cannot find a suitable value for PLL_M
#endif

#ifdef   PLL_M // not #error

#if      MP_OK_USB(PLL_M, 2)
#define                      PLL_P   2
#elif    MP_OK_USB(PLL_M, 4)
#define                      PLL_P   4
#elif    MP_OK_USB(PLL_M, 6)
#define                      PLL_P   6
#elif    MP_OK_USB(PLL_M, 8)
#define                      PLL_P   8
#elif    MP_OK(PLL_M, 2)
#define                      PLL_P   2
#elif    MP_OK(PLL_M, 4)
#define                      PLL_P   4
#elif    MP_OK(PLL_M, 6)
#define                      PLL_P   6
#elif    MP_OK(PLL_M, 8)
#define                      PLL_P   8
#else
#error Cannot find a suitable value for PLL_P
#endif

#define  PLL_N  N(PLL_M, PLL_P)
#define  PLL_Q  Q(PLL_M, PLL_N)

#endif // not #error

#endif // (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL) && !(defined(PLL_M) && defined(PLL_N) && defined(PLL_P))


// #############################################################################
//
//      check defined PLL configuration is valid
//
// #############################################################################


#if (PLLON != 0) && !(defined(PLL_M) && defined(PLL_N) && defined(PLL_P))
#error PLLON is set but PLL_M, PLL_N and PLL_P are not all defined
#endif

#ifndef PLL_M
#define PLL_M     16
#endif

#ifndef PLL_N
#define PLL_N    192
#endif

#ifndef PLL_P
#define PLL_P      2
#endif

#ifndef PLL_Q
#if (PLLON != 0)
#define PLL_Q     (((PLL_INPUT * PLL_N) + ((USBCLK_MAX * PLL_M) - 1)) / (USBCLK_MAX * PLL_M))
#else
#define PLL_Q      4
#endif
#endif

#ifndef SSCGEN
#define SSCGEN     0
#endif

#if (SSCGEN != 0) && !(defined(SPREADSEL) && defined(MODPER) && defined(INCSTEP))
#error SSCGEN is set but SPREADSEL, MODPER and INCSTEP are not all defined
#endif

#ifndef SPREADSEL
#define SPREADSEL  0
#endif

#ifndef MODPER
#define MODPER     0
#endif

#ifndef INCSTEP
#define INCSTEP    0
#endif

#if !VALID_PLL_M(PLL_M)
#error Invalid definition of PLL_M (must be in [2:63])
#endif

#if !VALID_PLL_N(PLL_N)
#error Invalid definition of PLL_N (must be in [50:432])
#endif

#if !VALID_PLL_P(PLL_P)
#error Invalid definition of PLL_P (must be one of 2,4,6,8)
#endif

#if !VALID_PLL_Q(PLL_Q)
#error Invalid definition of PLL_Q (must be in [2:15])
#endif

#if defined(PLL_R) && (PLL_R != 2)
#error Invalid definition of PLL_R (must be 2 or undefined)
#endif

#if (SSCGEN != 0) && (SSCGEN != 1)
#error Invalid definition of SSCGEN (must be 0 or 1)
#endif

#if (SPREADSEL != 0) && (SPREADSEL != 1)
#error Invalid definition of SPREADSEL (must be 0 or 1)
#endif

#if (MODPER < 0) || (MODPER >= (1 << 13))
#error Invalid definition of MODPER (must be in [0:8191])
#endif

#if (INCSTEP < 0) || (INCSTEP >= (1 << 15))
#error Invalid definition of INCSTEP (must be in [0:32767])
#endif

#if (SSCGEN != 0) && (PLLON != 1)
#warning SSCGEN is set but PLLON is not 1
#endif

#if (MODPER != 0) && (SSCGEN != 1)
#warning MODPER is defined as non-zero but SSCGEN is not 1
#endif

#if (INCSTEP != 0) && (SSCGEN != 1)
#warning INCSTEP is defined as non-zero but SSCGEN is not 1
#endif

#if (PLLON != 0)

#if (PLL_INPUT < (RCC_PLLVCO_INPUT_MIN * PLL_M)) || (PLL_INPUT > (RCC_PLLVCO_INPUT_MAX * PLL_M))
#error Main PLL VCO input out of range
#endif

#if ((PLL_INPUT * PLL_N) < (RCC_PLLVCO_OUTPUT_MIN * PLL_M)) || ((PLL_INPUT * PLL_N) > (RCC_PLLVCO_OUTPUT_MAX * PLL_M))
#error Main PLL VCO output out of range
#endif

#if (PLL_INPUT * PLL_N) > (SYSCLK_MAX * PLL_M * PLL_P)
#error system core clock exceeds maximum
#endif

#if (PLL_INPUT * PLL_N) > (USBCLK_MAX * PLL_M * PLL_Q)
#error USB clock exceeds maximum
#endif

#if (SSCGEN != 0)

#if ((40000 * MODPER * PLL_M) < PLL_INPUT)
#error PLL spread modulation frequency exceeds maximum (10kHz)
#endif

#if ((MODPER * INCSTEP) >= (1 << 15))
#error PLL spread depth exceeds maximum (MODPER * INCSTEP) >= (1 << 15)
#endif

#if ((500 * MODPER * INCSTEP) > (65534 * PLL_N))
#error PLL spread depth exceeds maximum (2%)
#endif

#endif // (SSCGEN != 0)
#else  // (PLLON != 0)

#if (SSCGEN != 0)
#warning SSCGEN is defined as non-zero but PLLON is 0
#endif

#endif // (PLLON != 0)


// #############################################################################
//
//      check I2S PLL configuration
//
// #############################################################################

#ifndef PLLI2SON
#define PLLI2SON  0
#endif

#if (PLLI2SON != 0) && (PLLI2SON != 1)
#error Invalid definition of PLLI2SON (must be 0 or 1)
#endif

#if (PLLI2SON != 0) && !defined(PLLI2S_N)
#error PLLI2S_N must be defined (because PLLI2SON is 1)
#endif

#if (PLLI2SON != 0) && !defined(PLLI2S_R)
#error PLLI2S_R must be defined (because PLLI2SON is 1)
#endif

#if defined(PLLI2S_N) && ((PLLI2S_N < 50) || (PLLI2S_N > 432))
#error Invalid definition of PLLI2S_N (must be in [50:432])
#endif

#if defined(PLLI2S_R) && ((PLLI2S_R < 2) || (PLLI2S_R > 7))
#error Invalid definition of PLLI2S_R (must be in [2:7])
#endif

#if (PLLI2SON != 0)

#if ((PLL_INPUT * PLLI2S_N) < (RCC_PLLVCO_OUTPUT_MIN * PLL_M)) || ((PLL_INPUT * PLLI2S_N) > (RCC_PLLVCO_OUTPUT_MAX * PLL_M))
#error PLLI2S VCO output out of range [100MHz:432MHz]
#endif

// no limit on PLLI2S_R output frequency stricter than than VCO/2

#else  // (PLLI2SON != 0)

#ifdef PLLI2S_N
#warning PLLI2S_N is defined but PLLI2SON is 0
#endif

#ifdef PLLI2S_Q
#warning PLLI2S_Q is defined but PLLI2SON is 0
#endif

#ifdef PLLI2S_R
#warning PLLI2S_R is defined but PLLI2SON is 0
#endif

#ifndef PLLI2S_N
#define PLLI2S_N  192
#endif

#ifndef PLLI2S_R
#define PLLI2S_R    2
#endif

#endif // (PLLI2SON != 0)

// #############################################################################
//
//      check I2S PLL Q configuration
//
// #############################################################################

#ifdef RCC_PLLI2SCFGR_PLLI2SQ_Pos

#if (PLLI2SON != 0) && !defined(PLLI2S_Q)
#error PLLI2S_Q must be defined (because PLLI2SON is 1)
#endif

#if (PLLI2SON != 0) && !defined(PLLI2SDIVQ)
#error PLLI2SDIVQ must be defined (because PLLI2SON is 1)
#endif

#ifndef PLLI2S_Q
#define PLLI2S_Q    4
#endif

#ifndef PLLI2SDIVQ
#define PLLI2SDIVQ  1
#endif

#if (PLLI2S_Q < 2) || (PLLI2S_Q > 15)
#error Invalid definition of PLLI2S_Q (must be in [2:15])
#endif

#if (PLLI2SDIVQ < 1) || (PLLI2SDIVQ > 32)
#error Invalid definition of PLLI2SDIVQ (must be in [1:32])
#endif

// no limit on PLLI2S_Q output frequency stricter than than VCO/2

#else  // RCC_PLLI2SCFGR_PLLI2SQ_Pos

#ifdef PLLI2S_Q
#error PLLI2S_Q is defined but is not available on selected part
#endif

#ifdef PLLI2SDIVQ
#error PLLI2SDIVQ is defined but is not available on selected part
#endif

#endif // RCC_PLLI2SCFGR_PLLI2SQ_Pos


// #############################################################################
//
//      check SAI PLL configuration
//
// #############################################################################

#ifdef RCC_PLLSAICFGR_PLLSAIN_Pos

#ifndef PLLSAION
#define PLLSAION  0
#endif

#if (PLLSAION != 0) && (PLLSAION != 1)
#error Invalid definition of PLLSAION (must be 0 or 1)
#endif

#if (PLLSAION != 0) && !defined(PLLSAI_N)
#error PLLSAI_N must be defined (because PLLSAION is 1)
#endif

#if (PLLSAION != 0) && !defined(PLLSAI_Q)
#error PLLSAI_Q must be defined (because PLLSAION is 1)
#endif

#if (PLLSAION != 0) && !defined(PLLSAI_R)
#error PLLSAI_R must be defined (because PLLSAION is 1)
#endif

#if (PLLSAION != 0) && !defined(PLLSAIDIVQ)
#error PLLSAIDIVQ must be defined (because PLLSAION is 1)
#endif

#if (PLLSAION != 0) && !defined(PLLSAIDIVR)
#error PLLSAIDIVR must be defined (because PLLSAION is 1)
#endif

#if defined(PLLSAI_N) && ((PLLSAI_N < 50) || (PLLSAI_N > 432))
#error Invalid definition of PLLSAI_N (must be in [50:432])
#endif

#if defined(PLLSAI_Q) && ((PLLSAI_Q < 2) || (PLLSAI_Q > 15))
#error Invalid definition of PLLSAI_Q (must be in [2:15])
#endif

#if defined(PLLSAI_R) && ((PLLSAI_R < 2) || (PLLSAI_R > 7))
#error Invalid definition of PLLSAI_R (must be in [2:7])
#endif

#ifndef PLLSAIDIVQ
#define PLLSAIDIVQ  1
#endif

#ifndef PLLSAIDIVR
#define PLLSAIDIVR  2
#endif

#if (PLLSAIDIVQ < 1) || (PLLSAIDIVQ > 32)
#error Invalid definition of PLLSAIDIVQ (must be in [1:32])
#endif

#if (PLLSAIDIVR != 2) && (PLLSAIDIVR != 4) && (PLLSAIDIVR != 8) && (PLLSAIDIVR != 16)
#error Invalid definition of PLLSAIDIVR (must be one of 2,4,8,16)
#endif

#if (PLLSAION != 0)

#if ((PLL_INPUT * PLLSAI_N) < (RCC_PLLVCO_OUTPUT_MIN * PLL_M)) || ((PLL_INPUT * PLLSAI_N) > (RCC_PLLVCO_OUTPUT_MAX * PLL_M))
#error PLLSAI VCO output out of range [100MHz:432MHz]
#endif

// no limit on PLLSAI_Q output frequency stricter than than VCO/2
// no limit on PLLSAI_R output frequency stricter than than VCO/2

#else  // (PLLSAION != 0)

#ifdef PLLSAI_N
#warning PLLSAI_N is defined but PLLSAION is 0
#endif

#ifdef PLLSAI_Q
#warning PLLSAI_Q is defined but PLLSAION is 0
#endif

#ifdef PLLSAI_R
#warning PLLSAI_R is defined but PLLSAION is 0
#endif

#ifndef PLLSAI_N
#define PLLSAI_N  192
#endif

#ifndef PLLSAI_Q
#define PLLSAI_Q    4
#endif

#ifndef PLLSAI_R
#define PLLSAI_R    2
#endif

#endif // (PLLSAION != 0)

#else  // RCC_PLLSAICFGR_PLLSAIN_Pos

#ifdef PLLSAION
#error PLLSAION is defined but is not available on selected part
#endif

#ifdef PLLSAI_N
#error PLLSAI_N is defined but is not available on selected part
#endif

#ifdef PLLSAI_Q
#error PLLSAI_Q is defined but is not available on selected part
#endif

#ifdef PLLSAI_R
#error PLLSAI_R is defined but is not available on selected part
#endif

#ifdef PLLSAIDIVQ
#error PLLSAIDIVQ is defined but is not available on selected part
#endif

#ifdef PLLSAIDIVR
#error PLLSAIDIVR is defined but is not available on selected part
#endif

#endif // RCC_PLLSAICFGR_PLLSAIN_Pos


// #############################################################################
//
//      calculate bus clocks
//
// #############################################################################

// -----------------------------------------------------------------------------
//      check peripheral bus dividers
// -----------------------------------------------------------------------------

#if defined(PPRE2) && (PPRE2 != 1) && (PPRE2 != 2) && (PPRE2 != 4) && (PPRE2 != 8) && (PPRE2 != 16)
#error Invalid definition of PPRE2 (must be one of 1,2,4,8,16)
#endif

#if defined(PPRE1) && (PPRE1 != 1) && (PPRE1 != 2) && (PPRE1 != 4) && (PPRE1 != 8) && (PPRE1 != 16)
#error Invalid definition of PPRE1 (must be one of 1,2,4,8,16)
#endif

// -----------------------------------------------------------------------------
//      calculate bus clocks (wihout PLL)
// -----------------------------------------------------------------------------

#if (RCC_CFGR_SW_Value != RCC_CFGR_SW_PLL)

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSE) && !defined(SYSCLK)

#define SYSCLK  HSE_VALUE
#endif

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_HSI) && !defined(SYSCLK)

#define SYSCLK  HSI_VALUE
#endif

#if   (SYSCLK <= (APB1CLK_MAX * HPRE * 1)) && !defined(PPRE1)
#define                                                       PPRE1   1
#elif (SYSCLK <= (APB1CLK_MAX * HPRE * 2)) && !defined(PPRE1)
#define                                                       PPRE1   2
#elif (SYSCLK <= (APB1CLK_MAX * HPRE * 4)) && !defined(PPRE1)
#define                                                       PPRE1   4
#elif (SYSCLK <= (APB1CLK_MAX * HPRE * 8)) && !defined(PPRE1)
#define                                                       PPRE1   8
#elif                                         !defined(PPRE1)
#define                                                       PPRE1  16
#endif

#if   (SYSCLK <= (APB2CLK_MAX * HPRE * 1)) && !defined(PPRE2)
#define                                                       PPRE2   1
#elif (SYSCLK <= (APB2CLK_MAX * HPRE * 2)) && !defined(PPRE2)
#define                                                       PPRE2   2
#elif (SYSCLK <= (APB2CLK_MAX * HPRE * 4)) && !defined(PPRE2)
#define                                                       PPRE2   4
#elif (SYSCLK <= (APB2CLK_MAX * HPRE * 8)) && !defined(PPRE2)
#define                                                       PPRE2   8
#elif                                         !defined(PPRE2)
#define                                                       PPRE2  16
#endif

#if (SYSCLK > (APB1CLK_MAX * HPRE * PPRE1))
#error APB1 clock exceeds maximum
#endif

#if (SYSCLK > (APB2CLK_MAX * HPRE * PPRE2))
#error APB2 clock exceeds maximum
#endif

#define HCLK      ((1uLL * SYSCLK) / (HPRE        ))
#define APB1_CLK  ((1uLL * SYSCLK) / (HPRE * PPRE1))
#define APB2_CLK  ((1uLL * SYSCLK) / (HPRE * PPRE2))

#endif // (RCC_CFGR_SW_Value != RCC_CFGR_SW_PLL)

// -----------------------------------------------------------------------------
//      calculate bus clocks (with PLL)
// -----------------------------------------------------------------------------

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL)

#if   ((PLL_INPUT * PLL_N) <= (APB1CLK_MAX * PLL_M * PLL_P * HPRE * 1)) && !defined(PPRE1)
#define                                                                                    PPRE1   1
#elif ((PLL_INPUT * PLL_N) <= (APB1CLK_MAX * PLL_M * PLL_P * HPRE * 2)) && !defined(PPRE1)
#define                                                                                    PPRE1   2
#elif ((PLL_INPUT * PLL_N) <= (APB1CLK_MAX * PLL_M * PLL_P * HPRE * 4)) && !defined(PPRE1)
#define                                                                                    PPRE1   4
#elif ((PLL_INPUT * PLL_N) <= (APB1CLK_MAX * PLL_M * PLL_P * HPRE * 8)) && !defined(PPRE1)
#define                                                                                    PPRE1   8
#elif                                                                      !defined(PPRE1)
#define                                                                                    PPRE1  16
#endif

#if   ((PLL_INPUT * PLL_N) <= (APB2CLK_MAX * PLL_M * PLL_P * HPRE * 1)) && !defined(PPRE2)
#define                                                                                    PPRE2   1
#elif ((PLL_INPUT * PLL_N) <= (APB2CLK_MAX * PLL_M * PLL_P * HPRE * 2)) && !defined(PPRE2)
#define                                                                                    PPRE2   2
#elif ((PLL_INPUT * PLL_N) <= (APB2CLK_MAX * PLL_M * PLL_P * HPRE * 4)) && !defined(PPRE2)
#define                                                                                    PPRE2   4
#elif ((PLL_INPUT * PLL_N) <= (APB2CLK_MAX * PLL_M * PLL_P * HPRE * 8)) && !defined(PPRE2)
#define                                                                                    PPRE2   8
#elif                                                                      !defined(PPRE2)
#define                                                                                    PPRE2  16
#endif

#if (PLL_INPUT * PLL_N) > (APB1CLK_MAX * PLL_M * PLL_P * HPRE * PPRE1)
#error APB1 clock exceeds maximum
#endif

#if (PLL_INPUT * PLL_N) > (APB2CLK_MAX * PLL_M * PLL_P * HPRE * PPRE2)
#error APB2 clock exceeds maximum
#endif

#ifndef SYSCLK
#define SYSCLK    ((1uLL * PLL_INPUT * PLL_N) / (PLL_M * PLL_P               ))
#endif

#define HCLK      ((1uLL * PLL_INPUT * PLL_N) / (PLL_M * PLL_P * HPRE        ))
#define APB1_CLK  ((1uLL * PLL_INPUT * PLL_N) / (PLL_M * PLL_P * HPRE * PPRE1))
#define APB2_CLK  ((1uLL * PLL_INPUT * PLL_N) / (PLL_M * PLL_P * HPRE * PPRE2))

#endif // (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL)


// #############################################################################
//
//      Timer clock configuration
//
// #############################################################################

#ifdef RCC_DCKCFGR_TIMPRE_Pos

#ifndef TIMPRE
#define TIMPRE  1
#endif

#if (TIMPRE != 0) && (TIMPRE != 1)
#error Invalid definition of TIMPRE (must be 0 or 1)
#endif

#else  // RCC_DCKCFGR_TIMPRE_Pos

#ifdef TIMPRE
#error TIMPRE is defined but is not available on selected part
#endif

#endif // RCC_DCKCFGR_TIMPRE_Pos

// -----------------------------------------------------------------------------
//      calculate timer clocks (without PLL)
// -----------------------------------------------------------------------------

#if (RCC_CFGR_SW_Value != RCC_CFGR_SW_PLL)

#if defined(TIMPRE) && (TIMPRE == 1)

#if (PPRE1 <= 4)
#define APB1_TIM_CLK    HCLK
#else
#define APB1_TIM_CLK    ((4uLL * SYSCLK) / (HPRE * PPRE1))
#endif

#if (PPRE2 <= 4)
#define APB2_TIM_CLK    HCLK
#else
#define APB2_TIM_CLK    ((4uLL * SYSCLK) / (HPRE * PPRE2))
#endif

#else  // (TIMPRE == 1)

#if (PPRE1 == 1)
#define APB1_TIM_CLK    APB1_CLK
#else
#define APB1_TIM_CLK    ((2uLL * SYSCLK) / (HPRE * PPRE1))
#endif

#if (PPRE2 == 1)
#define APB2_TIM_CLK    APB2_CLK
#else
#define APB2_TIM_CLK    ((2uLL * SYSCLK) / (HPRE * PPRE2))
#endif

#endif // (TIMPRE == 1)

#endif // (RCC_CFGR_SW_Value != RCC_CFGR_SW_PLL)

// -----------------------------------------------------------------------------
//      calculate timer clocks (with PLL)
// -----------------------------------------------------------------------------

#if (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL)

#if defined(TIMPRE) && (TIMPRE == 1)

#if (PPRE1 <= 4)
#define APB1_TIM_CLK  HCLK
#else
#define APB1_TIM_CLK  ((4uLL * PLL_INPUT * PLL_N) / (PLL_M * PLL_P * HPRE * PPRE1))
#endif

#if (PPRE2 <= 4)
#define APB2_TIM_CLK  HCLK
#else
#define APB2_TIM_CLK  ((4uLL * PLL_INPUT * PLL_N) / (PLL_M * PLL_P * HPRE * PPRE2))
#endif

#else  // (TIMPRE == 1)

#if (PPRE1 == 1)
#define APB1_TIM_CLK  APB1_CLK
#else
#define APB1_TIM_CLK  ((2uLL * PLL_INPUT * PLL_N) / (PLL_M * PLL_P * HPRE * PPRE1))
#endif

#if (PPRE2 == 1)
#define APB2_TIM_CLK  APB2_CLK
#else
#define APB2_TIM_CLK  ((2uLL * PLL_INPUT * PLL_N) / (PLL_M * PLL_P * HPRE * PPRE2))
#endif

#endif // (TIMPRE == 1)

#endif // (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL)

// -----------------------------------------------------------------------------
//      define timer clocks
// -----------------------------------------------------------------------------

#define TIM1_CLK   APB2_TIM_CLK
#define TIM2_CLK   APB1_TIM_CLK
#define TIM3_CLK   APB1_TIM_CLK
#define TIM4_CLK   APB1_TIM_CLK
#define TIM5_CLK   APB1_TIM_CLK
#define TIM6_CLK   APB1_TIM_CLK
#define TIM7_CLK   APB1_TIM_CLK
#define TIM8_CLK   APB2_TIM_CLK
#define TIM9_CLK   APB2_TIM_CLK
#define TIM10_CLK  APB2_TIM_CLK
#define TIM11_CLK  APB2_TIM_CLK
#define TIM12_CLK  APB1_TIM_CLK
#define TIM13_CLK  APB1_TIM_CLK
#define TIM14_CLK  APB1_TIM_CLK


// #############################################################################
//
//      flash interface settings
//
// #############################################################################

#define FLASH_LATENCY  ((HCLK - 1uLL) / FLASH_LATENCY_STEP)

#if (FLASH_LATENCY > (FLASH_ACR_LATENCY_Msk >> FLASH_ACR_LATENCY_Pos))
#error Host bus too fast for flash access
#endif


// #############################################################################
//
//      clock output configuration
//
// #############################################################################

// -----------------------------------------------------------------------------
//      clock output source definitions
// -----------------------------------------------------------------------------

#ifndef RCC_CFGR_MCO1_Value
#define RCC_CFGR_MCO1_Value  RCC_CFGR_MCO1_HSI
#endif

#ifndef RCC_CFGR_MCO2_Value
#define RCC_CFGR_MCO2_Value  RCC_CFGR_MCO2_SYSCLK
#endif

#if (RCC_CFGR_MCO1_Value != RCC_CFGR_MCO1_HSI) && (RCC_CFGR_MCO1_Value != RCC_CFGR_MCO1_LSE) && (RCC_CFGR_MCO1_Value != RCC_CFGR_MCO1_HSE) && (RCC_CFGR_MCO1_Value != RCC_CFGR_MCO1_PLL)
#error Invalid definition of RCC_CFGR_MCO1_Value (must be one of RCC_CFGR_MCO1_HSI, RCC_CFGR_MCO1_LSE, RCC_CFGR_MCO1_HSE, RCC_CFGR_MCO1_PLL)
#endif

#if (RCC_CFGR_MCO2_Value != RCC_CFGR_MCO2_SYSCLK) && (RCC_CFGR_MCO2_Value != RCC_CFGR_MCO2_PLLI2S) && (RCC_CFGR_MCO2_Value != RCC_CFGR_MCO2_HSE) && (RCC_CFGR_MCO2_Value != RCC_CFGR_MCO2_PLL)
#error Invalid definition of RCC_CFGR_MCO2_Value (must be one of RCC_CFGR_MCO2_SYSCLK, RCC_CFGR_MCO2_PLLI2S, RCC_CFGR_MCO2_HSE, RCC_CFGR_MCO2_PLL)
#endif

// -----------------------------------------------------------------------------
//      clock output source enable
// -----------------------------------------------------------------------------

#if (RCC_CFGR_MCO1_Value == RCC_CFGR_MCO1_HSI) && !defined(HSION)
#define HSION  1
#endif

#if (RCC_CFGR_MCO1_Value == RCC_CFGR_MCO1_HSE) && !defined(HSEON)
#define HSEON  1
#endif

#if (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_HSE) && !defined(HSEON)
#define HSEON  1
#endif

#if (RCC_CFGR_MCO1_Value == RCC_CFGR_MCO1_HSI) && (HSION != 1)
#error RCC_CFGR_MCO1_Value is RCC_CFGR_MCO1_HSI but HSION is not 1
#endif

#if (RCC_CFGR_MCO1_Value == RCC_CFGR_MCO1_HSE) && (HSEON != 1)
#error RCC_CFGR_MCO1_Value is RCC_CFGR_MCO1_HSE but HSEON is not 1
#endif

#if (RCC_CFGR_MCO1_Value == RCC_CFGR_MCO1_PLL) && (PLLON != 1)
#error RCC_CFGR_MCO1_Value is RCC_CFGR_MCO1_PLL but PLLON is not 1
#endif

#if (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_HSE) && (HSEON != 1)
#error RCC_CFGR_MCO2_Value is RCC_CFGR_MCO2_HSE but HSEON is not 1
#endif

#if (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_PLL) && (PLLON != 1)
#error RCC_CFGR_MCO2_Value is RCC_CFGR_MCO2_PLL but PLLON is not 1
#endif

#if (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_PLLI2S) && (PLLI2SON != 1)
#error RCC_CFGR_MCO2_Value is RCC_CFGR_MCO2_PLLI2S but PLLI2SON is not 1
#endif

// -----------------------------------------------------------------------------
//      clock output minimum dividers
// -----------------------------------------------------------------------------

#if (RCC_CFGR_MCO1_Value == RCC_CFGR_MCO1_PLL)

#define MCO1PRE_MIN  (((PLL_INPUT * PLL_N) + (PLL_M * PLL_P * OUTPUT_FREQUENCY_MAX) - 1) / (PLL_M * PLL_P * OUTPUT_FREQUENCY_MAX))
#else
#define MCO1PRE_MIN  1
#endif

#if (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_PLL)

#define MCO2PRE_MIN  (((PLL_INPUT * PLL_N) + (PLL_M * PLL_P * OUTPUT_FREQUENCY_MAX) - 1) / (PLL_M * PLL_P * OUTPUT_FREQUENCY_MAX))

#elif (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_PLLI2S)

#define MCO2PRE_MIN  (((PLL_INPUT * PLLI2S_N) + (PLL_M * PLLI2S_R * OUTPUT_FREQUENCY_MAX) - 1) / (PLL_M * PLLI2S_R * OUTPUT_FREQUENCY_MAX))

#elif (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_SYSCLK) && (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL)

// FIXME should this include HPRE?
#define MCO2PRE_MIN  (((PLL_INPUT * PLL_N) + (PLL_M * PLL_P * HPRE * OUTPUT_FREQUENCY_MAX) - 1) / (PLL_M * PLL_P * HPRE * OUTPUT_FREQUENCY_MAX))

#else
#define MCO2PRE_MIN  1
#endif

// -----------------------------------------------------------------------------
//      clock output divider definitions
// -----------------------------------------------------------------------------

#ifndef MCO1PRE
#define MCO1PRE  MCO1PRE_MIN
#endif

#ifndef MCO2PRE
#define MCO2PRE  MCO2PRE_MIN
#endif

#if ((MCO1PRE < 1) || (MCO1PRE > 5))
#error Invalid definition of MCO1PRE (must be in [1:5])
#endif

#if ((MCO2PRE < 1) || (MCO2PRE > 5))
#error Invalid definition of MCO2PRE (must be in [1:5])
#endif

// -----------------------------------------------------------------------------
//      check clock output frequency
// -----------------------------------------------------------------------------

#if (RCC_CFGR_MCO1_Value == RCC_CFGR_MCO1_PLL) && (PLLON != 0) && ((PLL_INPUT * PLL_N) > (OUTPUT_FREQUENCY_MAX * PLL_M * PLL_P * MCO1PRE))
#error MCO1 exceeds maximum output frequency
#endif

#if (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_PLL) && (PLLON != 0) && ((PLL_INPUT * PLL_N) > (OUTPUT_FREQUENCY_MAX * PLL_M * PLL_P * MCO1PRE))
#error MCO2 exceeds maximum output frequency
#endif

#if (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_SYSCLK) && (RCC_CFGR_SW_Value == RCC_CFGR_SW_PLL) && ((PLL_INPUT * PLL_N) > (OUTPUT_FREQUENCY_MAX * PLL_M * PLL_P * MCO2PRE))
#error MCO2 exceeds maximum output frequency
#endif

#if (RCC_CFGR_MCO2_Value == RCC_CFGR_MCO2_PLLI2S) && (PLLI2SON != 0) && ((PLL_INPUT * PLLI2S_N) > (OUTPUT_FREQUENCY_MAX * PLL_M * PLLI2S_R * MCO2PRE))
#error MCO2 exceeds maximum output frequency
#endif


// #############################################################################
//
//      real time clock prescaler
//
// #############################################################################

#ifndef RTCPRE
#ifndef HSE_VALUE
#define                         RTCPRE   0u
#elif (HSE_VALUE <   2500000)
#define                         RTCPRE   2u
#elif (HSE_VALUE >= 30500000)
#define                         RTCPRE  31u
#else
#define                         RTCPRE  ((HSE_VALUE + 500000u) / 1000000u)
#endif
#endif // RTCPRE

#if (RTCPRE < 0) || (RTCPRE > 31)
#error Invalid definition of RTCPRE (must be in [0:31])
#endif


// #############################################################################
//
//      oscillators off if unused
//
// #############################################################################

#ifndef HSION
#define HSION  0
#endif

#ifndef HSEON
#define HSEON  0
#endif

#endif // SYSTEM_STM32F405_439_H_INCLUDED
