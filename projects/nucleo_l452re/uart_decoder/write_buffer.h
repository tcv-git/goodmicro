// Write buffer
// Copyright Green Energy Options Ltd.

#ifndef WRITE_BUFFER_H_INCLUDED
#define WRITE_BUFFER_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void write_buffer_init(uint8_t *buffer, uint32_t buffer_size);
void write_buffer_write(const uint8_t *data, uint32_t data_count);
void write_buffer_printf(const char *format, ...) __attribute__((format(printf,1,2)));
void write_buffer_poll(void);
void write_buffer_flush(void);

#ifdef __cplusplus
}
#endif

#endif // WRITE_BUFFER_H_INCLUDED
