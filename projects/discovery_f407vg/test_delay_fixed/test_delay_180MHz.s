@; delay_180MHz.s
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
@; delay functions using the debug cycle counter
@; assuming fixed system core clock of 180 MHz
@;##############################################################################

.syntax unified
.cpu    cortex-m3
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
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        ldr   r2, =180000000
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
        ldr   r2, =180000
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
        movs  r2, 180
        umull r0, r12, r0, r2
        b.n   delay_coreclk_long_inner

.size delay_us, . - delay_us


@;##############################################################################
.section  .text.delay_ns
@;##############################################################################

@; delay_ns: := delay_coreclk_long (      r0 * 0.18   )
@;           := delay_coreclk_long (ceil (r0 * 9 / 50))
.thumb_func
delay_ns:
        ldr   r3, =0xE0001004
        ldr   r1, [r3]
        push  {r1, r3, lr}
        movs  r1, 9
        umull r0, r1, r0, r1
        ldr   r3, =85899345  @; 2^32 / 50
        adds  r0, 49
        adcs  r1, 0
        movs  r2, 50
        bl    udiv64i  @; call not aeabi compliant beacuse stack not aligned here (I know udiv64i doesn't mind)
        mov   r12, r1
        pop   {r1, r3, lr}
        b.n   delay_coreclk_long_inner

.size delay_ns, . - delay_ns


@;##############################################################################
.section  .text.delay_coreclk_long
@;##############################################################################

.thumb_func
delay_coreclk_long_inner:
        mov r1, r12
        bx lr


@;##############################################################################
