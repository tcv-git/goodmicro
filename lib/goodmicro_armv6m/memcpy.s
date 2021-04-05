@; memcpy.s
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
.cpu    cortex-m0
.thumb

.section  .text


.global   memset
.type     memset, %function
.thumb_func

@void *memset (void *s, int c, size_t n)

memset:
  lsls r3, r0, 30
  beq .Luse_memset4
  movs r3, 0
  b .Lmemset_start
.Lmemset_loop:
  strb r1, [r0, r3]
  adds r3, 1
.Lmemset_start:
  cmp r2, r3
  bne .Lmemset_loop
  bx lr
.Luse_memset4:
  mov r3, r2 @; r3 = count
  mov r2, r1 @; r2 = byte
  mov r1, r3 @; r1 = count
  @; fall through

.size memset, .-memset


.global   __aeabi_memset4
.type     __aeabi_memset4, %function
.thumb_func

@void __aeabi_memset (void *dest, size_t n, int c)

__aeabi_memset4:
  push {r0,r4-r7,lr}
  uxtb r2, r2
  lsls r3, r2, 8
  orrs r2, r3
  lsls r3, r2, 16
  orrs r2, r3
  mov r3, r2
  mov r4, r2
  mov r5, r2
  mov r6, r2
  mov r7, r2
  subs r1, 24
  blo .Lmemset4_words
.Lmemset4_block_loop:
  stm r0!, {r2-r7}
  subs r1, 24
  bhs .Lmemset4_block_loop
.Lmemset4_words:
  adds r1, 20
  bcc .Lmemset4_bytes
.Lmemset4_word_loop:
  stm r0!, {r2}
  subs r1, 4
  bhs .Lmemset4_word_loop
.Lmemset4_bytes:
  lsrs r1, 1
  bcc .Lmemset4_no_byte
  lsrs r1, 1
  bcc .Lmemset4_byte_no_half
  strh r2, [r0]
  strb r2, [r0, 2]
  b .Lmemset4_return
.Lmemset4_byte_no_half:
  strb r2, [r0]
  b .Lmemset4_return
.Lmemset4_no_byte:
  lsrs r1, 1
  bcc .Lmemset4_return
  strh r2, [r0]
.Lmemset4_return:
  pop {r0,r4-r7,pc}

.size __aeabi_memset4, .-__aeabi_memset4


.global   memcpy
.type     memcpy, %function
.thumb_func

@void *memcpy (void *s1, const void *s2, size_t n)

memcpy:
  mov r3, r0
  orrs r3, r1
  lsls r3, 30
  beq.n __aeabi_memcpy4
  mov r12, r2
  movs r2, 0
  b .Lmemcpy_byte_start
.Lmemcpy_byte_loop:
  ldrb r3, [r1, r2]
  strb r3, [r0, r2]
  adds r2, 1
.Lmemcpy_byte_start:
  cmp r2, r12
  bne .Lmemcpy_byte_loop
  bx lr

.size memcpy, .-memcpy


.global   __aeabi_memcpy4
.type     __aeabi_memcpy4, %function
.thumb_func

@void __aeabi_memcpy4 (void *dest, const void *src, size_t nbytes)

__aeabi_memcpy4:
  push {r0,r4-r7,lr}
  subs r2, 20
  blo .Lmemcpy4_words
.Lmemcpy4_block_loop:
  ldm r1!, {r3-r7}
  stm r0!, {r3-r7}
  subs r2, 20
  bhs .Lmemcpy4_block_loop
.Lmemcpy4_words:
  adds r2, 16
  bcc .Lmemcpy4_bytes
.Lmemcpy4_word_loop:
  ldm r1!, {r3}
  stm r0!, {r3}
  subs r2, 4
  bhs .Lmemcpy4_word_loop
.Lmemcpy4_bytes:
  lsrs r2, 1
  bcc .Lmemcpy4_no_byte
  lsrs r2, 1
  bcc .Lmemcpy4_byte_no_half
  ldrh r3, [r1]
  strh r3, [r0]
  ldrb r3, [r1, 2]
  strb r3, [r0, 2]
  b .Lmemcpy4_return
.Lmemcpy4_byte_no_half:
  ldrb r3, [r1]
  strb r3, [r0]
  b .Lmemcpy4_return
.Lmemcpy4_no_byte:
  lsrs r2, 1
  bcc .Lmemcpy4_return
  ldrh r3, [r1]
  strh r3, [r0]
.Lmemcpy4_return:
  pop {r0,r4-r7,pc}

.size __aeabi_memcpy4, .-__aeabi_memcpy4
