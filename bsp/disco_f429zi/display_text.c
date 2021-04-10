// display_text.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/software/goodmicro

/*
  Except as noted below,
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all copyright and other intellectual property rights
  in them.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  If you use, modify or distribute this software then you do so at your own
  risk.  If you do not pass on this warning then you may be responsible for any
  problems encountered by those who obtain the software through you.
*/

#include <string.h>
#include "lcd.h"
#include "display_text.h"

#define  COLS        40
#define  ROWS        40
#define  TABSTOP     8
#define  FIRST_CHAR  0x20
#define  LAST_CHAR   0x7E
#define  FONT_WIDTH  6
#define  FONT_HEIGHT 8
#define  BACKGROUND  0x00000040u
#define  FOREGROUND  0xFFFFFF1Cu

/*
  I can't remember where I got this font, or if I created it myself.

  There have been several court cases which found that (in the USA at least) bitmap fonts are ineligible
  for copyright.  In any case, if you think this is yours and want your name here or want it removed then
  let me know.
*/
static const unsigned short font [(LAST_CHAR - FIRST_CHAR) + 1] [3] = {
  {0x0000, 0x0000, 0x0000},  {0x0000, 0x002E, 0x0000},  {0x0600, 0x0600, 0x0000},  {0x1400, 0x143E, 0x143E},
  {0x2800, 0x762C, 0x0014},  {0x0200, 0x0830, 0x2006},  {0x1400, 0x2A2A, 0x2810},  {0x0000, 0x0006, 0x0000},
  {0x0000, 0x221C, 0x0000},  {0x0000, 0x1C22, 0x0000},  {0x0A00, 0x0A04, 0x0000},  {0x0800, 0x081C, 0x0000},
  {0x4000, 0x0020, 0x0000},  {0x0800, 0x0808, 0x0000},  {0x0000, 0x0020, 0x0000},  {0x2000, 0x0810, 0x0204},
  {0x1C00, 0x2222, 0x001C},  {0x0000, 0x3E02, 0x0000},  {0x3200, 0x2A2A, 0x0024},  {0x2200, 0x2A2A, 0x0014},
  {0x1800, 0x3E14, 0x0010},  {0x2E00, 0x2A2A, 0x0012},  {0x1C00, 0x2A2A, 0x0010},  {0x0200, 0x0A32, 0x0006},
  {0x1400, 0x2A2A, 0x0014},  {0x0400, 0x2A2A, 0x001C},  {0x0000, 0x0014, 0x0000},  {0x4000, 0x0024, 0x0000},
  {0x0800, 0x2214, 0x0000},  {0x1400, 0x1414, 0x0000},  {0x2200, 0x0814, 0x0000},  {0x0200, 0x0A2A, 0x0004},
  {0x1C00, 0x3A22, 0x1C2A},  {0x3C00, 0x1212, 0x003C},  {0x3E00, 0x2A2A, 0x0014},  {0x1C00, 0x2222, 0x0000},
  {0x3E00, 0x2222, 0x001C},  {0x3E00, 0x2A2A, 0x0000},  {0x3E00, 0x0A0A, 0x0000},  {0x1C00, 0x2A22, 0x003A},
  {0x3E00, 0x0808, 0x003E},  {0x2200, 0x223E, 0x0000},  {0x1000, 0x2220, 0x001E},  {0x3E00, 0x1408, 0x0022},
  {0x3E00, 0x2020, 0x0000},  {0x3E00, 0x0804, 0x3E04},  {0x3E00, 0x0804, 0x003E},  {0x1C00, 0x2222, 0x001C},
  {0x3E00, 0x1212, 0x000C},  {0x1C00, 0x2222, 0x005C},  {0x3E00, 0x1212, 0x002C},  {0x2400, 0x2A2A, 0x0012},
  {0x0200, 0x023E, 0x0000},  {0x1E00, 0x2020, 0x001E},  {0x1E00, 0x1820, 0x0006},  {0x1E00, 0x1C20, 0x1E20},
  {0x3600, 0x0808, 0x0036},  {0x0600, 0x2828, 0x001E},  {0x3200, 0x262A, 0x0000},  {0x0000, 0x223E, 0x0000},
  {0x0200, 0x0804, 0x2010},  {0x0000, 0x3E22, 0x0000},  {0x0400, 0x0402, 0x0000},  {0x2000, 0x2020, 0x0020},
  {0x0000, 0x0402, 0x0000},  {0x1800, 0x2424, 0x003C},  {0x3E00, 0x2424, 0x0018},  {0x1800, 0x2424, 0x0000},
  {0x1800, 0x2424, 0x003E},  {0x1800, 0x2C34, 0x0008},  {0x0800, 0x0A3C, 0x0000},  {0x1800, 0xA4A4, 0x007C},
  {0x3E00, 0x0404, 0x0038},  {0x0000, 0x003A, 0x0000},  {0x0000, 0x7A80, 0x0000},  {0x3E00, 0x1810, 0x0024},
  {0x0000, 0x003E, 0x0000},  {0x3C00, 0x3C04, 0x3804},  {0x3C00, 0x0404, 0x0038},  {0x1800, 0x2424, 0x0018},
  {0xFC00, 0x2424, 0x0018},  {0x1800, 0x2424, 0x00FC},  {0x3C00, 0x0408, 0x0000},  {0x2800, 0x342C, 0x0014},
  {0x0400, 0x241E, 0x0000},  {0x1C00, 0x2020, 0x003C},  {0x1C00, 0x1020, 0x000C},  {0x0C00, 0x0C30, 0x0C30},
  {0x2400, 0x2418, 0x0000},  {0x1C00, 0xA0A0, 0x007C},  {0x2400, 0x2C34, 0x0024},  {0x0800, 0x2236, 0x0000},
  {0x0000, 0x003E, 0x0000},  {0x2200, 0x0836, 0x0000},  {0x0400, 0x0402, 0x0002}};

static unsigned int   first_row  = 0;     // 0 .. (ROWS-1) first unmasked character after newline is here
static unsigned int   first_col  = 0;     // 0 .. (COLS-1) first unmasked line after form feed is here
static unsigned int   end_row    = ROWS;  // 1 .. (ROWS) one more than last unmasked character in row
static unsigned int   end_col    = COLS;  // 1 .. (COLS) one more than last unmasked line

static unsigned int   cursor_row = 0;     // 0 .. (ROWS-1) where the next character will go
static unsigned int   cursor_col = 0;     // 0 .. (COLS-1) where the next character will go


static void text_write_at (unsigned int y, unsigned int x, unsigned char c)
{
  union
  {
    unsigned short shorts[3];
    unsigned char bytes [6];
  } glyph;

  glyph.shorts[0] = font [c - FIRST_CHAR][0];
  glyph.shorts[1] = font [c - FIRST_CHAR][1];
  glyph.shorts[2] = font [c - FIRST_CHAR][2];

  unsigned int i, j;

  for (j = 0; j < FONT_HEIGHT; j++)
  {
    for (i = 0; i < FONT_WIDTH; i++)
    {
      framebuffer [(y * FONT_HEIGHT) + j][(x * FONT_WIDTH) + i]
        = ((glyph.bytes[i] & (1 << j)) ? FOREGROUND : BACKGROUND);
    }
  }
}


void text_mask (unsigned int set_first_row,  // limit range of text printing functions
                unsigned int set_first_col,
                unsigned int set_num_rows,
                unsigned int set_num_cols)
{
  if ((set_first_row >= ROWS)
   || (set_first_col >= COLS)
   || (set_num_rows < 1)
   || (set_num_cols < 1)
   || (set_num_rows > (ROWS - set_first_row))
   || (set_num_cols > (COLS - set_first_col)))
  {
    return;
  }

  first_row  = set_first_row;
  first_col  = set_first_col;
  end_row    = (set_first_row + set_num_rows);
  end_col    = (set_first_col + set_num_cols);
  cursor_row = first_row;
  cursor_col = first_col;

  unsigned int x, y;

  for (y = first_row; y < end_row; y++)
  {
    for (x = first_col; x < end_col; x++)
    {
      text_write_at (y, x, ' ');
    }
  }
}

void text_cursor (unsigned int row, unsigned int col)  // set the position of the next character written (relative to mask)
{
  cursor_row = (first_row + row);
  cursor_col = (first_col + col);
}

void lcd_putc (unsigned char c)
{
  unsigned int x, y;

  if (!c)
  {
    return;
  }

  if (c == '\r')
  {
    cursor_col = first_col;
    return;
  }

  if (c == '\v')
  {
    cursor_row = first_row;
    return;
  }

  if (c == '\f')
  {
    cursor_col = first_col;
    cursor_row = first_row;

    for (y = first_row; y < end_row; y++)
    {
      for (x = first_col; x < end_col; x++)
      {
        text_write_at (y, x, ' ');
      }
    }
    return;
  }

  if ((c == '\n') || (cursor_col >= end_col))
  {
    cursor_col  = first_col;
    cursor_row += 1;

    if (cursor_row >= end_row)
    {
      cursor_row = first_row;
    }

    for (x = first_col; x < end_col; x++)
    {
      text_write_at (cursor_row, x, ' ');
    }

    if (c == '\n')
    {
      return;
    }
  }

  if (c == '\t')
  {
    unsigned int add_cols = (TABSTOP - (cursor_col & TABSTOP));

    for (x = cursor_col; x < (cursor_col + add_cols); x++)
    {
      text_write_at (cursor_row, x, ' ');
    }

    cursor_col += add_cols;

    return;
  }

  if ((c < FIRST_CHAR) || (c > LAST_CHAR))
  {
    c = '?';
  }

  text_write_at (cursor_row, cursor_col, c);

  cursor_col += 1;
}

void text_write (const unsigned char *str, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
  {
    lcd_putc (str[i]);
  }
}
