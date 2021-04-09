// uptime.h
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

#ifndef UPTIME_H_INCLUDED
#define UPTIME_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t uptime_sysclk (void);
uint64_t uptime_us     (void);
uint64_t uptime_ms     (void);
uint64_t uptime_s      (void);

#ifdef __cplusplus
}
#endif

#endif /* UPTIME_H_INCLUDED */
