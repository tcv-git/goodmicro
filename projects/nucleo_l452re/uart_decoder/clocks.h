// Clocks
// Copyright Green Energy Options Ltd.

#ifndef CLOCKS_H_INCLUDED
#define CLOCKS_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// counts of monotime() per second
const uint32_t MONOTIME_HZ;

// fast monotonic clock, system dependant units
uint64_t monotime(void);

// unix timestamp but in nanoseconds if available, else returns zero
int64_t walltime(void);

#ifdef __cplusplus
}
#endif

#endif // CLOCKS_H_INCLUDED
