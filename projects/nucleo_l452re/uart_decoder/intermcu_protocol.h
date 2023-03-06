// Intermcu protocol decoder
// Copyright Green Energy Options Ltd.

#ifndef INTERMCU_PROTOCOL_H_INCLUDED
#define INTERMCU_PROTOCOL_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "linebuffer.h"
#include "event_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

struct intermcu_decoder
{
  struct linebuffer output_buffer;
  uint8_t          *input_buffer;
  uint32_t          input_buffer_size;

  char     prefix;
  uint8_t  normal_color;
  uint8_t  bold_color;
  uint8_t  super_color;

  uint32_t input_count;
  bool     could_be_valid;
  bool     flush_needed;

  uint64_t last_data_time;
  uint64_t timeout_ticks;
};

// set up an intermcu protocol decoder
// prefix is a byte that is prepended to every line printed to the terminal
// normal, bold and super colours are the terminal output modes for different message severities
// a byte buffer must be provided which will be shared betweeb input and output buffers
void intermcu_decoder_init(struct intermcu_decoder *dec,
                  char prefix,
                  uint8_t normal_color,
                  uint8_t bold_color,
                  uint8_t super_color,
                  uint8_t *buffer,
                  uint32_t buffer_size);

// report an event to the decoder
// the data argument is only meaningful if the event type is EVENT_DATA
void intermcu_decoder_event(struct intermcu_decoder *dec, enum event_type type, uint8_t data);

// this must be called every so often to allow the decoder to do its own timeouts
// (in addition to hardware timeuot events received through the queue)
void intermcu_decoder_poll(struct intermcu_decoder *dec);

#ifdef __cplusplus
}
#endif

#endif // INTERMCU_PROTOCOL_H_INCLUDED
