// stm32f0xx_missing.h
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

/* constants that should have been in stm32f0xx.h */

#ifndef STM32F0XX_MISSING_H_INCLUDED
#define STM32F0XX_MISSING_H_INCLUDED

/* oldest */
#ifdef STM32F0XX
#error replace definition of STM32F0XX with STM32F051x8
#endif

/* older */
#ifdef STM32F030X6
#error replace definition of STM32F030X6 with STM32F030x6
#endif

#ifdef STM32F030X8
#error replace definition of STM32F030X8 with STM32F030x8
#endif

#ifdef STM32F0XX_LD
#error replace definition of STM32F0XX_LD with STM32F031x6
#endif

#ifdef STM32F0XX_MD
#error replace definition of STM32F0XX_MD with STM32F051x8
#endif

#ifdef STM32F0XX_HD
#error replace definition of STM32F0XX_HD with STM32F072xB
#endif

/* old */
#ifdef STM32F030
#error replace definition of STM32F030 with STM32F030x6 or STM32F030x8
#endif

#ifdef STM32F031
#error replace definition of STM32F031 with STM32F031x6
#endif

#ifdef STM32F042
#error replace definition of STM32F042 with STM32F042x6
#endif

#ifdef STM32F051
#error replace definition of STM32F051 with STM32F051x8
#endif

#ifdef STM32F072
#error replace definition of STM32F072 with STM32F072xB
#endif

/* current */
#if !defined (STM32F030x6) && !defined (STM32F030x8) &&                           \
    !defined (STM32F031x6) && !defined (STM32F038xx) &&                           \
    !defined (STM32F042x6) && !defined (STM32F048xx) && !defined (STM32F070x6) && \
    !defined (STM32F051x8) && !defined (STM32F058xx) &&                           \
    !defined (STM32F071xB) && !defined (STM32F072xB) && !defined (STM32F078xx) && !defined (STM32F070xB) && \
    !defined (STM32F091xC) && !defined (STM32F098xx) && !defined (STM32F030xC)
#error no STM32F0xxx part number macro defined
#endif

#include "stm32f0xx.h"

#ifndef HSI48_VALUE
#define HSI48_VALUE     48000000u
#endif

#ifndef LSI_VALUE
#define LSI_VALUE          40000u
#endif

#ifndef HSI_VALUE
#define HSI_VALUE        8000000u
#endif

#ifndef HSI14_VALUE
#define HSI14_VALUE     14000000u
#endif

#define                    TIM_CR2_MMS_RESET   (                                            0)
#define                   TIM_CR2_MMS_ENABLE   (                                TIM_CR2_MMS_0)
#define                   TIM_CR2_MMS_UPDATE   (                TIM_CR2_MMS_1                )
#define                      TIM_CR2_MMS_CC1   (                TIM_CR2_MMS_1 | TIM_CR2_MMS_0)
#define                      TIM_CR2_MMS_OC1   (TIM_CR2_MMS_2                                )
#define                      TIM_CR2_MMS_OC2   (TIM_CR2_MMS_2                 | TIM_CR2_MMS_0)
#define                      TIM_CR2_MMS_OC3   (TIM_CR2_MMS_2 | TIM_CR2_MMS_1                )
#define                      TIM_CR2_MMS_OC4   (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0)
#define                     TIM_SMCR_TS_ITR0   (                                                     0)
#define                     TIM_SMCR_TS_ITR1   (                                         TIM_SMCR_TS_0)
#define                     TIM_SMCR_TS_ITR2   (                      TIM_SMCR_TS_1                   )
#define                     TIM_SMCR_TS_ITR3   (                      TIM_SMCR_TS_1 |    TIM_SMCR_TS_0)

#define                    TIM1_SMCR_TS_TIM15  TIM_SMCR_TS_ITR0
#define                    TIM1_SMCR_TS_TIM2   TIM_SMCR_TS_ITR1
#define                    TIM1_SMCR_TS_TIM3   TIM_SMCR_TS_ITR2
#define                    TIM1_SMCR_TS_TIM17  TIM_SMCR_TS_ITR3
#define                    TIM2_SMCR_TS_TIM1   TIM_SMCR_TS_ITR0
#define                    TIM2_SMCR_TS_TIM15  TIM_SMCR_TS_ITR1
#define                    TIM2_SMCR_TS_TIM3   TIM_SMCR_TS_ITR2
#define                    TIM2_SMCR_TS_TIM14  TIM_SMCR_TS_ITR3
#define                    TIM3_SMCR_TS_TIM1   TIM_SMCR_TS_ITR0
#define                    TIM3_SMCR_TS_TIM2   TIM_SMCR_TS_ITR1
#define                    TIM3_SMCR_TS_TIM15  TIM_SMCR_TS_ITR2
#define                    TIM3_SMCR_TS_TIM14  TIM_SMCR_TS_ITR3
#define                   TIM15_SMCR_TS_TIM2   TIM_SMCR_TS_ITR0
#define                   TIM15_SMCR_TS_TIM3   TIM_SMCR_TS_ITR1
#define                   TIM15_SMCR_TS_TIM16  TIM_SMCR_TS_ITR2
#define                   TIM15_SMCR_TS_TIM17  TIM_SMCR_TS_ITR3

#define                  TIM_SMCR_TS_TI1F_ED   (   TIM_SMCR_TS_2                                      )
#define                   TIM_SMCR_TS_TI1FP1   (   TIM_SMCR_TS_2                    |    TIM_SMCR_TS_0)
#define                   TIM_SMCR_TS_TI2FP2   (   TIM_SMCR_TS_2 |    TIM_SMCR_TS_1                   )
#define                     TIM_SMCR_TS_ETRF   (   TIM_SMCR_TS_2 |    TIM_SMCR_TS_1 |    TIM_SMCR_TS_0)
#define                TIM_SMCR_SMS_DISABLED   (                                                     0)
#define           TIM_SMCR_SMS_ENCODER_MODE1   (                                        TIM_SMCR_SMS_0)
#define           TIM_SMCR_SMS_ENCODER_MODE2   (                     TIM_SMCR_SMS_1                   )
#define           TIM_SMCR_SMS_ENCODER_MODE3   (                     TIM_SMCR_SMS_1 |   TIM_SMCR_SMS_0)
#define                   TIM_SMCR_SMS_RESET   (  TIM_SMCR_SMS_2                                      )
#define                   TIM_SMCR_SMS_GATED   (  TIM_SMCR_SMS_2                    |   TIM_SMCR_SMS_0)
#define                 TIM_SMCR_SMS_TRIGGER   (  TIM_SMCR_SMS_2 |   TIM_SMCR_SMS_1                   )
#define              TIM_SMCR_SMS_ECLK_MODE1   (  TIM_SMCR_SMS_2 |   TIM_SMCR_SMS_1 |   TIM_SMCR_SMS_0)
#define                TIM_CCMR1_OC1M_FROZEN   (                                                     0)
#define                TIM_CCMR1_OC2M_FROZEN   (                                                     0)
#define                TIM_CCMR2_OC3M_FROZEN   (                                                     0)
#define                TIM_CCMR2_OC4M_FROZEN   (                                                     0)
#define          TIM_CCMR1_OC1M_MATCH_ACTIVE   (                                      TIM_CCMR1_OC1M_0)
#define          TIM_CCMR1_OC2M_MATCH_ACTIVE   (                                      TIM_CCMR1_OC2M_0)
#define          TIM_CCMR2_OC3M_MATCH_ACTIVE   (                                      TIM_CCMR2_OC3M_0)
#define          TIM_CCMR2_OC4M_MATCH_ACTIVE   (                                      TIM_CCMR2_OC4M_0)
#define        TIM_CCMR1_OC1M_MATCH_INACTIVE   (                   TIM_CCMR1_OC1M_1                   )
#define        TIM_CCMR1_OC2M_MATCH_INACTIVE   (                   TIM_CCMR1_OC2M_1                   )
#define        TIM_CCMR2_OC3M_MATCH_INACTIVE   (                   TIM_CCMR2_OC3M_1                   )
#define        TIM_CCMR2_OC4M_MATCH_INACTIVE   (                   TIM_CCMR2_OC4M_1                   )
#define          TIM_CCMR1_OC1M_MATCH_TOGGLE   (                   TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)
#define          TIM_CCMR1_OC2M_MATCH_TOGGLE   (                   TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0)
#define          TIM_CCMR2_OC3M_MATCH_TOGGLE   (                   TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0)
#define          TIM_CCMR2_OC4M_MATCH_TOGGLE   (                   TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0)
#define        TIM_CCMR1_OC1M_FORCE_INACTIVE   (TIM_CCMR1_OC1M_2                                      )
#define        TIM_CCMR1_OC2M_FORCE_INACTIVE   (TIM_CCMR1_OC2M_2                                      )
#define        TIM_CCMR2_OC3M_FORCE_INACTIVE   (TIM_CCMR2_OC3M_2                                      )
#define        TIM_CCMR2_OC4M_FORCE_INACTIVE   (TIM_CCMR2_OC4M_2                                      )
#define          TIM_CCMR1_OC1M_FORCE_ACTIVE   (TIM_CCMR1_OC1M_2                    | TIM_CCMR1_OC1M_0)
#define          TIM_CCMR1_OC2M_FORCE_ACTIVE   (TIM_CCMR1_OC2M_2                    | TIM_CCMR1_OC2M_0)
#define          TIM_CCMR2_OC3M_FORCE_ACTIVE   (TIM_CCMR2_OC3M_2                    | TIM_CCMR2_OC3M_0)
#define          TIM_CCMR2_OC4M_FORCE_ACTIVE   (TIM_CCMR2_OC4M_2                    | TIM_CCMR2_OC4M_0)
#define             TIM_CCMR1_OC1M_PWM_MODE1   (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1                   )
#define             TIM_CCMR1_OC2M_PWM_MODE1   (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1                   )
#define             TIM_CCMR2_OC3M_PWM_MODE1   (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1                   )
#define             TIM_CCMR2_OC4M_PWM_MODE1   (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1                   )
#define             TIM_CCMR1_OC1M_PWM_MODE2   (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)
#define             TIM_CCMR1_OC2M_PWM_MODE2   (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0)
#define             TIM_CCMR2_OC3M_PWM_MODE2   (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0)
#define             TIM_CCMR2_OC4M_PWM_MODE2   (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0)
#define                   TIM_CCMR1_CC1S_OC1   (                                  0)
#define                   TIM_CCMR1_CC2S_OC2   (                                  0)
#define                   TIM_CCMR2_CC3S_OC3   (                                  0)
#define                   TIM_CCMR2_CC4S_OC4   (                                  0)
#define                   TIM_CCMR1_CC1S_TI1   (                   TIM_CCMR1_CC1S_0)
#define                   TIM_CCMR1_CC2S_TI2   (                   TIM_CCMR1_CC2S_0)
#define                   TIM_CCMR2_CC3S_TI3   (                   TIM_CCMR2_CC3S_0)
#define                   TIM_CCMR2_CC4S_TI4   (                   TIM_CCMR2_CC4S_0)
#define                   TIM_CCMR1_CC1S_TI2   (TIM_CCMR1_CC1S_1                   )
#define                   TIM_CCMR1_CC2S_TI1   (TIM_CCMR1_CC2S_1                   )
#define                   TIM_CCMR2_CC3S_TI4   (TIM_CCMR2_CC3S_1                   )
#define                   TIM_CCMR2_CC4S_TI3   (TIM_CCMR2_CC4S_1                   )
#define                   TIM_CCMR1_CC1S_TRC   (TIM_CCMR1_CC1S_1 | TIM_CCMR1_CC1S_0)
#define                   TIM_CCMR1_CC2S_TRC   (TIM_CCMR1_CC2S_1 | TIM_CCMR1_CC2S_0)
#define                   TIM_CCMR2_CC3S_TRC   (TIM_CCMR2_CC3S_1 | TIM_CCMR2_CC3S_0)
#define                   TIM_CCMR2_CC4S_TRC   (TIM_CCMR2_CC4S_1 | TIM_CCMR2_CC4S_0)

#define  SPI_CR1_BR_DIV2    (                                         0)
#define  SPI_CR1_BR_DIV4    (                              SPI_CR1_BR_0)
#define  SPI_CR1_BR_DIV8    (               SPI_CR1_BR_1               )
#define  SPI_CR1_BR_DIV16   (               SPI_CR1_BR_1 | SPI_CR1_BR_0)
#define  SPI_CR1_BR_DIV32   (SPI_CR1_BR_2                              )
#define  SPI_CR1_BR_DIV64   (SPI_CR1_BR_2                | SPI_CR1_BR_0)
#define  SPI_CR1_BR_DIV128  (SPI_CR1_BR_2 | SPI_CR1_BR_1               )
#define  SPI_CR1_BR_DIV256  (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)

#define DMA_CCR_PSIZE_8BIT   0
#define DMA_CCR_PSIZE_16BIT  DMA_CCR_PSIZE_0
#define DMA_CCR_PSIZE_32BIT  DMA_CCR_PSIZE_1

#define DMA_CCR_MSIZE_8BIT   0
#define DMA_CCR_MSIZE_16BIT  DMA_CCR_MSIZE_0
#define DMA_CCR_MSIZE_32BIT  DMA_CCR_MSIZE_1

#define DMA_CCR_PL_LOW     (                          0)
#define DMA_CCR_PL_MEDIUM  (               DMA_CCR_PL_0)
#define DMA_CCR_PL_HIGH    (DMA_CCR_PL_1               )
#define DMA_CCR_PL_VHIGH   (DMA_CCR_PL_1 | DMA_CCR_PL_0)

#define DAC_CR_TSEL1_TIM6       (                                               0)
#define DAC_CR_TSEL1_TIM3       (                                  DAC_CR_TSEL1_0)
#define DAC_CR_TSEL1_TIM7       (                 DAC_CR_TSEL1_1                 )
#define DAC_CR_TSEL1_TIM15      (                 DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0)
#define DAC_CR_TSEL1_TIM2       (DAC_CR_TSEL1_2                                  )
#define DAC_CR_TSEL1_EXTI9      (DAC_CR_TSEL1_2 | DAC_CR_TSEL1_1                 )
#define DAC_CR_TSEL1_SW         (DAC_CR_TSEL1_2 | DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0)

#define ADC_CFGR1_EXTEN_NONE    (ADC_CFGR1_EXTEN_0 * 0)
#define ADC_CFGR1_EXTEN_RISING  (ADC_CFGR1_EXTEN_0 * 1)
#define ADC_CFGR1_EXTEN_FALLING (ADC_CFGR1_EXTEN_0 * 2)
#define ADC_CFGR1_EXTEN_BOTH    (ADC_CFGR1_EXTEN_0 * 3)

#define ADC_CFGR1_EXTSEL_TIM1_TRGO   (ADC_CFGR1_EXTSEL_0 * 0)
#define ADC_CFGR1_EXTSEL_TIM1_CC4    (ADC_CFGR1_EXTSEL_0 * 1)
#define ADC_CFGR1_EXTSEL_TIM2_TRGO   (ADC_CFGR1_EXTSEL_0 * 2)
#define ADC_CFGR1_EXTSEL_TIM3_TRGO   (ADC_CFGR1_EXTSEL_0 * 3)
#define ADC_CFGR1_EXTSEL_TIM15_TRGO  (ADC_CFGR1_EXTSEL_0 * 4)

#define ADC_CFGR2_CKMODE_ADCCLK    (ADC_CFGR2_CKMODE_0 * 0)
#define ADC_CFGR2_CKMODE_PCLK_DIV2 (ADC_CFGR2_CKMODE_0 * 1)
#define ADC_CFGR2_CKMODE_PCLK_DIV4 (ADC_CFGR2_CKMODE_0 * 2)

#define ADC_SMPR_SMP_1_5_CLK    (ADC_SMPR_SMP_0 * 0)
#define ADC_SMPR_SMP_7_5_CLK    (ADC_SMPR_SMP_0 * 1)
#define ADC_SMPR_SMP_13_5_CLK   (ADC_SMPR_SMP_0 * 2)
#define ADC_SMPR_SMP_28_5_CLK   (ADC_SMPR_SMP_0 * 3)
#define ADC_SMPR_SMP_41_5_CLK   (ADC_SMPR_SMP_0 * 4)
#define ADC_SMPR_SMP_55_5_CLK   (ADC_SMPR_SMP_0 * 5)
#define ADC_SMPR_SMP_71_5_CLK   (ADC_SMPR_SMP_0 * 6)
#define ADC_SMPR_SMP_239_5_CLK  (ADC_SMPR_SMP_0 * 7)

#endif /* STM32F0XX_MISSING_H_INCLUDED */
