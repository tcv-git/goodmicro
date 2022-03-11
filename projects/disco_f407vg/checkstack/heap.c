// heap.c
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

#include <stddef.h>
#include "heap.h"

// symbols defined in linker script
//
extern const char __HeapBase;
extern const char __HeapLimit;

// _sbrk is required by newlib c library, it is not for direct application use
//
void * _sbrk(ptrdiff_t diff);
void * _sbrk(ptrdiff_t diff)
{
  const char * const heap_base  = &__HeapBase;
  const char * const heap_limit = &__HeapLimit;

  static const char * current_end = &__HeapBase;

  const char * previous_end = current_end;

  if ((diff < (heap_base - previous_end)) || (diff > (heap_limit - previous_end)))
  {
    return (void*)-1;
  }

  current_end += diff;

  return (void*)previous_end;
}

// Check how much heap memory has been allocated
// return: number of bytes
size_t heap_used(void)
{
  const char * const heap_base = &__HeapBase;

  const char * heap_end = (const char*)_sbrk(0);

  return (size_t)(heap_end - heap_base);
}

// Check how much heap memory has not been allocated
// return: number of bytes
size_t heap_remaining(void)
{
  const char * const heap_limit = &__HeapLimit;

  const char * heap_end = (const char*)_sbrk(0);

  return (size_t)(heap_limit - heap_end);
}
