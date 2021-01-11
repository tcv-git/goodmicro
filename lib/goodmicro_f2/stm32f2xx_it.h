// stm32f2xx_it.h
// PUBLIC DOMAIN
// http:///www.purposeful.co.uk/software/goodmicro

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all intellectual property rights in them, including
  copyright, trademarks, design rights, database right, patents, and the right
  to be identified as the author.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  You are free to use, modify and distribute this software as you please, but
  you do so at your own risk.  If you do not pass on this warning then you may
  be responsible for any problems encountered by those who obtain the software
  through you.
*/

#ifndef STM32F2XX_IT_H_INCLUDED
#define STM32F2XX_IT_H_INCLUDED

#ifdef STM32F205xx
#include "vectors/vectors_stm32f205xx.h"
#endif
#ifdef STM32F215xx
#include "vectors/vectors_stm32f207xx.h"
#endif
#ifdef STM32F207xx
#include "vectors/vectors_stm32f215xx.h"
#endif
#ifdef STM32F217xx
#include "vectors/vectors_stm32f217xx.h"
#endif

#endif /* STM32F2XX_IT_H_INCLUDED */
