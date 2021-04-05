@; test_delay_coreclk.s
@; PUBLIC DOMAIN
@; https://www.purposeful.co.uk/software/goodmicro


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

.global   test_sequence
.type     test_sequence, %function

.section  .text.test_sequence
.thumb_func

test_sequence:
  push {r4-r8,lr}

  mov r4, r0
  mov r5, r1
  mov r6, r2
  mov r7, r3

  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]
  mov r0, r4
  bl delay_coreclk
  str r6, [r5]
  mov r0, r4
  bl delay_coreclk
  str r7, [r5]

  pop {r4-r8,pc}

.size test_sequence, .-test_sequence


.global   just_return
.type     just_return, %function

.thumb_func

just_return:
  bx lr

.size just_return, .-just_return



.global   just_return_sequence
.type     just_return_sequence, %function

.section  .text.just_return_sequence
.thumb_func

just_return_sequence:
  push {r4-r8,lr}

  mov r4, r0
  mov r5, r1
  mov r6, r2
  mov r7, r3

  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]
  mov r0, r4
  bl just_return
  str r6, [r5]
  mov r0, r4
  bl just_return
  str r7, [r5]

  pop {r4-r8,pc}

.size just_return_sequence, .-just_return_sequence


.global   nop_sequence
.type     nop_sequence, %function

.section  .text.nop_sequence
.thumb_func

nop_sequence:
  push {r4-r8,lr}

  mov r4, r0
  mov r5, r1
  mov r6, r2
  mov r7, r3

  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]
  mov r0, r4
  nop.w
  str r6, [r5]
  mov r0, r4
  nop.w
  str r7, [r5]

  pop {r4-r8,pc}

.size nop_sequence, .-nop_sequence


.global   nonop_sequence
.type     nonop_sequence, %function

.section  .text.nonop_sequence
.thumb_func

nonop_sequence:
  push {r4-r8,lr}

  mov r4, r0
  mov r5, r1
  mov r6, r2
  mov r7, r3

  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]
  mov r0, r4
  str r6, [r5]
  mov r0, r4
  str r7, [r5]

  pop {r4-r8,pc}

.size nonop_sequence, .-nonop_sequence


.global   nomov_sequence
.type     nomov_sequence, %function

.section  .text.nomov_sequence
.thumb_func

nomov_sequence:
  push {r4-r8,lr}

  mov r4, r0
  mov r5, r1
  mov r6, r2
  mov r7, r3

  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]
  str r6, [r5]
  str r7, [r5]

  pop {r4-r8,pc}

.size nomov_sequence, .-nomov_sequence
