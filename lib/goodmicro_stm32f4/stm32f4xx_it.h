// stm32f4xx_it.h
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

#ifndef STM32F4XX_IT_H_INCLUDED
#define STM32F4XX_IT_H_INCLUDED

#ifdef STM32F401xC
#include "vectors/vectors_stm32f401xc.h"
#endif
#ifdef STM32F401xE
#include "vectors/vectors_stm32f401xe.h"
#endif
#ifdef STM32F405xx
#include "vectors/vectors_stm32f405xx.h"
#endif
#ifdef STM32F407xx
#include "vectors/vectors_stm32f407xx.h"
#endif
#ifdef STM32F410Cx
#include "vectors/vectors_stm32f410cx.h"
#endif
#ifdef STM32F410Rx
#include "vectors/vectors_stm32f410rx.h"
#endif
#ifdef STM32F410Tx
#include "vectors/vectors_stm32f410tx.h"
#endif
#ifdef STM32F411xE
#include "vectors/vectors_stm32f411xe.h"
#endif
#ifdef STM32F412Cx
#include "vectors/vectors_stm32f412cx.h"
#endif
#ifdef STM32F412Rx
#include "vectors/vectors_stm32f412rx.h"
#endif
#ifdef STM32F412Vx
#include "vectors/vectors_stm32f412vx.h"
#endif
#ifdef STM32F412Zx
#include "vectors/vectors_stm32f412zx.h"
#endif
#ifdef STM32F413xx
#include "vectors/vectors_stm32f413xx.h"
#endif
#ifdef STM32F415xx
#include "vectors/vectors_stm32f415xx.h"
#endif
#ifdef STM32F417xx
#include "vectors/vectors_stm32f417xx.h"
#endif
#ifdef STM32F423xx
#include "vectors/vectors_stm32f423xx.h"
#endif
#ifdef STM32F427xx
#include "vectors/vectors_stm32f427xx.h"
#endif
#ifdef STM32F429xx
#include "vectors/vectors_stm32f429xx.h"
#endif
#ifdef STM32F437xx
#include "vectors/vectors_stm32f437xx.h"
#endif
#ifdef STM32F439xx
#include "vectors/vectors_stm32f439xx.h"
#endif
#ifdef STM32F446xx
#include "vectors/vectors_stm32f446xx.h"
#endif
#ifdef STM32F469xx
#include "vectors/vectors_stm32f469xx.h"
#endif
#ifdef STM32F479xx
#include "vectors/vectors_stm32f479xx.h"
#endif

#endif /* STM32F4XX_IT_H_INCLUDED */
