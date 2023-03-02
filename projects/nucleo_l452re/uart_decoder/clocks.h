
#if 0
uint64_t walltime(void); // unix timestamp but in nanoseconds if available
uint64_t monotime(void); // fast monotonic clock, system dependant units

const uint32_t MONOTIME_HZ; // counts of monotime() per second
#endif
