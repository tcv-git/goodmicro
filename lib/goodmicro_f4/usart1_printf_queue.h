// usart1_printf_queue.h
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

#ifndef USART1_PRINTF_QUEUE_H_INCLUDED
#define USART1_PRINTF_QUEUE_H_INCLUDED

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void usart1_printf_init(unsigned int baud);

#ifdef __GNUC__
void usart1_vprintf (const char *format, va_list args) __attribute__((format(__printf__, 1, 0)));
void usart1_printf  (const char *format, ...)          __attribute__((format(__printf__, 1, 2)));
#else
void usart1_vprintf (const char *format, va_list args);
void usart1_printf  (const char *format, ...);
#endif

#ifdef __cplusplus
}
#endif

#endif // USART1_PRINTF_QUEUE_H_INCLUDED
