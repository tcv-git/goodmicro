// system_config.h

#ifndef SYSTEM_CONFIG_H_INCLUDED
#define SYSTEM_CONFIG_H_INCLUDED

#define VDD_mV         3000

// secret!
//#define HSE_VALUE   8000000u
#define SYSCLK     16000000u

#define HSEON             1
#define HSEBYP            1
#define PLLON             0

#define HPRE              1
#define PPRE1             1
#define PPRE2             1

#define RCC_CFGR_MCO1_Value  RCC_CFGR_MCO1_HSI
#define MCO1PRE           1

#define RCC_CFGR_MCO2_Value  RCC_CFGR_MCO2_HSE
#define MCO2PRE           1

#endif // SYSTEM_CONFIG_H_INCLUDED
