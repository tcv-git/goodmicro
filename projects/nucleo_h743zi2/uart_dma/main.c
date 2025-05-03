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

#include "stm32h7xx.h"
#include "stm32h7xx_it.h"
#include "stm32h7xx_simple_gpio.h"
#include "peripheral_enable.h"
#include "delay.h"
#include "debug_printf.h"

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
    peripheral_reset_enable(&RCC->NEWUART_UART_APBx_RSTR, &RCC->NEWUART_UART_APBx_ENR, NEWUART_UART_APBx_ENR_UARTxEN);

    NEWUART_UARTx->CR1 = 0;
    NEWUART_UARTx->CR2 = 0;
    NEWUART_UARTx->CR3 =  USART_CR3_DMAT;
    NEWUART_UARTx->BRR = ((NEWUART_UART_APBx_CLK + (NEWUART_BAUD / 2)) / NEWUART_BAUD);
    NEWUART_UARTx->CR1 = (USART_CR1_FIFOEN | USART_CR1_TE | USART_CR1_UE);


    peripheral_enable(&RCC->NEWUART_TX_AHBxENR, NEWUART_TX_AHBxENR_GPIOxEN);

    GPIO_alternate_push_pull_slow(NEWUART_TX_GPIOx, NEWUART_TX_PINx, NEWUART_TX_AFx);


    peripheral_enable(&RCC->NEWUART_DMA_AHBxENR, NEWUART_DMA_AHBxENR_DMAxEN);

    DMAMUX1_Channel7->CCR = DMAMUX1_CxCR_DMAREQ_ID_USART3_TX;
}

void newuart_write(const uint8_t *data, uint16_t count);
void newuart_write(const uint8_t *data, uint16_t count)
{
    NEWUART_DMAx->NEWUART_TX_DMA_xIFCR = NEWUART_TX_DMA_xIFCR_CALLIFx;

    NEWUART_TX_DMAx_Streamx->NDTR = count;
    NEWUART_TX_DMAx_Streamx->PAR  = (uint32_t)&(NEWUART_UARTx->TDR);
    NEWUART_TX_DMAx_Streamx->M0AR = (uint32_t)data;
    NEWUART_TX_DMAx_Streamx->FCR  = DMA_SxFCR_DMDIS;  /*| DMA_SxFCR_FEIE */
    NEWUART_TX_DMAx_Streamx->CR   = (DMA_SxCR_TRBUFF
                                   | DMA_SxCR_PL_LOW
                                   | DMA_SxCR_MSIZE_8BIT
                                   | DMA_SxCR_PSIZE_8BIT
                                   | DMA_SxCR_MINC
                                   | DMA_SxCR_DIR_M2P
                                   | DMA_SxCR_EN);
}


int main(void)
{
  debug_uart_init();

  newuart_init();

  static uint8_t buffer[16] = "Static Buffer\r\n";

  newuart_write((uint8_t*)buffer, 15);

  unsigned int i;

  for (i = 0;; i++)
  {
    debug_printf("%u %s", i, (char*)buffer);
    DELAY_MS(100);
  }
}
