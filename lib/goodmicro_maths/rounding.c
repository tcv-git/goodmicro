// rounding.c
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
#include "rounding.h"

#if (defined(__ARM_ARCH) && (__ARM_ARCH == 6))
#include "imath.h"
#else
static inline uint64_t __attribute__((always_inline,const)) mul_u64_u32 (uint64_t a, uint32_t b)
{
  return (a * b);
}
#endif

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

uint32_t ool_rshift_u32_up      (uint32_t dividend, unsigned int shift_bits)
{{{
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

uint32_t ool_rshift_u32_nearest (uint32_t dividend, unsigned int shift_bits)
{{{
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

int32_t ool_rshift_i32_up       (int32_t dividend, unsigned int shift_bits)
{{{
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

int32_t ool_rshift_i32_nearest  (int32_t dividend, unsigned int shift_bits)
{{{
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

uint64_t ool_rshift_u64_up      (uint64_t dividend, unsigned int shift_bits)
{{{
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

uint64_t ool_rshift_u64_nearest (uint64_t dividend, unsigned int shift_bits)
{{{
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

int64_t ool_rshift_i64_up       (int64_t dividend, unsigned int shift_bits)
{{{
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

int64_t ool_rshift_i64_nearest  (int64_t dividend, unsigned int shift_bits)
{{{
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

uint32_t div_u32_u32_up      (uint32_t dividend, uint32_t divisor)
{{{
  uint32_t quotient = div_u32_u32_down (dividend, divisor);

  if ((dividend - (quotient * divisor)) != 0)
  {
    quotient++;
  }

  return quotient;
}}}

uint32_t div_u32_u32_nearest (uint32_t dividend, uint32_t divisor)
{{{
  uint32_t quotient = div_u32_u32_down (dividend, divisor);

  uint32_t remainder = (dividend - (quotient * divisor));

  uint32_t half_divisor = (divisor / 2);

  if (remainder > half_divisor)
  {
    quotient++;
  }
  else
  {
    if ((remainder == half_divisor) && ((divisor & 1) == 0))
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}

/*   ** SIGNED BY UNSIGNED ** */

int32_t div_i32_u32_down     (int32_t dividend, uint32_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u32_u32_up (-dividend, divisor);
  }
  else
  {
    return div_u32_u32_down (dividend, divisor);
  }
}}}

int32_t div_i32_u32_up       (int32_t dividend, uint32_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u32_u32_down (-dividend, divisor);
  }
  else
  {
    return div_u32_u32_up (dividend, divisor);
  }
}}}

int32_t div_i32_u32_nearest  (int32_t dividend, uint32_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u32_u32_nearest (-dividend, divisor);
  }
  else
  {
    return div_u32_u32_nearest (dividend, divisor);
  }
}}}

/*   ** UNSIGNED BY SIGNED ** */

int32_t div_u32_i32_down     (uint32_t dividend, int32_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u32_u32_up (dividend, -divisor);
  }
  else
  {
    return div_u32_u32_down (dividend, divisor);
  }
}}}

int32_t div_u32_i32_up       (uint32_t dividend, int32_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u32_u32_down (dividend, -divisor);
  }
  else
  {
    return div_u32_u32_up (dividend, divisor);
  }
}}}

int32_t div_u32_i32_nearest  (uint32_t dividend, int32_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u32_u32_nearest (dividend, -divisor);
  }
  else
  {
    return div_u32_u32_nearest (dividend, divisor);
  }
}}}

/*   ** SIGNED BY SIGNED ** */

int32_t div_i32_i32_down     (int32_t dividend, int32_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u32_u32_down (-dividend, -divisor);
    }
    else
    {
      return -div_u32_u32_up (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u32_u32_up (dividend, -divisor);
    }
    else
    {
      return div_u32_u32_down (dividend, divisor);
    }
  }
}}}

int32_t div_i32_i32_up       (int32_t dividend, int32_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u32_u32_up (-dividend, -divisor);
    }
    else
    {
      return -div_u32_u32_down (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u32_u32_down (dividend, -divisor);
    }
    else
    {
      return div_u32_u32_up (dividend, divisor);
    }
  }
}}}

int32_t div_i32_i32_nearest  (int32_t dividend, int32_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u32_u32_nearest (-dividend, -divisor);
    }
    else
    {
      return -div_u32_u32_nearest (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u32_u32_nearest (dividend, -divisor);
    }
    else
    {
      return div_u32_u32_nearest (dividend, divisor);
    }
  }
}}}


/*   *** 64 BY 32 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

uint64_t div_u64_u32_up      (uint64_t dividend, uint32_t divisor)
{{{
  uint64_t quotient = div_u64_u32_down (dividend, divisor);

  if ((dividend - mul_u64_u32 (quotient, divisor)) != 0)
  {
    quotient++;
  }

  return quotient;
}}}

uint64_t div_u64_u32_nearest (uint64_t dividend, uint32_t divisor)
{{{
  uint64_t quotient = div_u64_u32_down (dividend, divisor);

  uint32_t remainder = (dividend - mul_u64_u32 (quotient, divisor));

  uint32_t half_divisor = (divisor / 2);

  if (remainder > half_divisor)
  {
    quotient++;
  }
  else
  {
    if ((remainder == half_divisor) && ((divisor & 1) == 0))
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}

/*   ** SIGNED BY UNSIGNED ** */

int64_t div_i64_u32_down     (int64_t dividend, uint32_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u64_u32_up (-dividend, divisor);
  }
  else
  {
    return div_u64_u32_down (dividend, divisor);
  }
}}}

int64_t div_i64_u32_up       (int64_t dividend, uint32_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u64_u32_down (-dividend, divisor);
  }
  else
  {
    return div_u64_u32_up (dividend, divisor);
  }
}}}

int64_t div_i64_u32_nearest  (int64_t dividend, uint32_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u64_u32_nearest (-dividend, divisor);
  }
  else
  {
    return div_u64_u32_nearest (dividend, divisor);
  }
}}}

/*   ** UNSIGNED BY SIGNED ** */

int64_t div_u64_i32_down     (uint64_t dividend, int32_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u64_u32_up (dividend, -divisor);
  }
  else
  {
    return div_u64_u32_down (dividend, divisor);
  }
}}}

int64_t div_u64_i32_up       (uint64_t dividend, int32_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u64_u32_down (dividend, -divisor);
  }
  else
  {
    return div_u64_u32_up (dividend, divisor);
  }
}}}

int64_t div_u64_i32_nearest  (uint64_t dividend, int32_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u64_u32_nearest (dividend, -divisor);
  }
  else
  {
    return div_u64_u32_nearest (dividend, divisor);
  }
}}}

/*   ** SIGNED BY SIGNED ** */

int64_t div_i64_i32_down     (int64_t dividend, int32_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u64_u32_down (-dividend, -divisor);
    }
    else
    {
      return -div_u64_u32_up (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u64_u32_up (dividend, -divisor);
    }
    else
    {
      return div_u64_u32_down (dividend, divisor);
    }
  }
}}}

int64_t div_i64_i32_up       (int64_t dividend, int32_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u64_u32_up (-dividend, -divisor);
    }
    else
    {
      return -div_u64_u32_down (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u64_u32_down (dividend, -divisor);
    }
    else
    {
      return div_u64_u32_up (dividend, divisor);
    }
  }
}}}

int64_t div_i64_i32_nearest  (int64_t dividend, int32_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u64_u32_nearest (-dividend, -divisor);
    }
    else
    {
      return -div_u64_u32_nearest (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u64_u32_nearest (dividend, -divisor);
    }
    else
    {
      return div_u64_u32_nearest (dividend, divisor);
    }
  }
}}}


/*   *** 32 BY 64 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

uint32_t div_u32_u64_up      (uint32_t dividend, uint64_t divisor)
{{{
  uint32_t quotient = div_u32_u64_down (dividend, divisor);

  if ((dividend - (quotient * (uint32_t)divisor)) != 0)
  {
    quotient++;
  }

  return quotient;
}}}

uint32_t div_u32_u64_nearest (uint32_t dividend, uint64_t divisor)
{{{
  uint32_t quotient = div_u32_u64_down (dividend, divisor);

  uint32_t remainder = (dividend - (quotient * (uint32_t)divisor));

  uint64_t half_divisor = (divisor / 2);

  if (remainder > half_divisor)
  {
    quotient++;
  }
  else
  {
    if ((remainder == half_divisor) && ((divisor & 1) == 0))
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}

/*   ** SIGNED BY UNSIGNED ** */

int32_t div_i32_u64_down     (int32_t dividend, uint64_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u32_u64_up (-dividend, divisor);
  }
  else
  {
    return div_u32_u64_down (dividend, divisor);
  }
}}}

int32_t div_i32_u64_up       (int32_t dividend, uint64_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u32_u64_down (-dividend, divisor);
  }
  else
  {
    return div_u32_u64_up (dividend, divisor);
  }
}}}

int32_t div_i32_u64_nearest  (int32_t dividend, uint64_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u32_u64_nearest (-dividend, divisor);
  }
  else
  {
    return div_u32_u64_nearest (dividend, divisor);
  }
}}}

/*   ** UNSIGNED BY SIGNED ** */

int32_t div_u32_i64_down     (uint32_t dividend, int64_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u32_u64_up (dividend, -divisor);
  }
  else
  {
    return div_u32_u64_down (dividend, divisor);
  }
}}}

int32_t div_u32_i64_up       (uint32_t dividend, int64_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u32_u64_down (dividend, -divisor);
  }
  else
  {
    return div_u32_u64_up (dividend, divisor);
  }
}}}

int32_t div_u32_i64_nearest  (uint32_t dividend, int64_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u32_u64_nearest (dividend, -divisor);
  }
  else
  {
    return div_u32_u64_nearest (dividend, divisor);
  }
}}}

/*   ** SIGNED BY SIGNED ** */

int32_t div_i32_i64_down     (int32_t dividend, int64_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u32_u64_down (-dividend, -divisor);
    }
    else
    {
      return -div_u32_u64_up (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u32_u64_up (dividend, -divisor);
    }
    else
    {
      return div_u32_u64_down (dividend, divisor);
    }
  }
}}}

int32_t div_i32_i64_up       (int32_t dividend, int64_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u32_u64_up (-dividend, -divisor);
    }
    else
    {
      return -div_u32_u64_down (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u32_u64_down (dividend, -divisor);
    }
    else
    {
      return div_u32_u64_up (dividend, divisor);
    }
  }
}}}

int32_t div_i32_i64_nearest  (int32_t dividend, int64_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u32_u64_nearest (-dividend, -divisor);
    }
    else
    {
      return -div_u32_u64_nearest (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u32_u64_nearest (dividend, -divisor);
    }
    else
    {
      return div_u32_u64_nearest (dividend, divisor);
    }
  }
}}}


/*   *** 64 BY 64 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

uint64_t div_u64_u64_up      (uint64_t dividend, uint64_t divisor)
{{{
  uint64_t quotient = div_u64_u64_down (dividend, divisor);

  if ((dividend - (quotient * divisor)) != 0)
  {
    quotient++;
  }

  return quotient;
}}}

uint64_t div_u64_u64_nearest (uint64_t dividend, uint64_t divisor)
{{{
  uint64_t quotient = div_u64_u64_down (dividend, divisor);

  uint64_t remainder = (dividend - (quotient * divisor));

  uint64_t half_divisor = (divisor / 2);

  if (remainder > half_divisor)
  {
    quotient++;
  }
  else
  {
    if ((remainder == half_divisor) && ((divisor & 1) == 0))
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}

/*   ** SIGNED BY UNSIGNED ** */

int64_t div_i64_u64_down     (int64_t dividend, uint64_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u64_u64_up (-dividend, divisor);
  }
  else
  {
    return div_u64_u64_down (dividend, divisor);
  }
}}}

int64_t div_i64_u64_up       (int64_t dividend, uint64_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u64_u64_down (-dividend, divisor);
  }
  else
  {
    return div_u64_u64_up (dividend, divisor);
  }
}}}

int64_t div_i64_u64_nearest  (int64_t dividend, uint64_t divisor)
{{{
  if (dividend < 0)
  {
    return -div_u64_u64_nearest (-dividend, divisor);
  }
  else
  {
    return div_u64_u64_nearest (dividend, divisor);
  }
}}}

/*   ** UNSIGNED BY SIGNED ** */

int64_t div_u64_i64_down     (uint64_t dividend, int64_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u64_u64_up (dividend, -divisor);
  }
  else
  {
    return div_u64_u64_down (dividend, divisor);
  }
}}}

int64_t div_u64_i64_up       (uint64_t dividend, int64_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u64_u64_down (dividend, -divisor);
  }
  else
  {
    return div_u64_u64_up (dividend, divisor);
  }
}}}

int64_t div_u64_i64_nearest  (uint64_t dividend, int64_t divisor)
{{{
  if (divisor < 0)
  {
    return -div_u64_u64_nearest (dividend, -divisor);
  }
  else
  {
    return div_u64_u64_nearest (dividend, divisor);
  }
}}}

/*   ** SIGNED BY SIGNED ** */

int64_t div_i64_i64_down     (int64_t dividend, int64_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u64_u64_down (-dividend, -divisor);
    }
    else
    {
      return -div_u64_u64_up (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u64_u64_up (dividend, -divisor);
    }
    else
    {
      return div_u64_u64_down (dividend, divisor);
    }
  }
}}}

int64_t div_i64_i64_up       (int64_t dividend, int64_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u64_u64_up (-dividend, -divisor);
    }
    else
    {
      return -div_u64_u64_down (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u64_u64_down (dividend, -divisor);
    }
    else
    {
      return div_u64_u64_up (dividend, divisor);
    }
  }
}}}

int64_t div_i64_i64_nearest  (int64_t dividend, int64_t divisor)
{{{
  if (dividend < 0)
  {
    if (divisor < 0)
    {
      return div_u64_u64_nearest (-dividend, -divisor);
    }
    else
    {
      return -div_u64_u64_nearest (-dividend, divisor);
    }
  }
  else
  {
    if (divisor < 0)
    {
      return -div_u64_u64_nearest (dividend, -divisor);
    }
    else
    {
      return div_u64_u64_nearest (dividend, divisor);
    }
  }
}}}



/*   ***** FIXED POINT DIVISION ***** */

/*   *** 64 BY 64 *** */

/*   ** UNSIGNED BY UNSIGNED ** */

uint64_t div_u64_u64_q_down    (uint64_t dividend, uint64_t divisor, unsigned int fixed_bits)
{{{
  if (divisor == 0)
  {
    return 0;
  }

  unsigned int divisor_zeros = __builtin_clzll (divisor);

  uint64_t shifted_divisor = (divisor << divisor_zeros);

  uint64_t quotient  = 0;
  uint64_t remainder = dividend;

  while ((fixed_bits > 0) && (remainder > 0))
  {
    unsigned int remainder_zeros = __builtin_clzll (remainder);

    if (remainder_zeros >= fixed_bits)
    {
      break;
    }

    quotient   <<= remainder_zeros;
    remainder  <<= remainder_zeros;
    fixed_bits  -= remainder_zeros;

    if (remainder < shifted_divisor)
    {
      quotient  <<= 1;
      remainder <<= 1;
      fixed_bits -= 1;
    }

    remainder -= shifted_divisor;
    quotient  |= (1uLL << divisor_zeros);
  }

  if (fixed_bits > 0)
  {
    quotient  <<= fixed_bits;
    remainder <<= fixed_bits;
  }

  while (remainder > 0)
  {
    unsigned int remainder_zeros = __builtin_clzll (remainder);

    if (remainder_zeros >= divisor_zeros)
    {
      break;
    }

    unsigned int shift = (divisor_zeros - remainder_zeros);

    shifted_divisor = (divisor << shift);

    if (shifted_divisor > remainder)
    {
      shift--;
      shifted_divisor = (divisor << shift);
    }

    remainder -= shifted_divisor;
    quotient |= (1uLL << shift);
  }

  if (remainder >= divisor)
  {
    quotient++;
    remainder -= divisor;
  }

  return quotient;
}}}

uint64_t div_u64_u64_q_up      (uint64_t dividend, uint64_t divisor, unsigned int fixed_bits)
{{{
  if (divisor == 0)
  {
    return 0;
  }

  unsigned int divisor_zeros = __builtin_clzll (divisor);

  uint64_t shifted_divisor = (divisor << divisor_zeros);

  uint64_t quotient  = 0;
  uint64_t remainder = dividend;

  while ((fixed_bits > 0) && (remainder > 0))
  {
    unsigned int remainder_zeros = __builtin_clzll (remainder);

    if (remainder_zeros >= fixed_bits)
    {
      break;
    }

    quotient   <<= remainder_zeros;
    remainder  <<= remainder_zeros;
    fixed_bits  -= remainder_zeros;

    if (remainder < shifted_divisor)
    {
      quotient  <<= 1;
      remainder <<= 1;
      fixed_bits -= 1;
    }

    remainder -= shifted_divisor;
    quotient  |= (1uLL << divisor_zeros);
  }

  if (fixed_bits > 0)
  {
    quotient  <<= fixed_bits;
    remainder <<= fixed_bits;
  }

  while (remainder > 0)
  {
    unsigned int remainder_zeros = __builtin_clzll (remainder);

    if (remainder_zeros >= divisor_zeros)
    {
      break;
    }

    unsigned int shift = (divisor_zeros - remainder_zeros);

    shifted_divisor = (divisor << shift);

    if (shifted_divisor > remainder)
    {
      shift--;
      shifted_divisor = (divisor << shift);
    }

    remainder -= shifted_divisor;
    quotient |= (1uLL << shift);
  }

  if (remainder >= divisor)
  {
    quotient++;
    remainder -= divisor;
  }

  if (remainder > 0)
  {
    quotient++;
  }

  return quotient;
}}}

uint64_t div_u64_u64_q_nearest (uint64_t dividend, uint64_t divisor, unsigned int fixed_bits)
{{{
  if (divisor == 0)
  {
    return 0;
  }

  unsigned int divisor_zeros = __builtin_clzll (divisor);

  uint64_t shifted_divisor = (divisor << divisor_zeros);

  uint64_t quotient  = 0;
  uint64_t remainder = dividend;

  while ((fixed_bits > 0) && (remainder > 0))
  {
    unsigned int remainder_zeros = __builtin_clzll (remainder);

    if (remainder_zeros >= fixed_bits)
    {
      break;
    }

    quotient   <<= remainder_zeros;
    remainder  <<= remainder_zeros;
    fixed_bits  -= remainder_zeros;

    if (remainder < shifted_divisor)
    {
      quotient  <<= 1;
      remainder <<= 1;
      fixed_bits -= 1;
    }

    remainder -= shifted_divisor;
    quotient  |= (1uLL << divisor_zeros);
  }

  if (fixed_bits > 0)
  {
    quotient  <<= fixed_bits;
    remainder <<= fixed_bits;
  }

  while (remainder > 0)
  {
    unsigned int remainder_zeros = __builtin_clzll (remainder);

    if (remainder_zeros >= divisor_zeros)
    {
      break;
    }

    unsigned int shift = (divisor_zeros - remainder_zeros);

    shifted_divisor = (divisor << shift);

    if (shifted_divisor > remainder)
    {
      shift--;
      shifted_divisor = (divisor << shift);
    }

    remainder -= shifted_divisor;
    quotient |= (1uLL << shift);
  }

  if (remainder >= divisor)
  {
    quotient++;
    remainder -= divisor;
  }

  uint64_t half_divisor = (divisor / 2);

  if (remainder > half_divisor)
  {
    quotient++;
  }
  else
  {
    if ((remainder == half_divisor) && ((divisor & 1) == 0))
    {
      quotient |= 1;
    }
  }

  return quotient;
}}}
