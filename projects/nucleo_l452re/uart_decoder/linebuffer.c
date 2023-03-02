// Formatted print to a write buffer
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "write_buffer.h"
#include "wb_printf.h"

struct write_buffer wb;


void wb_init(uint8_t *buffer, uint32_t buffer_size)
{
  write_buffer_init(&wb, buffer, buffer_size);
}

void wb_poll(void)
{
  write_buffer_poll(&wb);
}

void wb_printf(const char *format, ...)
{
  uint8_t buffer[128];
  va_list args;

  va_start(args, format);
  int len = vsnprintf((char*)buffer, sizeof buffer, format, args);
  va_end(args);

  if (len < 0)
  {
    len = 0;
  }

  if ((size_t)len >= sizeof buffer)
  {
    len = ((sizeof buffer) - 1);
  }

  write_buffer_write(&wb, buffer, len);
}
