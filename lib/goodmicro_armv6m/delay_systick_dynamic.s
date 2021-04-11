@; delay_systick_dynamic.s
@; PUBLIC DOMAIN
@; https://www.purposeful.co.uk/goodmicro/


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
.cpu    cortex-m0
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
        push  {r2, lr}
        bl    mul_u32_u32
        pop   {r2, r3}
        mov   lr, r3
        ldr   r3, =0xE000E010
        b.n   delay_coreclk_long_start

.size delay_s, . - delay_s

@;##############################################################################
.section  .text.delay_ms
@;##############################################################################

.thumb_func
delay_ms:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        ldr   r1, =SystemCoreClock
        ldr   r1, [r1]
        push  {r2, lr}
        bl    mul_u32_u32
        ldr   r2, =999
        movs  r3, 0
        adds  r0, r2
        adcs  r1, r3
        adds  r2, 1
        bl    __aeabi_uldivmod
        pop   {r2, r3}
        mov   lr, r3
        ldr   r3, =0xE000E010
        b.n   delay_coreclk_long_start

.size delay_ms, . - delay_ms


@;##############################################################################
.section  .text.delay_us
@;##############################################################################

.thumb_func
delay_us:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        ldr   r1, =SystemCoreClock
        ldr   r1, [r1]
        push  {r2, lr}
        bl    mul_u32_u32
        ldr   r2, =999999
        movs  r3, 0
        adds  r0, r2
        adcs  r1, r3
        adds  r2, 1
        bl    __aeabi_uldivmod
        pop   {r2, r3}
        mov   lr, r3
        ldr   r3, =0xE000E010
        b.n   delay_coreclk_long_start

.size delay_us, . - delay_us


@;##############################################################################
.section  .text.delay_ns
@;##############################################################################

.thumb_func
delay_ns:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        ldr   r1, =SystemCoreClock
        ldr   r1, [r1]
        push  {r2, lr}
        bl    mul_u32_u32
        ldr   r2, =999999999
        movs  r3, 0
        adds  r0, r2
        adcs  r1, r3
        adds  r2, 1
        bl    __aeabi_uldivmod
        pop   {r2, r3}
        mov   lr, r3
        ldr   r3, =0xE000E010
        b.n   delay_coreclk_long_start


.size delay_ns, . - delay_ns


@;##############################################################################
.section  .text.delay_coreclk_long
@;##############################################################################

.thumb_func
delay_coreclk_long:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
delay_coreclk_long_start:
        push  {r4}
        ldr   r4, [r3, 4]
        adds  r4, 1
        mov   r12, r4
1:      mov   r4, r2
        ldr   r2, [r3, 8]
        subs  r4, r2
        bhs   2f
        add   r4, r12
2:      subs  r0, r4
        movs  r4, 0
        sbcs  r1, r4
        bhi   1b
        pop   {r4}
        bcs.n delay_coreclk_loop
        bx    lr

.size delay_coreclk_long, . - delay_coreclk_long


@;##############################################################################
.section  .text.delay_coreclk
@;##############################################################################

.thumb_func
delay_coreclk:
        ldr   r3, =0xE000E010
        ldr   r2, [r3, 8]
        ldr   r1, [r3, 4]
        adds  r1, 1
        mov   r12, r1
delay_coreclk_loop:
        mov   r1, r2
        ldr   r2, [r3, 8]
        subs  r1, r2
        bhs   2f
        add   r1, r12
2:      subs  r0, r1
        bhi   delay_coreclk_loop
        bx    lr

.size delay_coreclk, . - delay_coreclk


@;##############################################################################
