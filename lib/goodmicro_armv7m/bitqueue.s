@; bitqueue.s
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
@; int bitqueue_write(unsigned int *control, unsigned int message);
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global  bitqueue_write
.type    bitqueue_write, %function

.thumb_func
bitqueue_write:

control_ptr .req r0
new_entry   .req r1
control_val .req r2
temp        .req r3
result      .req r0

  bfi new_entry, new_entry, 4, 4
  bfi new_entry, new_entry, 8, 8
  bfi new_entry, new_entry, 16, 16

1:
  ldrex control_val, [control_ptr]

  cmp control_val, 0x10000
  it eq
  moveq control_val, new_entry
  beq 2f

  eor temp, control_val, control_val, lsl 4
  clz temp, temp
  bics temp, 3

  ittt eq
  clrexeq
  moveq result, -1
  bxeq lr

  lsls control_val, temp
  lsrs control_val, temp
  rsbs temp, 32

  ite eq
  lsleq new_entry, 4
  lslne new_entry, temp
  orrs control_val, new_entry

2:
  strex temp, control_val, [control_ptr]
  cmp temp, 0
  bne 1b

  movs result, 0
  bx lr

.unreq control_ptr
.unreq new_entry
.unreq control_val
.unreq temp
.unreq result

.size bitqueue_write, .-bitqueue_write


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@; int bitqueue_read(unsigned int *control);
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global  bitqueue_read
.type    bitqueue_read, %function

.thumb_func
bitqueue_read:

control_ptr     .req r0
old_control_val .req r1
new_control_val .req r2
temp            .req r3
result          .req r0

  ldrex old_control_val, [control_ptr]

  cmp old_control_val, 0x10000
  ittt eq
  clrexeq
  moveq result, -1
  bxeq lr

  lsrs new_control_val, old_control_val, 4
  lsrs temp, old_control_val, 28
  bfi new_control_val, temp, 28, 4

  cmp new_control_val, old_control_val
  it eq
  moveq new_control_val, 0x10000

  strex temp, new_control_val, [control_ptr]
  cmp temp, 0
  bne bitqueue_read

  and result, old_control_val, 0xF
  bx lr

.unreq control_ptr
.unreq old_control_val
.unreq new_control_val
.unreq temp
.unreq result

.size bitqueue_read, .-bitqueue_read
