// clock_config.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

#ifndef CLOCK_CONFIG_H_INCLUDED
#define CLOCK_CONFIG_H_INCLUDED

#define HSE_VALUE 8000000
#define HSEBYP          1

#define PLLSRC RCC_CFGR_PLLSRC_HSE_PREDIV

#define PREDIV          2
#define PLLMUL         12

#define HPRE            1
#define PPRE            1

#endif /* CLOCK_CONFIG_H_INCLUDED */
