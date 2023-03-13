// Clocks
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include "uptime.h"
#include "clocks.h"

// fast monotonic clock, system dependant units
uint64_t monotime(void)
{
  return uptime_sysclk();
}

// unix timestamp but in nanoseconds if available, else returns zero
int64_t walltime(void)
{
  return 0;
}
