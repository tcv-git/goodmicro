@; startup_ldo.s
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

.section .text.startup_ldo, "ax", %progbits
.global  startup_ldo
.type    startup_ldo, %function

.thumb_func
startup_ldo:

  mrs   r3, faultmask   @; store interrupt mask
  cpsid f               @; interrupts off

  ldr   r2, =0x58024800 @; PWR_BASE

  ldr   r0, [r2, 12]    @; PWR_CR3
  lsrs  r1, r0, 1       @; if PWR_CR3_BYPASS
  bcs   .               @; loop here forever

  lsrs  r1, r0, 3       @; if PWR_CR3_SCUEN
  itt   cs
  orrcs r0, 2           @; |= PWR_CR3_LDOEN
  strcs r0, [r2, 12]    @; PWR_CR3
1:
  ldr   r0, [r2, 4]     @; PWR_CSR1
  lsrs  r0, 14          @; PWR_CSR1_ACTVOSRDY
  bcc   1b              @; if !PWR_CSR1_ACTVOSRDY repeat

  msr   faultmask, r3   @; restore interrupt mask
  bx    lr              @; return

.size startup_ldo, .-startup_ldo
