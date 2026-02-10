// parse_int.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/yabaplib/

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

#ifndef PARSE_INT_H_INCLUDED
#define PARSE_INT_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// convert a string of decimal digits to a integer
// signed versions also allow a positive or negative sign
// if p_end is non-null set *p_end to the first character after digits
// if no digits return negative and set *p_end to value of str
// if converted value exceeds maximum of output type return positive and do not write to *p_result
// if converted value is within range of output type return zero
int decimal_to_u8       (const char *str, char **p_end, uint8_t  *p_result);
int decimal_to_u16      (const char *str, char **p_end, uint16_t *p_result);
int decimal_to_u32      (const char *str, char **p_end, uint32_t *p_result);
int decimal_to_u64      (const char *str, char **p_end, uint64_t *p_result);
int decimal_to_i8       (const char *str, char **p_end, int8_t   *p_result);
int decimal_to_i16      (const char *str, char **p_end, int16_t  *p_result);
int decimal_to_i32      (const char *str, char **p_end, int32_t  *p_result);
int decimal_to_i64      (const char *str, char **p_end, int64_t  *p_result);

// skip space before number and return negative if there is anything but space after the number to the end of the string
int decimal_only_to_u8  (const char *str,               uint8_t  *p_result);
int decimal_only_to_u16 (const char *str,               uint16_t *p_result);
int decimal_only_to_u32 (const char *str,               uint32_t *p_result);
int decimal_only_to_u64 (const char *str,               uint64_t *p_result);
int decimal_only_to_i8  (const char *str,               int8_t   *p_result);
int decimal_only_to_i16 (const char *str,               int16_t  *p_result);
int decimal_only_to_i32 (const char *str,               int32_t  *p_result);
int decimal_only_to_i64 (const char *str,               int64_t  *p_result);

// return non-negative converted value on success
// return negative on error with errno set to ERANGE or EINVAL
int8_t  decimal_only_to_u7  (const char *str);
int16_t decimal_only_to_u15 (const char *str);
int32_t decimal_only_to_u31 (const char *str);
int64_t decimal_only_to_u63 (const char *str);
int64_t decimal_size_to_u63 (const char *str);

// convert a decimal number to a fixed decimal-point integer
int decimal_fixed_to_u8  (const char *str, char **p_end, unsigned int decimal_places, uint8_t   *p_result);
int decimal_fixed_to_u16 (const char *str, char **p_end, unsigned int decimal_places, uint16_t  *p_result);
int decimal_fixed_to_u32 (const char *str, char **p_end, unsigned int decimal_places, uint32_t  *p_result);
int decimal_fixed_to_u64 (const char *str, char **p_end, unsigned int decimal_places, uint64_t  *p_result);
int decimal_fixed_to_i8  (const char *str, char **p_end, unsigned int decimal_places, int8_t    *p_result);
int decimal_fixed_to_i16 (const char *str, char **p_end, unsigned int decimal_places, int16_t   *p_result);
int decimal_fixed_to_i32 (const char *str, char **p_end, unsigned int decimal_places, int32_t   *p_result);
int decimal_fixed_to_i64 (const char *str, char **p_end, unsigned int decimal_places, int64_t   *p_result);

// also return negative if there is anything but space after the digits to the end of the string
int decimal_fixed_only_to_u8  (const char *str,          unsigned int decimal_places, uint8_t   *p_result);
int decimal_fixed_only_to_u16 (const char *str,          unsigned int decimal_places, uint16_t  *p_result);
int decimal_fixed_only_to_u32 (const char *str,          unsigned int decimal_places, uint32_t  *p_result);
int decimal_fixed_only_to_u64 (const char *str,          unsigned int decimal_places, uint64_t  *p_result);
int decimal_fixed_only_to_i8  (const char *str,          unsigned int decimal_places, int8_t    *p_result);
int decimal_fixed_only_to_i16 (const char *str,          unsigned int decimal_places, int16_t   *p_result);
int decimal_fixed_only_to_i32 (const char *str,          unsigned int decimal_places, int32_t   *p_result);
int decimal_fixed_only_to_i64 (const char *str,          unsigned int decimal_places, int64_t   *p_result);

// return non-negative converted value on success
// return negative on error with errno set to ERANGE or EINVAL
int8_t  decimal_fixed_only_to_u7   (const char *str, unsigned int decimal_places);
int16_t decimal_fixed_only_to_u15  (const char *str, unsigned int decimal_places);
int32_t decimal_fixed_only_to_u31  (const char *str, unsigned int decimal_places);
int64_t decimal_fixed_only_to_u63  (const char *str, unsigned int decimal_places);

#ifdef __cplusplus
}
#endif

#endif /* PARSE_INT_H_INCLUDED */
