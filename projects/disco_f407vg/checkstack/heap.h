// heap.h
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

#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Check how much heap memory has been allocated
// return: number of bytes
size_t heap_used(void);

// Check how much heap memory has not been allocated
// return: number of bytes
size_t heap_remaining(void);

#ifdef __cplusplus
}
#endif

#endif // HEAP_H_INCLUDED
