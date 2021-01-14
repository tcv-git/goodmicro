@; startup_stm32f4xx_extram.s
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
.cpu            cortex-m4

.section        .text.Reset_Handler
.global         Reset_Handler
.type           Reset_Handler, %function
.thumb_func

Reset_Handler:
        ldr     r0, =_ccm_data_addr
        ldr     r1, =_ccm_data_load
        ldr     r2, =_ccm_data_size
        bl      memcpy

        ldr     r0, =_sram_data_addr
        ldr     r1, =_sram_data_load
        ldr     r2, =_sram_data_size
        bl      memcpy

        ldr     r0, =_ccm_bss_addr
        ldr     r2, =_ccm_bss_size
        movs    r1, 0
        bl      memset

        ldr     r0, =_sram_bss_addr
        ldr     r2, =_sram_bss_size
        movs    r1, 0
        bl      memset

        bl      SystemInit
        bl      extram_init

        ldr     r0, =_ext_data_addr
        ldr     r1, =_ext_data_load
        ldr     r2, =_ext_data_size
        bl      memcpy

        ldr     r0, =_ext_bss_addr
        ldr     r2, =_ext_bss_size
        movs    r1, 0
        bl      memset

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
