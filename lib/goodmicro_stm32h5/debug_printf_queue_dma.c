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
#include "peripheral_enable.h"
#include "printf_queue.h"
#include "debug_uart.h"
#include "debug_printf.h"

#define DMA_CFCR_ALL  (DMA_CFCR_TCF | DMA_CFCR_HTF | DMA_CFCR_DTEF | DMA_CFCR_ULEF | DMA_CFCR_USEF | DMA_CFCR_SUSPF | DMA_CFCR_TOF)

void debug_uart_init(void)
{
    NVIC_DisableIRQ(DEBUG_UART_IRQn);
    NVIC_DisableIRQ(DEBUG_TX_DMAx_Channelx_IRQn);
    //NVIC_DisableIRQ(DEBUG_RX_DMAx_Channelx_IRQn);

    peripheral_reset_enable(&RCC->DEBUG_UART_APBx_RSTR, &RCC->DEBUG_UART_APBx_ENR, DEBUG_UART_APBx_ENR_UARTxEN);

    peripheral_enable(&RCC->DEBUG_DMA_AHBxENR, DEBUG_DMA_AHBxENR_DMAxEN);

    if ((DEBUG_TX_DMAx_Channelx->CSR & DMA_CSR_IDLEF) != DMA_CSR_IDLEF)
    {
        DEBUG_TX_DMAx_Channelx->CCR = DMA_CCR_SUSP;
    }

    while ((DEBUG_TX_DMAx_Channelx->CSR & DMA_CSR_IDLEF) != DMA_CSR_IDLEF);

    DEBUG_TX_DMAx_Channelx->CCR = DMA_CCR_RESET;

    while ((DEBUG_TX_DMAx_Channelx->CCR & DMA_CCR_EN) != 0);

    DEBUG_TX_DMAx_Channelx->CFCR = DMA_CFCR_ALL;

    NVIC_ClearPendingIRQ(DEBUG_TX_DMAx_Channelx_IRQn);
    NVIC_EnableIRQ      (DEBUG_TX_DMAx_Channelx_IRQn);

    DEBUG_UARTx->CR1 = 0;
    DEBUG_UARTx->CR2 = 0;
    DEBUG_UARTx->CR3 = USART_CR3_DMAT; // USART_CR3_DMAR
    DEBUG_UARTx->BRR = ((DEBUG_UART_APBx_CLK + (DEBUG_BAUD / 2)) / DEBUG_BAUD);
    DEBUG_UARTx->CR1 = (USART_CR1_FIFOEN | USART_CR1_TE | USART_CR1_UE); // USART_CR1_RE

    peripheral_enable(&RCC->DEBUG_TX_AHBxENR, DEBUG_TX_AHBxENR_GPIOxEN);
    //peripheral_enable(&RCC->DEBUG_RX_AHBxENR, DEBUG_RX_AHBxENR_GPIOxEN);

    GPIO_alternate_push_pull_slow (DEBUG_TX_GPIOx, DEBUG_TX_PINx, DEBUG_TX_AFx);
    //GPIO_alternate_pull_up_slow (DEBUG_RX_GPIOx, DEBUG_RX_PINx, DEBUG_RX_AFx);
}

void DEBUG_TX_DMAx_Channelx_IRQHandler(void)
{
    if ((DEBUG_TX_DMAx_Channelx->CCR & DMA_CCR_EN) != 0)
    {
        return;
    }

    const char *old_buffer = (const char*)DEBUG_TX_DMAx_Channelx->CSAR;

    if (old_buffer != NULL)
    {
        DEBUG_TX_DMAx_Channelx->CSAR = 0;
        printf_queue_free(old_buffer);
    }

    uint16_t byte_count;
    char *buffer = printf_queue_get_crlf(&byte_count);

    if (!buffer)
    {
        DEBUG_TX_DMAx_Channelx->CFCR = DMA_CFCR_ALL;
        return;
    }

    DEBUG_TX_DMAx_Channelx->CTR1 = DMA_CTR1_SINC;
    DEBUG_TX_DMAx_Channelx->CTR2 = (DEBUG_TX_DMAx_Channelx_CTR2_REQSEL | DMA_CTR2_DREQ);
    DEBUG_TX_DMAx_Channelx->CBR1 = byte_count;
    DEBUG_TX_DMAx_Channelx->CSAR = (uint32_t)buffer;
    DEBUG_TX_DMAx_Channelx->CDAR = (uint32_t)&DEBUG_UARTx->TDR;
    DEBUG_TX_DMAx_Channelx->CLLR = 0;
    DEBUG_TX_DMAx_Channelx->CFCR = DMA_CFCR_ALL;

    NVIC_ClearPendingIRQ(DEBUG_TX_DMAx_Channelx_IRQn);

    DEBUG_TX_DMAx_Channelx->CCR = (DMA_CCR_TCIE | DMA_CCR_EN);
}

static void debug_vprintf(const char *format, va_list args)
{
    printf_queue_put(format, args);

    if ((DEBUG_TX_DMAx_Channelx->CCR & DMA_CCR_EN) != DMA_CCR_EN)
    {
        NVIC_SetPendingIRQ(DEBUG_TX_DMAx_Channelx_IRQn);
    }
}

void debug_printf(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    debug_vprintf(format, args);
    va_end(args);
}
