@; Atomic test-and-set functions
@; Copyright Green Energy Options Limited

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


.section  .text.atomic_set_u8_if_zero, "ax", %progbits

.global   atomic_set_u8_if_zero
.type     atomic_set_u8_if_zero, %function
.thumb_func

@; int atomic_set_u8_if_zero(volatile uint8_t*, uint8_t);

atomic_set_u8_if_zero:
    ldrexb  r2, [r0]
    cmp     r2, 0
    ittt    ne
    clrexne
    movne   r0, r2
    bxne    lr
    strexb  r2, r1, [r0]
    tst     r2, r2
    bne.n   atomic_set_u8_if_zero
    movs    r0, 0
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
    ittt    gt
    movgt   r0, 1
    clrexgt
    bxgt    lr
    strexb  r2, r1, [r0]
    tst     r2, r2
    bne.n   atomic_set_i8_if_le_zero
    movs    r0, 0
    bx      lr

.size atomic_set_i8_if_le_zero, .-atomic_set_i8_if_le_zero


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