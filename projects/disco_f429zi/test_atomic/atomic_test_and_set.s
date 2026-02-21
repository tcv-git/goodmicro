@; Atomic test-and-set functions
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


.section  .text.atomic_inc_u8, "ax", %progbits

.global   atomic_inc_u8
.type     atomic_inc_u8, %function
.thumb_func

@; uint8_t atomic_inc_u8(volatile uint8_t*);

atomic_inc_u8:
    ldrexb  r1, [r0]
    adds    r1, 1
    strexb  r2, r1, [r0]
    tst     r2, r2
    bne.n   atomic_inc_u8
    mov     r0, r1
    bx      lr

.size atomic_inc_u8, .-atomic_inc_u8


.section  .text.atomic_dec_u8, "ax", %progbits

.global   atomic_dec_u8
.type     atomic_dec_u8, %function
.thumb_func

@; uint8_t atomic_dec_u8(volatile uint8_t*);

atomic_dec_u8:
    ldrexb  r1, [r0]
    subs    r1, 1
    strexb  r2, r1, [r0]
    tst     r2, r2
    bne.n   atomic_dec_u8
    mov     r0, r1
    bx      lr

.size atomic_dec_u8, .-atomic_dec_u8


.section  .text.atomic_inc_nowrap_u8, "ax", %progbits

.global   atomic_inc_nowrap_u8
.type     atomic_inc_nowrap_u8, %function
.thumb_func

@; uint8_t atomic_inc_nowrap_u8(volatile uint8_t*);

atomic_inc_nowrap_u8:
    ldrexb  r1, [r0]
    adds    r1, 1
    lsrs    r2, r1, 8
    bne     1f
    strexb  r2, r1, [r0]
    tst     r2, r2
    bne.n   atomic_inc_nowrap_u8
    mov     r0, r1
    bx      lr
1:  negs    r0, r2
    clrex
    bx      lr

.size atomic_inc_nowrap_u8, .-atomic_inc_nowrap_u8


.section  .text.atomic_dec_nowrap_u8, "ax", %progbits

.global   atomic_dec_nowrap_u8
.type     atomic_dec_nowrap_u8, %function
.thumb_func

@; uint8_t atomic_dec_nowrap_u8(volatile uint8_t*);

atomic_dec_nowrap_u8:
    ldrexb  r1, [r0]
    subs    r1, 1
    bcc     1f
    strexb  r2, r1, [r0]
    tst     r2, r2
    bne.n   atomic_dec_nowrap_u8
    mov     r0, r1
    bx      lr
1:  clrex
    mov     r0, r1
    bx      lr

.size atomic_dec_nowrap_u8, .-atomic_dec_nowrap_u8


.section  .text.atomic_set_u8_if_zero, "ax", %progbits

.global   atomic_set_u8_if_zero
.type     atomic_set_u8_if_zero, %function
.thumb_func

@; int atomic_set_u8_if_zero(volatile uint8_t*, uint8_t);

atomic_set_u8_if_zero:
    ldrexb  r2, [r0]
    cbnz    r2, 1f
    strexb  r2, r1, [r0]
    tst     r2, r2
    bne.n   atomic_set_u8_if_zero
    movs    r0, 0
    bx      lr
1:  movs    r0, 1
    clrex
    bx      lr

.size atomic_set_u8_if_zero, .-atomic_set_u8_if_zero


.section  .text.atomic_set_i8_if_le_zero, "ax", %progbits

.global   atomic_set_i8_if_le_zero
.type     atomic_set_i8_if_le_zero, %function
.thumb_func

@; int atomic_set_i8_if_le_zero(volatile int8_t*, int8_t);

atomic_set_i8_if_le_zero:
    ldrexb  r2, [r0]
    sxtb    r2, r2
    cmp     r2, 0
    bgt     1f
    strexb  r2, r1, [r0]
    tst     r2, r2
    bne.n   atomic_set_i8_if_le_zero
    movs    r0, 0
    bx      lr
1:  movs    r0, 1
    clrex
    bx      lr

.size atomic_set_i8_if_le_zero, .-atomic_set_i8_if_le_zero


.section  .text.atomic_swap_u8, "ax", %progbits

.global   atomic_swap_u8
.type     atomic_swap_u8, %function
.thumb_func

@; uint8_t atomic_swap_u8(volatile uint8_t*, uint8_t);

atomic_swap_u8:
    ldrexb  r2, [r0]
    strexb  r3, r1, [r0]
    tst     r3, r3
    bne.n   atomic_swap_u8
    mov     r0, r2
    bx      lr

.size atomic_swap_u8, .-atomic_swap_u8


.section  .text.atomic_swap_u32, "ax", %progbits

.global   atomic_swap_u32
.type     atomic_swap_u32, %function
.thumb_func

@; uint32_t atomic_swap_u32(volatile uint32_t*, uint32_t);

atomic_swap_u32:
    ldrex   r2, [r0]
    strex   r3, r1, [r0]
    tst     r3, r3
    bne.n   atomic_swap_u32
    mov     r0, r2
    bx      lr

.size atomic_swap_u32, .-atomic_swap_u32


.section  .text.atomic_or_u32, "ax", %progbits

.global   atomic_or_u32
.type     atomic_or_u32, %function
.thumb_func

@; uint32_t atomic_or_u32(volatile uint32_t*, uint32_t);

atomic_or_u32:
    ldrex   r2, [r0]
    orrs    r2, r1
    strex   r3, r2, [r0]
    tst     r3, r3
    bne.n   atomic_or_u32
    mov     r0, r2
    bx      lr

.size atomic_or_u32, .-atomic_or_u32


.section  .text.atomic_bic_u32_if_u8_eq_zero, "ax", %progbits

.global   atomic_bic_u32_if_u8_eq_zero
.type     atomic_bic_u32_if_u8_eq_zero, %function
.thumb_func

@; int atomic_bic_u32_if_u8_eq_zero(volatile uint32_t *, uint32_t, const volatile uint8_t*);

atomic_bic_u32_if_u8_eq_zero:
    ldrex   r12, [r0]
    ldrb    r3, [r2]
    cbnz    r3, 1f
    bic     r12, r1
    strex   r3, r12, [r0]
    tst     r3, r3
    bne.n   atomic_bic_u32_if_u8_eq_zero
1:  clrex
    mov     r0, r3
    bx      lr

.size atomic_bic_u32_if_u8_eq_zero, .-atomic_bic_u32_if_u8_eq_zero

