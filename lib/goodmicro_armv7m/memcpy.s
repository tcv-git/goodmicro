@; memcpy.s
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


.syntax unified
.cpu    cortex-m3
.thumb

.section  .text


.global   memset
.type     memset, %function
.thumb_func

@void *memset (void *s, int c, size_t n)

memset:
  mov r3, r2 @; swap r1 <-> r2
  mov r2, r1
  mov r1, r3
  mov r3, r0 @; save return value
.Lmemset_unaligned:
  cmp r1, 1 @; ASPR.C := (r1 >= 1)
  tst r0, 3 @; ASPR.Z := ((r0 & 3) == 0) ;  ASPR.C preserved
  itt hi    @; if ((C == 1) && (Z == 0))  i.e: (nbytes >= 1) && (dest unaligned)
  strbhi r2, [r0], 1
  subhi r1, 1
  bhi .Lmemset_unaligned
  @; fall through

.size memset, .-memset


.global   __aeabi_memset4
.type     __aeabi_memset4, %function
.thumb_func

@void __aeabi_memset (void *dest, size_t n, int c)

@; always returns r3, if called directly this is garbage but will not be used
@; because type is void, if falling through from memset this is initial r0

__aeabi_memset4:
  push {r3-r11,lr}
  bfi r2, r2, 8, 8
  bfi r2, r2, 16, 16
  mov r3, r2
  mov r4, r2
  mov r5, r2
  mov r6, r2
  mov r7, r2
  mov r8, r2
  mov r9, r2
  mov r10, r2
  mov r11, r2
  mov r12, r2
  mov lr, r2
  subs r1, 48
  blo .Lmemset4_words
.Lmemset4_block_loop:
  stm r0!, {r2-r12,lr}
  subs r1, 48
  bhs .Lmemset4_block_loop
.Lmemset4_words:
  adds r1, 44
  bcc .Lmemset4_bytes
.Lmemset4_word_loop:
  stm r0!, {r2}
  subs r1, 4
  bhs .Lmemset4_word_loop
.Lmemset4_bytes:
  tst r1, 2
  it ne
  strhne r2, [r0], 2
  lsrs r1, 1
  it cs
  strbcs r2, [r0]
  pop {r0,r4-r11,pc}

.size __aeabi_memset4, .-__aeabi_memset4


.global   memcpy
.type     memcpy, %function
.thumb_func

@void *memcpy (void *s1, const void *s2, size_t n)

memcpy:
  cbz r2, .Lmemcpy_return
  orr r3, r0, r1
  lsls r3, 30
  beq.n __aeabi_memcpy4
  mov r12, r0
.Lmemcpy_byte_loop:
  ldrb r3, [r1], 1
  strb r3, [r0], 1
  subs r2, 1
  bne .Lmemcpy_byte_loop
  mov r0, r12
.Lmemcpy_return:
  bx lr

.size memcpy, .-memcpy


.global   __aeabi_memcpy4
.type     __aeabi_memcpy4, %function
.thumb_func

@void __aeabi_memcpy4 (void *dest, const void *src, size_t nbytes)

__aeabi_memcpy4:
  push {r0,r4-r11,lr}
  subs r2, 44
  blo .Lmemcpy4_words
.Lmemcpy4_block_loop:
  ldm r1!, {r3-r12,lr}
  stm r0!, {r3-r12,lr}
  subs r2, 44
  bhs .Lmemcpy4_block_loop
.Lmemcpy4_words:
  adds r2, 40
  bcc .Lmemcpy4_bytes
.Lmemcpy4_word_loop:
  ldm r1!, {r3}
  stm r0!, {r3}
  subs r2, 4
  bhs .Lmemcpy4_word_loop
.Lmemcpy4_bytes:
  tst r2, 2
  itt ne
  ldrhne r3, [r1], 2
  strhne r3, [r0], 2
  lsrs r2, 1
  itt cs
  ldrbcs r3, [r1]
  strbcs r3, [r0]
  pop {r0,r4-r11,pc}

.size __aeabi_memcpy4, .-__aeabi_memcpy4
