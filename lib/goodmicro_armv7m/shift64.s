@; shift64.s
@; PUBLIC DOMAIN
@; https://www.purposeful.co.uk/software/goodmicro


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


.section  .text.__aeabi_llsl
.global   __aeabi_llsl
.type     __aeabi_llsl, %function
.thumb_func

@ long long __aeabi_llsl (long long, int)

__aeabi_llsl: @; 6 or 7 cycles (excluding return), 28 bytes
  subs r3, r2, 32
  bhs .Lllsl_single
  rsbs r3, 0
  lsr r3, r0, r3
  lsls r1, r2
  lsls r0, r2
  orrs r1, r3
  bx lr
.Lllsl_single:
  lsls r1, r0, r3
  movs r0, 0
  bx lr

.size __aeabi_llsl, .-__aeabi_llsl


.section  .text.__aeabi_llsr
.global   __aeabi_llsr
.type     __aeabi_llsr, %function
.thumb_func

@ long long __aeabi_llsr (long long, int)

__aeabi_llsr: @; 6 or 7 cycles (excluding return), 28 bytes
  subs r3, r2, 32
  bhs .Lllsr_single
  rsbs r3, 0
  lsl r3, r1, r3
  lsrs r0, r2
  lsrs r1, r2
  orrs r0, r3
  bx lr
.Lllsr_single:
  lsrs r0, r1, r3
  movs r1, 0
  bx lr

.size __aeabi_llsr, .-__aeabi_llsr


.section  .text.__aeabi_lasr
.global   __aeabi_lasr
.type     __aeabi_lasr, %function
.thumb_func

@ long long __aeabi_lasr (long long, int)

__aeabi_lasr: @; 6 or 7 cycles (excluding return), 28 bytes
  subs r3, r2, 32
  bhs .Llasr_single
  rsbs r3, 0
  lsl r3, r1, r3
  lsrs r0, r2
  asrs r1, r2
  orrs r0, r3
  bx lr
.Llasr_single:
  asrs r0, r1, r3
  asrs r1, 31
  bx lr

.size __aeabi_lasr, .-__aeabi_lasr
