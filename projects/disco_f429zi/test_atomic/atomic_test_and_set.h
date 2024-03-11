/* Atomic test-and-set functions
 * Copyright Green Energy Options Limited
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
//
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

// Atomically set the bits in the second argument in the word pointed to by the
// first argument and return the new value
//
uint32_t atomic_or_u32(volatile uint32_t *, uint32_t);

// If the byte pointed to by the third argument is zero, atomically clear the
// bits set in the second argument from the word pointed to by the first
// argument and return zero. Otherwise do not change anything and return
// non-zero.
//
int atomic_bic_u32_if_u8_eq_zero(volatile uint32_t *, uint32_t, const volatile uint8_t*);

#ifdef __cplusplus
}
#endif

#endif // ATOMIC_TEST_AND_SET_H_INCLUDED
