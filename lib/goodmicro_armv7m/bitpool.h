// bitpool.h
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

/*
  This small library uses Cortex-M exclusive load and store instructions to
  implement an allocation pool.

  Each pool can have up to 32 members, each represented by a single bit in the
  control word.  The actual number available is set by the number of ones in
  the initial value of the control word.

  It can be used with or without an operating system and is fully re-entrant,
  so multiple calls can pre-empt or overlap each other in different tasks or
  interrupts with no possibility of data loss.
*/

#ifndef BITPOOL_H_INCLUDED
#define BITPOOL_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* allocate a member of the pool and return its index
 * or return negative if none available.
 */
int bitpool_alloc(volatile unsigned int *control);


/* mark the member specified by index as available for reallocation.
 */
void bitpool_free(volatile unsigned int *control, unsigned int index);

#ifdef __cplusplus
}
#endif

#endif // BITPOOL_H_INCLUDED
