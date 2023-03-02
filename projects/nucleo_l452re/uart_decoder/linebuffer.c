// Formatted print to a line buffer
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "linebuffer.h"

void linebuffer_init(struct linebuffer *lb, uint8_t *buffer, uint32_t buffer_size)
{
  lb->buffer = buffer;
  lb->size   = buffer_size;
  lb->length = 0;
}

void linebuffer_write(struct linebuffer *lb, const uint8_t *data, uint32_t count)
{
  uint32_t space = (lb->size - lb->length);

  if (count <= space)
  {
    memcpy(&lb->buffer[lb->length], data, count);
    lb->length += count;
  }
  else
  {
    memcpy(&lb->buffer[lb->length], data, space);
    lb->length = lb->size;
  }
}

void linebuffer_printf(struct linebuffer *lb, const char *format, ...)
{
  uint32_t space = (lb->size - lb->length);
  va_list args;

  va_start(args, format);
  int written = vsnprintf((char*)&lb->buffer[lb->length], space, format, args);
  va_end(args);

  if (written < 0)
  {
    written = 0;
  }

  if ((uint32_t)written < space)
  {
    lb->length += written;
  }
  else
  {
    lb->buffer[lb->size - 1] = '-'; // hyphen to show truncation
    lb->length = lb->size;
  }
}
