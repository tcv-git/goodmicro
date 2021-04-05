@; test_udiv64i.s
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

.global test_udiv64i
.type   test_udiv64i, %function

.section .text
.thumb_func

test_udiv64i:
        push {r4-r6,lr}
        ldr r4, =0xE0001004
        ldr r5, [r4]
        bl udiv64i
        ldr r4, [r4]
        subs r4, r5
        ldr r5, [sp,16]
        str r4, [r5]
        pop {r4-r6,pc}

.size test_udiv64i, .-test_udiv64i
