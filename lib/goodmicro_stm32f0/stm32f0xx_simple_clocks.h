// stm32f0xx_simple_clocks.h
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

#ifndef STM32F0XX_CLOCKS_H_INCLUDED
#define STM32F0XX_CLOCKS_H_INCLUDED

#include "stm32f0xx.h"
#include "stm32f0xx_missing.h"
#include "clock_config.h"


/* check part number */

#if !defined (STM32F030x6) && !defined (STM32F030x8) &&                           \
    !defined (STM32F031x6) && !defined (STM32F038xx) &&                           \
    !defined (STM32F042x6) && !defined (STM32F048xx) && !defined (STM32F070x6) && \
    !defined (STM32F051x8) && !defined (STM32F058xx) &&                           \
    !defined (STM32F071xB) && !defined (STM32F072xB) && !defined (STM32F078xx) && !defined (STM32F070xB) && \
    !defined (STM32F091xC) && !defined (STM32F098xx) && !defined (STM32F030xC)
#  error incorrect or no STM32F0xx part number macro
#endif


/* check PLL and bus configuration macros are defined */

#ifndef PLLSRC
#  error PLLSRC must be defined in clock_config.h
#endif

#if PLLSRC == RCC_CFGR_PLLSRC_HSE_PREDIV
#  ifndef HSE_VALUE
#    error HSE_VALUE must be defined in clock_config.h (because PLLSRC is RCC_CFGR_PLLSRC_HSE_PREDIV)
#  endif
#endif

#if (PLLSRC != RCC_CFGR_PLLSRC_HSI_DIV2)
#  ifndef PREDIV
#    error PREDIV must be defined in clock_config.h
#  endif
#endif

#ifndef PLLMUL
#  error PLLMUL must be defined in clock_config.h
#endif

#ifndef HPRE
#  error HPRE must be defined in clock_config.h
#endif

#ifndef PPRE
#  error PPRE must be defined in clock_config.h
#endif


/* check PLL and bus configuration macros are in range */

#if defined(RCC_CFGR_PLLSRC_HSI48_PREDIV) && defined(RCC_CFGR_PLLSRC_HSI_PREDIV)

#if (PLLSRC != RCC_CFGR_PLLSRC_HSI_DIV2)   && (PLLSRC != RCC_CFGR_PLLSRC_HSI_PREDIV)  \
 && (PLLSRC != RCC_CFGR_PLLSRC_HSE_PREDIV) && (PLLSRC != RCC_CFGR_PLLSRC_HSI48_PREDIV)
#error PLLSRC must be one of RCC_CFGR_PLLSRC_HSI_DIV2, RCC_CFGR_PLLSRC_HSI_PREDIV, RCC_CFGR_PLLSRC_HSE_PREDIV or RCC_CFGR_PLLSRC_HSI48_PREDIV
#endif

#elif defined(RCC_CFGR_PLLSRC_HSI_PREDIV)

#if (PLLSRC != RCC_CFGR_PLLSRC_HSI_DIV2) && (PLLSRC != RCC_CFGR_PLLSRC_HSI_PREDIV)  \
 && (PLLSRC != RCC_CFGR_PLLSRC_HSE_PREDIV)
#error PLLSRC must be one of RCC_CFGR_PLLSRC_HSI_DIV2, RCC_CFGR_PLLSRC_HSI_PREDIV or RCC_CFGR_PLLSRC_HSE_PREDIV
#endif

#else // defined(RCC_CFGR_PLLSRC_HSI_PREDIV)

#if (PLLSRC != RCC_CFGR_PLLSRC_HSI_DIV2) && (PLLSRC != RCC_CFGR_PLLSRC_HSE_PREDIV)
#error PLLSRC must be either RCC_CFGR_PLLSRC_HSI_DIV2 or RCC_CFGR_PLLSRC_HSE_PREDIV
#endif

#endif // defined(RCC_CFGR_PLLSRC_HSI_PREDIV)

#ifdef HSE_VALUE
#  if (HSE_VALUE < 4000000) || (HSE_VALUE > 32000000)
#    error HSE_VALUE out of range [4MHz:32MHz]
#  endif
#endif

#if (PLLSRC == RCC_CFGR_PLLSRC_HSI_DIV2)
#  if defined (PREDIV) && (PREDIV != 2)
#    error PLLSRC is RCC_CFGR_PLLSRC_HSI_DIV2 but PREDIV is defined as other than 2
#  endif
#else
#  if (PREDIV < 1) || (PREDIV > 16)
#    error PREDIV out of range [1:16]
#  endif
#endif

#if (PLLMUL < 2) || (PLLMUL > 16)
#error PLLMUL out of range [2:16]
#endif

#if (HPRE !=   1) && (HPRE !=   2) && (HPRE !=   4) && (HPRE !=   8) && (HPRE !=  16) \
 && (HPRE !=  64) && (HPRE != 128) && (HPRE != 256) && (HPRE != 512)
#error HPRE not in (1,2,4,8,16,64,128,256,512)
#endif

#if (PPRE != 1) && (PPRE != 2) && (PPRE != 4) && (PPRE != 8) && (PPRE != 16)
#error PPRE not in (1,2,4,8,16)
#endif


/* check PLL frequencies are in range */

#if (PLLSRC == RCC_CFGR_PLLSRC_HSI_DIV2)
#  if (PLLMUL < 4u) || (PLLMUL > 12u)
#    error PLL output out of range [16MHz:48MHz]
#  endif
#endif

#if defined(RCC_CFGR_PLLSRC_HSI_PREDIV) && (PLLSRC == RCC_CFGR_PLLSRC_HSI_PREDIV)
#  if (PLLMUL < (2u * PREDIV)) || (PLLMUL > (6u * PREDIV))
#    error PLL output out of range [16MHz:48MHz]
#  endif
#endif

#if (PLLSRC == RCC_CFGR_PLLSRC_HSE_PREDIV)
#  if ((HSI_VALUE * PLLMUL) < (16000000u * PREDIV)) || ((HSI_VALUE * PLLMUL) > (48000000u * PREDIV))
#    error PLL output out of range [16MHz:48MHz]
#  endif
#endif

#if defined(RCC_CFGR_PLLSRC_HSI48_PREDIV) && (PLLSRC == RCC_CFGR_PLLSRC_HSI48_PREDIV)
#  if ((3 * PLLMUL) < PREDIV) || (PLLMUL > PREDIV)
#    error PLL output out of range [16MHz:48MHz]
#  endif
#endif


/* derived clock frequencies */

#if (PLLSRC == RCC_CFGR_PLLSRC_HSI_DIV2)
#  define SYSCLK    ((HSI_VALUE * PLLMUL) / (2u              ))
#  define HCLK      ((HSI_VALUE * PLLMUL) / (2u * HPRE       ))
#  define APB1_CLK  ((HSI_VALUE * PLLMUL) / (2u * HPRE * PPRE))
#  define APB2_CLK  ((HSI_VALUE * PLLMUL) / (2u * HPRE * PPRE))

#  if (PPRE == 1)
#    define APB1_TIM_CLK   APB1_CLK
#    define APB2_TIM_CLK   APB2_CLK
#  else
#    define APB1_TIM_CLK   ((HSI_VALUE * PLLMUL) / (HPRE * PPRE))
#    define APB2_TIM_CLK   ((HSI_VALUE * PLLMUL) / (HPRE * PPRE))
#  endif
#endif

#if defined(RCC_CFGR_PLLSRC_HSI_PREDIV) && (PLLSRC == RCC_CFGR_PLLSRC_HSI_PREDIV)
#  define SYSCLK    ((HSI_VALUE * PLLMUL) / (PREDIV              ))
#  define HCLK      ((HSI_VALUE * PLLMUL) / (PREDIV * HPRE       ))
#  define APB1_CLK  ((HSI_VALUE * PLLMUL) / (PREDIV * HPRE * PPRE))
#  define APB2_CLK  ((HSI_VALUE * PLLMUL) / (PREDIV * HPRE * PPRE))

#  if (PPRE == 1)
#    define APB1_TIM_CLK   APB1_CLK
#    define APB2_TIM_CLK   APB2_CLK
#  else
#    define APB1_TIM_CLK   ((HSI_VALUE * PLLMUL * 2u) / (PREDIV * HPRE * PPRE))
#    define APB2_TIM_CLK   ((HSI_VALUE * PLLMUL * 2u) / (PREDIV * HPRE * PPRE))
#  endif
#endif

#if (PLLSRC == RCC_CFGR_PLLSRC_HSE_PREDIV)
#  define SYSCLK    ((HSE_VALUE * PLLMUL) / (PREDIV              ))
#  define HCLK      ((HSE_VALUE * PLLMUL) / (PREDIV * HPRE       ))
#  define APB1_CLK  ((HSE_VALUE * PLLMUL) / (PREDIV * HPRE * PPRE))
#  define APB2_CLK  ((HSE_VALUE * PLLMUL) / (PREDIV * HPRE * PPRE))

#  if (PPRE == 1)
#    define APB1_TIM_CLK   APB1_CLK
#    define APB2_TIM_CLK   APB2_CLK
#  else
#    define APB1_TIM_CLK   ((HSE_VALUE * PLLMUL * 2u) / (PREDIV * HPRE * PPRE))
#    define APB2_TIM_CLK   ((HSE_VALUE * PLLMUL * 2u) / (PREDIV * HPRE * PPRE))
#  endif
#endif

#if defined(RCC_CFGR_PLLSRC_HSI48_PREDIV) && (PLLSRC == RCC_CFGR_PLLSRC_HSI48_PREDIV)
#  define SYSCLK    ((HSI48_VALUE * PLLMUL) / (PREDIV              ))
#  define HCLK      ((HSI48_VALUE * PLLMUL) / (PREDIV * HPRE       ))
#  define APB1_CLK  ((HSI48_VALUE * PLLMUL) / (PREDIV * HPRE * PPRE))
#  define APB2_CLK  ((HSI48_VALUE * PLLMUL) / (PREDIV * HPRE * PPRE))

#  if (PPRE == 1)
#    define APB1_TIM_CLK   APB1_CLK
#    define APB2_TIM_CLK   APB2_CLK
#  else
#    define APB1_TIM_CLK   ((HSI48_VALUE * PLLMUL * 2u) / (PREDIV * HPRE * PPRE))
#    define APB2_TIM_CLK   ((HSI48_VALUE * PLLMUL * 2u) / (PREDIV * HPRE * PPRE))
#  endif
#endif

#define TIM1_CLK  APB2_TIM_CLK
#define TIM2_CLK  APB1_TIM_CLK
#define TIM3_CLK  APB1_TIM_CLK
#define TIM6_CLK  APB1_TIM_CLK
#define TIM7_CLK  APB1_TIM_CLK
#define TIM14_CLK APB1_TIM_CLK
#define TIM15_CLK APB2_TIM_CLK
#define TIM16_CLK APB2_TIM_CLK
#define TIM17_CLK APB2_TIM_CLK

#endif /* STM32F0XX_CLOCKS_H_INCLUDED */
