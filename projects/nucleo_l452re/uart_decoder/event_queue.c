// Ring buffer for passing UART events
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include <stdbool.h>
#include "event_queue.h"

struct state
{
  uint16_t *buffer;
  uint32_t buffer_count;
  uint32_t next_write;
  uint32_t next_read;
  bool     overflow;
};

static struct state state;


void event_queue_init(uint16_t *buffer, uint32_t buffer_count)
{
  state.buffer        = buffer;
  state.buffer_count = buffer_count;
  state.next_write    = 0;
  state.next_read     = 0;
}

void event_queue_put(enum event_type type, uint_fast8_t channel, uint8_t data)
{
  uint16_t event = event_pack(type, channel, data);

  if (state.overflow)
  {
    state.overflow = false;
    event_queue_put(EVENT_MUX_OVERRUN, 0, 0);  // recurses a maximum of once!
  }

  uint32_t next_next_write = (state.next_write + 1);

  if (next_next_write == state.buffer_count)
  {
    next_next_write = 0;
  }

  if (next_next_write == state.next_read)
  {
    state.overflow = true;
  }
  else
  {
    state.buffer[state.next_write] = event;
    state.next_write = next_next_write;
  }
}

uint16_t event_queue_get(void)
{
  uint32_t next_read = state.next_read;

  if (next_read == state.next_write)
  {
    return event_pack(EVENT_NO_DATA, 0, 0);
  }
  else
  {
    uint16_t event = state.buffer[next_read];

    next_read++;

    if (next_read == state.buffer_count)
    {
      next_read = 0;
    }

    state.next_read = next_read;

    return event;
  }
}

