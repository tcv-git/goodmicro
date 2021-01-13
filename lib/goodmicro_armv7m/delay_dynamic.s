@; delay_dynamic.s
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

.global   delay_s
.global   delay_ms
.global   delay_us
.global   delay_100_ns
.global   delay_sysclk_long
.global   delay_sysclk

.type     delay_s          , %function
.type     delay_ms         , %function
.type     delay_us         , %function
.type     delay_100_ns     , %function
.type     delay_sysclk_long, %function
.type     delay_sysclk     , %function

@ void delay_s           (unsigned int)
@ void delay_ms          (unsigned int)
@ void delay_us          (unsigned int)
@ void delay_100_ns      (unsigned int)
@ void delay_sysclk_long (unsigned long long int)
@ void delay_sysclk      (unsigned int)

.section  .text

.thumb_func

delay_s:
        ldr r3, =0xE000E010
        ldr r2, [r3, 8]
        cbnz r0, .Lnonzero_s
        bx lr
.Lnonzero_s:
        ldr r1, =SystemCoreClock
        ldr r1, [r1]
        umull r0, r1, r0, r1
        b .Llong_start

.size delay_s, .-delay_s

.thumb_func

delay_ms:
        ldr r3, =0xE000E010
        ldr r2, [r3, 8]
        cbnz r0, .Lnonzero_ms
        bx lr
.Lnonzero_ms:
        ldr r1, =SystemCoreClock
        ldr r1, [r1]
        movw r12, 999
        umull r0, r1, r0, r1
        adds r0, r12
        adcs r1, 0
        beq .Lloop_pre_start
        push {r4,lr}
        mov r4, r2
        add r2, r12, 1
        ldr r3, =4294967
        adr lr, .Llong_loop_pre_start + 1 @; +1 for interworking address
        b udiv64i

.size delay_ms, .-delay_ms

.thumb_func

delay_us:
        ldr r3, =0xE000E010
        ldr r2, [r3, 8]
        cbnz r0, .Lnonzero_us
        bx lr
.Lnonzero_us:
        ldr r1, =SystemCoreClock
        ldr r1, [r1]
        ldr r12, =999999
        umull r0, r1, r0, r1
        adds r0, r12
        adcs r1, 0
        beq .Lloop_pre_start
        push {r4,lr}
        mov r4, r2
        add r2, r12, 1
        movw r3, 4294
        adr lr, .Llong_loop_pre_start + 1 @; +1 for interworking address
        b udiv64i

.size delay_us, .-delay_us

.thumb_func

delay_100_ns:
        ldr r3, =0xE000E010
        ldr r2, [r3, 8]
        cbnz r0, .Lnonzero_100_ns
        bx lr
.Lnonzero_100_ns:
        ldr r1, =SystemCoreClock
        ldr r1, [r1]
        ldr r12, =9999999
        umull r0, r1, r0, r1
        adds r0, r12
        adcs r1, 0
        beq .Lloop_pre_start
        push {r4,lr}
        mov r4, r2
        add r2, r12, 1
        movw r3, 429
        adr lr, .Llong_loop_pre_start + 1 @; +1 for interworking address
        b udiv64i

.size delay_100_ns, .-delay_100_ns

.thumb_func

.Llong_loop_pre_start:
        ldr r3, =0xE000E010
        ldr r12, [r3, 4]
        add r12, 1
        b .Llong_loop_start

.thumb_func

delay_sysclk_long:
        ldr r3, =0xE000E010
        ldr r2, [r3, 8]
.Llong_start:
        ldr r12, [r3, 4]
        add r12, 1
        push {r4,lr}
.Llong_loop:
        mov r4, r2
.Llong_loop_start:
        ldr r2, [r3, 8]
        subs r4, r2
        it lo
        addlo r4, r12
        subs r0, r4
        sbcs r1, 0
        bhi .Llong_loop
        pop {r4,lr}
        b .Lloop

.size delay_sysclk_long, .-.Llong_loop_pre_start

.thumb_func

.Lloop_pre_start:
        add r12, 1
        udiv r0, r12
        b .Lloop_start

.thumb_func

delay_sysclk:
        ldr r3, =0xE000E010
        ldr r2, [r3, 8]
.Lloop_start:
        ldr r12, [r3, 4]
        add r12, 1
.Lloop:
        mov r1, r2
        ldr r2, [r3, 8]
        subs r1, r2
        it lo
        addlo r1, r12
        subs r0, r1
        bhi .Lloop
        bx lr

.size delay_sysclk, .-.Lloop_pre_start
