// system_config.h

#ifndef SYSTEM_CONFIG_H_INCLUDED
#define SYSTEM_CONFIG_H_INCLUDED

#define VDD_mV         3000

#define HSE_VALUE   8000000u
#define SYSCLK     30000000u

#define PLL_M             4
#define PLL_N            60
#define PLL_P             4

#define SSCGEN            0

#define HPRE              1
#define PPRE1             1
#define PPRE2             1

#define RCC_CFGR_MCO2_Value  RCC_CFGR_MCO2_SYSCLK
#define MCO2PRE           1

#define PLLI2SON          0

#endif /* SYSTEM_CONFIG_H_INCLUDED */
