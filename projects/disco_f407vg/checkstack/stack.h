// stack.h
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

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Fill the stack with canary values, from the stack limit to the current stack pointer
//
void stack_fill(void);

// Check how much stack memory has had its canaries overwritten
// return: number of bytes of stack which have ever been used
size_t stack_used(void);

// Check how much stack memory has not had its canaries overwritten
// return: number of bytes of stack which have never been used
size_t stack_remaining(void);

#ifdef __cplusplus
}
#endif

#endif // STACK_H_INCLUDED
