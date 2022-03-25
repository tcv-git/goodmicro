@; startup.s
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


.syntax         unified

.section        .text.Reset_Handler
.global         Reset_Handler
.type           Reset_Handler, %function
.thumb_func

Reset_Handler:
        ldr     r0, =_sdata
        ldr     r1, =_sidata
        ldr     r2, =_edata
        subs    r2, r0
        bl      memcpy

        ldr     r0, =_sbss
        ldr     r2, =_ebss
        subs    r2, r0
        movs    r1, 0
        bl      memset

        bl      SystemInit
        bl      __libc_init_array

        movs    r0, 0
        adr.n   r1, 1f
        bl      main
        bl      exit
        b       .

        .align  2
1:      .word   0

.size   Reset_Handler, . - Reset_Handler


@; define symbol __libc_fini as non-zero to make register_fini do
@; atexit(__libc_fini_array)

.global         __libc_fini
.set            __libc_fini, 1
