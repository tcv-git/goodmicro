// stm32h7xx_extra.c
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

#include <stddef.h>
#include <stdint.h>
#include "stm32h7xx.h"
#include "stm32h7xx_it.h"
#include "stm32h7xx_extra.h"
#include "stm32h7xx_simple_gpio.h"
#include "peripheral_enable.h"
#include "common_macros.h"

void dma_stop(DMA_Stream_TypeDef *stream)
{
    for (;;)
    {
        uint32_t cr = stream->CR;

        if ((cr & DMA_SxCR_EN) == 0)
        {
            return;
        }

        stream->CR = (cr & ~DMA_SxCR_EN);
    }
}
