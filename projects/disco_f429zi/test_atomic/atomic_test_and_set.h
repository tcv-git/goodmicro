// Atomic test-and-set functions
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

#ifndef ATOMIC_TEST_AND_SET_H_INCLUDED
#define ATOMIC_TEST_AND_SET_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// atomically increment the pointed unsigned-byte value and return the new value
//
uint8_t atomic_inc_u8(volatile uint8_t*);

// atomically decrement the pointed unsigned-byte value and return the new value
//
uint8_t atomic_dec_u8(volatile uint8_t*);

// If the unsigned-byte value pointed to by the first argument is zero then
// atomically replace it with the second argument and return zero.  If it is
// non-zero, do not change it and return non-zero.
int atomic_set_u8_if_zero(volatile uint8_t*, uint8_t);

// If the signed-byte value pointed to by the first argument is less than or
// equal to zero, atomically replace it with the second argument and return
// zero. If it is greater than zero, do not change it and return non-zero.
//
int atomic_set_i8_if_le_zero(volatile int8_t*, int8_t);

// Atomically set the value pointed to by the first argument to the value of the
// second argument and return the previous value.
//
uint32_t atomic_swap_u32(volatile uint32_t*, uint32_t);

#ifdef __cplusplus
}
#endif

#endif // ATOMIC_TEST_AND_SET_H_INCLUDED
