// Clocks
// Copyright Green Energy Options Ltd.

#ifndef CLOCKS_H_INCLUDED
#define CLOCKS_H_INCLUDED

#include <stdint.h>
#include "system_stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

// counts of monotime() per second
#define MONOTIME_HZ  SystemCoreClock

// fast monotonic clock, system dependant units
uint64_t monotime(void);

// unix timestamp but in nanoseconds if available, else returns zero
int64_t walltime(void);

#ifdef __cplusplus
}
#endif

#endif // CLOCKS_H_INCLUDED
