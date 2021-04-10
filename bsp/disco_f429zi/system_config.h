// system_config.h

#ifndef SYSTEM_CONFIG_H_INCLUDED
#define SYSTEM_CONFIG_H_INCLUDED

#define VDD_mV         3000

#define HSE_VALUE   8000000u
#define SYSCLK    180000000u

#define PLL_M             4
#define PLL_N           180
#define PLL_P             2
#define PLL_Q             8

#define SSCGEN            0

#define HPRE              1
#define PPRE1             4
#define PPRE2             2
#define TIMPRE            1

#define RCC_CFGR_MCO1_Value  RCC_CFGR_MCO1_HSI
#define MCO1PRE           1

#define RCC_CFGR_MCO2_Value  RCC_CFGR_MCO2_HSE
#define MCO2PRE           1

#define PLLI2SON          0
#define PLLSAION          1

#define PLLSAI_N         96
#define PLLSAI_Q          7
#define PLLSAI_R          4
#define PLLSAIDIVQ       32
#define PLLSAIDIVR        8

#endif // SYSTEM_CONFIG_H_INCLUDED
