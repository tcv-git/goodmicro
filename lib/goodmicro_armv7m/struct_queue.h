// struct_queue.h
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

#ifndef STRUCT_QUEUE_H_INCLUDED
#define STRUCT_QUEUE_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct queued_item
{
    struct queued_item *next;
    uintptr_t placeholder[];
};

/* This function atomically adds an item to the queue.  It always succeeds.
 * It is re-entrant: multiple threads and interrupts can call this function at
 * the same time.  It can also be called at the same time as the read function.
 */
void queue_write(struct queued_item * volatile * head_ptr, struct queued_item *new_item);

/* This function atomically removes the oldest item from the queue and returns
 * a pointer to it.  It returns a null pointer if the queue is empty.
 *
 * This function is not re-entrant: only one thread or interrupt can call this
 * function on a single queue at the same time.  It can however be called at the
 * same time as the write function.
 */
struct queued_item *queue_read(struct queued_item * volatile * head_ptr);

#ifdef __cplusplus
}
#endif

#endif /* STRUCT_QUEUE_H_INCLUDED */
