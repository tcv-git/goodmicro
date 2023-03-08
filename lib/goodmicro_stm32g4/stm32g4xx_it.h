// stm32g4xx_it.h
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

#ifndef STM32G4XX_IT_H_INCLUDED
#define STM32G4XX_IT_H_INCLUDED

#ifdef STM32G431xx
#include "vectors/vectors_stm32g431xx.h"
#endif

#ifdef STM32G441xx
#include "vectors/vectors_stm32g441xx.h"
#endif

#ifdef STM32G471xx
#include "vectors/vectors_stm32g471xx.h"
#endif

#ifdef STM32G473xx
#include "vectors/vectors_stm32g473xx.h"
#endif

#ifdef STM32G474xx
#include "vectors/vectors_stm32g474xx.h"
#endif

#ifdef STM32G483xx
#include "vectors/vectors_stm32g483xx.h"
#endif

#ifdef STM32G484xx
#include "vectors/vectors_stm32g484xx.h"
#endif

#ifdef STM32G491xx
#include "vectors/vectors_stm32g491xx.h"
#endif

#ifdef STM32G4A1xx
#include "vectors/vectors_stm32g4a1xx.h"
#endif

#ifdef STM32GBK1CB
#include "vectors/vectors_stm32gbk1cb.h"
#endif

#endif /* STM32G4XX_IT_H_INCLUDED */
