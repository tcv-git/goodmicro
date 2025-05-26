@; startup_stm32h7xx.s
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
        ldr     r2, =0x58024800 @; PWR_BASE

        ldr     r0, [r2, 12]    @; PWR_CR3
        lsrs    r1, r0, 1       @; if PWR_CR3_BYPASS
        bcs     .               @; loop here forever

        lsrs    r1, r0, 3       @; if PWR_CR3_SCUEN
        itt     cs
        orrcs   r0, 2           @; |= PWR_CR3_LDOEN
        strcs   r0, [r2, 12]    @; PWR_CR3
1:
        ldr     r0, [r2, 4]     @; PWR_CSR1
        lsrs    r0, 14          @; PWR_CSR1_ACTVOSRDY
        bcc     1b              @; if !PWR_CSR1_ACTVOSRDY repeat

        @; copy initialized RAM contents
        ldr     r0, =_sdata
        ldr     r1, =_sidata
        ldr     r2, =_edata
        subs    r2, r0
        bl      memcpy

        @; clear zero-initialized RAM contents
        ldr     r0, =_sbss
        ldr     r2, =_ebss
        subs    r2, r0
        movs    r1, 0
        bl      memset

        @; setup clocks etc
        bl      SystemInit

        @; call library initializers and C++ constructors
        bl      __libc_init_array

        @; args to main are ((int)0, (*char[]){NULL})
        movs    r0, 0
        adr.n   r1, 1f
        bl      main

        @; return value of main is argument to exit
        bl      exit
        b       .

        .align  2
1:      .word   0

.size   Reset_Handler, . - Reset_Handler


@; define symbol __libc_fini as non-zero to make register_fini do
@; atexit(__libc_fini_array)

.global         __libc_fini
.set            __libc_fini, 1
