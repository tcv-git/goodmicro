// rounding.h
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

#ifndef ROUNDING_H_INCLUDED
#define ROUNDING_H_INCLUDED

#include <stdint.h>

#define EXTERN_CONST  extern        __attribute__((const))
#define INLINE_CONST  static inline __attribute__((const,always_inline,unused))

/*  SHIFTING AND DIVISION FUNCTIONS WITH ROUNDING       */

/*  xxx_up rounds towards positive infinity             */
/*  xxx_down rounds towards negative infinity           */
/*  xxx_nearest rouunds to nearest, with ties to odd    */
/*  (which is sooo much cleverer than ties to even      */
/*  because avoids increasing the number of bits in the */
/*  result and helps avoid double rounding errors)      */

/*   ***** RIGHT SHIFT ***** */

/*   *** 32 BIT *** */

/*   ** UNSIGNED ** */

INLINE_CONST uint32_t rshift_u32_down        (uint32_t dividend, unsigned int shift_bits)
{{{
  if (shift_bits >= 32)
  {
    return 0;
  }

  return (dividend >> shift_bits);
}}}

EXTERN_CONST uint32_t ool_rshift_u32_up      (uint32_t dividend, unsigned int shift_bits);
INLINE_CONST uint32_t     rshift_u32_up      (uint32_t dividend, unsigned int shift_bits)
{{{
  if (!__builtin_constant_p (shift_bits))
  {
    return ool_rshift_u32_up (dividend, shift_bits);
  }

  if (shift_bits >= 32)
  {
    if (dividend == 0)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  uint32_t quotient  = (dividend >> shift_bits);
  uint32_t lost_bits = ((1u << shift_bits) - 1);

  if ((dividend & lost_bits) != 0)
  {
    quotient += 1;
  }

  return quotient;
}}}

EXTERN_CONST uint32_t ool_rshift_u32_nearest (uint32_t dividend, unsigned int shift_bits);
INLINE_CONST uint32_t     rshift_u32_nearest (uint32_t dividend, unsigned int shift_bits)
{{{
  if (!__builtin_constant_p (shift_bits))
  {
    return ool_rshift_u32_nearest (dividend, shift_bits);
  }

  if (shift_bits > 32)
  {
    return 0;
  }

  if (shift_bits == 32)
  {
    if (dividend < (1u << 31))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  if (shift_bits == 0)
  {
    return dividend;
  }

  uint32_t quotient = (dividend >> shift_bits);
  uint32_t half_bit = (1u << (shift_bits - 1));

  if ((dividend & half_bit) != 0)
  {
    if ((dividend & (half_bit - 1)) != 0)
    {
      quotient += 1;
    }
    else
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}

/*   ** SIGNED ** */

INLINE_CONST int32_t rshift_i32_down         (int32_t dividend, unsigned int shift_bits)
{{{
  if (shift_bits >= 32)
  {
    shift_bits = 31;
  }

  return (dividend >> shift_bits);
}}}

EXTERN_CONST int32_t ool_rshift_i32_up       (int32_t dividend, unsigned int shift_bits);
INLINE_CONST int32_t     rshift_i32_up       (int32_t dividend, unsigned int shift_bits)
{{{
  if (!__builtin_constant_p (shift_bits))
  {
    return ool_rshift_i32_up (dividend, shift_bits);
  }

  if (shift_bits >= 32)
  {
    if (dividend <= 0)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  int32_t  quotient  = (dividend >> shift_bits);
  uint32_t lost_bits = ((1u << shift_bits) - 1);

  if ((dividend & lost_bits) != 0)
  {
    quotient += 1;
  }

  return quotient;
}}}

EXTERN_CONST int32_t ool_rshift_i32_nearest  (int32_t dividend, unsigned int shift_bits);
INLINE_CONST int32_t     rshift_i32_nearest  (int32_t dividend, unsigned int shift_bits)
{{{
  if (!__builtin_constant_p (shift_bits))
  {
    return ool_rshift_i32_nearest (dividend, shift_bits);
  }

  if (shift_bits > 32)
  {
    return 0;
  }

  if (shift_bits == 32)
  {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-negative-value"

    if (dividend == (-1 << 31))
    {
      return -1;
    }
    else
    {
      return 0;
    }
#pragma GCC diagnostic pop
  }

  if (shift_bits == 0)
  {
    return dividend;
  }

  int32_t quotient = (dividend >> shift_bits);
  uint32_t half_bit = (1u << (shift_bits - 1));

  if ((dividend & half_bit) != 0)
  {
    if ((dividend & (half_bit - 1)) != 0)
    {
      quotient += 1;
    }
    else
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}

/*   *** 64 BIT *** */

/*   ** UNSIGNED ** */

INLINE_CONST uint64_t rshift_u64_down        (uint64_t dividend, unsigned int shift_bits)
{{{
  if (shift_bits >= 64)
  {
    return 0;
  }

  return (dividend >> shift_bits);
}}}

EXTERN_CONST uint64_t ool_rshift_u64_up      (uint64_t dividend, unsigned int shift_bits);
INLINE_CONST uint64_t     rshift_u64_up      (uint64_t dividend, unsigned int shift_bits)
{{{
  if (!__builtin_constant_p (shift_bits))
  {
    return ool_rshift_u64_up (dividend, shift_bits);
  }

  if (shift_bits >= 64)
  {
    if (dividend == 0)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  uint64_t quotient  = (dividend >> shift_bits);
  uint64_t lost_bits = ((1uLL << shift_bits) - 1);

  if ((dividend & lost_bits) != 0)
  {
    quotient += 1;
  }

  return quotient;
}}}

EXTERN_CONST uint64_t ool_rshift_u64_nearest (uint64_t dividend, unsigned int shift_bits);
INLINE_CONST uint64_t     rshift_u64_nearest (uint64_t dividend, unsigned int shift_bits)
{{{
  if (!__builtin_constant_p (shift_bits))
  {
    return ool_rshift_u64_nearest (dividend, shift_bits);
  }

  if (shift_bits > 64)
  {
    return 0;
  }

  if (shift_bits == 64)
  {
    if (dividend < (1uLL << 63))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  if (shift_bits == 0)
  {
    return dividend;
  }

  uint64_t quotient = (dividend >> shift_bits);
  uint64_t half_bit = (1uLL << (shift_bits - 1));

  if ((dividend & half_bit) != 0)
  {
    if ((dividend & (half_bit - 1)) != 0)
    {
      quotient += 1;
    }
    else
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}

/*   ** SIGNED ** */

INLINE_CONST int64_t rshift_i64_down         (int64_t dividend, unsigned int shift_bits)
{{{
  if (shift_bits >= 64)
  {
    shift_bits = 63;
  }

  return (dividend >> shift_bits);
}}}

EXTERN_CONST int64_t ool_rshift_i64_up       (int64_t dividend, unsigned int shift_bits);
INLINE_CONST int64_t     rshift_i64_up       (int64_t dividend, unsigned int shift_bits)
{{{
  if (!__builtin_constant_p (shift_bits))
  {
    return ool_rshift_i64_up (dividend, shift_bits);
  }

  if (shift_bits >= 64)
  {
    if (dividend <= 0)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  int64_t  quotient  = (dividend >> shift_bits);
  uint64_t lost_bits = ((1uLL << shift_bits) - 1);

  if ((dividend & lost_bits) != 0)
  {
    quotient += 1;
  }

  return quotient;
}}}

EXTERN_CONST int64_t ool_rshift_i64_nearest  (int64_t dividend, unsigned int shift_bits);
INLINE_CONST int64_t     rshift_i64_nearest  (int64_t dividend, unsigned int shift_bits)
{{{
  if (!__builtin_constant_p (shift_bits))
  {
    return ool_rshift_i64_nearest (dividend, shift_bits);
  }

  if (shift_bits > 64)
  {
    return 0;
  }

  if (shift_bits == 64)
  {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-negative-value"

    if (dividend == (-1LL << 63))
    {
      return -1;
    }
    else
    {
      return 0;
    }
#pragma GCC diagnostic pop
  }

  if (shift_bits == 0)
  {
    return dividend;
  }

  int64_t quotient = (dividend >> shift_bits);
  uint64_t half_bit = (1uLL << (shift_bits - 1));

  if ((dividend & half_bit) != 0)
  {
    if ((dividend & (half_bit - 1)) != 0)
    {
      quotient += 1;
    }
    else
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}


/*   ***** DIVISION ***** */

/*   *** 32 BY 32 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

INLINE_CONST uint32_t div_u32_u32_down (uint32_t dividend, uint32_t divisor)
{{{
  return (dividend / divisor);
}}}

EXTERN_CONST uint32_t div_u32_u32_up      (uint32_t dividend, uint32_t divisor);
EXTERN_CONST uint32_t div_u32_u32_nearest (uint32_t dividend, uint32_t divisor);

/*   ** SIGNED BY UNSIGNED ** */

EXTERN_CONST int32_t div_i32_u32_down     (int32_t dividend, uint32_t divisor);
EXTERN_CONST int32_t div_i32_u32_up       (int32_t dividend, uint32_t divisor);
EXTERN_CONST int32_t div_i32_u32_nearest  (int32_t dividend, uint32_t divisor);

/*   ** UNSIGNED BY SIGNED ** */

EXTERN_CONST int32_t div_u32_i32_down     (uint32_t dividend, int32_t divisor);
EXTERN_CONST int32_t div_u32_i32_up       (uint32_t dividend, int32_t divisor);
EXTERN_CONST int32_t div_u32_i32_nearest  (uint32_t dividend, int32_t divisor);

/*   ** SIGNED BY SIGNED ** */

EXTERN_CONST int32_t div_i32_i32_down     (int32_t dividend, int32_t divisor);
EXTERN_CONST int32_t div_i32_i32_up       (int32_t dividend, int32_t divisor);
EXTERN_CONST int32_t div_i32_i32_nearest  (int32_t dividend, int32_t divisor);

/*   *** 64 BY 32 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

INLINE_CONST uint64_t div_u64_u32_down (uint64_t dividend, uint32_t divisor)
{{{
  return (dividend / divisor);
}}}

EXTERN_CONST uint64_t div_u64_u32_up      (uint64_t dividend, uint32_t divisor);
EXTERN_CONST uint64_t div_u64_u32_nearest (uint64_t dividend, uint32_t divisor);

/*   ** SIGNED BY UNSIGNED ** */

EXTERN_CONST int64_t div_i64_u32_down     (int64_t dividend, uint32_t divisor);
EXTERN_CONST int64_t div_i64_u32_up       (int64_t dividend, uint32_t divisor);
EXTERN_CONST int64_t div_i64_u32_nearest  (int64_t dividend, uint32_t divisor);

/*   ** UNSIGNED BY SIGNED ** */

EXTERN_CONST int64_t div_u64_i32_down     (uint64_t dividend, int32_t divisor);
EXTERN_CONST int64_t div_u64_i32_up       (uint64_t dividend, int32_t divisor);
EXTERN_CONST int64_t div_u64_i32_nearest  (uint64_t dividend, int32_t divisor);

/*   ** SIGNED BY SIGNED ** */

EXTERN_CONST int64_t div_i64_i32_down     (int64_t dividend, int32_t divisor);
EXTERN_CONST int64_t div_i64_i32_up       (int64_t dividend, int32_t divisor);
EXTERN_CONST int64_t div_i64_i32_nearest  (int64_t dividend, int32_t divisor);


/*   *** 32 BY 64 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

INLINE_CONST uint32_t div_u32_u64_down    (uint32_t dividend, uint64_t divisor)
{{{
  uint32_t divisor32 = (uint32_t)divisor;

  if (divisor32 != divisor)
  {
    return 0;
  }
  else
  {
    return div_u32_u32_down (dividend, divisor32);
  }
}}}

EXTERN_CONST uint32_t div_u32_u64_up      (uint32_t dividend, uint64_t divisor);
EXTERN_CONST uint32_t div_u32_u64_nearest (uint32_t dividend, uint64_t divisor);

/*   ** SIGNED BY UNSIGNED ** */

EXTERN_CONST int32_t div_i32_u64_down     (int32_t dividend, uint64_t divisor);
EXTERN_CONST int32_t div_i32_u64_up       (int32_t dividend, uint64_t divisor);
EXTERN_CONST int32_t div_i32_u64_nearest  (int32_t dividend, uint64_t divisor);

/*   ** UNSIGNED BY SIGNED ** */

EXTERN_CONST int32_t div_u32_i64_down     (uint32_t dividend, int64_t divisor);
EXTERN_CONST int32_t div_u32_i64_up       (uint32_t dividend, int64_t divisor);
EXTERN_CONST int32_t div_u32_i64_nearest  (uint32_t dividend, int64_t divisor);

/*   ** SIGNED BY SIGNED ** */

EXTERN_CONST int32_t div_i32_i64_down     (int32_t dividend, int64_t divisor);
EXTERN_CONST int32_t div_i32_i64_up       (int32_t dividend, int64_t divisor);
EXTERN_CONST int32_t div_i32_i64_nearest  (int32_t dividend, int64_t divisor);

/*   *** 64 BY 64 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

INLINE_CONST uint64_t div_u64_u64_down (uint64_t dividend, uint64_t divisor)
{{{
  return (dividend / divisor);
}}}

EXTERN_CONST uint64_t div_u64_u64_up      (uint64_t dividend, uint64_t divisor);
EXTERN_CONST uint64_t div_u64_u64_nearest (uint64_t dividend, uint64_t divisor);

/*   ** SIGNED BY UNSIGNED ** */

EXTERN_CONST int64_t div_i64_u64_down     (int64_t dividend, uint64_t divisor);
EXTERN_CONST int64_t div_i64_u64_up       (int64_t dividend, uint64_t divisor);
EXTERN_CONST int64_t div_i64_u64_nearest  (int64_t dividend, uint64_t divisor);

/*   ** UNSIGNED BY SIGNED ** */

EXTERN_CONST int64_t div_u64_i64_down     (uint64_t dividend, int64_t divisor);
EXTERN_CONST int64_t div_u64_i64_up       (uint64_t dividend, int64_t divisor);
EXTERN_CONST int64_t div_u64_i64_nearest  (uint64_t dividend, int64_t divisor);

/*   ** SIGNED BY SIGNED ** */

EXTERN_CONST int64_t div_i64_i64_down     (int64_t dividend, int64_t divisor);
EXTERN_CONST int64_t div_i64_i64_up       (int64_t dividend, int64_t divisor);
EXTERN_CONST int64_t div_i64_i64_nearest  (int64_t dividend, int64_t divisor);


/*   ***** FIXED POINT DIVISION ***** */

/*   *** 64 BY 64 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

EXTERN_CONST uint64_t div_u64_u64_q_down    (uint64_t dividend, uint64_t divisor, unsigned int fixed_bits);
EXTERN_CONST uint64_t div_u64_u64_q_up      (uint64_t dividend, uint64_t divisor, unsigned int fixed_bits);
EXTERN_CONST uint64_t div_u64_u64_q_nearest (uint64_t dividend, uint64_t divisor, unsigned int fixed_bits);

#endif /* ROUNDING_H_INCLUDED */
