// main.c
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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "debug_printf.h"
#include "delay.h"
#include "rng.h"
#include "stack.h"
#include "heap.h"

int main(void)
{
  rng_init();
  debug_uart_init();
  debug_printf("booted\n");

  stack_fill();

  debug_printf("stack_used %u stack_remaining %u heap_used %u heap_remaining %u\n", (unsigned int)stack_used(), (unsigned int)stack_remaining(), (unsigned int)heap_used(), (unsigned int)heap_remaining());

  volatile char foo[4000];

  foo[0] = 0;

  DELAY_S(1);

  debug_printf("stack_used %u stack_remaining %u heap_used %u heap_remaining %u\n", (unsigned int)stack_used(), (unsigned int)stack_remaining(), (unsigned int)heap_used(), (unsigned int)heap_remaining());

  volatile char * ptr1 = malloc(99);

  ptr1[98] = 8;

  debug_printf("stack_used %u stack_remaining %u heap_used %u heap_remaining %u\n", (unsigned int)stack_used(), (unsigned int)stack_remaining(), (unsigned int)heap_used(), (unsigned int)heap_remaining());

  volatile char * ptr2 = malloc(10099);

  ptr2[198] = 7;

  debug_printf("stack_used %u stack_remaining %u heap_used %u heap_remaining %u\n", (unsigned int)stack_used(), (unsigned int)stack_remaining(), (unsigned int)heap_used(), (unsigned int)heap_remaining());

  free((void*)ptr2);

  debug_printf("stack_used %u stack_remaining %u heap_used %u heap_remaining %u\n", (unsigned int)stack_used(), (unsigned int)stack_remaining(), (unsigned int)heap_used(), (unsigned int)heap_remaining());

  free((void*)ptr1);

  debug_printf("stack_used %u stack_remaining %u heap_used %u heap_remaining %u\n", (unsigned int)stack_used(), (unsigned int)stack_remaining(), (unsigned int)heap_used(), (unsigned int)heap_remaining());

  for (;;);
}
