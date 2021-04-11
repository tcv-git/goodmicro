@; bitpool.s
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

.section .text, "ax", %progbits


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@; int bitpool_alloc(unsigned int *control);
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global  bitpool_alloc
.type    bitpool_alloc, %function

.thumb_func
bitpool_alloc:

control_ptr .req r0
control_val .req r1
zeros       .req r2
success     .req r3
result      .req r0

  ldrex control_val, [control_ptr]

  clz zeros, control_val
  adds zeros, 1
  lsls control_val, zeros
  lsrs control_val, zeros

  strex success, control_val, [control_ptr]
  cmp success, 0
  bne bitpool_alloc

  rsb result, zeros, 32
  bx lr

.unreq control_ptr
.unreq control_val
.unreq zeros
.unreq success
.unreq result

.size bitpool_alloc, .-bitpool_alloc


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@; void bitpool_free(unsigned int *control, unsigned int index);
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global  bitpool_free
.type    bitpool_free, %function

.thumb_func
bitpool_free:

  movs r2, 1
  lsls r2, r1
1:
  ldrex r1, [r0]
  orrs r1, r2
  strex r3, r1, [r0]
  cmp r3, 0
  bne 1b
  bx lr

.size bitpool_free, .-bitpool_free
