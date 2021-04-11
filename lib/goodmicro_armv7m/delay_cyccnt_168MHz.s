@; delay_168MHz.s
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
@; delay functions using the debug cycle counter
@; assuming fixed system core clock of 168 MHz
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
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        ldr   r2, =168000000
        umull r0, r12, r0, r2
        b.n   delay_coreclk_long_inner

.size delay_s, . - delay_s


@;##############################################################################
.section  .text.delay_ms
@;##############################################################################

.thumb_func
delay_ms:
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        ldr   r2, =168000
        umull r0, r12, r0, r2
        b.n   delay_coreclk_long_inner

.size delay_ms, . - delay_ms


@;##############################################################################
.section  .text.delay_us
@;##############################################################################

.thumb_func
delay_us:
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        movs  r2, 168
        umull r0, r12, r0, r2
        b.n   delay_coreclk_long_inner

.size delay_us, . - delay_us


@;##############################################################################
.section  .text.delay_ns
@;##############################################################################

@; delay_ns: := delay_coreclk_long (      r0 * 0.168    )
@;           := delay_coreclk_long (ceil (r0 * 21 / 125))
.thumb_func
delay_ns:
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        push  {r1, r3, lr}
        movs  r1, 21
        umull r0, r1, r0, r1
        ldr   r3, =34359738  @; 2^32 / 125
        adds  r0, 124
        adcs  r1, 0
        movs  r2, 125
        bl    udiv64i  @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        mov   r12, r1
        pop   {r1, r3, lr}
        b.n   delay_coreclk_long_inner

.size delay_ns, . - delay_ns


@;##############################################################################
.section  .text.delay_coreclk_long
@;##############################################################################

.thumb_func
delay_coreclk_long:
        ldr   r3, =0xE0001004
        ldr   r2, [r3]
        mov   r12, r1
1:      mov   r1, r2
delay_coreclk_long_inner:
        ldr   r2, [r3]
        subs  r1, r2
        adds  r0, r1
        adcs  r12, -1
        bhi   1b
        bcs   delay_coreclk_loop
        bx    lr

.size delay_coreclk_long, . - delay_coreclk_long


@;##############################################################################
.section  .text.delay_coreclk
@;##############################################################################

.thumb_func
delay_coreclk:
        ldr   r3, =0xE0001004
        ldr   r2, [r3]
delay_coreclk_loop:
        mov   r1, r2
        ldr   r2, [r3]
        subs  r1, r2
        adds  r0, r1
        bhi   delay_coreclk_loop
        bx    lr

.size delay_coreclk, . - delay_coreclk


@;##############################################################################
