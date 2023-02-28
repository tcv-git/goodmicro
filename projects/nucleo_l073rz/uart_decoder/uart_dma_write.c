/* Non-blocking write to UART by DMA
 * Copyright Green Energy Options Limited
 */

#include <stdint.h>
#include <stdbool.h>
#include "stm32l0xx.h"
#include "stm32l0xx_simple_gpio.h"
#include "uart_dma_write.h"

// PA2 AF4 USART2_TX

#define PIN_AHBxENR              IOPENR
#define PIN_AHBxENR_GPIOxEN      RCC_IOPENR_IOPAEN
#define PIN_GPIOx                GPIOA
#define PIN_PINx                 PIN2
#define PIN_AFx                  AF4

#define UART_APBx_ENR            APB1ENR
#define UART_APBx_ENR_UARTxEN    RCC_APB1ENR_USART2EN
#define UART_APBx_RSTR           APB1RSTR
#define UART_APBx_RSTR_UARTxRST  RCC_APB1RSTR_USART2RST
#define UARTx                    USART2

#define UART_APBx_CLK            SYSTEM_CORE_CLOCK
#define BAUD_RATE                115200u

#define DMA_AHBxENR              AHBENR
#define DMA_AHBxENR_DMAxEN       RCC_AHBENR_DMAEN
#define DMAx                     DMA1
#define DMAx_Streamx             DMA1_Channel7

#define DMAx_CSELR_CxS           DMA_CSELR_C7S
#define DMAx_CSELR_CxS_VALUE     (4 << DMA_CSELR_C7S_Pos)

#define DMAx_ISR_TCIFx           DMA_ISR_TCIF7
#define DMAx_IFCR_CTCIFx         DMA_IFCR_CTCIF7

/* Prepare UART and DMA for writing.
 */
void uart_write_init(void)
{
  RCC->PIN_AHBxENR    |= PIN_AHBxENR_GPIOxEN;
  RCC->DMA_AHBxENR    |= DMA_AHBxENR_DMAxEN;
  RCC->UART_APBx_RSTR |= UART_APBx_RSTR_UARTxRST;
  RCC->UART_APBx_ENR  |= UART_APBx_ENR_UARTxEN;

  DMAx_Streamx->CCR &= ~DMA_CCR_EN;

  while ((DMAx_Streamx->CCR & DMA_CCR_EN) != 0);

  RCC->UART_APBx_RSTR &= ~UART_APBx_RSTR_UARTxRST;

  DMA1_CSELR->CSELR = ((DMA1_CSELR->CSELR & ~DMAx_CSELR_CxS) | DMAx_CSELR_CxS_VALUE);

  DMAx->IFCR |= DMAx_IFCR_CTCIFx;

  UARTx->CR1 = 0;
  UARTx->CR2 = 0;
  UARTx->CR3 = USART_CR3_DMAT;
  UARTx->BRR = ((UART_APBx_CLK + (BAUD_RATE / 2)) / BAUD_RATE);
  UARTx->CR1 = (USART_CR1_UE | USART_CR1_TE);

  GPIO_alternate_push_pull_slow(PIN_GPIOx, PIN_PINx, PIN_AFx);
}

/* Start DMA writing to the UART.
 *
 * Call only after uart_write_init() or after uart_write_complete() returns
 * true.
 */
void uart_write_start(const uint8_t *data, uint16_t data_count)
{
  DMAx_Streamx->CNDTR = data_count;
  DMAx_Streamx->CPAR  = (uint32_t)&(UARTx->TDR);
  DMAx_Streamx->CMAR  = (uint32_t)data;

  // MEM2MEM=0
  // PL=0(low priority)
  // MSIZE=0(8-bit)
  // PSIZE=0(8-bit)
  // MINC=1
  // PINC=0
  // CIRC=0
  // DIR=1(memory to peripheral)
  DMAx_Streamx->CCR = (DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_EN);
}

/* If the previous write has now completed then prepare to write again and
 * return true, else return false.
 *
 * Call only after uart_write_start().
 */
bool uart_write_complete(void)
{
  if ((DMAx->ISR & DMAx_ISR_TCIFx) != DMAx_ISR_TCIFx)
  {
    return false;
  }

  DMAx_Streamx->CCR &= ~DMA_CCR_EN;

  while ((DMAx_Streamx->CCR & DMA_CCR_EN) != 0);

  DMAx->IFCR |= DMAx_IFCR_CTCIFx;

  return true;
}
