// stm32f0xx_it.h
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

#ifndef STM32F0XX_IT_H_INCLUDED
#define STM32F0XX_IT_H_INCLUDED

#ifdef STM32F030x6
#include "vectors/vectors_stm32f030x6.h"
#endif
#ifdef STM32F030x8
#include "vectors/vectors_stm32f030x8.h"
#endif
#ifdef STM32F030xC
#include "vectors/vectors_stm32f030xc.h"
#endif
#ifdef STM32F031x6
#include "vectors/vectors_stm32f031x6.h"
#endif
#ifdef STM32F038xx
#include "vectors/vectors_stm32f038xx.h"
#endif
#ifdef STM32F042x6
#include "vectors/vectors_stm32f042x6.h"
#endif
#ifdef STM32F048xx
#include "vectors/vectors_stm32f048xx.h"
#endif
#ifdef STM32F051x8
#include "vectors/vectors_stm32f051x8.h"
#endif
#ifdef STM32F058xx
#include "vectors/vectors_stm32f058xx.h"
#endif
#ifdef STM32F070x6
#include "vectors/vectors_stm32f070x6.h"
#endif
#ifdef STM32F070xB
#include "vectors/vectors_stm32f070xb.h"
#endif
#ifdef STM32F071xB
#include "vectors/vectors_stm32f071xb.h"
#endif
#ifdef STM32F072xB
#include "vectors/vectors_stm32f072xb.h"
#endif
#ifdef STM32F078xx
#include "vectors/vectors_stm32f078xx.h"
#endif
#ifdef STM32F091xC
#include "vectors/vectors_stm32f091xc.h"
#endif
#ifdef STM32F098xx
#include "vectors/vectors_stm32f098xx.h"
#endif

#endif /* STM32F0XX_IT_H_INCLUDED */
