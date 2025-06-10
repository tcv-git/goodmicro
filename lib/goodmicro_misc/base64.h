// base64.h
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

#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// convert binary data to base64 text
// returns the number of characters output on success, or negative on failure
// (the only failure is if dest_size is not big enough)
// output string is *not* null terminated
//
int32_t base64_encode(char *dest, uint32_t dest_size, const void *src, uint32_t src_len);


// convert base64 text to binary data
// returns the number of bytes output on success, or negative on failure
// (failure is if dest_size is not big enough or the whole src_len bytes are not correctly formed base64)
//
int32_t base64_decode(void *dest, uint32_t dest_size, const char *src, uint32_t src_len);

#ifdef __cplusplus
}
#endif

#endif /* BASE64_H_INCLUDED */
