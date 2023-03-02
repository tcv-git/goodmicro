// Coloured terminal output with timestamps
// Based on part of dqrs: PUBLIC DOMAIN 2016 <http:///www.purposeful.co.uk/software/dqrs>
// Further modifications: Copyright Green Energy Options Limited

#include <stdint.h>
#include <stdbool.h>
#include "write_buffer.h"
#include "linebuffer.h"
#include "terminal.h"

// need this because we pass lots of string literals as uint8_t*
#pragma GCC diagnostic ignored "-Wpointer-sign"


#define DEFAULT_MODE (WHITE | ON_BLACK)

struct state
{
  bool    mode_ever_written;
  bool    mode_ever_requested;
  uint8_t mode_written;
  uint8_t mode_requested;
};

static struct state state = {false, false, DEFAULT_MODE, DEFAULT_MODE};

static void output_mode (void)
{{{
  uint8_t mode        = DEFAULT_MODE;
  bool    set_bg      = true;
  bool    set_fg      = true;
  bool    set_inverse = true;
  bool    set_weight  = true;

  if (state.mode_ever_requested)
  {
    mode = state.mode_requested;
  }

  if (state.mode_ever_written)
  {
    unsigned int mode_written = state.mode_written;

    set_bg      = ((mode & ON_WHITE) != (mode_written & ON_WHITE));
    set_fg      = ((mode &    WHITE) != (mode_written &    WHITE));
    set_inverse = ((mode &  INVERSE) != (mode_written &  INVERSE));
    set_weight  = ((mode &     BOLD) != (mode_written &     BOLD));
  }

  state.mode_ever_written = true;
  state.mode_written      = mode;

  if (set_bg || set_fg || set_inverse || set_weight)
  {
    write_buffer_write ("\e[", 2);
  }

  if (set_bg)
  {
    switch (mode & ON_WHITE)
    {
      case ON_BLACK   : write_buffer_write ("40", 2); break;
      case ON_RED     : write_buffer_write ("41", 2); break;
      case ON_GREEN   : write_buffer_write ("42", 2); break;
      case ON_YELLOW  : write_buffer_write ("43", 2); break;
      case ON_BLUE    : write_buffer_write ("44", 2); break;
      case ON_MAGENTA : write_buffer_write ("45", 2); break;
      case ON_CYAN    : write_buffer_write ("46", 2); break;
      case ON_WHITE   : write_buffer_write ("47", 2); break;
    }
  }

  if (set_fg)
  {
    if (set_bg)
    {
      write_buffer_write (";", 1);
    }

    switch (mode & WHITE)
    {
      case BLACK   : write_buffer_write ("30", 2); break;
      case RED     : write_buffer_write ("31", 2); break;
      case GREEN   : write_buffer_write ("32", 2); break;
      case YELLOW  : write_buffer_write ("33", 2); break;
      case BLUE    : write_buffer_write ("34", 2); break;
      case MAGENTA : write_buffer_write ("35", 2); break;
      case CYAN    : write_buffer_write ("36", 2); break;
      case WHITE   : write_buffer_write ("37", 2); break;
    }
  }

  if (set_inverse)
  {
    if (set_bg || set_fg)
    {
      write_buffer_write (";", 1);
    }

    if (mode & INVERSE)
    {
      write_buffer_write ("7", 1);
    }
    else
    {
      write_buffer_write ("27", 2);
    }
  }

  if (set_weight)
  {
    if (set_bg || set_fg || set_inverse)
    {
      write_buffer_write (";", 1);
    }

    if (mode & BOLD)
    {
      write_buffer_write ("1", 1);
    }
    else
    {
      write_buffer_write ("22", 2);
    }
  }

  if (set_bg || set_fg || set_inverse || set_weight)
  {
    write_buffer_write ("m", 1);
  }
}}}

void terminal_set_color(uint8_t color)
{{{
  state.mode_ever_requested = true;
  state.mode_requested      = color;
}}}

void terminal_write(const uint8_t *data, uint32_t count)
{{{
  if (count > 0)
  {
    output_mode ();
    write_buffer_write (data, count);
  }
}}}

void terminal_write_line(uint64_t timestamp, uint8_t color, struct linebuffer *lb)
{
  (void)timestamp; // FIXME
  terminal_write (lb->buffer, lb->length);
  lb->length = 0;
}

void terminal_restore(void)
{{{
  terminal_set_color (DEFAULT_MODE);
  output_mode ();
}}}
