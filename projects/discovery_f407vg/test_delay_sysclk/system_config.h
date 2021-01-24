// system_config.h

#ifndef SYSTEM_CONFIG_H_INCLUDED
#define SYSTEM_CONFIG_H_INCLUDED

#define VDD_mV         3000

#define HSE_VALUE   8000000u

#define HSION             0
#define HSEON             1
#define PLLON             0
#define PLLI2SON          0

#define RCC_CFGR_SW_Value RCC_CFGR_SW_HSE
#define HPRE              8
#define PPRE1             1
#define PPRE2             1

#define RCC_CFGR_MCO2_Value  RCC_CFGR_MCO2_SYSCLK
#define MCO2PRE           1

#endif /* SYSTEM_CONFIG_H_INCLUDED */
