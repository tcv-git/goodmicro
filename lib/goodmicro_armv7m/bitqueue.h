// bitqueue.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/software/goodmicro

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
  implement a queue of unsigned integers.

  There is a fixed number of eight places in the queue, and each entry is four
  bits.

  It can be used with or without an operating system and is fully re-entrant,
  so multiple calls can pre-empt or overlap each other in different tasks or
  interrupts with no possibility of data loss.
*/

#ifndef BITQUEUE_H_INCLUDED
#define BITQUEUE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* the value to initialize an empty queue
 */
#define BITQUEUE_EMPTY_INIT  0x10000u


/* enqueue the message specified
 * return zero on success, non-zero on queue full
 */
int bitqueue_write(volatile unsigned int *control, unsigned int message);


/* read and return the oldest message in the queue
 * or return negative if the queue is empty
 */
int bitqueue_read(volatile unsigned int *control);


#ifdef __cplusplus
}
#endif

#endif // BITQUEUE_H_INCLUDED
