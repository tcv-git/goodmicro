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
#include "printf_queue.h"
#include "debug_uart.h"
#include "peripheral_enable.h"
#include "debug_printf.h"

void debug_uart_init(void)
{
    NVIC_DisableIRQ(DEBUG_UART_IRQn);
    NVIC_DisableIRQ(DEBUG_TX_DMAx_Streamx_IRQn);

    peripheral_enable(&RCC->DEBUG_DMA_AHBxENR, DEBUG_DMA_AHBxENR_DMAxEN);

    dma_stop(DEBUG_TX_DMAx_Streamx);

    DEBUG_DMAx->DEBUG_TX_DMA_xIFCR = (DEBUG_DMAx->DEBUG_TX_DMA_xISR & DEBUG_TX_DMA_xIFCR_CALLIFx);
    DEBUG_TX_DMAMUXx_Channelx->CCR = DEBUG_TX_DMAMUXx_CxCR_DMAREQ_ID;
    DEBUG_TX_DMAx_Streamx->M0AR    = 0;  // prevent incorrect free on first interrupt

    NVIC_ClearPendingIRQ (DEBUG_TX_DMAx_Streamx_IRQn);
    NVIC_EnableIRQ       (DEBUG_TX_DMAx_Streamx_IRQn);

    peripheral_reset_enable(&RCC->DEBUG_UART_APBx_RSTR, &RCC->DEBUG_UART_APBx_ENR, DEBUG_UART_APBx_ENR_UARTxEN);

    DEBUG_UARTx->CR1 = 0;
    DEBUG_UARTx->CR2 = 0;
    DEBUG_UARTx->CR3 =  USART_CR3_DMAT;
    DEBUG_UARTx->BRR = ((DEBUG_UART_APBx_CLK + (DEBUG_BAUD / 2)) / DEBUG_BAUD);
    DEBUG_UARTx->CR1 = (USART_CR1_FIFOEN | USART_CR1_TE | USART_CR1_UE);

    peripheral_enable(&RCC->DEBUG_TX_AHBxENR, DEBUG_TX_AHBxENR_GPIOxEN);

    GPIO_alternate_push_pull_slow(DEBUG_TX_GPIOx, DEBUG_TX_PINx, DEBUG_TX_AFx);
}

void DEBUG_TX_DMAx_Streamx_IRQHandler(void)
{
  if ((DEBUG_DMAx->DEBUG_TX_DMA_xISR & DEBUG_TX_DMA_xISR_TEIFx) != 0)
  {
    // set permanent break condition
    GPIO_set_reset             (DEBUG_TX_GPIOx, LO(DEBUG_TX_PINx));
    GPIO_output_push_pull_slow (DEBUG_TX_GPIOx, DEBUG_TX_PINx);

    RCC->DEBUG_UART_APBx_RSTR |=  DEBUG_UART_APBx_RSTR_UARTxRST;
    RCC->DEBUG_UART_APBx_ENR  &= ~DEBUG_UART_APBx_ENR_UARTxEN;

    while (DEBUG_TX_DMAx_Streamx->CR != 0)
    {
        DEBUG_TX_DMAx_Streamx->CR = 0;
    }

    DEBUG_DMAx->DEBUG_TX_DMA_xIFCR = (DEBUG_DMAx->DEBUG_TX_DMA_xISR & DEBUG_TX_DMA_xIFCR_CALLIFx);

    NVIC_DisableIRQ      (DEBUG_TX_DMAx_Streamx_IRQn);
    NVIC_ClearPendingIRQ (DEBUG_TX_DMAx_Streamx_IRQn);
    return;
  }

  if ((DEBUG_TX_DMAx_Streamx->CR & DMA_SxCR_EN) == DMA_SxCR_EN)
  {
    return;
  }

  const char *old_buffer = (const char*)DEBUG_TX_DMAx_Streamx->M0AR;

  if (old_buffer)
  {
    DEBUG_TX_DMAx_Streamx->M0AR = 0;
    printf_queue_free(old_buffer);
  }

  uint16_t byte_count;
  char *buffer = printf_queue_get_crlf(&byte_count);

  if (!buffer)
  {
    DEBUG_DMAx->DEBUG_TX_DMA_xIFCR = (DEBUG_DMAx->DEBUG_TX_DMA_xISR & DEBUG_TX_DMA_xIFCR_CALLIFx);
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

  DEBUG_TX_DMAx_Streamx->NDTR = byte_count;
  DEBUG_TX_DMAx_Streamx->PAR  = (uint32_t)&(DEBUG_UARTx->TDR);
  DEBUG_TX_DMAx_Streamx->M0AR = buffer_address;
  DEBUG_TX_DMAx_Streamx->FCR  = DMA_SxFCR_DMDIS;

  DEBUG_DMAx->DEBUG_TX_DMA_xIFCR = (DEBUG_DMAx->DEBUG_TX_DMA_xISR & DEBUG_TX_DMA_xIFCR_CALLIFx);

  NVIC_ClearPendingIRQ(DEBUG_TX_DMAx_Streamx_IRQn);

  DEBUG_TX_DMAx_Streamx->CR   = (DMA_SxCR_TRBUFF
                               | DMA_SxCR_PL_LOW
                               | msize
                               | DMA_SxCR_PSIZE_8BIT
                               | DMA_SxCR_MINC
                               | DMA_SxCR_DIR_M2P
                               | DMA_SxCR_TCIE
                               | DMA_SxCR_TEIE
                               | DMA_SxCR_EN);
}

static void debug_vprintf(const char *format, va_list args)
{
  printf_queue_put(format, args);

  if ((DEBUG_TX_DMAx_Streamx->CR & DMA_SxCR_EN) != DMA_SxCR_EN)
  {
    NVIC_SetPendingIRQ(DEBUG_TX_DMAx_Streamx_IRQn);
  }
}

void debug_printf(const char *format, ...)
{
  va_list args;

  va_start(args, format);
  debug_vprintf(format, args);
  va_end(args);
}

void debug_putc(unsigned char c)
{
  debug_printf("%c", c);
}
