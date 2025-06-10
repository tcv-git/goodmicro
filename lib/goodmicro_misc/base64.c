// base64.c
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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "hints.h"
#include "base64.h"

/*
    B64   HEX         BIN
    -----------------------
    A-Z   0x41-0x5A   010 00001-11010
    a-z   0x61-0x7A   011 00001-11010
    0-9   0x30-0x39   0011 0000-1001
    +     0x2B        00101 011
    /     0x2F        00101 111
    =     0x3D        0011 1101
*/

static inline bool is_base64_digit(uint8_t digit)
{
    return (((uint32_t)((digit | 0x20) - 'a') <= 25) || ((uint32_t)(digit - '0') <= 9) || ((digit | 4) == 0x2F));
}

static inline uint32_t base64_length(const uint8_t *str, uint32_t max_length)
{
    uint32_t length = 0;

    while ((length < max_length) && is_base64_digit(str[length]))
    {
        length++;
    }

    return length;
}

static uint32_t base64_decode_digit(uint8_t digit)
{
    if (LIKELY(digit & 0x40))
    {
        return ((digit & 0x20) ? ((digit - 'a') + 26) : (digit - 'A'));
    }
    else if (LIKELY(digit & 0x10))
    {
        return ((digit - '0') + 52);
    }
    else
    {
        return (((digit >> 2) & 1) + 62);
    }
}

// convert base64 text to binary data
// returns the number of bytes output on success, or negative on failure
// (failure is if dest_size is not big enough or the whole src_len bytes are not
// correctly formed base64)
//
int32_t base64_decode(void *dest, uint32_t dest_size, const char *src, uint32_t src_len)
{
    if ((src_len & 3) != 0)
    {
        return -1;
    }

    // change pointer types to use unsigned octets internally
    const uint8_t *src_ptr = (const uint8_t*)src;
    uint8_t      *dest_ptr = (uint8_t*)dest;

    uint32_t   digit_count = base64_length(src_ptr, src_len);
    uint32_t   extra_bytes;

    if (digit_count == src_len)
    {
        extra_bytes = 0;
    }
    else if (((digit_count + 2) == src_len) && (src[digit_count] == '=') && (src[digit_count + 1] == '='))
    {
        extra_bytes = 1;
    }
    else if (((digit_count + 1) == src_len) && (src[digit_count] == '='))
    {
        extra_bytes = 2;
    }
    else
    {
        return -1;
    }

    const uint8_t *last_src_block = (src_ptr + (digit_count & ~3u));

    while (src_ptr < last_src_block)
    {
        uint32_t digit0 = base64_decode_digit(*src_ptr++);
        uint32_t digit1 = base64_decode_digit(*src_ptr++);

        // use + not | because the result is the same but there are more opcodes
        // available to the compiler for +
        *dest_ptr++ = ((digit0 << 2) + (digit1 >> 4));

        uint32_t digit2 = base64_decode_digit(*src_ptr++);

        *dest_ptr++ = ((digit1 << 4) + (digit2 >> 2));

        uint32_t digit3 = base64_decode_digit(*src_ptr++);

        *dest_ptr++ = ((digit2 << 6) + digit3);
    }

    if (extra_bytes > 0)
    {
        uint32_t digit0 = base64_decode_digit(*src_ptr++);
        uint32_t digit1 = base64_decode_digit(*src_ptr++);

        *dest_ptr++ = ((digit0 << 2) + (digit1 >> 4));

        if (extra_bytes > 1)
        {
            uint32_t digit2 = base64_decode_digit(*src_ptr);

            *dest_ptr++ = ((digit1 << 4) + (digit2 >> 2));
        }
    }

    return (dest_ptr - (uint8_t*)dest);
}
