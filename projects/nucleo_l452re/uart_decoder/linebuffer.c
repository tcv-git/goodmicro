// Formatted print to a line buffer
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "linebuffer.h"

#define MIN_STRING_LENGTH 3

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

void linebuffer_print_hex(struct linebuffer *lb, const uint8_t *data, uint32_t count)
{
  uint32_t i;

  for (i = 0; i < count; i++)
  {
    linebuffer_printf(lb, " %02X", data[i]);
  }
}

// return true if it was all ASCII, false if reverted to hex
bool linebuffer_print_string(struct linebuffer *lb, const uint8_t *data, uint32_t count)
{
  uint32_t count_nuls = 0;

  while ((count_nuls < count) && (data[count - (count_nuls + 1)] == '\0'))
  {
    count_nuls++;
  }

  if (count_nuls > 1)
  {
    count -= count_nuls;
  }

  bool     to_return = true;
  uint32_t count_done = 0;

  while (count_done < count)
  {
    uint32_t text_length = 0;

    while (((count_done + text_length) < count) && (data[count_done + text_length] >= 0x20) && (data[count_done + text_length] <= 0x7E))
    {
      text_length++;
    }

    if ((text_length >= MIN_STRING_LENGTH) || ((text_length > 0) && ((count_done + text_length) == count)))
    {
      linebuffer_printf(lb, " \"%.*s\"", (int)text_length, (const char*)&data[count_done]);
      count_done += text_length;
    }

    if (count_done < count)
    {
      switch (data[count_done])
      {
        case '\0': linebuffer_write(lb, (const uint8_t*)" \\0", 3); break;
        case '\f': linebuffer_write(lb, (const uint8_t*)" \\f", 3); break;
        case '\v': linebuffer_write(lb, (const uint8_t*)" \\v", 3); break;
        case '\r': linebuffer_write(lb, (const uint8_t*)" \\r", 3); break;
        case '\n': linebuffer_write(lb, (const uint8_t*)" \\n", 3); break;
        case '\t': linebuffer_write(lb, (const uint8_t*)" \\t", 3); break;
        default:   linebuffer_printf(lb, " %02X", data[count_done]); to_return = false; // non-text found
      }
      count_done++;
    }
  }

  if (count_nuls > 1)
  {
    linebuffer_printf(lb, " \\0{%u}", (unsigned int)count_nuls);
  }

  return to_return;
}
