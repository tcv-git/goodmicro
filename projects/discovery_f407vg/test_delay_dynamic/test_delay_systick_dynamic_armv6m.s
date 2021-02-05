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
.cpu    cortex-m0
.thumb

.global   delay_s
.global   delay_ms
.global   delay_us
.global   delay_ns

.type     delay_s            , %function
.type     delay_ms           , %function
.type     delay_us           , %function
.type     delay_ns           , %function


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
delay_coreclk_long_start:
        bx lr


@;##############################################################################
