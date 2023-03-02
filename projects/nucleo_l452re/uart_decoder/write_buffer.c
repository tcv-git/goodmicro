// Write buffer
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "uart_dma_write.h"
#include "write_buffer.h"

struct state
{
  uint8_t *buffer;
  uint32_t buffer_size;

  uint32_t next_write;
  uint32_t read_start;
  uint32_t read_end;
  bool     overflow;
};

static struct state state;

void write_buffer_init(uint8_t *buffer, uint32_t buffer_size)
{
  state.buffer      = buffer;
  state.buffer_size = buffer_size;
  state.next_write  = 0;
  state.read_start  = 0;
  state.read_end    = 0;
  state.overflow    = false;
}

void write_buffer_write(const uint8_t *data, uint32_t data_count)
{
  if (state.overflow)
  {
    return;
  }

  if (state.read_start == 0)
  {
    uint32_t space = ((state.buffer_size - 1) - state.next_write);

    if (data_count <= space)
    {
      memcpy(&state.buffer[state.next_write], data, data_count);

      state.next_write += data_count;
    }
    else
    {
      state.overflow = true;
    }
  }
  else if (state.next_write >= state.read_start)
  {
    uint32_t space_here = (state.buffer_size - state.next_write);
    uint32_t total_space = (space_here + (state.read_start - 1));

    if (data_count < space_here)
    {
      memcpy(&state.buffer[state.next_write], data, data_count);

      state.next_write += data_count;
    }
    else if (data_count <= total_space)
    {
      uint32_t remainder = (data_count - space_here);

      memcpy(&state.buffer[state.next_write], data, space_here);

      memcpy(state.buffer, &data[space_here], remainder);

      state.next_write = remainder;
    }
    else
    {
      state.overflow = true;
    }
  }
  else
  {
    uint32_t space = ((state.read_start - 1) - state.next_write);

    if (data_count <= space)
    {
      memcpy(&state.buffer[state.next_write], data, data_count);

      state.next_write += data_count;
    }
    else
    {
      state.overflow = true;
    }
  }
}

void write_buffer_poll(void)
{
  if (state.read_end != state.read_start)
  {
    if (uart_write_complete())
    {
      state.read_start = state.read_end;
    }
  }

  if (state.overflow)
  {
    uint8_t overflow_marker = '\v';

    state.overflow = false;

    write_buffer_write(&overflow_marker, sizeof overflow_marker);
  }

  if (state.read_end != state.read_start)
  {
    return;
  }

  if (state.read_start < state.next_write)
  {
    uart_write_start(&state.buffer[state.read_start], (state.next_write - state.read_start));
    state.read_end = state.next_write;
  }
  else if (state.read_start > state.next_write)
  {
    uart_write_start(&state.buffer[state.read_start], (state.buffer_size - state.read_start));
    state.read_end = 0;
  }
  else
  {
    // it's empty
  }
}

void write_buffer_printf(const char *format, ...)
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

  write_buffer_write(buffer, len);
}

void write_buffer_flush(void)
{
  while ((state.read_end != state.read_start) || (state.read_start != state.next_write))
  {
    write_buffer_poll();
  }
}
