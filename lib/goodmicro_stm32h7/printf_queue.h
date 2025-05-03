// printf_queue.h
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

#ifndef PRINTF_QUEUE_H_INCLUDED
#define PRINTF_QUEUE_H_INCLUDED

#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


/* works like vprintf
 */
void printf_queue_put(const char *format, va_list args);


/* return a pointer to the oldest message queued
 * or a null pointer if none available
 * string is null-terminated
 */
char *printf_queue_get(void);


/* return a pointer to the oldest message queued
 * or a null pointer if none available
 * string is not neccessarily null-terminated
 * message length is output to *p_length
 * \n at the end is replaced with \r\n
 */
char *printf_queue_get_crlf(uint16_t *p_length);


/* free a buffer previously returned by printf_queue_get{,_crlf}
 */
void printf_queue_free(const char *buffer);


#ifdef __cplusplus
}
#endif

#endif // PRINTF_QUEUE_H_INCLUDED
