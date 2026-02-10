// parse_int.c
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

#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include "parse_int.h"

static const char *skip_space(const char *str)
{{{
  while ((str[0] == ' ') || (str[0] == '\t'))
  {
    str++;
  }

  return str;
}}}

static bool is_empty(const char *str)
{{{
  while ((str[0] == ' ') || (str[0] == '\t') || (str[0] == '\r') || (str[0] == '\n') || (str[0] == '\v') || (str[0] == '\f'))
  {
    str++;
  }

  return (str[0] == '\0');
}}}

static int decimal_to_uintmax(const char *str, char **p_end, uintmax_t *p_result)
{{{
  str = skip_space(str);

  int status = 0;

  if ((*str < '0') || (*str > '9'))
  {
    status = -1;
  }

  uintmax_t result = 0;

  for (; ((*str >= '0') && (*str <= '9')); str++)
  {
    if ((result > (UINTMAX_MAX / 10)) || ((result == (UINTMAX_MAX / 10)) && (*str > ('0' + (int)(UINTMAX_MAX % 10)))))
    {
      status = +1;
      result = UINTMAX_MAX;
    }
    else
    {
      result = ((result * 10) + (*str - '0'));
    }
  }

  if (p_end)
  {
    *p_end = (char*)str;  // discard const because original argument might not have been const to begin with
  }

  if (p_result)
  {
    *p_result = result;
  }

  return status;
}}}

static int decimal_fixed_to_umax(const char *str, char **p_end, unsigned int decimal_places, uintmax_t *p_result)
{{{
  while ((*str == ' ') || (*str == '\t'))
  {
    str++;
  }

  if ((*str < '0') || (*str > '9'))
  {
    if (p_end)
    {
      *p_end = (char*)str;
    }

    return -1;
  }

  uintmax_t result = (*str - '0');

  str++;

  bool overflow = false;

  for (; (*str >= '0') && (*str <= '9'); str++)
  {
    if (!overflow)
    {
      if ((result > (UINTMAX_MAX / 10)) || ((result == (UINTMAX_MAX / 10)) && (*str > ('0' + (int)(UINTMAX_MAX % 10)))))
      {
        overflow = true;
      }
      else
      {
        result = ((result * 10) + (*str - '0'));
      }
    }
  }

  if (*str == '.')
  {
    str++;

    for (; (decimal_places > 0) && (*str >= '0') && (*str <= '9'); str++, decimal_places--)
    {
      if (!overflow)
      {
        if ((result > (UINTMAX_MAX / 10)) || ((result == (UINTMAX_MAX / 10)) && (*str > ('0' + (int)(UINTMAX_MAX % 10)))))
        {
          overflow = true;
        }
        else
        {
          result = ((result * 10) + (*str - '0'));
        }
      }
    }
  }

  for (; decimal_places > 0; decimal_places--)
  {
    if (result > (UINTMAX_MAX / 10))
    {
      overflow = true;
    }
    else
    {
      result *= 10;
    }
  }

  if ((*str >= '6') && (*str <= '9'))
  {
    if (result >= UINTMAX_MAX)
    {
      overflow = true;
    }
    else
    {
      result++;
    }

    str++;
  }
  else
  {
    if (*str == '5')
    {
      str++;

      while (*str == '0')
      {
        str++;
      }

      if ((*str >= '1') && (*str <= '9'))
      {
        if (result >= UINTMAX_MAX)
        {
          overflow = true;
        }
        else
        {
          result++;
        }

        str++;
      }
    }
  }

  while ((*str >= '0') && (*str <= '9'))
  {
    str++;
  }

  if (p_end)
  {
    *p_end = (char*)str;
  }

  if (p_result && !overflow)
  {
    *p_result = result;
  }

  return (overflow ? +1 : 0);
}}}

static inline intmax_t negate(uintmax_t u)
{{{
  if (u <= (uintmax_t)INTMAX_MAX)
  {
    return -(intmax_t)u;
  }
  else
  {
    return INTMAX_MIN;
  }
}}}

static int decimal_to_intmax(const char *str, char **p_end, intmax_t *p_result)
{{{
  str = skip_space(str);

  if (str[0] == '-')
  {
    str++;

    uintmax_t result;

    int status = decimal_to_uintmax(str, p_end, &result);

    if ((status == 0) && (result > -(uintmax_t)INTMAX_MIN))
    {
      status = +1;
    }

    if ((status == 0) && p_result)
    {
      *p_result = negate(result);
    }

    return status;
  }
  else
  {
    if (str[0] == '+')
    {
      str++;
    }

    uintmax_t result;

    int status = decimal_to_uintmax(str, p_end, &result);

    if ((status == 0) && (result > (uintmax_t)INTMAX_MAX))
    {
      status = +1;
    }

    if ((status == 0) && p_result)
    {
      *p_result = result;
    }

    return status;
  }
}}}

static int decimal_fixed_to_imax(const char *str, char **p_end, unsigned int decimal_places, intmax_t *p_result)
{{{
  str = skip_space(str);

  if (str[0] == '-')
  {
    str++;

    uintmax_t result;

    int status = decimal_fixed_to_umax(str, p_end, decimal_places, &result);

    if ((status == 0) && (result > -(uintmax_t)INTMAX_MIN))
    {
      status = +1;
    }

    if ((status == 0) && p_result)
    {
      *p_result = negate(result);
    }

    return status;
  }
  else
  {
    if (str[0] == '+')
    {
      str++;
    }

    uintmax_t result;

    int status = decimal_fixed_to_umax(str, p_end, decimal_places, &result);

    if ((status == 0) && (result > (uintmax_t)INTMAX_MAX))
    {
      status = +1;
    }

    if ((status == 0) && p_result)
    {
      *p_result = result;
    }

    return status;
  }
}}}

intmax_t decimal_only_to_return(const char *str, uintmax_t max)
{{{
  uintmax_t value;
  char      *end;

  int status = decimal_to_uintmax(str, &end, &value);

  intmax_t result;

  if (status > 0)
  {
    errno = ERANGE;
    result = -1;
  }
  else if ((status < 0) || !is_empty(end))
  {
    errno = EINVAL;
    result = -1;
  }
  else if (value > max)
  {
    errno = ERANGE;
    result = -1;
  }
  else
  {
    result = (intmax_t)value;
  }

  return result;
}}}

static intmax_t decimal_fixed_only_to_return(const char *str, unsigned int decimal_places, uintmax_t max)
{{{
  uintmax_t value;
  char      *end;

  int status = decimal_fixed_to_umax(str, &end, decimal_places, &value);

  intmax_t result;

  if (status > 0)
  {
    errno = ERANGE;
    result = -1;
  }
  else if ((status < 0) || !is_empty(end))
  {
    errno = EINVAL;
    result = -1;
  }
  else if (value > max)
  {
    errno = ERANGE;
    result = -1;
  }
  else
  {
    result = (intmax_t)value;
  }

  return result;
}}}

static int to_u8  (uintmax_t result, uint8_t  *p_result){  if (                         result > UINT8_MAX ){ return +1; }  if (p_result){ *p_result = result; }  return 0;  }
static int to_u16 (uintmax_t result, uint16_t *p_result){  if (                         result > UINT16_MAX){ return +1; }  if (p_result){ *p_result = result; }  return 0;  }
static int to_u32 (uintmax_t result, uint32_t *p_result){  if (                         result > UINT32_MAX){ return +1; }  if (p_result){ *p_result = result; }  return 0;  }
static int to_u64 (uintmax_t result, uint64_t *p_result){  if (                         result > UINT64_MAX){ return +1; }  if (p_result){ *p_result = result; }  return 0;  }
static int to_i8  (intmax_t  result, int8_t   *p_result){  if ((result < INT8_MIN ) || (result > INT8_MAX )){ return +1; }  if (p_result){ *p_result = result; }  return 0;  }
static int to_i16 (intmax_t  result, int16_t  *p_result){  if ((result < INT16_MIN) || (result > INT16_MAX)){ return +1; }  if (p_result){ *p_result = result; }  return 0;  }
static int to_i32 (intmax_t  result, int32_t  *p_result){  if ((result < INT32_MIN) || (result > INT32_MAX)){ return +1; }  if (p_result){ *p_result = result; }  return 0;  }
static int to_i64 (intmax_t  result, int64_t  *p_result){  if ((result < INT64_MIN) || (result > INT64_MAX)){ return +1; }  if (p_result){ *p_result = result; }  return 0;  }

int decimal_to_u8       (const char *str, char **p_end, uint8_t  *p_result){  uintmax_t result;  int status = decimal_to_uintmax (str, p_end, &result);  if (status == 0){ status = to_u8  (result, p_result); }  return status;  }
int decimal_to_u16      (const char *str, char **p_end, uint16_t *p_result){  uintmax_t result;  int status = decimal_to_uintmax (str, p_end, &result);  if (status == 0){ status = to_u16 (result, p_result); }  return status;  }
int decimal_to_u32      (const char *str, char **p_end, uint32_t *p_result){  uintmax_t result;  int status = decimal_to_uintmax (str, p_end, &result);  if (status == 0){ status = to_u32 (result, p_result); }  return status;  }
int decimal_to_u64      (const char *str, char **p_end, uint64_t *p_result){  uintmax_t result;  int status = decimal_to_uintmax (str, p_end, &result);  if (status == 0){ status = to_u64 (result, p_result); }  return status;  }
int decimal_to_i8       (const char *str, char **p_end, int8_t   *p_result){  intmax_t  result;  int status = decimal_to_intmax  (str, p_end, &result);  if (status == 0){ status = to_i8  (result, p_result); }  return status;  }
int decimal_to_i16      (const char *str, char **p_end, int16_t  *p_result){  intmax_t  result;  int status = decimal_to_intmax  (str, p_end, &result);  if (status == 0){ status = to_i16 (result, p_result); }  return status;  }
int decimal_to_i32      (const char *str, char **p_end, int32_t  *p_result){  intmax_t  result;  int status = decimal_to_intmax  (str, p_end, &result);  if (status == 0){ status = to_i32 (result, p_result); }  return status;  }
int decimal_to_i64      (const char *str, char **p_end, int64_t  *p_result){  intmax_t  result;  int status = decimal_to_intmax  (str, p_end, &result);  if (status == 0){ status = to_i64 (result, p_result); }  return status;  }

int decimal_only_to_u8  (const char *str,               uint8_t  *p_result){  char *end;  int status = decimal_to_u8  (str, &end, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_only_to_u16 (const char *str,               uint16_t *p_result){  char *end;  int status = decimal_to_u16 (str, &end, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_only_to_u32 (const char *str,               uint32_t *p_result){  char *end;  int status = decimal_to_u32 (str, &end, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_only_to_u64 (const char *str,               uint64_t *p_result){  char *end;  int status = decimal_to_u64 (str, &end, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_only_to_i8  (const char *str,               int8_t   *p_result){  char *end;  int status = decimal_to_i8  (str, &end, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_only_to_i16 (const char *str,               int16_t  *p_result){  char *end;  int status = decimal_to_i16 (str, &end, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_only_to_i32 (const char *str,               int32_t  *p_result){  char *end;  int status = decimal_to_i32 (str, &end, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_only_to_i64 (const char *str,               int64_t  *p_result){  char *end;  int status = decimal_to_i64 (str, &end, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }

int8_t  decimal_only_to_u7  (const char *str){ return decimal_only_to_return(str, (uintmax_t) INT8_MAX); }
int16_t decimal_only_to_u15 (const char *str){ return decimal_only_to_return(str, (uintmax_t)INT16_MAX); }
int32_t decimal_only_to_u31 (const char *str){ return decimal_only_to_return(str, (uintmax_t)INT32_MAX); }
int64_t decimal_only_to_u63 (const char *str){ return decimal_only_to_return(str, (uintmax_t)INT64_MAX); }

int decimal_fixed_to_u8  (const char *str, char **p_end, unsigned int decimal_places, uint8_t  *p_result){  uintmax_t result;  int status = decimal_fixed_to_umax (str, p_end, decimal_places, &result);  if (status == 0){ status = to_u8  (result, p_result); }  return status;  }
int decimal_fixed_to_u16 (const char *str, char **p_end, unsigned int decimal_places, uint16_t *p_result){  uintmax_t result;  int status = decimal_fixed_to_umax (str, p_end, decimal_places, &result);  if (status == 0){ status = to_u16 (result, p_result); }  return status;  }
int decimal_fixed_to_u32 (const char *str, char **p_end, unsigned int decimal_places, uint32_t *p_result){  uintmax_t result;  int status = decimal_fixed_to_umax (str, p_end, decimal_places, &result);  if (status == 0){ status = to_u32 (result, p_result); }  return status;  }
int decimal_fixed_to_u64 (const char *str, char **p_end, unsigned int decimal_places, uint64_t *p_result){  uintmax_t result;  int status = decimal_fixed_to_umax (str, p_end, decimal_places, &result);  if (status == 0){ status = to_u64 (result, p_result); }  return status;  }
int decimal_fixed_to_i8  (const char *str, char **p_end, unsigned int decimal_places, int8_t   *p_result){  intmax_t  result;  int status = decimal_fixed_to_imax (str, p_end, decimal_places, &result);  if (status == 0){ status = to_i8  (result, p_result); }  return status;  }
int decimal_fixed_to_i16 (const char *str, char **p_end, unsigned int decimal_places, int16_t  *p_result){  intmax_t  result;  int status = decimal_fixed_to_imax (str, p_end, decimal_places, &result);  if (status == 0){ status = to_i16 (result, p_result); }  return status;  }
int decimal_fixed_to_i32 (const char *str, char **p_end, unsigned int decimal_places, int32_t  *p_result){  intmax_t  result;  int status = decimal_fixed_to_imax (str, p_end, decimal_places, &result);  if (status == 0){ status = to_i32 (result, p_result); }  return status;  }
int decimal_fixed_to_i64 (const char *str, char **p_end, unsigned int decimal_places, int64_t  *p_result){  intmax_t  result;  int status = decimal_fixed_to_imax (str, p_end, decimal_places, &result);  if (status == 0){ status = to_i64 (result, p_result); }  return status;  }

int decimal_fixed_only_to_u8  (const char *str, unsigned int decimal_places, uint8_t  *p_result){  char *end;  int status = decimal_fixed_to_u8  (str, &end, decimal_places, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_fixed_only_to_u16 (const char *str, unsigned int decimal_places, uint16_t *p_result){  char *end;  int status = decimal_fixed_to_u16 (str, &end, decimal_places, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_fixed_only_to_u32 (const char *str, unsigned int decimal_places, uint32_t *p_result){  char *end;  int status = decimal_fixed_to_u32 (str, &end, decimal_places, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_fixed_only_to_u64 (const char *str, unsigned int decimal_places, uint64_t *p_result){  char *end;  int status = decimal_fixed_to_u64 (str, &end, decimal_places, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_fixed_only_to_i8  (const char *str, unsigned int decimal_places, int8_t   *p_result){  char *end;  int status = decimal_fixed_to_i8  (str, &end, decimal_places, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_fixed_only_to_i16 (const char *str, unsigned int decimal_places, int16_t  *p_result){  char *end;  int status = decimal_fixed_to_i16 (str, &end, decimal_places, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_fixed_only_to_i32 (const char *str, unsigned int decimal_places, int32_t  *p_result){  char *end;  int status = decimal_fixed_to_i32 (str, &end, decimal_places, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }
int decimal_fixed_only_to_i64 (const char *str, unsigned int decimal_places, int64_t  *p_result){  char *end;  int status = decimal_fixed_to_i64 (str, &end, decimal_places, p_result);  if ((status == 0) && !is_empty(end)){ status = -1; }  return status;  }

int8_t  decimal_fixed_only_to_u7  (const char *str, unsigned int decimal_places){ return decimal_fixed_only_to_return(str, decimal_places, (uintmax_t) INT8_MAX); }
int16_t decimal_fixed_only_to_u15 (const char *str, unsigned int decimal_places){ return decimal_fixed_only_to_return(str, decimal_places, (uintmax_t)INT16_MAX); }
int32_t decimal_fixed_only_to_u31 (const char *str, unsigned int decimal_places){ return decimal_fixed_only_to_return(str, decimal_places, (uintmax_t)INT32_MAX); }
int64_t decimal_fixed_only_to_u63 (const char *str, unsigned int decimal_places){ return decimal_fixed_only_to_return(str, decimal_places, (uintmax_t)INT64_MAX); }

static int parse_suffix(const char *str)
{{{
  const char *unit = skip_space(str);

  if (is_empty(unit))
  {
    return 0;
  }

  int shift;

  switch (unit[0])
  {
    case 'k': case 'K': shift = 10; break;
    case 'm': case 'M': shift = 20; break;
    case 'g': case 'G': shift = 30; break;
    case 't': case 'T': shift = 40; break;
    case 'p': case 'P': shift = 50; break;
    case 'e': case 'E': shift = 60; break;
    case 'z': case 'Z': shift = 70; break;
    case 'y': case 'Y': shift = 80; break;
    default:
      return  -1;
  }

  const char *end;

  if (((unit[1] == 'i') || (unit[1] == 'I')) && ((unit[2] == 'b') || (unit[2] == 'B')))
  {
    end = &unit[3];
  }
  else if ((unit[1] == 'b') || (unit[1] == 'B'))
  {
    end = &unit[2];
  }
  else
  {
    end = &unit[1];
  }

  if (!is_empty(end))
  {
    return -1;
  }

  return shift;
}}}

int64_t decimal_size_to_u63(const char *str)
{{{
  uintmax_t number = 1; // redundant initializer to silence compiler
  char      *end;

  int status = decimal_to_uintmax(str, &end, &number);

  if (status > 0)
  {
    errno = ERANGE;
    return -1;
  }

  int shift = parse_suffix(end);

  if (shift < 0)
  {
    errno = EINVAL;
    return -1;
  }

  if (status < 0)
  {
    if (shift > 0)
    {
      number = 1;
    }
    else
    {
      errno = EINVAL;
      return -1;
    }
  }

  if (number == 0)
  {
    return 0;
  }

  if (shift >= 64)
  {
    errno = ERANGE;
    return -1;
  }

  uintmax_t limit = ((uintmax_t)INT64_MAX >> shift);

  if (number > limit)
  {
    errno = ERANGE;
    return -1;
  }

  return (number << shift);
}}}
