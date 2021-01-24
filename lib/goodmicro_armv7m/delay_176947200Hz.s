@; delay_176947200Hz.s
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


@; delay functions using the debug cycle counter
@; assuming fixed system core clock of 176947200 Hz
@; prime factors are 5^2 3^3 2^18


.syntax unified
.cpu    cortex-m3
.thumb

.global   delay_s
.global   delay_ms
.global   delay_us
.global   delay_ns
.global   delay_sysclk_long
.global   delay_sysclk

.type     delay_s          , %function
.type     delay_ms         , %function
.type     delay_us         , %function
.type     delay_ns         , %function
.type     delay_sysclk_long, %function
.type     delay_sysclk     , %function

@ void delay_s           (unsigned int)
@ void delay_ms          (unsigned int)
@ void delay_us          (unsigned int)
@ void delay_ns          (unsigned int)
@ void delay_sysclk_long (unsigned long long int)
@ void delay_sysclk      (unsigned int)


.section  .text.delay_s
.thumb_func

delay_s:
        ldr r3, =0xE0001004
        ldr r1, [r3]
        ldr r2, =176947200
        umull r0, r12, r0, r2
        b.n delay_sysclk_long_inner

.size delay_s, .-delay_s


.section  .text.delay_ms
.thumb_func

@; delay_ms: := delay_sysclk_long (      r0 * 176947.2   )
@;           := delay_sysclk_long (ceil (r0 * 884736 / 5))
delay_ms:
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        push {r1, r3, lr}
        ldr   r1, =884736    @; 176947.2 * 5
        umull r0, r1, r0, r1
        ldr   r3, =858993459 @; 2^32     / 5
        adds  r0, 4   @; no need to adc r1 because carry must be zero
        mov   r2, 5
        bl udiv64i    @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        mov   r12, r1
        pop  {r1, r3, lr}
        b.n delay_sysclk_long_inner

.size delay_ms, .-delay_ms


.section  .text.delay_us
.thumb_func
@; delay_us: := delay_sysclk_long (      r0 * 176.9472     )
@;           := delay_sysclk_long (ceil (r0 * 110592 / 625))
delay_us:
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        push {r1, r3, lr}
        ldr   r3, =6871947   @; 2^32     / 625
        mov.w r1, 110592     @; 176.9472 * 625
        umull r0, r1, r0, r1
        add.w r0, 624   @; no need to adc r1 because carry must be zero
        movw  r2, 625
        bl udiv64i    @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        mov   r12, r1
        pop  {r1, r3, lr}
        b.n delay_sysclk_long_inner

.size delay_us, .-delay_us


.section  .text.delay_ns
.thumb_func
@; delay_ns: := delay_sysclk_long (      r0 * .1769472      )
@;           := delay_sysclk_long (ceil (r0 * 13824 / 78125))
delay_ns:
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        push {r1, r3, lr}
        ldr   r2, =78124
        movw  r1, 13824
        umull r0, r1, r0, r1
        movw  r3, 54975  @; 2^32 / 78125
        adds  r0, r2
        adcs  r1, 0
        adds  r2, 1
        bl udiv64i    @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        mov  r12, r1
        pop  {r1, r3, lr}
        b.n delay_sysclk_long_inner

.size delay_ns, .-delay_ns


.section  .text.delay_sysclk_long
.thumb_func

delay_sysclk_long:
        ldr r3, =0xE0001004
        ldr r2, [r3]
        mov r12, r1
1:      mov r1, r2
delay_sysclk_long_inner:
        ldr r2, [r3]
        subs r1, r2
        adds r0, r1
        adcs r12, -1
        bhi 1b
        bcs delay_sysclk_inner
        bx lr

.size delay_sysclk_long, .-delay_sysclk_long


.section  .text.delay_sysclk
.thumb_func

delay_sysclk:
        ldr r3, =0xE0001004
        ldr r2, [r3]
delay_sysclk_inner:
        mov r1, r2
        ldr r2, [r3]
        subs r1, r2
        adds r0, r1
        bhi delay_sysclk_inner
        bx lr

.size delay_sysclk, .-delay_sysclk
