// main.c
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
#include "stm32h7xx.h"
#include "stm32h7xx_it.h"
#include "stm32h7xx_simple_gpio.h"
#include "peripheral_enable.h"
#include "delay.h"
#include "debug_printf.h"
#include "printf_queue.h"

////////////////////////////////////////////////////////////////////////

#define DMA_SxCR_MSIZE_8BIT                              0
#define DMA_SxCR_MSIZE_16BIT              DMA_SxCR_MSIZE_0
#define DMA_SxCR_MSIZE_32BIT              DMA_SxCR_MSIZE_1

#define DMA_SxCR_PL_LOW                   (                            0)
#define DMA_SxCR_PL_MEDIUM                (                DMA_SxCR_PL_0)
#define DMA_SxCR_PL_HIGH                  (DMA_SxCR_PL_1                )
#define DMA_SxCR_PL_VHIGH                 (DMA_SxCR_PL_1 | DMA_SxCR_PL_0)

#define DMA_SxCR_MSIZE_8BIT                              0
#define DMA_SxCR_MSIZE_16BIT              DMA_SxCR_MSIZE_0
#define DMA_SxCR_MSIZE_32BIT              DMA_SxCR_MSIZE_1
#define DMA_SxCR_PSIZE_8BIT                              0
#define DMA_SxCR_PSIZE_16BIT              DMA_SxCR_PSIZE_0
#define DMA_SxCR_PSIZE_32BIT              DMA_SxCR_PSIZE_1

#define DMA_SxCR_DIR_P2M                               0
#define DMA_SxCR_DIR_M2P                  DMA_SxCR_DIR_0
#define DMA_SxCR_DIR_M2M                  DMA_SxCR_DIR_1

#define DMAMUX1_CxCR_DMAREQ_ID_USART1_TX  42
#define DMAMUX1_CxCR_DMAREQ_ID_USART3_TX  46

////////////////////////////////////////////////////////////////////////

#define NEWUART_TX_AHBxENR                  AHB4ENR
#define NEWUART_TX_AHBxENR_GPIOxEN          RCC_AHB4ENR_GPIODEN
#define NEWUART_TX_GPIOx                    GPIOD
#define NEWUART_TX_PINx                     PIN8
#define NEWUART_TX_AFx                      AF7

#define NEWUART_UART_APBx_ENR               APB1LENR
#define NEWUART_UART_APBx_ENR_UARTxEN       RCC_APB1LENR_USART3EN
#define NEWUART_UART_APBx_RSTR              APB1LRSTR
#define NEWUART_UART_APBx_RSTR_UARTxRST     RCC_APB1LRSTR_USART3RST
#define NEWUART_UARTx                       USART3

#define NEWUART_UART_APBx_CLK               120000000u
#define NEWUART_BAUD                        115200u

#define NEWUART_UART_IRQn                   USART3_IRQn
#define NEWUART_UART_IRQHandler             USART3_IRQHandler

#define NEWUART_DMA_AHBxENR                 AHB1ENR
#define NEWUART_DMA_AHBxENR_DMAxEN          RCC_AHB1ENR_DMA1EN
#define NEWUART_DMAx                        DMA1

#define NEWUART_TX_DMA_xISR                 HISR
#define NEWUART_TX_DMA_xIFCR                HIFCR

#define NEWUART_TX_DMA_xISR_TCIFx           DMA_HISR_TCIF7
#define NEWUART_TX_DMA_xISR_HTIFx           DMA_HISR_HTIF7
#define NEWUART_TX_DMA_xISR_TEIFx           DMA_HISR_TEIF7
#define NEWUART_TX_DMA_xISR_DMEIFx          DMA_HISR_DMEIF7
#define NEWUART_TX_DMA_xISR_FEIFx           DMA_HISR_FEIF7

#define NEWUART_TX_DMA_xIFCR_CTCIFx         DMA_HIFCR_CTCIF7
#define NEWUART_TX_DMA_xIFCR_CHTIFx         DMA_HIFCR_CHTIF7
#define NEWUART_TX_DMA_xIFCR_CTEIFx         DMA_HIFCR_CTEIF7
#define NEWUART_TX_DMA_xIFCR_CDMEIFx        DMA_HIFCR_CDMEIF7
#define NEWUART_TX_DMA_xIFCR_CFEIFx         DMA_HIFCR_CFEIF7

#define NEWUART_TX_DMAx_Streamx             DMA1_Stream7
#define NEWUART_TX_DMAx_Streamx_IRQn        DMA1_Stream7_IRQn
#define NEWUART_TX_DMAx_Streamx_IRQHandler  DMA1_Stream7_IRQHandler

#define NEWUART_TX_DMAMUXx_Channelx         DMAMUX1_Channel7
#define NEWUART_TX_DMAMUXx_CxCR_DMAREQ_ID   DMAMUX1_CxCR_DMAREQ_ID_USART3_TX

////////////////////////////////////////////////////////////////////////

#define NEWUART_TX_DMA_xISR_ALLIFx    (NEWUART_TX_DMA_xISR_TCIFx   | NEWUART_TX_DMA_xISR_HTIFx   | NEWUART_TX_DMA_xISR_TEIFx   | NEWUART_TX_DMA_xISR_DMEIFx   | NEWUART_TX_DMA_xISR_FEIFx  )
#define NEWUART_TX_DMA_xIFCR_CALLIFx  (NEWUART_TX_DMA_xIFCR_CTCIFx | NEWUART_TX_DMA_xIFCR_CHTIFx | NEWUART_TX_DMA_xIFCR_CTEIFx | NEWUART_TX_DMA_xIFCR_CDMEIFx | NEWUART_TX_DMA_xIFCR_CFEIFx)

////////////////////////////////////////////////////////////////////////

void newuart_init(void);
void newuart_init(void)
{
    NVIC_DisableIRQ(NEWUART_TX_DMAx_Streamx_IRQn);
    NVIC_DisableIRQ(NEWUART_UART_IRQn);

    peripheral_enable(&RCC->NEWUART_DMA_AHBxENR, NEWUART_DMA_AHBxENR_DMAxEN);

    while (NEWUART_TX_DMAx_Streamx->CR != 0)
    {
      NEWUART_TX_DMAx_Streamx->CR = 0;
    }

    NEWUART_DMAx->NEWUART_TX_DMA_xIFCR = (NEWUART_DMAx->NEWUART_TX_DMA_xISR & NEWUART_TX_DMA_xIFCR_CALLIFx);
    NEWUART_TX_DMAMUXx_Channelx->CCR   = NEWUART_TX_DMAMUXx_CxCR_DMAREQ_ID;
    NEWUART_TX_DMAx_Streamx->M0AR      = 0;

    NVIC_ClearPendingIRQ(NEWUART_TX_DMAx_Streamx_IRQn);
    NVIC_EnableIRQ      (NEWUART_TX_DMAx_Streamx_IRQn);

    peripheral_reset_enable(&RCC->NEWUART_UART_APBx_RSTR, &RCC->NEWUART_UART_APBx_ENR, NEWUART_UART_APBx_ENR_UARTxEN);

    NEWUART_UARTx->CR1 = 0;
    NEWUART_UARTx->CR2 = 0;
    NEWUART_UARTx->CR3 =  USART_CR3_DMAT;
    NEWUART_UARTx->BRR = ((NEWUART_UART_APBx_CLK + (NEWUART_BAUD / 2)) / NEWUART_BAUD);
    NEWUART_UARTx->CR1 = (USART_CR1_FIFOEN | USART_CR1_TE | USART_CR1_UE);

    peripheral_enable(&RCC->NEWUART_TX_AHBxENR, NEWUART_TX_AHBxENR_GPIOxEN);

    GPIO_alternate_push_pull_slow(NEWUART_TX_GPIOx, NEWUART_TX_PINx, NEWUART_TX_AFx);
}

void NEWUART_TX_DMAx_Streamx_IRQHandler(void)
{
  if ((NEWUART_DMAx->NEWUART_TX_DMA_xISR & NEWUART_TX_DMA_xISR_TEIFx) != 0)
  {
    // set permanent break condition
    GPIO_set_reset             (NEWUART_TX_GPIOx, LO(NEWUART_TX_PINx));
    GPIO_output_push_pull_slow (NEWUART_TX_GPIOx, NEWUART_TX_PINx);

    RCC->NEWUART_UART_APBx_RSTR |=  NEWUART_UART_APBx_RSTR_UARTxRST;
    RCC->NEWUART_UART_APBx_ENR  &= ~NEWUART_UART_APBx_ENR_UARTxEN;

    while (NEWUART_TX_DMAx_Streamx->CR != 0)
    {
      NEWUART_TX_DMAx_Streamx->CR = 0;
    }

    NEWUART_DMAx->NEWUART_TX_DMA_xIFCR = (NEWUART_DMAx->NEWUART_TX_DMA_xISR & NEWUART_TX_DMA_xIFCR_CALLIFx);

    NVIC_DisableIRQ      (NEWUART_TX_DMAx_Streamx_IRQn);
    NVIC_ClearPendingIRQ (NEWUART_TX_DMAx_Streamx_IRQn);
    return;
  }

  if ((NEWUART_TX_DMAx_Streamx->CR & DMA_SxCR_EN) == DMA_SxCR_EN)
  {
    return;
  }

  const char *old_buffer = (const char*)NEWUART_TX_DMAx_Streamx->M0AR;

  if (old_buffer)
  {
    NEWUART_TX_DMAx_Streamx->M0AR = 0;
    printf_queue_free(old_buffer);
  }

  uint16_t byte_count;
  char *buffer = printf_queue_get_crlf(&byte_count);

  if (!buffer)
  {
    NEWUART_DMAx->NEWUART_TX_DMA_xIFCR = (NEWUART_DMAx->NEWUART_TX_DMA_xISR & NEWUART_TX_DMA_xIFCR_CALLIFx);
    return;
  }

  SCB_CleanInvalidateDCache_by_Addr(buffer, byte_count);

  uint32_t buffer_address = (uint32_t)buffer;
  uint32_t alignment      = (byte_count | buffer_address);
  uint32_t msize;

  switch (alignment & 3)
  {
    case 0:  msize = DMA_SxCR_MSIZE_32BIT; break;
    case 2:  msize = DMA_SxCR_MSIZE_16BIT; break;
    default: msize = DMA_SxCR_MSIZE_8BIT;
  }

  NEWUART_DMAx->NEWUART_TX_DMA_xIFCR = (NEWUART_DMAx->NEWUART_TX_DMA_xISR & NEWUART_TX_DMA_xIFCR_CALLIFx);

  NVIC_ClearPendingIRQ(NEWUART_TX_DMAx_Streamx_IRQn);

  NEWUART_TX_DMAx_Streamx->NDTR = byte_count;
  NEWUART_TX_DMAx_Streamx->PAR  = (uint32_t)&(NEWUART_UARTx->TDR);
  NEWUART_TX_DMAx_Streamx->M0AR = buffer_address;
  NEWUART_TX_DMAx_Streamx->FCR  = DMA_SxFCR_DMDIS;
  NEWUART_TX_DMAx_Streamx->CR   = (DMA_SxCR_TCIE
                                   | DMA_SxCR_TRBUFF
                                   | DMA_SxCR_PL_LOW
                                   | msize
                                   | DMA_SxCR_PSIZE_8BIT
                                   | DMA_SxCR_MINC
                                   | DMA_SxCR_DIR_M2P
                                   | DMA_SxCR_EN);
}

static void newuart_vprintf(const char *format, va_list args);
static void newuart_vprintf(const char *format, va_list args)
{
  printf_queue_put(format, args);

  if ((NEWUART_TX_DMAx_Streamx->CR & DMA_SxCR_EN) != DMA_SxCR_EN)
  {
    NVIC_SetPendingIRQ(NEWUART_TX_DMAx_Streamx_IRQn);
    NVIC_EnableIRQ    (NEWUART_TX_DMAx_Streamx_IRQn);
  }
}

void newuart_printf(const char *format, ...);
void newuart_printf(const char *format, ...)
{
  va_list args;

  va_start(args, format);
  newuart_vprintf(format, args);
  va_end(args);
}

void newuart_putc(unsigned char c);
void newuart_putc(unsigned char c)
{
  newuart_printf("%c", c);
}


int main(void)
{
  debug_uart_init();

  newuart_init();

  unsigned int i;

  for (i = 0;; i++)
  {
    newuart_printf("%u\n", i);

    debug_printf("%u\n", i);
    DELAY_MS(1000);
  }
}
