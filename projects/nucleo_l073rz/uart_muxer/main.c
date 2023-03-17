// main.c
// Copyright Green Energy Options Ltd.

#include "stm32l0xx.h"
#include "stm32l0xx_simple_gpio.h"

#define UART_APBx_CLK   SYSTEM_CORE_CLOCK
#define READ_BAUD       115200u
#define WRITE_BAUD      (1000u * 1000)

#define LUT_INDEX_OVERRUN       4
#define LUT_INDEX_FRAMING_ERROR 5
#define LUT_INDEX_NOISE_ERROR   6

static const uint8_t CH1_LUT[ 7] = ".,:;#{}";
static const uint8_t CH2_LUT[ 7] = "-_=|@()";
static const uint8_t CH3_LUT[ 7] = "!?&$%[]";
static const uint8_t LSB_LUT[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// chars left:  "'*<>\^`~

static void uart_write_init(USART_TypeDef *uart)
{
  uart->CR1 = 0;
  uart->CR2 = 0;
  uart->CR3 = 0;
  uart->BRR = ((UART_APBx_CLK + (WRITE_BAUD / 2)) / WRITE_BAUD);
  uart->CR1 = (USART_CR1_UE | USART_CR1_TE);
}

static void uart_read_init(USART_TypeDef *uart)
{
  uart->CR1 = 0;
  uart->CR2 = 0;
  uart->CR3 = 0;
  uart->BRR = ((UART_APBx_CLK + (READ_BAUD / 2)) / READ_BAUD);
  uart->CR1 = (USART_CR1_UE | USART_CR1_RE);
}

static inline void uart_putc(uint8_t byte)
{
  while ((USART2->ISR & USART_ISR_TXE) != USART_ISR_TXE);

  USART2->TDR = byte;
}

static inline void uart_read(USART_TypeDef *uart, const uint8_t *msb_lut)
{
  uint32_t isr = uart->ISR;

  if ((isr & USART_ISR_ORE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_ORECF | USART_ICR_FECF | USART_ICR_NECF);
    uart_putc(msb_lut[LUT_INDEX_OVERRUN]);
  }

  else if ((isr & USART_ISR_FE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_FECF | USART_ICR_NECF);
    uart_putc(msb_lut[LUT_INDEX_FRAMING_ERROR]);
  }

  else if ((isr & USART_ISR_NE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = USART_ICR_NECF;
    uart_putc(msb_lut[LUT_INDEX_NOISE_ERROR]);
  }

  else if ((isr & USART_ISR_RXNE) != 0)
  {
    uint8_t data = uart->RDR;
    uart_putc(msb_lut[(data >> 6) & 3]);
    uart_putc(LSB_LUT[data & 63]);
  }

  else
  {
    // nothing
  }
}

int main(void)
{
  /*
  Pinout:
  PA2  AF4 USART2_TX
  PB7  AF0 USART1_RX
  PA1  AF6 USART4_RX
  PD2  AF6 USART5_RX
  */

  RCC->IOPENR   |=  RCC_IOPENR_IOPAEN;
  RCC->IOPENR   |=  RCC_IOPENR_IOPBEN;
  RCC->IOPENR   |=  RCC_IOPENR_IOPDEN;
  RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST;
  RCC->APB1RSTR |=  RCC_APB1RSTR_USART2RST;
  RCC->APB1RSTR |=  RCC_APB1RSTR_USART4RST;
  RCC->APB1RSTR |=  RCC_APB1RSTR_USART5RST;
  RCC->APB2ENR  |=  RCC_APB2ENR_USART1EN;
  RCC->APB1ENR  |=  RCC_APB1ENR_USART2EN;
  RCC->APB1ENR  |=  RCC_APB1ENR_USART4EN;
  RCC->APB1ENR  |=  RCC_APB1ENR_USART5EN;
  RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
  RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
  RCC->APB1RSTR &= ~RCC_APB1RSTR_USART4RST;
  RCC->APB1RSTR &= ~RCC_APB1RSTR_USART5RST;

  GPIO_alternate_push_pull_slow(GPIOA, PIN2, AF4);
  GPIO_alternate_push_pull_slow(GPIOB, PIN7, AF0);
  GPIO_alternate_push_pull_slow(GPIOA, PIN1, AF6);
  GPIO_alternate_push_pull_slow(GPIOD, PIN2, AF6);

  uart_write_init(USART2);
  uart_read_init(USART1);
  uart_read_init(USART4);
  uart_read_init(USART5);

  for (;;)
  {
    uart_read(USART1, CH1_LUT);
    uart_read(USART4, CH2_LUT);
    uart_read(USART5, CH3_LUT);
  }
}
/* TODO:
 * send commands back the other way:
 *   -will need a ring buffer because its faster
 *   -will need a "buffer full" message
 *
 * enable 7bit+parity on console?
 * newlines on console
 */
