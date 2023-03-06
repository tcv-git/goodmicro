// Intermcu protocol decoder
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "clocks.h"
#include "linebuffer.h"
#include "event_queue.h"
#include "terminal.h"
#include "crc.h"
#include "intermcu_protocol.h"

// function in string library but not in string header by default:
void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);

/* output something like:
    >WELCOME_CHALLENGE(seqno) 12 AB 12 AB 12 AB
    <ACK(WELCOME_CHALLENGE,seqno)
    <WELCOME_RESPONSE 23 23 12 56 67 23
    <23 12 45 56 87 65 23
    ^56 23 23 34 87
    <"er df fg d \r\n"
    <MUX OVERFLOW
    <FRAMING ERROR
    <PARITY ERROR
*/

#define BYTE_TIMEOUT_MS 150
#define MIN_STRING_LENGTH 5

static void check_buffer(struct intermcu_decoder *dec);
static void flush_buffer(struct intermcu_decoder *dec);
static inline bool is_printable(uint8_t byte);
static void print_non_packet(struct intermcu_decoder *dec, const uint8_t *data, uint32_t count);
static void print_packet(struct intermcu_decoder *dec, const uint8_t *data, uint32_t count);
static void output_linebuffer(struct intermcu_decoder *dec, uint8_t color);

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
                  uint32_t buffer_size)
{{{
  // 3 bytes in line buffer for each byte in input buffer (to print in hex with spaces)
  dec->input_buffer      = buffer;
  dec->input_buffer_size = (buffer_size / 4);

  linebuffer_init(&dec->output_buffer, &buffer[dec->input_buffer_size], (buffer_size - dec->input_buffer_size));
  linebuffer_write(&dec->output_buffer, (const uint8_t*)&prefix, sizeof prefix);

  dec->prefix       = prefix;
  dec->normal_color = normal_color;
  dec->bold_color   = bold_color;
  dec->super_color  = super_color;

  dec->input_count    = 0;
  dec->could_be_valid = true;
  dec->flush_needed   = false;

  dec->timeout_ticks = ((((uint64_t)BYTE_TIMEOUT_MS * MONOTIME_HZ) + 999) / 1000);
}}}

// report an event to the decoder
// the data argument is only meaningful if the event type is EVENT_DATA
void intermcu_decoder_event(struct intermcu_decoder *dec, enum event_type type, uint8_t data)
{{{
  switch (type)
  {
    case EVENT_DATA:
      // see below
      break;

    case EVENT_HW_TIMEOUT:
      flush_buffer(dec);
      return;

    case EVENT_MUX_OVERRUN:
      flush_buffer(dec);
      linebuffer_printf(&dec->output_buffer, "MUX OVERFLOW");
      output_linebuffer(dec, dec->super_color);
      return;

    case EVENT_HW_OVERRUN:
      flush_buffer(dec);
      linebuffer_printf(&dec->output_buffer, "UART OVERFLOW");
      output_linebuffer(dec, dec->super_color);
      return;

    case EVENT_NOISE_ERROR:
      flush_buffer(dec);
      linebuffer_printf(&dec->output_buffer, "noise error");
      output_linebuffer(dec, dec->bold_color);
      return;

    case EVENT_FRAMING_ERROR:
      flush_buffer(dec);
      linebuffer_printf(&dec->output_buffer, "framing error");
      output_linebuffer(dec, dec->bold_color);
      return;

    case EVENT_PARITY_ERROR:
      flush_buffer(dec);
      linebuffer_printf(&dec->output_buffer, "parity error");
      output_linebuffer(dec, dec->bold_color);
      return;

    default:
      // must be EVENT_NO_DATA
      return;
  }

  // only here if type is EVENT_DATA

  dec->last_data_time = monotime();
  dec->input_buffer[dec->input_count] = data;
  dec->input_count++;

  check_buffer(dec);

  if (dec->input_count == dec->input_buffer_size)
  {
    flush_buffer(dec);
    linebuffer_printf(&dec->output_buffer, "BUFFER FULL");
    output_linebuffer(dec, dec->super_color);
  }
}}}

// this must be called every so often to allow the decoder to do its own timeouts
// (in addition to hardware timeuot events received through the queue)
void intermcu_decoder_poll(struct intermcu_decoder *dec)
{{{
  if (dec->input_count > 0)
  {
    uint64_t now = monotime();

    if ((now - dec->last_data_time) > dec->timeout_ticks)
    {
      flush_buffer(dec);
    }
  }
}}}

// check the contents of the buffer after bytes have been added
// print any whole intermcu packets found
// print any non-protocol bytes which are before an intermcu packet
// but not ones at the end of the buffer (as there may be more to come)
static void check_buffer(struct intermcu_decoder *dec)
{{{
  for (;;)
  {
    if (dec->could_be_valid && (dec->input_count >= 1) && (dec->input_buffer[0] != 0xAA))
    {
      dec->could_be_valid = false;
    }

    if (dec->could_be_valid && (dec->input_count >= 2) && (dec->input_buffer[1] != 0xAA))
    {
      dec->could_be_valid = false;
    }

    if (dec->could_be_valid && (dec->input_count < 5)) // need AA, AA, 1 byte type, 2 bytes length
    {
      if (dec->flush_needed)
      {
        dec->could_be_valid = false;
      }
      else
      {
        return; // need more data
      }
    }

    uint32_t payload_length;

    if (dec->could_be_valid)
    {
      payload_length = ((dec->input_buffer[4] << 8) | dec->input_buffer[3]);

      if ((2 + 4 + payload_length + 2) > dec->input_buffer_size)
      {
        // we can't handle a packet that big
        dec->could_be_valid = false;
      }
    }

    if (dec->could_be_valid)
    {
      if (dec->input_count < (2 + 4 + payload_length + 2))
      {
        if (dec->flush_needed)
        {
          dec->could_be_valid = false;
        }
        else
        {
          return; // need more data
        }
      }
    }

    if (dec->could_be_valid)
    {
      uint16_t received_crc = ((dec->input_buffer[2 + 4 + payload_length] << 8) | dec->input_buffer[2 + 4 + payload_length + 1]);

      uint16_t calculated_crc = crc_calc(&dec->input_buffer[2], (4 + payload_length));

      if (received_crc == calculated_crc)
      {
        print_packet(dec, &dec->input_buffer[2], (4 + payload_length));

        if (dec->input_count == (2 + 4 + payload_length + 2))
        {
          dec->input_count = 0;
          dec->flush_needed = false;
          // dec->could_be_valid stays true
          return;
        }
        else
        {
          dec->input_count -= (2 + 4 + payload_length + 2);
          memmove(dec->input_buffer, &dec->input_buffer[2 + 4 + payload_length + 2], dec->input_count);
          // dec->could_be_valid stays true
          continue;
        }
      }
      else
      {
        dec->could_be_valid = false;
      }
    }

    // by here, dec->could_be_valid must be false

    uint8_t *found = memmem(&dec->input_buffer[1], (dec->input_count - 1), (const uint8_t*)"\xAA\xAA", 2);
    uint32_t discard_size;

    if (found)
    {
      discard_size = (found - dec->input_buffer);

      found = memchr(dec->input_buffer, '\n', discard_size);

      if (found)
      {
        discard_size = ((found + 1) - dec->input_buffer);
      }
    }
    else
    {
      found = memchr(dec->input_buffer, '\n', dec->input_count);

      if (found)
      {
        discard_size = ((found + 1) - dec->input_buffer);
      }
      else
      {
        if (dec->flush_needed)
        {
          discard_size = dec->input_count;
        }
        else
        {
          return; // keep looking for AA AA or '\n' before discarding
        }
      }
    }

    print_non_packet(dec, dec->input_buffer, discard_size);

    if (discard_size == dec->input_count)
    {
      dec->input_count = 0;
      dec->flush_needed = false;
      dec->could_be_valid = true;
      return;
    }
    else
    {
      dec->input_count -= discard_size;
      memmove(dec->input_buffer, &dec->input_buffer[discard_size], dec->input_count);
      dec->could_be_valid = true;
      continue;
    }
  }
}}}

// print the whole contents of the buffer and empty it
// (there definitely isn't a whole intermcu packet at the start of the buffer)
static void flush_buffer(struct intermcu_decoder *dec)
{{{
  dec->flush_needed   = true;
  dec->could_be_valid = false;

  check_buffer(dec);
}}}

// is this a printable ASCII character
static inline bool is_printable(uint8_t byte)
{{{
  return ((byte >= 0x20) && (byte <= 0x7E));
}}}

// is this an ASCII character
static inline bool is_ascii(uint8_t byte)
{{{
  return (((byte >= 0x20) && (byte <= 0x7E)) || (byte == '\f') || (byte == '\v') || (byte == '\r') || (byte == '\n') || (byte == '\t'));
}}}

// output a line representing the non-packet bytes in the arguments
static void print_non_packet(struct intermcu_decoder *dec, const uint8_t *data, uint32_t count)
{{{
  uint8_t color = dec->normal_color;

  uint32_t count_done = 0;

  while (count_done < count)
  {
    if (!is_printable(data[count_done]))
    {
      linebuffer_printf(&dec->output_buffer, " %02X", data[count_done]);
      count_done++;

      if (!is_ascii(data[count_done]))
      {
        color = dec->bold_color; // non-text & non-protocol bytes are unexpected
      }
    }
    else
    {
      uint32_t count_text = 0;

      while (((count_done + count_text) < count) && is_printable(data[count_done + count_text]))
      {
        count_text++;
      }

      if ((count_text >= MIN_STRING_LENGTH) || ((count_done == 0) && (count_text == count)))
      {
        linebuffer_printf(&dec->output_buffer, " \"%.*s\"", (int)count_text, &data[count_done]);
        count_done += count_text;
      }
      else
      {
        uint32_t i;

        for (i = 0; i < count_text; i++)
        {
          linebuffer_printf(&dec->output_buffer, " %02X", data[count_done + i]);
        }

        count_done += count_text;
      }
    }
  }

  output_linebuffer(dec, color);
}}}

// output a line representing one whole packet
// the data argument points to the packet header (excluding the sync bytes)
// the count argument includes the header and payload but not the sync bytes or trailing CRC
static void print_packet(struct intermcu_decoder *dec, const uint8_t *data, uint32_t count)
{{{
  linebuffer_printf(&dec->output_buffer, "packet type %02X length %u", data[0], (unsigned int)count);

  output_linebuffer(dec, dec->normal_color);
}}}

// output the contents of the output line buffer to the terminal in the color specified
// reset the line buffer to contain just the prefix
static void output_linebuffer(struct intermcu_decoder *dec, uint8_t color)
{{{
  // FIXME insert walltime() timestamp

  linebuffer_write(&dec->output_buffer, (const uint8_t*)"\r\n", 2);

  terminal_set_color(color);
  terminal_write(dec->output_buffer.buffer, dec->output_buffer.length);

  // get ready for next time
  dec->output_buffer.length = 0;

  linebuffer_write(&dec->output_buffer, (const uint8_t*)&dec->prefix, sizeof dec->prefix);
}}}
