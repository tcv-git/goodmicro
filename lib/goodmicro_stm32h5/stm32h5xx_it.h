// stm32h5xx_it.h
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

#ifndef STM32H5XX_IT_H_INCLUDED
#define STM32H5XX_IT_H_INCLUDED

#ifdef STM32H573xx
#include "vectors/vectors_stm32h573xx.h"
#endif

#ifdef STM32H563xx
#include "vectors/vectors_stm32h563xx.h"
#endif

#ifdef STM32H562xx
#include "vectors/vectors_stm32h562xx.h"
#endif

#ifdef STM32H503xx
#include "vectors/vectors_stm32h503xx.h"
#endif

#ifdef STM32H523xx
#include "vectors/vectors_stm32h523xx.h"
#endif

#ifdef STM32H533xx
#include "vectors/vectors_stm32h533xx.h"
#endif

#endif /* STM32H5XX_IT_H_INCLUDED */
