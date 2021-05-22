// limit_buttons.h
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

#ifndef LIMIT_BUTTONS_H_INCLUDED
#define LIMIT_BUTTONS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define BUTTON_20  (1u << 2)
#define BUTTON_30  (1u << 3)
#define BUTTON_40  (1u << 4)
#define BUTTON_50  (1u << 5)
#define BUTTON_60  (1u << 6)
#define BUTTON_70  (1u << 7)

void limit_buttons_init(void);

unsigned int get_buttons(void);
unsigned int get_limit(void);

#ifdef __cplusplus
}
#endif

#endif // LIMIT_BUTTONS_H_INCLUDED
