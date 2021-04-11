@; udiv64.s
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


.syntax unified
.cpu    cortex-m3
.thumb

.section  .text.udiv64i

.global   udiv64i
.type     udiv64i, %function
.align 2
.thumb_func

@uint64_t udiv64i (uint64_t dividend, uint32_t divisor, uint32_t inverse)

udiv64i:

dividend_lo .req r0
dividend_hi .req r1
divisor     .req r2
inverse     .req r3
part_lo     .req r4
part_hi     .req r5
quotient_lo .req r12
quotient_hi .req r14

  push  {r4,r5,lr}
  umull quotient_lo, quotient_hi, dividend_hi, inverse
  mls   dividend_hi, quotient_hi, divisor, dividend_hi
  umull part_lo, part_hi, quotient_lo, divisor
  subs  dividend_lo, part_lo
  sbcs  dividend_hi, part_hi

.Loop:
  umlal quotient_lo, quotient_hi, dividend_hi, inverse
  umull part_lo, part_hi, dividend_hi, inverse
  mls   dividend_hi, part_hi, divisor, dividend_hi
  umull part_lo, part_hi, part_lo, divisor
  subs  dividend_lo, part_lo
  sbcs  dividend_hi, part_hi
  bne  .Loop

  udiv  dividend_lo, dividend_lo, divisor
  adds  dividend_lo, quotient_lo
  adc   dividend_hi, quotient_hi, 0
  pop   {r4,r5,pc}

.size  udiv64i, .-udiv64i
