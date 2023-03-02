// Formatted print to a line buffer
// Copyright Green Energy Options Ltd.

#ifndef LINEBUFFER_H_INCLUDED
#define LINEBUFFER_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct linebuffer
{
  uint8_t *buffer;
  uint32_t size;
  uint32_t length;
};

void linebuffer_init(struct linebuffer *lb, uint8_t *buffer, uint32_t buffer_size);
void linebuffer_write(struct linebuffer *lb, const uint8_t *data, uint32_t count);
void linebuffer_printf(struct linebuffer *lb, const char *format, ...) __attribute__((format(printf,2,3)));


#ifdef __cplusplus
}
#endif

#endif // LINEBUFFER_H_INCLUDED
