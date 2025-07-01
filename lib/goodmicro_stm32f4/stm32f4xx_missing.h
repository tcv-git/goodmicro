// stm32f4xx_missing.h
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

/* constants that should have been in stm32f4xx.h */

#ifndef STM32F4XX_MISSING_H_INCLUDED
#define STM32F4XX_MISSING_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// #############################################################################
//
//      check part number macro
//
// #############################################################################

/* oldest */
#ifdef STM32F4XX
#error replace definition of STM32F4XX with eg: STM32F405xx
#endif

/* older */
#ifdef STM32F40XX
#error replace definition of STM32F40XX with STM32F405xx, STM32F415xx, STM32F407xx, or STM32F417xx
#endif

#ifdef STM32F427X
#error replace definition of STM32F427X with either STM32F427xx or STM32F437xx
#endif

/* old */
#ifdef STM32F40_41xxx
#error replace definition of STM32F40_41xxx with STM32F405xx, STM32F415xx, STM32F407xx, or STM32F417xx
#endif

#ifdef STM32F427_437xx
#error replace definition of STM32F427_437xx with either STM32F427xx or STM32F437xx
#endif

#ifdef STM32F429_439xx
#error replace definition of STM32F429_439xx with either STM32F429xx or STM32F439xx
#endif

#ifdef STM32F401xx
#error replace definition of STM32F401xx with either STM32F401xC or STM32F401xE
#endif


// #############################################################################
//
//      Device electronic signature
//
// #############################################################################

typedef struct
{
  uint32_t UDIDR[3];    /*!< Unique device ID register */
  uint16_t RESERVED[3];
  uint16_t FSIZER;      /*!< Flash size register       */
} DES_TypeDef;

#define DES_BASE                                0x1FFF7A10u
#define DES                                     ((const DES_TypeDef*)DES_BASE)


// #############################################################################
//
//      RCC parameter constants
//
// #############################################################################

#define HSI_VALUE                               16000000u

#define USBCLK_MAX                              48000000u

#define RCC_PLLM_MIN_VALUE                             2u
#define RCC_PLLM_MAX_VALUE                            63u
#define RCC_PLLQ_MIN_VALUE                             2u
#define RCC_PLLQ_MAX_VALUE                            15u


// #############################################################################
//
//      RCC register values
//
// #############################################################################

#define RCC_CR_HSITRIM_Default                  RCC_CR_HSITRIM_4

#define RCC_CR_HSEBYP_DISABLE                   (0u << RCC_CR_HSEBYP_Pos)
#define RCC_CR_HSEBYP_ENABLE                    (1u << RCC_CR_HSEBYP_Pos)

#define RCC_CFGR_MCO1_HSI                       (0u << RCC_CFGR_MCO1_Pos)
#define RCC_CFGR_MCO1_LSE                       (1u << RCC_CFGR_MCO1_Pos)
#define RCC_CFGR_MCO1_HSE                       (2u << RCC_CFGR_MCO1_Pos)
#define RCC_CFGR_MCO1_PLL                       (3u << RCC_CFGR_MCO1_Pos)
#define RCC_CFGR_MCO2_SYSCLK                    (0u << RCC_CFGR_MCO2_Pos)
#define RCC_CFGR_MCO2_PLLI2S                    (1u << RCC_CFGR_MCO2_Pos)
#define RCC_CFGR_MCO2_HSE                       (2u << RCC_CFGR_MCO2_Pos)
#define RCC_CFGR_MCO2_PLL                       (3u << RCC_CFGR_MCO2_Pos)

#define RCC_CFGR_MCO1PRE_DIV1                   (0u << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO1PRE_DIV2                   (4u << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO1PRE_DIV3                   (5u << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO1PRE_DIV4                   (6u << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO1PRE_DIV5                   (7u << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO2PRE_DIV1                   (0u << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_MCO2PRE_DIV2                   (4u << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_MCO2PRE_DIV3                   (5u << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_MCO2PRE_DIV4                   (6u << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_MCO2PRE_DIV5                   (7u << RCC_CFGR_MCO2PRE_Pos)

#ifdef RCC_DCKCFGR_PLLSAIDIVR_Pos
#define RCC_DCKCFGR_PLLSAIDIVR_DIV2             (0u << RCC_DCKCFGR_PLLSAIDIVR_Pos)
#define RCC_DCKCFGR_PLLSAIDIVR_DIV4             (1u << RCC_DCKCFGR_PLLSAIDIVR_Pos)
#define RCC_DCKCFGR_PLLSAIDIVR_DIV8             (2u << RCC_DCKCFGR_PLLSAIDIVR_Pos)
#define RCC_DCKCFGR_PLLSAIDIVR_DIV16            (3u << RCC_DCKCFGR_PLLSAIDIVR_Pos)
#endif


// #############################################################################
//
//      PWR register values
//
// #############################################################################

#if (defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx))
#define PWR_CR_VOS_SCALE2                       (0u << PWR_CR_VOS_Pos)  // low power
#define PWR_CR_VOS_SCALE1                       (1u << PWR_CR_VOS_Pos)  // high power, default
#endif

#if (defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx))
#define PWR_CR_VOS_SCALE3                       (1u << PWR_CR_VOS_Pos)  // low power
#define PWR_CR_VOS_SCALE2                       (2u << PWR_CR_VOS_Pos)
#define PWR_CR_VOS_SCALE1                       (3u << PWR_CR_VOS_Pos)  // high power, default
#endif

#define PWR_CR_ODEN_DISABLE                     (0u << PWR_CR_ODEN_Pos)
#define PWR_CR_ODEN_ENABLE                      (1u << PWR_CR_ODEN_Pos)


// #############################################################################
//
//      SYSCFG register values
//
// #############################################################################

#define SYSCFG_CMPCR_CMP_PD_DISABLE             (0u << SYSCFG_CMPCR_CMP_PD_Pos)
#define SYSCFG_CMPCR_CMP_PD_ENABLE              (1u << SYSCFG_CMPCR_CMP_PD_Pos)


// #############################################################################
//
//      FLASH register values
//
// #############################################################################

#define FLASH_CR_ERRIE_Pos                      (25U)
#define FLASH_CR_ERRIE_Msk                      (0x1UL << FLASH_CR_ERRIE_Pos)            /*!< 0x02000000 */
#define FLASH_CR_ERRIE                          FLASH_CR_ERRIE_Msk

#define FLASH_CR_PSIZE_8BIT                     ( 0u << FLASH_CR_PSIZE_Pos)
#define FLASH_CR_PSIZE_16BIT                    ( 1u << FLASH_CR_PSIZE_Pos)
#define FLASH_CR_PSIZE_32BIT                    ( 2u << FLASH_CR_PSIZE_Pos)
#define FLASH_CR_PSIZE_64BIT                    ( 3u << FLASH_CR_PSIZE_Pos)


// #############################################################################
//
//      DMA register values
//
// #############################################################################

#define DMA_LIFCR_ALL0                          (DMA_LIFCR_CTCIF0 | DMA_LIFCR_CHTIF0 | DMA_LIFCR_CTEIF0 | DMA_LIFCR_CDMEIF0 | DMA_LIFCR_CFEIF0)
#define DMA_LIFCR_ALL1                          (DMA_LIFCR_CTCIF1 | DMA_LIFCR_CHTIF1 | DMA_LIFCR_CTEIF1 | DMA_LIFCR_CDMEIF1 | DMA_LIFCR_CFEIF1)
#define DMA_LIFCR_ALL2                          (DMA_LIFCR_CTCIF2 | DMA_LIFCR_CHTIF2 | DMA_LIFCR_CTEIF2 | DMA_LIFCR_CDMEIF2 | DMA_LIFCR_CFEIF2)
#define DMA_LIFCR_ALL3                          (DMA_LIFCR_CTCIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CFEIF3)
#define DMA_HIFCR_ALL4                          (DMA_HIFCR_CTCIF4 | DMA_HIFCR_CHTIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CFEIF4)
#define DMA_HIFCR_ALL5                          (DMA_HIFCR_CTCIF5 | DMA_HIFCR_CHTIF5 | DMA_HIFCR_CTEIF5 | DMA_HIFCR_CDMEIF5 | DMA_HIFCR_CFEIF5)
#define DMA_HIFCR_ALL6                          (DMA_HIFCR_CTCIF6 | DMA_HIFCR_CHTIF6 | DMA_HIFCR_CTEIF6 | DMA_HIFCR_CDMEIF6 | DMA_HIFCR_CFEIF6)
#define DMA_HIFCR_ALL7                          (DMA_HIFCR_CTCIF7 | DMA_HIFCR_CHTIF7 | DMA_HIFCR_CTEIF7 | DMA_HIFCR_CDMEIF7 | DMA_HIFCR_CFEIF7)

#define DMA_SxCR_CHSEL_CH0                      (0u << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_CH1                      (1u << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_CH2                      (2u << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_CH3                      (3u << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_CH4                      (4u << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_CH5                      (5u << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_CH6                      (6u << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_CH7                      (7u << DMA_SxCR_CHSEL_Pos)

#define DMA1_S0CR_CHSEL_SPI3_RX                 DMA_SxCR_CHSEL_CH0
#define DMA1_S0CR_CHSEL_I2C1_RX                 DMA_SxCR_CHSEL_CH1
#define DMA1_S0CR_CHSEL_TIM4_CH1                DMA_SxCR_CHSEL_CH2
#define DMA1_S0CR_CHSEL_I2S3_EXT_RX             DMA_SxCR_CHSEL_CH3
#define DMA1_S0CR_CHSEL_UART5_RX                DMA_SxCR_CHSEL_CH4
#define DMA1_S0CR_CHSEL_UART8_TX                DMA_SxCR_CHSEL_CH5
#define DMA1_S0CR_CHSEL_TIM5_CH3_UP             DMA_SxCR_CHSEL_CH6
                     // NONE                    DMA_SxCR_CHSEL_CH7
                     // NONE                    DMA_SxCR_CHSEL_CH0
                     // NONE                    DMA_SxCR_CHSEL_CH1
                     // NONE                    DMA_SxCR_CHSEL_CH2
#define DMA1_S1CR_CHSEL_TIM2_UP_CH3             DMA_SxCR_CHSEL_CH3
#define DMA1_S1CR_CHSEL_USART3_RX               DMA_SxCR_CHSEL_CH4
#define DMA1_S1CR_CHSEL_UART7_TX                DMA_SxCR_CHSEL_CH5
#define DMA1_S1CR_CHSEL_TIM5_CH4_TRIG           DMA_SxCR_CHSEL_CH6
#define DMA1_S1CR_CHSEL_TIM6_UP                 DMA_SxCR_CHSEL_CH7
#define DMA1_S2CR_CHSEL_SPI3_RX                 DMA_SxCR_CHSEL_CH0
#define DMA1_S2CR_CHSEL_TIM7_UP                 DMA_SxCR_CHSEL_CH1
#define DMA1_S2CR_CHSEL_I2S3_EXT_RX             DMA_SxCR_CHSEL_CH2
#define DMA1_S2CR_CHSEL_I2C3_RX                 DMA_SxCR_CHSEL_CH3
#define DMA1_S2CR_CHSEL_UART4_RX                DMA_SxCR_CHSEL_CH4
#define DMA1_S2CR_CHSEL_TIM3_CH4_UP             DMA_SxCR_CHSEL_CH5
#define DMA1_S2CR_CHSEL_TIM5_CH1                DMA_SxCR_CHSEL_CH6
#define DMA1_S2CR_CHSEL_I2C2_RX                 DMA_SxCR_CHSEL_CH7
#define DMA1_S3CR_CHSEL_SPI2_RX                 DMA_SxCR_CHSEL_CH0
                     // NONE                    DMA_SxCR_CHSEL_CH1
#define DMA1_S3CR_CHSEL_TIM4_CH2                DMA_SxCR_CHSEL_CH2
#define DMA1_S3CR_CHSEL_I2S2_EXT_RX             DMA_SxCR_CHSEL_CH3
#define DMA1_S3CR_CHSEL_USART3_TX               DMA_SxCR_CHSEL_CH4
#define DMA1_S3CR_CHSEL_UART7_RX                DMA_SxCR_CHSEL_CH5
#define DMA1_S3CR_CHSEL_TIM5_CH4_TRIG           DMA_SxCR_CHSEL_CH6
#define DMA1_S3CR_CHSEL_I2C2_RX                 DMA_SxCR_CHSEL_CH7
#define DMA1_S4CR_CHSEL_SPI2_TX                 DMA_SxCR_CHSEL_CH0
#define DMA1_S4CR_CHSEL_TIM7_UP                 DMA_SxCR_CHSEL_CH1
#define DMA1_S4CR_CHSEL_I2S2_EXT_TX             DMA_SxCR_CHSEL_CH2
#define DMA1_S4CR_CHSEL_I2C3_TX                 DMA_SxCR_CHSEL_CH3
#define DMA1_S4CR_CHSEL_UART4_TX                DMA_SxCR_CHSEL_CH4
#define DMA1_S4CR_CHSEL_TIM3_CH1_TRIG           DMA_SxCR_CHSEL_CH5
#define DMA1_S4CR_CHSEL_TIM5_CH2                DMA_SxCR_CHSEL_CH6
#define DMA1_S4CR_CHSEL_USRART3_TX              DMA_SxCR_CHSEL_CH7
#define DMA1_S5CR_CHSEL_SPI3_TX                 DMA_SxCR_CHSEL_CH0
#define DMA1_S5CR_CHSEL_I2C1_RX                 DMA_SxCR_CHSEL_CH1
#define DMA1_S5CR_CHSEL_I2S3_EXT_TX             DMA_SxCR_CHSEL_CH2
#define DMA1_S5CR_CHSEL_TIM2_CH1                DMA_SxCR_CHSEL_CH3
#define DMA1_S5CR_CHSEL_USART2_RX               DMA_SxCR_CHSEL_CH4
#define DMA1_S5CR_CHSEL_TIM3_CH2                DMA_SxCR_CHSEL_CH5
                     // NONE                    DMA_SxCR_CHSEL_CH6
#define DMA1_S5CR_CHSEL_DAC1                    DMA_SxCR_CHSEL_CH7
                     // NONE                    DMA_SxCR_CHSEL_CH0
#define DMA1_S6CR_CHSEL_I2C1_TX                 DMA_SxCR_CHSEL_CH1
#define DMA1_S6CR_CHSEL_TIM4_UP                 DMA_SxCR_CHSEL_CH2
#define DMA1_S6CR_CHSEL_TIM2_CH2_CH4            DMA_SxCR_CHSEL_CH3
#define DMA1_S6CR_CHSEL_USART2_TX               DMA_SxCR_CHSEL_CH4
#define DMA1_S6CR_CHSEL_UART8_RX                DMA_SxCR_CHSEL_CH5
#define DMA1_S6CR_CHSEL_TIM5_UP                 DMA_SxCR_CHSEL_CH6
#define DMA1_S6CR_CHSEL_DAC2                    DMA_SxCR_CHSEL_CH7
#define DMA1_S7CR_CHSEL_SPI3_TX                 DMA_SxCR_CHSEL_CH0
#define DMA1_S7CR_CHSEL_I2C1_TX                 DMA_SxCR_CHSEL_CH1
#define DMA1_S7CR_CHSEL_TIM4_CH3                DMA_SxCR_CHSEL_CH2
#define DMA1_S7CR_CHSEL_TIM2_UP_CH4             DMA_SxCR_CHSEL_CH3
#define DMA1_S7CR_CHSEL_UART5_TX                DMA_SxCR_CHSEL_CH4
#define DMA1_S7CR_CHSEL_TIM3_CH3                DMA_SxCR_CHSEL_CH5
                     // NONE                    DMA_SxCR_CHSEL_CH6
#define DMA1_S7CR_CHSEL_I2C2_TX                 DMA_SxCR_CHSEL_CH7
#define DMA2_S0CR_CHSEL_ADC1                    DMA_SxCR_CHSEL_CH0
                     // NONE                    DMA_SxCR_CHSEL_CH1
#define DMA2_S0CR_CHSEL_ADC3                    DMA_SxCR_CHSEL_CH2
#define DMA2_S0CR_CHSEL_SPI1_RX                 DMA_SxCR_CHSEL_CH3
#define DMA2_S0CR_CHSEL_SPI4_RX                 DMA_SxCR_CHSEL_CH4
                     // NONE                    DMA_SxCR_CHSEL_CH5
#define DMA2_S0CR_CHSEL_TIM1_TRIG               DMA_SxCR_CHSEL_CH6
                     // NONE                    DMA_SxCR_CHSEL_CH7
#define DMA2_S1CR_CHSEL_SAI1_A                  DMA_SxCR_CHSEL_CH0
#define DMA2_S1CR_CHSEL_DCMI                    DMA_SxCR_CHSEL_CH1
#define DMA2_S1CR_CHSEL_ADC3                    DMA_SxCR_CHSEL_CH2
                     // NONE                    DMA_SxCR_CHSEL_CH3
#define DMA2_S1CR_CHSEL_SPI4_TX                 DMA_SxCR_CHSEL_CH4
#define DMA2_S1CR_CHSEL_USART6_RX               DMA_SxCR_CHSEL_CH5
#define DMA2_S1CR_CHSEL_TIM1_CH1                DMA_SxCR_CHSEL_CH6
#define DMA2_S1CR_CHSEL_TIM8_UP                 DMA_SxCR_CHSEL_CH7
#define DMA2_S2CR_CHSEL_TIM8_CH1_CH2_CH3        DMA_SxCR_CHSEL_CH0
#define DMA2_S2CR_CHSEL_ADC2                    DMA_SxCR_CHSEL_CH1
                     // NONE                    DMA_SxCR_CHSEL_CH2
#define DMA2_S2CR_CHSEL_SPI1_RX                 DMA_SxCR_CHSEL_CH3
#define DMA2_S2CR_CHSEL_USART1_RX               DMA_SxCR_CHSEL_CH4
#define DMA2_S2CR_CHSEL_USART6_RX               DMA_SxCR_CHSEL_CH5
#define DMA2_S2CR_CHSEL_TIM1_CH2                DMA_SxCR_CHSEL_CH6
#define DMA2_S2CR_CHSEL_TIM8_CH1                DMA_SxCR_CHSEL_CH7
#define DMA2_S3CR_CHSEL_SAI1_A                  DMA_SxCR_CHSEL_CH0
#define DMA2_S3CR_CHSEL_ADC2                    DMA_SxCR_CHSEL_CH1
#define DMA2_S3CR_CHSEL_SPI5_RX                 DMA_SxCR_CHSEL_CH2
#define DMA2_S3CR_CHSEL_SPI1_TX                 DMA_SxCR_CHSEL_CH3
#define DMA2_S3CR_CHSEL_SDIO                    DMA_SxCR_CHSEL_CH4
#define DMA2_S3CR_CHSEL_SPI4_RX                 DMA_SxCR_CHSEL_CH5
#define DMA2_S3CR_CHSEL_TIM1_CH1                DMA_SxCR_CHSEL_CH6
#define DMA2_S3CR_CHSEL_TIM8_CH2                DMA_SxCR_CHSEL_CH7
#define DMA2_S4CR_CHSEL_ADC1                    DMA_SxCR_CHSEL_CH0
#define DMA2_S4CR_CHSEL_SAI1_B                  DMA_SxCR_CHSEL_CH1
#define DMA2_S4CR_CHSEL_SPI5_TX                 DMA_SxCR_CHSEL_CH2
                     // NONE                    DMA_SxCR_CHSEL_CH3
                     // NONE                    DMA_SxCR_CHSEL_CH4
#define DMA2_S4CR_CHSEL_SPI4_TX                 DMA_SxCR_CHSEL_CH5
#define DMA2_S4CR_CHSEL_TIM1_CH4_TRIG_COM       DMA_SxCR_CHSEL_CH6
#define DMA2_S4CR_CHSEL_TIM8_CH3                DMA_SxCR_CHSEL_CH7
#define DMA2_S5CR_CHSEL_SAI1_B                  DMA_SxCR_CHSEL_CH0
#define DMA2_S5CR_CHSEL_SPI6_TX                 DMA_SxCR_CHSEL_CH1
#define DMA2_S5CR_CHSEL_CRYP_OUT                DMA_SxCR_CHSEL_CH2
#define DMA2_S5CR_CHSEL_SPI1_TX                 DMA_SxCR_CHSEL_CH3
#define DMA2_S5CR_CHSEL_USART1_RX               DMA_SxCR_CHSEL_CH4
                     // NONE                    DMA_SxCR_CHSEL_CH5
#define DMA2_S5CR_CHSEL_TIM1_UP                 DMA_SxCR_CHSEL_CH6
#define DMA2_S5CR_CHSEL_SPI5_RX                 DMA_SxCR_CHSEL_CH7
#define DMA2_S6CR_CHSEL_TIM1_CH1_CH2_CH3        DMA_SxCR_CHSEL_CH0
#define DMA2_S6CR_CHSEL_SPI6_RX                 DMA_SxCR_CHSEL_CH1
#define DMA2_S6CR_CHSEL_CRYP_IN                 DMA_SxCR_CHSEL_CH2
                     // NONE                    DMA_SxCR_CHSEL_CH3
#define DMA2_S6CR_CHSEL_SDIO                    DMA_SxCR_CHSEL_CH4
#define DMA2_S6CR_CHSEL_USART6_TX               DMA_SxCR_CHSEL_CH5
#define DMA2_S6CR_CHSEL_TIM1_CH3                DMA_SxCR_CHSEL_CH6
#define DMA2_S6CR_CHSEL_SPI5_TX                 DMA_SxCR_CHSEL_CH7
                     // NONE                    DMA_SxCR_CHSEL_CH0
#define DMA2_S7CR_CHSEL_DCMI                    DMA_SxCR_CHSEL_CH1
#define DMA2_S7CR_CHSEL_HASH_IN                 DMA_SxCR_CHSEL_CH2
                     // NONE                    DMA_SxCR_CHSEL_CH3
#define DMA2_S7CR_CHSEL_USART1_TX               DMA_SxCR_CHSEL_CH4
#define DMA2_S7CR_CHSEL_USART6_TX               DMA_SxCR_CHSEL_CH5
                     // NONE                    DMA_SxCR_CHSEL_CH6
#define DMA2_S7CR_CHSEL_TIM8_CH4_TRIG_COM       DMA_SxCR_CHSEL_CH7

#define DMA_SxCR_MBURST_SINGLE                  (0u << DMA_SxCR_MBURST_Pos)
#define DMA_SxCR_MBURST_INCR4                   (1u << DMA_SxCR_MBURST_Pos)
#define DMA_SxCR_MBURST_INCR8                   (2u << DMA_SxCR_MBURST_Pos)
#define DMA_SxCR_MBURST_INCR16                  (3u << DMA_SxCR_MBURST_Pos)
#define DMA_SxCR_PBURST_SINGLE                  (0u << DMA_SxCR_PBURST_Pos)
#define DMA_SxCR_PBURST_INCR4                   (1u << DMA_SxCR_PBURST_Pos)
#define DMA_SxCR_PBURST_INCR8                   (2u << DMA_SxCR_PBURST_Pos)
#define DMA_SxCR_PBURST_INCR16                  (3u << DMA_SxCR_PBURST_Pos)
#define DMA_SxCR_PL_LOW                         (0u << DMA_SxCR_PL_Pos)
#define DMA_SxCR_PL_MEDIUM                      (1u << DMA_SxCR_PL_Pos)
#define DMA_SxCR_PL_HIGH                        (2u << DMA_SxCR_PL_Pos)
#define DMA_SxCR_PL_VHIGH                       (3u << DMA_SxCR_PL_Pos)
#define DMA_SxCR_MSIZE_8BIT                     (0u << DMA_SxCR_MSIZE_Pos)
#define DMA_SxCR_MSIZE_16BIT                    (1u << DMA_SxCR_MSIZE_Pos)
#define DMA_SxCR_MSIZE_32BIT                    (2u << DMA_SxCR_MSIZE_Pos)
#define DMA_SxCR_PSIZE_8BIT                     (0u << DMA_SxCR_PSIZE_Pos)
#define DMA_SxCR_PSIZE_16BIT                    (1u << DMA_SxCR_PSIZE_Pos)
#define DMA_SxCR_PSIZE_32BIT                    (2u << DMA_SxCR_PSIZE_Pos)
#define DMA_SxCR_DIR_P2M                        (0u << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_DIR_M2P                        (1u << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_DIR_M2M                        (2u << DMA_SxCR_DIR_Pos)


// #############################################################################
//
//      SPI register values
//
// #############################################################################

#define SPI_CR1_BR_DIV2                         (0u << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV4                         (1u << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV8                         (2u << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV16                        (3u << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV32                        (4u << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV64                        (5u << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV128                       (6u << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_DIV256                       (7u << SPI_CR1_BR_Pos)


// #############################################################################
//
//      TIM register values
//
// #############################################################################

#define TIM_CR2_MMS_RESET                       (0u << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_ENABLE                      (1u << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_UPDATE                      (2u << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_CC1                         (3u << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_OC1                         (4u << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_OC2                         (5u << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_OC3                         (6u << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_OC4                         (7u << TIM_CR2_MMS_Pos)

#define TIM_SMCR_TS_ITR0                        (0u << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_ITR1                        (1u << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_ITR2                        (2u << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_ITR3                        (3u << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_TI1F_ED                     (4u << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_TI1FP1                      (5u << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_TI2FP2                      (6u << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_ETRF                        (7u << TIM_SMCR_TS_Pos)
#define TIM_SMCR_SMS_DISABLED                   (0u << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_ENCODER_MODE1              (1u << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_ENCODER_MODE2              (2u << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_ENCODER_MODE3              (3u << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_RESET                      (4u << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_GATED                      (5u << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_TRIGGER                    (6u << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_ECLK_MODE1                 (7u << TIM_SMCR_SMS_Pos)

#define TIM1_SMCR_TS_TIM5                       TIM_SMCR_TS_ITR0
#define TIM1_SMCR_TS_TIM2                       TIM_SMCR_TS_ITR1
#define TIM1_SMCR_TS_TIM3                       TIM_SMCR_TS_ITR2
#define TIM1_SMCR_TS_TIM4                       TIM_SMCR_TS_ITR3
#define TIM8_SMCR_TS_TIM1                       TIM_SMCR_TS_ITR0
#define TIM8_SMCR_TS_TIM2                       TIM_SMCR_TS_ITR1
#define TIM8_SMCR_TS_TIM4                       TIM_SMCR_TS_ITR2
#define TIM8_SMCR_TS_TIM5                       TIM_SMCR_TS_ITR3
#define TIM2_SMCR_TS_TIM1                       TIM_SMCR_TS_ITR0
#define TIM2_SMCR_TS_TIM8                       TIM_SMCR_TS_ITR1
#define TIM2_SMCR_TS_TIM3                       TIM_SMCR_TS_ITR2
#define TIM2_SMCR_TS_TIM4                       TIM_SMCR_TS_ITR3
#define TIM3_SMCR_TS_TIM1                       TIM_SMCR_TS_ITR0
#define TIM3_SMCR_TS_TIM2                       TIM_SMCR_TS_ITR1
#define TIM3_SMCR_TS_TIM5                       TIM_SMCR_TS_ITR2
#define TIM3_SMCR_TS_TIM4                       TIM_SMCR_TS_ITR3
#define TIM4_SMCR_TS_TIM1                       TIM_SMCR_TS_ITR0
#define TIM4_SMCR_TS_TIM2                       TIM_SMCR_TS_ITR1
#define TIM4_SMCR_TS_TIM3                       TIM_SMCR_TS_ITR2
#define TIM4_SMCR_TS_TIM8                       TIM_SMCR_TS_ITR3
#define TIM5_SMCR_TS_TIM2                       TIM_SMCR_TS_ITR0
#define TIM5_SMCR_TS_TIM3                       TIM_SMCR_TS_ITR1
#define TIM5_SMCR_TS_TIM4                       TIM_SMCR_TS_ITR2
#define TIM5_SMCR_TS_TIM8                       TIM_SMCR_TS_ITR3

#define TIM_CCMR1_OC1M_FROZEN                   (0u << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC2M_FROZEN                   (0u << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR2_OC3M_FROZEN                   (0u << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC4M_FROZEN                   (0u << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR1_OC1M_MATCH_ACTIVE             (1u << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC2M_MATCH_ACTIVE             (1u << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR2_OC3M_MATCH_ACTIVE             (1u << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC4M_MATCH_ACTIVE             (1u << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR1_OC1M_MATCH_INACTIVE           (2u << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC2M_MATCH_INACTIVE           (2u << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR2_OC3M_MATCH_INACTIVE           (2u << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC4M_MATCH_INACTIVE           (2u << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR1_OC1M_MATCH_TOGGLE             (3u << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC2M_MATCH_TOGGLE             (3u << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR2_OC3M_MATCH_TOGGLE             (3u << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC4M_MATCH_TOGGLE             (3u << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR1_OC1M_FORCE_INACTIVE           (4u << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC2M_FORCE_INACTIVE           (4u << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR2_OC3M_FORCE_INACTIVE           (4u << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC4M_FORCE_INACTIVE           (4u << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR1_OC1M_FORCE_ACTIVE             (5u << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC2M_FORCE_ACTIVE             (5u << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR2_OC3M_FORCE_ACTIVE             (5u << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC4M_FORCE_ACTIVE             (5u << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR1_OC1M_PWM_MODE1                (6u << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC2M_PWM_MODE1                (6u << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR2_OC3M_PWM_MODE1                (6u << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC4M_PWM_MODE1                (6u << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR1_OC1M_PWM_MODE2                (7u << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC2M_PWM_MODE2                (7u << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR2_OC3M_PWM_MODE2                (7u << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC4M_PWM_MODE2                (7u << TIM_CCMR2_OC4M_Pos)

#define TIM_CCMR1_CC1S_OC1                      (0u << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC2S_OC2                      (0u << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR2_CC3S_OC3                      (0u << TIM_CCMR2_CC3S_Pos)
#define TIM_CCMR2_CC4S_OC4                      (0u << TIM_CCMR2_CC4S_Pos)
#define TIM_CCMR1_CC1S_TI1                      (1u << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC2S_TI2                      (1u << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR2_CC3S_TI3                      (1u << TIM_CCMR2_CC3S_Pos)
#define TIM_CCMR2_CC4S_TI4                      (1u << TIM_CCMR2_CC4S_Pos)
#define TIM_CCMR1_CC1S_TI2                      (2u << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC2S_TI1                      (2u << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR2_CC3S_TI4                      (2u << TIM_CCMR2_CC3S_Pos)
#define TIM_CCMR2_CC4S_TI3                      (2u << TIM_CCMR2_CC4S_Pos)
#define TIM_CCMR1_CC1S_TRC                      (3u << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC2S_TRC                      (3u << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR2_CC3S_TRC                      (3u << TIM_CCMR2_CC3S_Pos)
#define TIM_CCMR2_CC4S_TRC                      (3u << TIM_CCMR2_CC4S_Pos)

#define TIM1_SR_ALL                             (TIM_SR_CC4OF | TIM_SR_CC3OF | TIM_SR_CC2OF | TIM_SR_CC1OF | TIM_SR_BIF | TIM_SR_TIF | TIM_SR_COMIF | TIM_SR_UIF | TIM_SR_CC4IF | TIM_SR_CC3IF | TIM_SR_CC2IF | TIM_SR_CC1IF)
#define TIM3_SR_ALL                             (TIM_SR_CC4OF | TIM_SR_CC3OF | TIM_SR_CC2OF | TIM_SR_CC1OF | TIM_SR_TIF                             | TIM_SR_UIF | TIM_SR_CC4IF | TIM_SR_CC3IF | TIM_SR_CC2IF | TIM_SR_CC1IF)

#define TIM11_OR_TI1_RMP_HSE_RTC                2u


// #############################################################################
//
//      ADC register values
//
// #############################################################################

#define ADC_SMPR2_SMP0_3_CYCLES                 ( 0u << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_15_CYCLES                ( 1u << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_28_CYCLES                ( 2u << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_56_CYCLES                ( 3u << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_84_CYCLES                ( 4u << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_112_CYCLES               ( 5u << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_144_CYCLES               ( 6u << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_480_CYCLES               ( 7u << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP1_3_CYCLES                 ( 0u << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_15_CYCLES                ( 1u << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_28_CYCLES                ( 2u << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_56_CYCLES                ( 3u << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_84_CYCLES                ( 4u << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_112_CYCLES               ( 5u << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_144_CYCLES               ( 6u << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_480_CYCLES               ( 7u << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP2_3_CYCLES                 ( 0u << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_15_CYCLES                ( 1u << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_28_CYCLES                ( 2u << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_56_CYCLES                ( 3u << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_84_CYCLES                ( 4u << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_112_CYCLES               ( 5u << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_144_CYCLES               ( 6u << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_480_CYCLES               ( 7u << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP3_3_CYCLES                 ( 0u << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_15_CYCLES                ( 1u << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_28_CYCLES                ( 2u << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_56_CYCLES                ( 3u << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_84_CYCLES                ( 4u << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_112_CYCLES               ( 5u << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_144_CYCLES               ( 6u << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_480_CYCLES               ( 7u << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP4_3_CYCLES                 ( 0u << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_15_CYCLES                ( 1u << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_28_CYCLES                ( 2u << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_56_CYCLES                ( 3u << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_84_CYCLES                ( 4u << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_112_CYCLES               ( 5u << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_144_CYCLES               ( 6u << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_480_CYCLES               ( 7u << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP5_3_CYCLES                 ( 0u << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_15_CYCLES                ( 1u << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_28_CYCLES                ( 2u << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_56_CYCLES                ( 3u << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_84_CYCLES                ( 4u << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_112_CYCLES               ( 5u << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_144_CYCLES               ( 6u << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_480_CYCLES               ( 7u << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP6_3_CYCLES                 ( 0u << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_15_CYCLES                ( 1u << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_28_CYCLES                ( 2u << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_56_CYCLES                ( 3u << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_84_CYCLES                ( 4u << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_112_CYCLES               ( 5u << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_144_CYCLES               ( 6u << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_480_CYCLES               ( 7u << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP7_3_CYCLES                 ( 0u << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_15_CYCLES                ( 1u << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_28_CYCLES                ( 2u << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_56_CYCLES                ( 3u << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_84_CYCLES                ( 4u << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_112_CYCLES               ( 5u << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_144_CYCLES               ( 6u << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_480_CYCLES               ( 7u << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP8_3_CYCLES                 ( 0u << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_15_CYCLES                ( 1u << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_28_CYCLES                ( 2u << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_56_CYCLES                ( 3u << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_84_CYCLES                ( 4u << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_112_CYCLES               ( 5u << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_144_CYCLES               ( 6u << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_480_CYCLES               ( 7u << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP9_3_CYCLES                 ( 0u << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_15_CYCLES                ( 1u << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_28_CYCLES                ( 2u << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_56_CYCLES                ( 3u << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_84_CYCLES                ( 4u << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_112_CYCLES               ( 5u << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_144_CYCLES               ( 6u << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_480_CYCLES               ( 7u << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR1_SMP10_3_CYCLES                ( 0u << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_15_CYCLES               ( 1u << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_28_CYCLES               ( 2u << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_56_CYCLES               ( 3u << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_84_CYCLES               ( 4u << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_112_CYCLES              ( 5u << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_144_CYCLES              ( 6u << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_480_CYCLES              ( 7u << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP11_3_CYCLES                ( 0u << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_15_CYCLES               ( 1u << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_28_CYCLES               ( 2u << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_56_CYCLES               ( 3u << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_84_CYCLES               ( 4u << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_112_CYCLES              ( 5u << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_144_CYCLES              ( 6u << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_480_CYCLES              ( 7u << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP12_3_CYCLES                ( 0u << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_15_CYCLES               ( 1u << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_28_CYCLES               ( 2u << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_56_CYCLES               ( 3u << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_84_CYCLES               ( 4u << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_112_CYCLES              ( 5u << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_144_CYCLES              ( 6u << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_480_CYCLES              ( 7u << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP13_3_CYCLES                ( 0u << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_15_CYCLES               ( 1u << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_28_CYCLES               ( 2u << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_56_CYCLES               ( 3u << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_84_CYCLES               ( 4u << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_112_CYCLES              ( 5u << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_144_CYCLES              ( 6u << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_480_CYCLES              ( 7u << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP14_3_CYCLES                ( 0u << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_15_CYCLES               ( 1u << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_28_CYCLES               ( 2u << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_56_CYCLES               ( 3u << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_84_CYCLES               ( 4u << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_112_CYCLES              ( 5u << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_144_CYCLES              ( 6u << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_480_CYCLES              ( 7u << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP15_3_CYCLES                ( 0u << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_15_CYCLES               ( 1u << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_28_CYCLES               ( 2u << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_56_CYCLES               ( 3u << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_84_CYCLES               ( 4u << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_112_CYCLES              ( 5u << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_144_CYCLES              ( 6u << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_480_CYCLES              ( 7u << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP16_3_CYCLES                ( 0u << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_15_CYCLES               ( 1u << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_28_CYCLES               ( 2u << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_56_CYCLES               ( 3u << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_84_CYCLES               ( 4u << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_112_CYCLES              ( 5u << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_144_CYCLES              ( 6u << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_480_CYCLES              ( 7u << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP17_3_CYCLES                ( 0u << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_15_CYCLES               ( 1u << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_28_CYCLES               ( 2u << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_56_CYCLES               ( 3u << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_84_CYCLES               ( 4u << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_112_CYCLES              ( 5u << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_144_CYCLES              ( 6u << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_480_CYCLES              ( 7u << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP18_3_CYCLES                ( 0u << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_15_CYCLES               ( 1u << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_28_CYCLES               ( 2u << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_56_CYCLES               ( 3u << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_84_CYCLES               ( 4u << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_112_CYCLES              ( 5u << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_144_CYCLES              ( 6u << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_480_CYCLES              ( 7u << ADC_SMPR1_SMP18_Pos)

#define ADC_SQR3_SQ1_IN0                        ( 0u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN1                        ( 1u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN2                        ( 2u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN3                        ( 3u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN4                        ( 4u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN5                        ( 5u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN6                        ( 6u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN7                        ( 7u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN8                        ( 8u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN9                        ( 9u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN10                       (10u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN11                       (11u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN12                       (12u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN13                       (13u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN14                       (14u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN15                       (15u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN16                       (16u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN17                       (17u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_IN18                       (18u << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ2_IN0                        ( 0u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN1                        ( 1u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN2                        ( 2u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN3                        ( 3u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN4                        ( 4u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN5                        ( 5u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN6                        ( 6u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN7                        ( 7u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN8                        ( 8u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN9                        ( 9u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN10                       (10u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN11                       (11u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN12                       (12u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN13                       (13u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN14                       (14u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN15                       (15u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN16                       (16u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN17                       (17u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_IN18                       (18u << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ3_IN0                        ( 0u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN1                        ( 1u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN2                        ( 2u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN3                        ( 3u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN4                        ( 4u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN5                        ( 5u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN6                        ( 6u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN7                        ( 7u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN8                        ( 8u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN9                        ( 9u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN10                       (10u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN11                       (11u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN12                       (12u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN13                       (13u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN14                       (14u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN15                       (15u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN16                       (16u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN17                       (17u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_IN18                       (18u << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ4_IN0                        ( 0u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN1                        ( 1u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN2                        ( 2u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN3                        ( 3u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN4                        ( 4u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN5                        ( 5u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN6                        ( 6u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN7                        ( 7u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN8                        ( 8u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN9                        ( 9u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN10                       (10u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN11                       (11u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN12                       (12u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN13                       (13u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN14                       (14u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN15                       (15u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN16                       (16u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN17                       (17u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_IN18                       (18u << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ5_IN0                        ( 0u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN1                        ( 1u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN2                        ( 2u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN3                        ( 3u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN4                        ( 4u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN5                        ( 5u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN6                        ( 6u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN7                        ( 7u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN8                        ( 8u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN9                        ( 9u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN10                       (10u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN11                       (11u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN12                       (12u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN13                       (13u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN14                       (14u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN15                       (15u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN16                       (16u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN17                       (17u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_IN18                       (18u << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ6_IN0                        ( 0u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN1                        ( 1u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN2                        ( 2u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN3                        ( 3u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN4                        ( 4u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN5                        ( 5u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN6                        ( 6u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN7                        ( 7u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN8                        ( 8u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN9                        ( 9u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN10                       (10u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN11                       (11u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN12                       (12u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN13                       (13u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN14                       (14u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN15                       (15u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN16                       (16u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN17                       (17u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_IN18                       (18u << ADC_SQR3_SQ6_Pos)
#define ADC_SQR2_SQ7_IN0                        ( 0u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN1                        ( 1u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN2                        ( 2u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN3                        ( 3u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN4                        ( 4u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN5                        ( 5u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN6                        ( 6u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN7                        ( 7u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN8                        ( 8u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN9                        ( 9u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN10                       (10u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN11                       (11u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN12                       (12u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN13                       (13u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN14                       (14u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN15                       (15u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN16                       (16u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN17                       (17u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_IN18                       (18u << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ8_IN0                        ( 0u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN1                        ( 1u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN2                        ( 2u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN3                        ( 3u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN4                        ( 4u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN5                        ( 5u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN6                        ( 6u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN7                        ( 7u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN8                        ( 8u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN9                        ( 9u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN10                       (10u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN11                       (11u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN12                       (12u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN13                       (13u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN14                       (14u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN15                       (15u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN16                       (16u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN17                       (17u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_IN18                       (18u << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ9_IN0                        ( 0u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN1                        ( 1u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN2                        ( 2u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN3                        ( 3u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN4                        ( 4u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN5                        ( 5u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN6                        ( 6u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN7                        ( 7u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN8                        ( 8u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN9                        ( 9u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN10                       (10u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN11                       (11u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN12                       (12u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN13                       (13u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN14                       (14u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN15                       (15u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN16                       (16u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN17                       (17u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_IN18                       (18u << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ10_IN0                       ( 0u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN1                       ( 1u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN2                       ( 2u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN3                       ( 3u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN4                       ( 4u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN5                       ( 5u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN6                       ( 6u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN7                       ( 7u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN8                       ( 8u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN9                       ( 9u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN10                      (10u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN11                      (11u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN12                      (12u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN13                      (13u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN14                      (14u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN15                      (15u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN16                      (16u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN17                      (17u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_IN18                      (18u << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ11_IN0                       ( 0u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN1                       ( 1u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN2                       ( 2u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN3                       ( 3u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN4                       ( 4u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN5                       ( 5u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN6                       ( 6u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN7                       ( 7u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN8                       ( 8u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN9                       ( 9u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN10                      (10u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN11                      (11u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN12                      (12u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN13                      (13u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN14                      (14u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN15                      (15u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN16                      (16u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN17                      (17u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_IN18                      (18u << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ12_IN0                       ( 0u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN1                       ( 1u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN2                       ( 2u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN3                       ( 3u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN4                       ( 4u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN5                       ( 5u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN6                       ( 6u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN7                       ( 7u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN8                       ( 8u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN9                       ( 9u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN10                      (10u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN11                      (11u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN12                      (12u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN13                      (13u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN14                      (14u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN15                      (15u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN16                      (16u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN17                      (17u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_IN18                      (18u << ADC_SQR2_SQ12_Pos)
#define ADC_SQR1_SQ13_IN0                       ( 0u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN1                       ( 1u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN2                       ( 2u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN3                       ( 3u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN4                       ( 4u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN5                       ( 5u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN6                       ( 6u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN7                       ( 7u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN8                       ( 8u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN9                       ( 9u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN10                      (10u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN11                      (11u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN12                      (12u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN13                      (13u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN14                      (14u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN15                      (15u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN16                      (16u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN17                      (17u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_IN18                      (18u << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ14_IN0                       ( 0u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN1                       ( 1u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN2                       ( 2u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN3                       ( 3u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN4                       ( 4u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN5                       ( 5u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN6                       ( 6u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN7                       ( 7u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN8                       ( 8u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN9                       ( 9u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN10                      (10u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN11                      (11u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN12                      (12u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN13                      (13u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN14                      (14u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN15                      (15u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN16                      (16u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN17                      (17u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_IN18                      (18u << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ15_IN0                       ( 0u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN1                       ( 1u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN2                       ( 2u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN3                       ( 3u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN4                       ( 4u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN5                       ( 5u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN6                       ( 6u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN7                       ( 7u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN8                       ( 8u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN9                       ( 9u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN10                      (10u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN11                      (11u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN12                      (12u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN13                      (13u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN14                      (14u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN15                      (15u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN16                      (16u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN17                      (17u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_IN18                      (18u << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ16_IN0                       ( 0u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN1                       ( 1u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN2                       ( 2u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN3                       ( 3u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN4                       ( 4u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN5                       ( 5u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN6                       ( 6u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN7                       ( 7u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN8                       ( 8u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN9                       ( 9u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN10                      (10u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN11                      (11u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN12                      (12u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN13                      (13u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN14                      (14u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN15                      (15u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN16                      (16u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN17                      (17u << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_IN18                      (18u << ADC_SQR1_SQ16_Pos)

#define ADC_SQR1_L_1_CONVERSION                 ( 0u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_2_CONVERSIONS                ( 1u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_3_CONVERSIONS                ( 2u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_4_CONVERSIONS                ( 3u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_5_CONVERSIONS                ( 4u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_6_CONVERSIONS                ( 5u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_7_CONVERSIONS                ( 6u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_8_CONVERSIONS                ( 7u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_9_CONVERSIONS                ( 8u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_10_CONVERSIONS               ( 9u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_11_CONVERSIONS               (10u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_12_CONVERSIONS               (11u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_13_CONVERSIONS               (12u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_14_CONVERSIONS               (13u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_15_CONVERSIONS               (14u << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_16_CONVERSIONS               (15u << ADC_SQR1_L_Pos)

#define ADC_JSQR_JSQ1_IN0                       ( 0u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN1                       ( 1u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN2                       ( 2u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN3                       ( 3u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN4                       ( 4u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN5                       ( 5u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN6                       ( 6u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN7                       ( 7u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN8                       ( 8u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN9                       ( 9u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN10                      (10u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN11                      (11u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN12                      (12u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN13                      (13u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN14                      (14u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN15                      (15u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN16                      (16u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN17                      (17u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_IN18                      (18u << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ2_IN0                       ( 0u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN1                       ( 1u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN2                       ( 2u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN3                       ( 3u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN4                       ( 4u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN5                       ( 5u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN6                       ( 6u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN7                       ( 7u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN8                       ( 8u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN9                       ( 9u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN10                      (10u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN11                      (11u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN12                      (12u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN13                      (13u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN14                      (14u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN15                      (15u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN16                      (16u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN17                      (17u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_IN18                      (18u << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ3_IN0                       ( 0u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN1                       ( 1u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN2                       ( 2u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN3                       ( 3u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN4                       ( 4u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN5                       ( 5u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN6                       ( 6u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN7                       ( 7u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN8                       ( 8u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN9                       ( 9u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN10                      (10u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN11                      (11u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN12                      (12u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN13                      (13u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN14                      (14u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN15                      (15u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN16                      (16u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN17                      (17u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_IN18                      (18u << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ4_IN0                       ( 0u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN1                       ( 1u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN2                       ( 2u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN3                       ( 3u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN4                       ( 4u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN5                       ( 5u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN6                       ( 6u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN7                       ( 7u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN8                       ( 8u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN9                       ( 9u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN10                      (10u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN11                      (11u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN12                      (12u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN13                      (13u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN14                      (14u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN15                      (15u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN16                      (16u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN17                      (17u << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_IN18                      (18u << ADC_JSQR_JSQ4_Pos)

#define ADC_JSQR_JL_1_CONVERSION                ( 0u << ADC_JSQR_JL_Pos)
#define ADC_JSQR_JL_2_CONVERSIONS               ( 1u << ADC_JSQR_JL_Pos)
#define ADC_JSQR_JL_3_CONVERSIONS               ( 2u << ADC_JSQR_JL_Pos)
#define ADC_JSQR_JL_4_CONVERSIONS               ( 3u << ADC_JSQR_JL_Pos)

#ifdef __cplusplus
}
#endif

#endif // STM32F4XX_MISSING_H_INCLUDED
