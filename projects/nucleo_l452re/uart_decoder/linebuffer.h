// Formatted print to a write buffer
// Copyright Green Energy Options Ltd.

#ifndef WB_PRINTF_H_INCLUDED
#define WB_PRINTF_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void wb_init(uint8_t *buffer, uint32_t buffer_size);
void wb_poll(void);
void wb_printf(const char *format, ...) __attribute__((format(printf,1,2)));

#ifdef __cplusplus
}
#endif

#endif // WB_PRINTF_H_INCLUDED
