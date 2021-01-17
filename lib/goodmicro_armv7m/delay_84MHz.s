@; delay_84MHz.s
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
@; assuming fixed system core clock of 84 MHz


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

.section  .text

.thumb_func

delay_s:
        ldr r3, =0xE0001004
        ldr r1, [r3]
        ldr r2, =84000000
        umull r0, r12, r0, r2
        b 2f

.size delay_s, .-delay_s

.thumb_func

delay_ms:
        ldr r3, =0xE0001004
        ldr r1, [r3]
        ldr r2, =84000
        umull r0, r12, r0, r2
        b 2f

.size delay_ms, .-delay_ms

.thumb_func

delay_us:
        ldr r3, =0xE0001004
        ldr r1, [r3]
        movs r2, 84
        umull r0, r12, r0, r2
        b 2f

.size delay_us, .-delay_us

.thumb_func

@; delay_ns: := delay_sysclk_long (      r0 * 0.084    )
@;           := delay_sysclk_long (ceil (r0 * 21 / 250))
delay_ns:
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        push {r1, r3, lr}
        movs  r1, 21
        umull r0, r1, r0, r1
        ldr   r3, =17179869  @; 2^32 / 250
        adds  r0, 249
        adcs  r1, 0
        movs  r2, 250
        bl udiv64i    @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        mov  r12, r1
        pop  {r1, r3, lr}
        b     2f

.size delay_ns, .-delay_ns

.thumb_func

delay_sysclk_long:
        ldr r3, =0xE0001004
        ldr r2, [r3]
        mov r12, r1
1:      mov r1, r2
2:      ldr r2, [r3]
        subs r1, r2
        adds r0, r1
        adcs r12, -1
        bhi 1b
        bcs 1f
        bx lr

.size delay_sysclk_long, .-delay_sysclk_long

.thumb_func

delay_sysclk:
        ldr r3, =0xE0001004
        ldr r2, [r3]
1:      mov r1, r2
        ldr r2, [r3]
        subs r1, r2
        adds r0, r1
        bhi 1b
        bx lr

.size delay_sysclk, .-delay_sysclk
