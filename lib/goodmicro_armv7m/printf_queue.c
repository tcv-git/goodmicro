// printf_queue.c
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

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include CMSIS_device_header
#include "bitpool.h"
#include "bitqueue.h"
#include "printf_queue.h"


#ifndef PRINTF_BUFFER_SIZE
#define PRINTF_BUFFER_SIZE  128 // any size up to UINT16_MAX
#endif

#ifndef PRINTF_BUFFER_COUNT
#define PRINTF_BUFFER_COUNT  10 // can be up to 16, but only 8 can be queued at once
#endif

#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT != 0)
#define ATTRIBUTE_ALIGNED __attribute__((aligned(__SCB_DCACHE_LINE_SIZE)))
#else
#define ATTRIBUTE_ALIGNED
#endif

#ifdef PRINTF_BUFFER_SECTION
#define ATTRIBUTE_SECTION __attribute__((section(PRINTF_BUFFER_SECTION)))
#else
#define ATTRIBUTE_SECTION
#endif

static char buffers[PRINTF_BUFFER_COUNT][PRINTF_BUFFER_SIZE] ATTRIBUTE_ALIGNED ATTRIBUTE_SECTION;

static volatile unsigned int buffers_available = ((1uLL << PRINTF_BUFFER_COUNT) - 1);
static volatile unsigned int buffer_queue      = BITQUEUE_EMPTY_INIT;


/* works like vprintf
 */
void printf_queue_put(const char *format, va_list args)
{
  int buffer_index = bitpool_alloc(&buffers_available);

  if (buffer_index < 0)
  {
    return;
  }

  int len = vsnprintf(buffers[buffer_index], PRINTF_BUFFER_SIZE, format, args);

  if (len < 1)
  {
    bitpool_free(&buffers_available, buffer_index);
    return;
  }

  if (bitqueue_write(&buffer_queue, buffer_index) != 0)
  {
    bitpool_free(&buffers_available, buffer_index);
    return;
  }

  return;
}


/* return a pointer to the oldest message queued
 * or a null pointer if none available
 * string is null-terminated
 */
char *printf_queue_get(void)
{
  int buffer_index = bitqueue_read(&buffer_queue);

  if (buffer_index < 0)
  {
    return NULL;
  }
  else
  {
    return buffers[buffer_index];
  }
}


/* return a pointer to the oldest message queued
 * or a null pointer if none available
 * string is not neccessarily null-terminated
 * message length is output to *p_length
 * \n at the end is replaced with \r\n
 */
char *printf_queue_get_crlf(uint16_t *p_length)
{
  char *buffer = printf_queue_get();

  uint16_t length = 0;

  if (buffer)
  {
    length = strlen(buffer);

    if ((length > 0) && (buffer[length - 1] == '\n'))
    {
      if ((length < 2) || (buffer[length - 2] != '\r'))
      {
        buffer[length - 1] = '\r';
        buffer[length++  ] = '\n';
      }
    }

#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT != 0)
    SCB_CleanInvalidateDCache_by_Addr(buffer, PRINTF_BUFFER_SIZE);
#endif
  }

  if (p_length)
  {
    *p_length = length;
  }

  return buffer;
}


/* free a buffer previously returned by printf_queue_get{,_crlf}
 */
void printf_queue_free(const char *buffer)
{
  if (buffer)
  {
    unsigned int buffer_index = ((buffer - &buffers[0][0]) / PRINTF_BUFFER_SIZE);

    bitpool_free(&buffers_available, buffer_index);
  }
}
