// hints.h
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

#ifndef HINTS_H_INCLUDED
#define HINTS_H_INCLUDED

// use to provide an alternate implementation at compile time
#define CONST_TRUE(x)   (__builtin_constant_p(!(x)) && !!(x))
#define CONST_FALSE(x)  (__builtin_constant_p(!(x)) &&  !(x))

// use to make compiler optimize order of branches
#define LIKELY(x)    __builtin_expect(!!(x), 1)
#define UNLIKELY(x)  __builtin_expect(!!(x), 0)

#endif // HINTS_H_INCLUDED
