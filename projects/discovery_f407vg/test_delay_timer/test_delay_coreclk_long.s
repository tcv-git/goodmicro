@; test_delay_coreclk_long.s
@; PUBLIC DOMAIN
@; http:///www.purposeful.co.uk/software/goodmicro


@; I, Tom Vajzovic, am the author of this software and its documentation.
@; I permanently abandon all copyright and other intellectual property rights
@; in them.

@; I am fairly certain that the software does what the documentation says it
@; does, but I do not guarantee that it does, or that it does what you think it
@; should.  I do not guarantee that it will not have undesirable side effects.

@; If you use, modify or distribute this software then you do so at your own
@; risk.  If you do not pass on this warning then you may be responsible for any
@; problems encountered by those who obtain the software through you.


.syntax unified
.cpu    cortex-m3
.thumb

.global   test_delay_coreclk_long
.type     test_delay_coreclk_long, %function

.section  .text.test_delay_coreclk_long
.thumb_func

@; uint64_t test_delay_coreclk_long(uint64_t delay, uint32_t *coarse_clock, uint32_t *fine_clock)

test_delay_coreclk_long:
  push {r3-r7,lr}
  mov r4, r2
  mov r5, r3
  ldr r6, [r4]
  ldr r7, [r5]
  bl delay_coreclk_long
  ldr r1, [r5]
  ldr r0, [r4]
  subs r0, r6
  subs r1, r7
  pop {r3-r7,pc}

.size test_delay_coreclk_long, .-test_delay_coreclk_long
