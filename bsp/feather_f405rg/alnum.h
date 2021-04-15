// alnum.h
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

#ifndef ALNUM_H_INCLUDED
#define ALNUM_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SEGMENT_A   (1u <<  0)
#define SEGMENT_B   (1u <<  1)
#define SEGMENT_C   (1u <<  2)
#define SEGMENT_D   (1u <<  3)
#define SEGMENT_E   (1u <<  4)
#define SEGMENT_F   (1u <<  5)
#define SEGMENT_G1  (1u <<  6)
#define SEGMENT_G2  (1u <<  7)
#define SEGMENT_H   (1u <<  8)
#define SEGMENT_J   (1u <<  9)
#define SEGMENT_K   (1u << 10)
#define SEGMENT_L   (1u << 11)
#define SEGMENT_M   (1u << 12)
#define SEGMENT_N   (1u << 13)
#define SEGMENT_DP  (1u << 14)

#define SEGMENTS_0  (SEGMENT_A  |SEGMENT_B  |SEGMENT_C  |SEGMENT_D  |SEGMENT_E  |SEGMENT_F                          )
#define SEGMENTS_1  (            SEGMENT_B  |SEGMENT_C                                                              )
#define SEGMENTS_2  (SEGMENT_A  |SEGMENT_B              |SEGMENT_D  |SEGMENT_E              |SEGMENT_G1  |SEGMENT_G2)
#define SEGMENTS_3  (SEGMENT_A  |SEGMENT_B  |SEGMENT_C  |SEGMENT_D                          |SEGMENT_G1  |SEGMENT_G2)
#define SEGMENTS_4  (            SEGMENT_B  |SEGMENT_C                          |SEGMENT_F  |SEGMENT_G1  |SEGMENT_G2)
#define SEGMENTS_5  (SEGMENT_A              |SEGMENT_C  |SEGMENT_D              |SEGMENT_F  |SEGMENT_G1  |SEGMENT_G2)
#define SEGMENTS_6  (SEGMENT_A              |SEGMENT_C  |SEGMENT_D  |SEGMENT_E  |SEGMENT_F  |SEGMENT_G1  |SEGMENT_G2)
#define SEGMENTS_7  (SEGMENT_A  |SEGMENT_B  |SEGMENT_C                                                              )
#define SEGMENTS_8  (SEGMENT_A  |SEGMENT_B  |SEGMENT_C  |SEGMENT_D  |SEGMENT_E  |SEGMENT_F  |SEGMENT_G1  |SEGMENT_G2)
#define SEGMENTS_9  (SEGMENT_A  |SEGMENT_B  |SEGMENT_C  |SEGMENT_D              |SEGMENT_F  |SEGMENT_G1  |SEGMENT_G2)

#define SEGMENTS_LI  (SEGMENT_E | SEGMENT_F | SEGMENT_C)
#define SEGMENTS_M   (SEGMENT_E | SEGMENT_G1 | SEGMENT_G2 | SEGMENT_M | SEGMENT_C)

extern const uint16_t ALNUM_DIGITS[10];

void alnum_init(void);
void alnum_write(uint16_t d1, uint16_t d2, uint16_t d3, uint16_t d4);

void alnum_red(unsigned int x);
void alnum_green(unsigned int x);
void alnum_lim(unsigned int x);

#ifdef __cplusplus
}
#endif

#endif // ALNUM_H_INCLUDED
