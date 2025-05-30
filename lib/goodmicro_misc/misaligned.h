// misaligned.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/yabaplib/

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

/*
  Inline functions for efficient access to not-necessarily-aligned data.

  (the names of these functions were chosen to match those used by the Analog
  Devices Blackfin compiler, but the implementations here are suitable for any
  platform that is supported by GCC)

  If your project is set up correctly then the compiler probably knows better
  than you do which is the fastest way to access misaligned data safely.

  If the compiler can work out that a pointer is aligned or if the platform
  supports misaligned access to the specified type then it can access the data
  in the normal way.  Otherwise it will automatically use whichever combination
  of masking and shifting is best.

  The load functions return signed types, because a signed value can be safely
  converted to unsigned if required (whereas if they returned unsigned types
  then converting them to signed would cause undefined behaviour).

  Conversely the store functions take unsigned arguments.  Signed values can be
  passed to them safely (whereas if the arguments were of signed type then
  passing them unsigned values would cause undefined behaviour).
*/

#ifndef MISALIGNED_H_INCLUDED
#define MISALIGNED_H_INCLUDED

#include <stdint.h>

#ifdef _ADI_COMPILER
#include <ccblkfn.h>

#elif defined __GNUC__

#ifdef __cplusplus

template <typename T> struct misaligned_container { T member; } __attribute__((packed));

#define misaligned_load(     type,address)          ((reinterpret_cast<const          misaligned_container<type>*>(address))->member)
#define misaligned_load_vol( type,address)          ((reinterpret_cast<const volatile misaligned_container<type>*>(address))->member)
#define misaligned_store(    type,address,value) do{ (reinterpret_cast<               misaligned_container<type>*>(address))->member = (value); }while(0)
#define misaligned_store_vol(type,address,value) do{ (reinterpret_cast<      volatile misaligned_container<type>*>(address))->member = (value); }while(0)
#else /*__cplusplus */
#define misaligned_load(     type,address)          (((const          struct{type member __attribute__((packed));}*)address)->member)
#define misaligned_load_vol( type,address)          (((const volatile struct{type member __attribute__((packed));}*)address)->member)
#define misaligned_store(    type,address,value) do{ ((               struct{type member __attribute__((packed));}*)address)->member = (value); }while(0)
#define misaligned_store_vol(type,address,value) do{ ((      volatile struct{type member __attribute__((packed));}*)address)->member = (value); }while(0)
#endif /*__cplusplus */

static inline __attribute__((always_inline)) int16_t misaligned_load16     (const          void *addr){ return misaligned_load     (int16_t, addr); }
static inline __attribute__((always_inline)) int32_t misaligned_load32     (const          void *addr){ return misaligned_load     (int32_t, addr); }
static inline __attribute__((always_inline)) int64_t misaligned_load64     (const          void *addr){ return misaligned_load     (int64_t, addr); }
static inline __attribute__((always_inline)) int16_t misaligned_load16_vol (const volatile void *addr){ return misaligned_load_vol (int16_t, addr); }
static inline __attribute__((always_inline)) int32_t misaligned_load32_vol (const volatile void *addr){ return misaligned_load_vol (int32_t, addr); }
static inline __attribute__((always_inline)) int64_t misaligned_load64_vol (const volatile void *addr){ return misaligned_load_vol (int64_t, addr); }

static inline __attribute__((always_inline)) void misaligned_store16     (         void *addr, uint16_t val){ misaligned_store     (uint16_t, addr, val); }
static inline __attribute__((always_inline)) void misaligned_store32     (         void *addr, uint32_t val){ misaligned_store     (uint32_t, addr, val); }
static inline __attribute__((always_inline)) void misaligned_store64     (         void *addr, uint64_t val){ misaligned_store     (uint64_t, addr, val); }
static inline __attribute__((always_inline)) void misaligned_store16_vol (volatile void *addr, uint16_t val){ misaligned_store_vol (uint16_t, addr, val); }
static inline __attribute__((always_inline)) void misaligned_store32_vol (volatile void *addr, uint32_t val){ misaligned_store_vol (uint32_t, addr, val); }
static inline __attribute__((always_inline)) void misaligned_store64_vol (volatile void *addr, uint64_t val){ misaligned_store_vol (uint64_t, addr, val); }

#else /* __GNUC__ */

/* WORST CASE: memcpy doesn't depend on endianness, but there is no portable version for volatile data */

#include <string.h>

static inline int16_t misaligned_load16 (void *addr){ int16_t val; memcpy (&val, addr, sizeof val); return val; }
static inline int32_t misaligned_load32 (void *addr){ int32_t val; memcpy (&val, addr, sizeof val); return val; }
static inline int64_t misaligned_load64 (void *addr){ int64_t val; memcpy (&val, addr, sizeof val); return val; }

static inline void misaligned_store16 (void *addr, uint16_t val){ memcpy (addr, &val, sizeof val); }
static inline void misaligned_store32 (void *addr, uint32_t val){ memcpy (addr, &val, sizeof val); }
static inline void misaligned_store64 (void *addr, uint64_t val){ memcpy (addr, &val, sizeof val); }

#endif /* __GNUC__ */
#endif /* MISALIGNED_H_INCLUDED */
