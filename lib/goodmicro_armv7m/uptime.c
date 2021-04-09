// uptime.c
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

#include <stdint.h>
#include "udiv64.h"

#if (defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) \
  || defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx))
#include "system_stm32f405-439.h"
#endif

#include "uptime.h"

#if defined(SYSTEM_CORE_CLOCK) && (SYSTEM_CORE_CLOCK != 0)

uint64_t uptime_s(void){ return udiv64(uptime_sysclk(), SYSTEM_CORE_CLOCK ); }

#if ((SYSTEM_CORE_CLOCK % 1000) == 0)
uint64_t uptime_ms(void){ return udiv64(uptime_sysclk(), (SYSTEM_CORE_CLOCK / 1000)); }
#endif

#if ((SYSTEM_CORE_CLOCK % 1000000) == 0)
uint64_t uptime_us(void){ return udiv64(uptime_sysclk(), (SYSTEM_CORE_CLOCK / 1000000)); }
#endif

#endif // SYSTEM_CORE_CLOCK
