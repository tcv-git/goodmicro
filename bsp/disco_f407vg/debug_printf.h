// debug_printf.h
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

#ifndef DEBUG_PRINTF_H_INCLUDED
#define DEBUG_PRINTF_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// Set-up serial interface after boot
//
void debug_uart_init(void);

// like printf
//
void debug_printf(const char *fmt, ...) __attribute__((format(printf,1,2)));

// write byte to interface (blocking)
//
void debug_putc(unsigned char c);

#ifdef __cplusplus
}
#endif

#endif // DEBUG_PRINTF_H_INCLUDED
