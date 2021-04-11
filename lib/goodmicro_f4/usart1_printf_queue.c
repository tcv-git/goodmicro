// usart1_printf_queue.c
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

#include <stdint.h>
#include <stdarg.h>
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_missing.h"
#include "stm32f4xx_simple_gpio.h"
#include "system_stm32f405-439.h"
#include "printf_queue.h"
#include "usart1_printf_queue.h"

void usart1_printf_init(unsigned int baud)
{
  NVIC_DisableIRQ(USART1_IRQn);
  NVIC_DisableIRQ(DMA2_Stream7_IRQn);

  RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST;
  RCC->APB2ENR  |=  RCC_APB2ENR_USART1EN;
  RCC->AHB1ENR  |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_DMA2EN);
  RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

  while (DMA2_Stream7->CR != 0)
  {
    DMA2_Stream7->CR = 0;
  }

  DMA2->HIFCR = DMA_HIFCR_ALL7;

  NVIC_ClearPendingIRQ(DMA2_Stream7_IRQn);
  NVIC_EnableIRQ      (DMA2_Stream7_IRQn);

  USART1->CR1 = 0;
  USART1->CR2 = 0;
  USART1->CR3 = USART_CR3_DMAT;
  USART1->BRR = ((APB2_CLK + (baud / 2)) / baud);
  USART1->CR1 = (USART_CR1_UE | USART_CR1_TE);

  GPIO_alternate_push_pull_slow(GPIOA, PIN9, AF7);
}

void DMA2_Stream7_IRQHandler(void)
{
  if ((DMA2->HISR & DMA_HISR_TEIF7) != 0)
  {
    // set permanent break condition
    GPIO_set_reset             (GPIOA, PIN9_LO);
    GPIO_output_push_pull_slow (GPIOA, PIN9);

    RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST;
    RCC->APB2ENR  &= ~RCC_APB2ENR_USART1EN;

    while (DMA2_Stream7->CR != 0)
    {
      DMA2_Stream7->CR = 0;
    }

    DMA2->HIFCR = DMA_HIFCR_ALL7;

    NVIC_DisableIRQ      (DMA2_Stream7_IRQn);
    NVIC_ClearPendingIRQ (DMA2_Stream7_IRQn);
    return;
  }

  if ((DMA2_Stream7->CR & DMA_SxCR_EN) == DMA_SxCR_EN)
  {
    return;
  }

  const char *old_buffer = (const char*)DMA2_Stream7->M0AR;

  if (old_buffer)
  {
    DMA2_Stream7->M0AR = 0;
    printf_queue_free(old_buffer);
  }

  uint16_t byte_count;
  char *buffer = printf_queue_get_crlf(&byte_count);

  if (!buffer)
  {
    DMA2->HIFCR = DMA_HIFCR_ALL7;
    return;
  }

  uint32_t buffer_address = (uint32_t)buffer;
  uint32_t alignment      = (byte_count | buffer_address);
  uint32_t msize;

  switch (alignment & 3)
  {
    case 0:  msize = DMA_SxCR_MSIZE_32BIT; break;
    case 2:  msize = DMA_SxCR_MSIZE_16BIT; break;
    default: msize = DMA_SxCR_MSIZE_8BIT;
  }

  DMA2_Stream7->NDTR = byte_count;
  DMA2_Stream7->PAR  = (uint32_t)&(USART1->DR);
  DMA2_Stream7->M0AR = buffer_address;
  DMA2_Stream7->FCR  = DMA_SxFCR_DMDIS;
  DMA2->HIFCR        = DMA_HIFCR_ALL7;

  NVIC_ClearPendingIRQ(DMA2_Stream7_IRQn);

  DMA2_Stream7->CR = (DMA2_S7CR_CHSEL_USART1_TX
                    | DMA_SxCR_PL_LOW
                    | msize
                    | DMA_SxCR_PSIZE_8BIT
                    | DMA_SxCR_MINC
                    | DMA_SxCR_DIR_M2P
                    | DMA_SxCR_TCIE
                    | DMA_SxCR_TEIE
                    | DMA_SxCR_EN);
}

void usart1_vprintf(const char *format, va_list args)
{
  printf_queue_put(format, args);

  if ((DMA2_Stream7->CR & DMA_SxCR_EN) != DMA_SxCR_EN)
  {
    NVIC_SetPendingIRQ(DMA2_Stream7_IRQn);
  }
}

void usart1_printf(const char *format, ...)
{
  va_list args;

  va_start(args, format);
  usart1_vprintf(format, args);
  va_end(args);
}
