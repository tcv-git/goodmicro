// imath.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

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

#ifndef IMATH_H_INCLUDED
#define IMATH_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NB: if the multiplicands are constant always just use (a*b) */

/* square root */
uint32_t __attribute__((const)) usqrt (uint32_t);

/* 32 squared = 64 */
uint64_t __attribute__((const)) sqr_u32 (uint32_t);
uint64_t __attribute__((const)) sqr_i32 (int32_t);

/* 32 x 16 = 64 */
uint64_t __attribute__((const)) mul_u32_u16 (uint32_t, uint16_t);
 int64_t __attribute__((const)) mul_u32_i16 (uint32_t,  int16_t);
 int64_t __attribute__((const)) mul_i32_u16 ( int32_t, uint16_t);
 int64_t __attribute__((const)) mul_i32_i16 ( int32_t,  int16_t);

/* 32 x 32 = 64 */
uint64_t __attribute__((const)) mul_u32_u32 (uint32_t, uint32_t);
 int64_t __attribute__((const)) mul_u32_i32 (uint32_t,  int32_t);
 int64_t __attribute__((const)) mul_i32_i32 ( int32_t,  int32_t);

/* 64 x 32 = 64 */
uint64_t __attribute__((const)) mul_u64_u32 (uint64_t, uint32_t);
 int64_t __attribute__((const)) mul_u64_i32 (uint64_t,  int32_t);
 int64_t __attribute__((const)) mul_i64_u32 ( int64_t, uint32_t);
 int64_t __attribute__((const)) mul_i64_i32 ( int64_t,  int32_t);

/* 64 x 64 = 64 */
/* (the following are all just aliases of __aeabi_lmul) */
uint64_t __attribute__((const)) mul_u64_u64 (uint64_t, uint64_t);
 int64_t __attribute__((const)) mul_i64_i64 ( int64_t,  int64_t);
 int64_t __attribute__((const)) mul_u64_i64 (uint64_t,  int64_t);

#define mul_u16_u32(a,b)  mul_u32_u16((b),(a))
#define mul_i16_u32(a,b)  mul_u32_i16((b),(a))
#define mul_u16_i32(a,b)  mul_i32_u16((b),(a))
#define mul_i16_i32(a,b)  mul_i32_i16((b),(a))
#define mul_i32_u32(a,b)  mul_u32_i32((b),(a))
#define mul_u32_u64(a,b)  mul_u64_u32((b),(a))
#define mul_i32_u64(a,b)  mul_u64_i32((b),(a))
#define mul_u32_i64(a,b)  mul_i64_u32((b),(a))
#define mul_i32_i64(a,b)  mul_i64_i32((b),(a))
#define mul_i64_u64(a,b)  mul_u64_i64((b),(a))

#ifdef __cplusplus
}
#endif

#endif /* IMATH_H_INCLUDED */
