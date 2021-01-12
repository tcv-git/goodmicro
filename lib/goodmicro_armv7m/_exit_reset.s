@; _exit_reset.s
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


.syntax         unified
.cpu            cortex-m3

.section        .text._exit
.global         _exit
.type           _exit, %function
.thumb_func

_exit:
        cpsid   f
        ldr     r0, =0xE000ED0C
        ldr     r1, =0x05FA0704
        dsb
1:
        str     r1, [r0]
        b       1b

.size   _exit, . - _exit
