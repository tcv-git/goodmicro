// buzzer.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all intellectual property rights in them, including
  copyright, trademarks, design rights, database right, patents, and the right
  to be identified as the author.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  You are free to use, modify and distribute this software as you please, but
  you do so at your own risk.  If you do not pass on this warning then you may
  be responsible for any problems encountered by those who obtain the software
  through you.
*/

#ifndef BUZZER_H_INCLUDED
#define BUZZER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void buzzer_init(void);
void buzzer_sound(unsigned int freq);

#ifdef __cplusplus
}
#endif

#endif // BUZZER_H_INCLUDED
