// Write buffer
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "uart_dma_write.h"
#include "write_buffer.h"


void write_buffer_init(struct write_buffer *wb, uint8_t *buffer, uint32_t buffer_size)
{
  wb->buffer      = buffer;
  wb->buffer_size = buffer_size;
  wb->next_write  = 0;
  wb->read_start  = 0;
  wb->read_end    = 0;
  wb->overflow    = false;

  uart_write_init();
}

void write_buffer_write(struct write_buffer *wb, const uint8_t *data, uint32_t data_count)
{
  if (wb->overflow)
  {
    return;
  }

  if (wb->read_start == 0)
  {
    uint32_t space = ((wb->buffer_size - 1) - wb->next_write);

    if (data_count <= space)
    {
      memcpy(&wb->buffer[wb->next_write], data, data_count);

      wb->next_write += data_count;
    }
    else
    {
      wb->overflow = true;
    }
  }
  else if (wb->next_write >= wb->read_start)
  {
    uint32_t space_here = (wb->buffer_size - wb->next_write);
    uint32_t total_space = (space_here + (wb->read_start - 1));

    if (data_count < space_here)
    {
      memcpy(&wb->buffer[wb->next_write], data, data_count);

      wb->next_write += data_count;
    }
    else if (data_count <= total_space)
    {
      uint32_t remainder = (data_count - space_here);

      memcpy(&wb->buffer[wb->next_write], data, space_here);

      memcpy(wb->buffer, &data[space_here], remainder);

      wb->next_write = remainder;
    }
    else
    {
      wb->overflow = true;
    }
  }
  else
  {
    uint32_t space = ((wb->read_start - 1) - wb->next_write);

    if (data_count <= space)
    {
      memcpy(&wb->buffer[wb->next_write], data, data_count);

      wb->next_write += data_count;
    }
    else
    {
      wb->overflow = true;
    }
  }
}

void write_buffer_poll(struct write_buffer *wb)
{
  if (wb->read_end != wb->read_start)
  {
    if (uart_write_complete())
    {
      wb->read_start = wb->read_end;
    }
  }

  if (wb->overflow)
  {
    uint8_t overflow_marker = '\f';

    wb->overflow = false;

    write_buffer_write(wb, &overflow_marker, sizeof overflow_marker);
  }

  if (wb->read_end != wb->read_start)
  {
    return;
  }

  if (wb->read_start < wb->next_write)
  {
    uart_write_start(&wb->buffer[wb->read_start], (wb->next_write - wb->read_start));
    wb->read_end = wb->next_write;
  }
  else if (wb->read_start > wb->next_write)
  {
    uart_write_start(&wb->buffer[wb->read_start], (wb->buffer_size - wb->read_start));
    wb->read_end = 0;
  }
  else
  {
    // it's empty
  }
}
