// Ring buffer for passing UART events
// Copyright Green Energy Options Ltd.

#ifndef EVENT_QUEUE_H_INCLUDED
#define EVENT_QUEUE_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum event_type
{
  EVENT_NO_DATA, // events of this type aren't put in the queue but are returned if the queue is empty
  EVENT_HW_TIMEOUT,
  EVENT_DATA,
  EVENT_MUX_OVERRUN, // events of this type aren't put in the queue but are returned if the queue overflowed
  EVENT_HW_OVERRUN,
  EVENT_NOISE_ERROR,
  EVENT_FRAMING_ERROR,
  EVENT_PARITY_ERROR,
};

void     event_queue_init(uint16_t *buffer, uint32_t buffer_count);
void     event_queue_put(enum event_type type, uint_fast8_t channel, uint8_t data);
uint16_t event_queue_get(void);


static inline __attribute__((always_inline)) uint16_t event_pack(enum event_type type, uint_fast8_t channel, uint8_t data)
{
  return ((type << 12) | ((channel & 0xF) << 8) | data);
}

static inline __attribute__((always_inline)) enum event_type event_get_type(uint16_t event)
{
  return (event >> 12);
}

static inline __attribute__((always_inline)) uint_fast8_t event_get_channel(uint16_t event)
{
  return ((event >> 8) & 0xF);
}

static inline __attribute__((always_inline)) uint8_t event_get_data(uint16_t event)
{
  return (event & 0xFF);
}

#ifdef __cplusplus
}
#endif

#endif // EVENT_QUEUE_H_INCLUDED
