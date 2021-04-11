// lcd.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

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

#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define HORIZONTAL_ACTIVE_WIDTH   240
#define VERTICAL_ACTIVE_HEIGHT    320

extern unsigned int framebuffer [VERTICAL_ACTIVE_HEIGHT][HORIZONTAL_ACTIVE_WIDTH];

void lcd_init (void);

#ifdef __cplusplus
}
#endif

#endif // LCD_H_INCLUDED
