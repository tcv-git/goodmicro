@; test_delay_units.s
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

.global   test_delay_s
.type     test_delay_s, %function

.section  .text.test_delay_s
.thumb_func

@; uint64_t test_delay_s(uint32_t s, uint32_t *coarse_clock, uint32_t *fine_clock)

test_delay_s:
  push {r3-r7,lr}
  mov r4, r1
  mov r5, r2
  ldr r6, [r4]
  ldr r7, [r5]
  bl delay_s
  ldr r1, [r5]
  ldr r0, [r4]
  subs r0, r6
  subs r1, r7
  pop {r3-r7,pc}

.size test_delay_s, .-test_delay_s


.global   test_delay_ms
.type     test_delay_ms, %function

.section  .text.test_delay_ms
.thumb_func

@; uint64_t test_delay_ms(uint32_t ms, uint32_t *coarse_clock, uint32_t *fine_clock)

test_delay_ms:
  push {r3-r7,lr}
  mov r4, r1
  mov r5, r2
  ldr r6, [r4]
  ldr r7, [r5]
  bl delay_ms
  ldr r1, [r5]
  ldr r0, [r4]
  subs r0, r6
  subs r1, r7
  pop {r3-r7,pc}

.size test_delay_ms, .-test_delay_ms


.global   test_delay_us
.type     test_delay_us, %function

.section  .text.test_delay_us
.thumb_func

@; uint64_t test_delay_us(uint32_t us, uint32_t *coarse_clock, uint32_t *fine_clock)

test_delay_us:
  push {r3-r7,lr}
  mov r4, r1
  mov r5, r2
  ldr r6, [r4]
  ldr r7, [r5]
  bl delay_us
  ldr r1, [r5]
  ldr r0, [r4]
  subs r0, r6
  subs r1, r7
  pop {r3-r7,pc}

.size test_delay_us, .-test_delay_us


.global   test_delay_ns
.type     test_delay_ns, %function

.section  .text.test_delay_ns
.thumb_func

@; uint64_t test_delay_ns(uint32_t ns, uint32_t *coarse_clock, uint32_t *fine_clock)

test_delay_ns:
  push {r3-r7,lr}
  mov r4, r1
  mov r5, r2
  ldr r6, [r4]
  ldr r7, [r5]
  bl delay_ns
  ldr r1, [r5]
  ldr r0, [r4]
  subs r0, r6
  subs r1, r7
  pop {r3-r7,pc}

.size test_delay_ns, .-test_delay_ns
