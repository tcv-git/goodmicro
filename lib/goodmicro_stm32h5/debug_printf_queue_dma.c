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
#include <string.h>
#include <stdarg.h>
#include "stm32h5xx.h"
#include "common_macros.h"
#include "peripheral_enable.h"
#include "printf_queue.h"
#include "debug_uart.h"
#include "debug_printf.h"

#define DMA_CFCR_ALL  (DMA_CFCR_TCF | DMA_CFCR_HTF | DMA_CFCR_DTEF | DMA_CFCR_ULEF | DMA_CFCR_USEF | DMA_CFCR_SUSPF | DMA_CFCR_TOF)

#define RX_BUFFER_SIZE  1024

static uint8_t  rx_buffer[RX_BUFFER_SIZE];
static uint16_t next_read = 0;

static const uint32_t dest_address = (uint32_t)&rx_buffer[0];


static void reset_dma(DMA_Channel_TypeDef *dma_channel)
{
    if ((dma_channel->CSR & DMA_CSR_IDLEF) != DMA_CSR_IDLEF)
    {
        dma_channel->CCR = DMA_CCR_SUSP;

        while ((dma_channel->CSR & DMA_CSR_IDLEF) != DMA_CSR_IDLEF);
    }

    dma_channel->CCR = DMA_CCR_RESET;

    while ((dma_channel->CCR & DMA_CCR_EN) != 0);

    dma_channel->CFCR = DMA_CFCR_ALL;
}

void debug_uart_init(void)
{
    NVIC_DisableIRQ(DEBUG_UART_IRQn);
    NVIC_DisableIRQ(DEBUG_TX_DMAx_Channelx_IRQn);
    NVIC_DisableIRQ(DEBUG_RX_DMAx_Channelx_IRQn);

    peripheral_reset_enable(&RCC->DEBUG_UART_APBx_RSTR, &RCC->DEBUG_UART_APBx_ENR, DEBUG_UART_APBx_ENR_UARTxEN);

    peripheral_enable(&RCC->DEBUG_DMA_AHBxENR, DEBUG_DMA_AHBxENR_DMAxEN);
    peripheral_enable(&RCC->DEBUG_TX_AHBxENR,  DEBUG_TX_AHBxENR_GPIOxEN);
    peripheral_enable(&RCC->DEBUG_RX_AHBxENR,  DEBUG_RX_AHBxENR_GPIOxEN);

    reset_dma(DEBUG_TX_DMAx_Channelx);
    reset_dma(DEBUG_RX_DMAx_Channelx);

    NVIC_ClearPendingIRQ(DEBUG_TX_DMAx_Channelx_IRQn);
    NVIC_EnableIRQ      (DEBUG_TX_DMAx_Channelx_IRQn);

    GPIO_alternate_pull_up_slow(DEBUG_RX_GPIOx, DEBUG_RX_PINx, DEBUG_RX_AFx);

    DEBUG_UARTx->CR1 = 0;
    DEBUG_UARTx->CR2 = 0;
    DEBUG_UARTx->CR3 = (USART_CR3_DMAT | USART_CR3_DMAR);
    DEBUG_UARTx->BRR = ((DEBUG_UART_APBx_CLK + (DEBUG_BAUD / 2)) / DEBUG_BAUD);
    DEBUG_UARTx->CR1 = (USART_CR1_FIFOEN | USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

    GPIO_alternate_push_pull_slow(DEBUG_TX_GPIOx, DEBUG_TX_PINx, DEBUG_TX_AFx);

    DEBUG_RX_DMAx_Channelx->CTR1  = DMA_CTR1_DINC;
    DEBUG_RX_DMAx_Channelx->CTR2  = DEBUG_RX_DMAx_Channelx_CTR2_REQSEL;
    DEBUG_RX_DMAx_Channelx->CBR1  = sizeof rx_buffer;
    DEBUG_RX_DMAx_Channelx->CSAR  = (uint32_t)&DEBUG_UARTx->RDR;
    DEBUG_RX_DMAx_Channelx->CDAR  = (uint32_t)rx_buffer;
    DEBUG_RX_DMAx_Channelx->CLBAR = ((uint32_t)(&dest_address) & DMA_CLBAR_LBA);
    DEBUG_RX_DMAx_Channelx->CLLR  = (((uint32_t)(&dest_address) & DMA_CLLR_LA) | DMA_CLLR_UDA);
    DEBUG_RX_DMAx_Channelx->CCR   = DMA_CCR_EN;
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

uint32_t terminal_read(char *read_buffer, uint32_t read_buffer_size)
{
    uint32_t dma_remaining = (DEBUG_RX_DMAx_Channelx->CBR1 & DMA_CBR1_BNDT);

    uint32_t next_write = ((RX_BUFFER_SIZE - dma_remaining) % RX_BUFFER_SIZE);

    uint32_t available = ((RX_BUFFER_SIZE + next_write - next_read) % RX_BUFFER_SIZE);

    uint32_t transfer_count = MIN(read_buffer_size, available);

    uint32_t count_here = (RX_BUFFER_SIZE - next_read);

    if (transfer_count <= count_here)
    {
        memcpy(read_buffer, &rx_buffer[next_read], transfer_count);
    }
    else
    {
        memcpy(read_buffer, &rx_buffer[next_read], count_here);
        memcpy(&read_buffer[count_here], rx_buffer, (transfer_count - count_here));
    }

    next_read = ((next_read + transfer_count) % RX_BUFFER_SIZE);

    return transfer_count;
}

int terminal_getc(void)
{
    uint32_t dma_remaining = (DEBUG_RX_DMAx_Channelx->CBR1 & DMA_CBR1_BNDT);

    uint32_t next_write = ((RX_BUFFER_SIZE - dma_remaining) % RX_BUFFER_SIZE);

    if (next_write == next_read)
    {
        return -1;
    }
    else
    {
        uint8_t byte = rx_buffer[next_read];

        next_read = ((next_read + 1) % RX_BUFFER_SIZE);

        return byte;
    }
}
