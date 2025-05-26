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


.section .startup_vectors, "a", %progbits


.local   startup_vectors
.type    startup_vectors, %object
.align   10

startup_vectors:
        .word   _estack
        .word   Reset_Handler
        .word   early_fault_handler  @; NMI
        .word   early_fault_handler  @; HardFault
        .word   early_fault_handler  @; MemManage
        .word   early_fault_handler  @; BusFault
        .word   early_fault_handler  @; UsageFault

.size    startup_vectors, . - startup_vectors


.section        .startup, "ax", %progbits


.local          early_fault_handler
.type           early_fault_handler, %function
.thumb_func

early_fault_handler:
        bx      lr

.size early_fault_handler, . - early_fault_handler


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

        @; copy ITCM contents
        ldr     r0, =_text0_addr
        ldr     r1, =_text0_load
        ldr     r2, =_text0_size
        ldr     r3, =memcpy

        subs    r3, r0
        adds    r3, r1
        blx     r3 @; memcpy from flash

        ldr     r0, =continue_startup
        bx      r0

.size   Reset_Handler, . - Reset_Handler


.section        .text0.continue_startup, "ax", %progbits

.local          continue_startup
.type           continue_startup, %function
.thumb_func

continue_startup:
        @; copy initialized DTCM contents
        ldr     r0, =_vectors_addr
        ldr     r1, =_vectors_load
        ldr     r2, =_vectors_size
        bl      memcpy

        @; copy initialized DTCM contents
        ldr     r0, =_rodata0_addr
        ldr     r1, =_rodata0_load
        ldr     r2, =_rodata0_size
        bl      memcpy

        @; copy initialized DTCM contents
        ldr     r0, =_data0_addr
        ldr     r1, =_data0_load
        ldr     r2, =_data0_size
        bl      memcpy

        @; copy initialized AXI-SRAM contents
        ldr     r0, =_data1_addr
        ldr     r1, =_data1_load
        ldr     r2, =_data1_size
        bl      memcpy

        @; clear zero-initialized DTCM contents
        ldr     r0, =_bss0_addr
        ldr     r2, =_bss0_size
        movs    r1, 0
        bl      memset

        @; clear zero-initialized AXI-SRAM contents
        ldr     r0, =_bss1_addr
        ldr     r2, =_bss1_size
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

.size   continue_startup, . - continue_startup


@; define symbol __libc_fini as non-zero to make register_fini do
@; atexit(__libc_fini_array)

.global         __libc_fini
.set            __libc_fini, 1
