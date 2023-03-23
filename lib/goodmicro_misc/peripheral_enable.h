// peripheral_enable.h
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

#ifndef PERIPHERAL_ENABLE_H_INCLUDED
#define PERIPHERAL_ENABLE_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline void peripheral_reset_enable(volatile uint32_t *rstr, volatile uint32_t *enr, uint32_t bit)
{
  uint32_t rst = *rstr;

  *rstr = (rst | bit);
  *enr |= bit;
  (void)*enr;
  *rstr = (rst & ~bit);
  (void)*rstr;
}

static inline void peripheral_enable(volatile uint32_t *enr, uint32_t bit)
{
  *enr |= bit;
  (void)*enr;
}

#ifdef __cplusplus
}
#endif

#endif /* PERIPHERAL_ENABLE_H_INCLUDED */
