@; startup_vos0.s
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

.section .text.startup_vos0, "ax", %progbits
.global  startup_vos0
.type    startup_vos0, %function

.thumb_func
startup_vos0:

pwr .req r3

  mrs   r12, faultmask  @; store interrupt mask
  cpsid f               @; interrupts off

  ldr   pwr,=0x58024800 @; PWR_BASE

  ldr   r0, [pwr, 12]   @; PWR_CR3
  lsrs  r1, r0, 1       @; if PWR_CR3_BYPASS
  bcs   .               @; loop here forever

  lsrs  r1, r0, 3       @; if PWR_CR3_SCUEN
  itt   cs
  orrcs r0, 2           @; |= PWR_CR3_LDOEN
  strcs r0, [pwr, 12]   @; PWR_CR3
1:
  ldr   r0, [pwr, 4]    @; PWR_CSR1
  lsrs  r0, 14          @; PWR_CSR1_ACTVOSRDY
  bcc   1b              @; if !PWR_CSR1_ACTVOSRDY repeat

  mov   r0, (3 << 14)   @; PWR_D3CR_VOS scale 1
  str   r0, [pwr, 24]   @; PWR_D3CR
1:
  ldr   r0, [pwr, 24]   @; PWR_D3CR
  lsrs  r0, 14          @; PWR_D3CR_VOSRDY
  bcc   1b              @; if !PWR_D3CR_VOSRDY repeat

  ldr   r1, =0x580244F4 @; RCC_APB4ENR
  ldr   r0, [r1]
  orr   r0, 2           @; |= RCC_APB4ENR_SYSCFGEN
  str   r0, [r1]
  ldr   r0, [r1]        @; dummy read to allow propagation

  ldr   r1, =0x5800042C @; SYSCFG_PWRCR
  ldr   r0, [r1]
  orr   r0, 1           @; |= SYSCFG_PWRCR_ODEN
  str   r0, [r1]
1:
  ldr   r0, [pwr, 4]    @; PWR_CSR1
  ubfx  r0, r0, 13, 3   @; PWR_CSR1_ACTVOS | PWR_CSR1_ACTVOSRDY
  cmp   r0, 7           @; == (PWR_CSR1_ACTVOS | PWR_CSR1_ACTVOSRDY)
  bne   1b              @; if != repeat

  msr   faultmask, r12  @; restore interrupt mask
  bx    lr              @; return

.size startup_vos0, .-startup_vos0
