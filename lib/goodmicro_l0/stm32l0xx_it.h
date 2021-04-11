// stm32l0xx_it.h
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

#ifndef STM32FL0X_IT_H_INCLUDED
#define STM32FL0X_IT_H_INCLUDED

#ifdef STM32L010x4
#include "vectors/vectors_stm32l010x4.h"
#endif
#ifdef STM32L010x6
#include "vectors/vectors_stm32l010x6.h"
#endif
#ifdef STM32L010x8
#include "vectors/vectors_stm32l010x8.h"
#endif
#ifdef STM32L010xB
#include "vectors/vectors_stm32l010xb.h"
#endif
#ifdef STM32L011xx
#include "vectors/vectors_stm32l011xx.h"
#endif
#ifdef STM32L021xx
#include "vectors/vectors_stm32l021xx.h"
#endif
#ifdef STM32L031xx
#include "vectors/vectors_stm32l031xx.h"
#endif
#ifdef STM32L041xx
#include "vectors/vectors_stm32l041xx.h"
#endif
#ifdef STM32L051xx
#include "vectors/vectors_stm32l051xx.h"
#endif
#ifdef STM32L052xx
#include "vectors/vectors_stm32l052xx.h"
#endif
#ifdef STM32L053xx
#include "vectors/vectors_stm32l053xx.h"
#endif
#ifdef STM32L062xx
#include "vectors/vectors_stm32l062xx.h"
#endif
#ifdef STM32L063xx
#include "vectors/vectors_stm32l063xx.h"
#endif
#ifdef STM32L071xx
#include "vectors/vectors_stm32l071xx.h"
#endif
#ifdef STM32L072xx
#include "vectors/vectors_stm32l072xx.h"
#endif
#ifdef STM32L073xx
#include "vectors/vectors_stm32l073xx.h"
#endif
#ifdef STM32L081xx
#include "vectors/vectors_stm32l081xx.h"
#endif
#ifdef STM32L082xx
#include "vectors/vectors_stm32l082xx.h"
#endif
#ifdef STM32L083xx
#include "vectors/vectors_stm32l083xx.h"
#endif

#endif /* STM32L0XX_IT_H_INCLUDED */
