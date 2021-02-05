@; delay_systick_dynamic.s
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


@;##############################################################################
@; delay functions using the SysTick timer and the SystemCoreClock variable
@;##############################################################################

.syntax unified
.cpu    cortex-m3
.thumb

.global   delay_s
.global   delay_ms
.global   delay_us
.global   delay_ns
.global   delay_coreclk
.global   delay_coreclk_long

.type     delay_s            , %function
.type     delay_ms           , %function
.type     delay_us           , %function
.type     delay_ns           , %function
.type     delay_coreclk      , %function
.type     delay_coreclk_long , %function

@ void delay_s            (unsigned int)
@ void delay_ms           (unsigned int)
@ void delay_us           (unsigned int)
@ void delay_ns           (unsigned int)
@ void delay_coreclk      (unsigned int)
@ void delay_coreclk_long (unsigned long long int)


@;##############################################################################
.section  .text.delay_s
@;##############################################################################

.thumb_func
delay_s:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        ldr   r1, =SystemCoreClock
        ldr   r1, [r1]
        push  {lr}
        umull r0, lr, r0, r1
        b.n   delay_coreclk_long_start2

.size delay_s, . - delay_s


@;##############################################################################
.section  .text.delay_ms
@;##############################################################################

.thumb_func
delay_ms:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        push  {r2, r3, lr}
        ldr   r1, =SystemCoreClock
        ldr   r3, =4294967  @; ((1 << 32) / 1000)
        ldr   r1, [r1]
        umull r0, r1, r0, r1
        movw  r2, 999
        adds  r0, r2
        adcs  r1, 0
        adds  r2, 1
        bl    udiv64i  @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        pop   {r2, r3}
        b.n   delay_coreclk_long_start1

.size delay_ms, . - delay_ms


@;##############################################################################
.section  .text.delay_us
@;##############################################################################

.thumb_func
delay_us:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        push  {r2, r3, lr}
        ldr   r1, =SystemCoreClock
        ldr   r2, =999999
        ldr   r1, [r1]
        umull r0, r1, r0, r1
        movw  r3, 4294  @; ((1 << 32) / 1000000)
        adds  r0, r2
        adcs  r1, 0
        adds  r2, 1
        bl    udiv64i  @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        pop   {r2, r3}
        b.n   delay_coreclk_long_start1

.size delay_us, . - delay_us


@;##############################################################################
.section  .text.delay_ns
@;##############################################################################

.thumb_func
delay_ns:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        push  {r2, r3, lr}
        ldr   r1, =SystemCoreClock
        ldr   r2, =999999999
        ldr   r1, [r1]
        umull r0, r1, r0, r1
        movs  r3, 4  @; ((1 << 32) / 1000000000)
        adds  r0, r2
        adcs  r1, 0
        adds  r2, 1
        bl    udiv64i  @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        pop   {r2, r3}
        b.n   delay_coreclk_long_start1

.size delay_ns, . - delay_ns


@;##############################################################################
.section  .text.delay_coreclk_long
@;##############################################################################

.thumb_func
delay_coreclk_long:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        push  {lr}
delay_coreclk_long_start1:
        mov   lr, r1
delay_coreclk_long_start2:
        ldr   r12, [r3, 4]
        add   r12, 1
1:      mov   r1, r2
        ldr   r2, [r3, 8]
        subs  r1, r2
        it    lo
        addlo r1, r12
        subs  r0, r1
        sbcs  lr, 0
        bhi   1b
        it    cc
        popcc {pc}
        pop   {lr}
        b.n   delay_coreclk_loop

.size delay_coreclk_long, . - delay_coreclk_long


@;##############################################################################
.section  .text.delay_coreclk
@;##############################################################################

.thumb_func
delay_coreclk:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        ldr   r12, [r3, 4]
        add   r12, 1
delay_coreclk_loop:
        mov   r1, r2
        ldr   r2, [r3, 8]
        subs  r1, r2
        it    lo
        addlo r1, r12
        subs  r0, r1
        bhi   delay_coreclk_loop
        bx    lr

.size delay_coreclk, . - delay_coreclk


@;##############################################################################
