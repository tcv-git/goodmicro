/* Non-blocking write to UART by DMA
 * Copyright Green Energy Options Limited
 */

#ifndef UART_DMA_WRITE_H_INCLUDED
#define UART_DMA_WRITE_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Prepare UART and DMA for writing.
 */
void uart_write_init(void);

/* Start DMA writing to the UART.
 *
 * Call only after uart_write_init() or after uart_write_complete() returns
 * true.
 */
void uart_write_start(const uint8_t *data, uint16_t data_count);

/* If the previous write has now completed then prepare to write again and
 * return true, else return false.
 *
 * Call only after uart_write_start().
 */
bool uart_write_complete(void);

#ifdef __cplusplus
}
#endif

#endif // UART_DMA_WRITE_H_INCLUDED
