// display_text.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/software/goodmicro

/*
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

#ifndef DISPLAY_TEXT_H_INCLUDED
#define DISPLAY_TEXT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void text_mask (unsigned int set_first_row,  // limit range of text printing functions
                unsigned int set_first_col,
                unsigned int set_num_rows,
                unsigned int set_num_cols);

void text_cursor (unsigned int row, unsigned int col);  // set the position of the next character written (relative to mask)

void text_write (const unsigned char *str, unsigned int len);

void lcd_putc (unsigned char c);

#ifdef __cplusplus
}
#endif

#endif // DISPLAY_TEXT_H_INCLUDED
