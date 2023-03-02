// Write buffer
// Copyright Green Energy Options Ltd.

#ifndef WRITE_BUFFER_H_INCLUDED
#define WRITE_BUFFER_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct write_buffer
{
  uint8_t *buffer;
  uint32_t buffer_size;

  uint32_t next_write;
  uint32_t read_start;
  uint32_t read_end;
  bool     overflow;
};

void write_buffer_init(struct write_buffer *wb, uint8_t *buffer, uint32_t buffer_size);
void write_buffer_write(struct write_buffer *wb, const uint8_t *data, uint32_t data_count);
void write_buffer_poll(struct write_buffer *wb);
void write_buffer_flush(struct write_buffer *wb);

#ifdef __cplusplus
}
#endif

#endif // WRITE_BUFFER_H_INCLUDED
