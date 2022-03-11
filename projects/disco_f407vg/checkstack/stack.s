@; stack.s
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


.syntax  unified
.cpu     cortex-m3

@;##############################################################################
.section .text.stack_fill
.global  stack_fill
.type    stack_fill, %function
@;##############################################################################

.thumb_func
stack_fill:
    ldr r0, =0x12345678
    ldr r1, =__StackLimit
    ldr r2, =__StackTop
    cmp sp, r2
    it lo
    movlo r2, sp
    b 2f
.align 2
1:  str r0, [r1], 4
2:  cmp r1, r2
    blo 1b
    bx lr

.size stack_fill, . - stack_fill


@;##############################################################################
.section .text.stack_high
.global  stack_high
.type    stack_high, %function
@;##############################################################################

.thumb_func
stack_high:
    push {r4-r11,lr}
    ldr r0, =__StackLimit
    ldr r1, =0x12345678
.align 2
1:  ldm r0!, {r2-r12,lr}
    cmp r2, r1
    it eq
    cmpeq r3, r1
    it eq
    cmpeq r4, r1
    it eq
    cmpeq r5, r1
    it eq
    cmpeq r6, r1
    it eq
    cmpeq r7, r1
    it eq
    cmpeq r8, r1
    it eq
    cmpeq r9, r1
    it eq
    cmpeq r10, r1
    it eq
    cmpeq r11, r1
    it eq
    cmpeq r12, r1
    it eq
    cmpeq lr, r1
    beq 1b
    subs r0, 48
1:  ldrb r2, [r0], 1
    cmp r2, 0x78
    bne 1f
    ldrb r2, [r0], 1
    cmp r2, 0x56
    bne 1f
    ldrb r2, [r0], 1
    cmp r2, 0x34
    bne 1f
    ldrb r2, [r0], 1
    cmp r2, 0x12
    beq 1b
1:  subs r0, 1
    pop {r4-r11,pc}

.size stack_high, . - stack_high


@;##############################################################################
.section .text.stack_used
.global  stack_used
.type    stack_used, %function
@;##############################################################################

.thumb_func
stack_used:
  push {lr}
  bl stack_high
  ldr r1, =__StackTop
  subs r0, r1, r0
  pop {pc}

.size stack_used, . - stack_used


@;##############################################################################
.section .text.stack_remaining
.global  stack_remaining
.type    stack_remaining, %function
@;##############################################################################

.thumb_func
stack_remaining:
  push {lr}
  bl stack_high
  ldr r1, =__StackLimit
  subs r0, r1
  pop {pc}

.size stack_remaining, . - stack_remaining


@;##############################################################################
