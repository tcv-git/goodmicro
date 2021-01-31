@; delay.s
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


@; delay function using the SysTick timer


.syntax unified
.cpu    cortex-m0
.thumb

.section  .text.delay_sysclk

.global   delay_sysclk
.type     delay_sysclk, %function
.align 2
.thumb_func

@void delay_sysclk (unsigned int count)

delay_sysclk:
        ldr r3, .LSysTick
        ldr r2, [r3, 8]
        ldr r1, [r3, 4]
        adds r1, 1
        mov r12, r1
.Lloop:
        mov r1, r2
        ldr r2, [r3, 8]
        subs r1, r2
        bhs .Lnowrap
        add r1, r12
.Lnowrap:
        subs r0, r1
        bhi .Lloop
        bx lr
        .align 2
.LSysTick:
        .word 0xE000E010

.size delay_sysclk, .-delay_sysclk
