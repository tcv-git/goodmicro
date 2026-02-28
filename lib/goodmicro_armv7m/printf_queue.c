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
#include "struct_queue.h"
#include "printf_queue.h"


#ifndef PRINTF_BUFFER_SIZE
#define PRINTF_BUFFER_SIZE  122 // any size up to UINT16_MAX
#endif

#ifndef PRINTF_BUFFER_COUNT
#define PRINTF_BUFFER_COUNT  10 // up to 32
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

struct queued_buffer
{
    struct queued_buffer *next;
    uint16_t              length;
    char                  buffer[PRINTF_BUFFER_SIZE];
};

static struct queued_buffer queued_buffers[PRINTF_BUFFER_COUNT] ATTRIBUTE_ALIGNED ATTRIBUTE_SECTION;

static volatile unsigned int buffers_available = ((1uLL << PRINTF_BUFFER_COUNT) - 1);

static struct queued_item * volatile queue_head = NULL;


/* works like vprintf
 */
void printf_queue_put(const char *format, va_list args)
{
    int buffer_index = bitpool_alloc(&buffers_available);

    if (buffer_index < 0)
    {
        return;
    }

    int length = vsnprintf(queued_buffers[buffer_index].buffer, PRINTF_BUFFER_SIZE, format, args);

    if (length < 1)
    {
        bitpool_free(&buffers_available, buffer_index);
        return;
    }

    if (length >= PRINTF_BUFFER_SIZE)
    {
        length = (PRINTF_BUFFER_SIZE - 1);
    }

    queued_buffers[buffer_index].length = length;

    queue_write(&queue_head, (struct queued_item*)&queued_buffers[buffer_index]);
}


/* return a pointer to the oldest message queued
 * or a null pointer if none available
 * string is null-terminated
 */
char *printf_queue_get(void)
{
    struct queued_buffer *entry = (struct queued_buffer*)queue_read(&queue_head);

    if (entry == NULL)
    {
        return NULL;
    }
    else
    {
        return entry->buffer;
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
    struct queued_buffer *entry = (struct queued_buffer*)queue_read(&queue_head);

    uint16_t length = 0;

    if (entry)
    {
        length = entry->length;

        if ((length > 0) && (entry->buffer[length - 1] == '\n'))
        {
            if ((length < 2) || (entry->buffer[length - 2] != '\r'))
            {
                entry->buffer[length - 1] = '\r';
                entry->buffer[length++  ] = '\n';
            }
        }

#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT != 0)
        SCB_CleanInvalidateDCache_by_Addr(entry->buffer, PRINTF_BUFFER_SIZE);
#endif
    }

    if (p_length)
    {
        *p_length = length;
    }

    return entry ? entry->buffer : NULL;
}


/* free a buffer previously returned by printf_queue_get{,_crlf}
 */
void printf_queue_free(const char *buffer)
{
    if (buffer)
    {
        unsigned int buffer_index = ((buffer - &queued_buffers[0].buffer[0]) / sizeof(struct queued_buffer));

        bitpool_free(&buffers_available, buffer_index);
    }
}
