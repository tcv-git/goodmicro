@; imath.s
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
.cpu    cortex-m0
.thumb

.section  .text.sqr_u32
.global   sqr_u32
.type     sqr_u32, %function
.thumb_func

@ uint64_t sqr_u32 (uint32_t)

sqr_u32:
  lsrs r2, r0, 16
  lsrs r1, r0, 16
  uxth r0, r0
  muls r2, r0
  muls r1, r1
  muls r0, r0
  lsrs r3, r2, 15
  lsls r2, 17
  adds r0, r2
  adcs r1, r3
  bx lr

.size sqr_u32, .-sqr_u32


.section  .text.sqr_i32
.global   sqr_i32
.type     sqr_i32, %function
.thumb_func

@ uint64_t sqr_i32 (int32_t)

sqr_i32:
  asrs r2, r0, 16
  asrs r1, r0, 16
  uxth r0, r0
  muls r2, r0
  muls r1, r1
  muls r0, r0
  asrs r3, r2, 15
  lsls r2, 17
  adds r0, r2
  adcs r1, r3
  bx lr

.size sqr_i32, .-sqr_i32


.section  .text.mul_u32_u16
.global   mul_u32_u16
.type     mul_u32_u16, %function
.thumb_func

@ uint64_t mul_u32_u16 (uint32_t, uint16_t)

mul_u32_u16:
  lsrs r2, r0, 16
  muls r2, r1
  uxth r0, r0
  muls r0, r1
  movs r3, 0
  lsrs r1, r2, 16
  lsls r2, 16
  adds r0, r2
  adcs r1, r3
  bx lr

.size mul_u32_u16, .-mul_u32_u16


.section  .text.mul_u32_i16
.global   mul_u32_i16
.type     mul_u32_i16, %function
.thumb_func

@ int64_t mul_u32_i16 (uint32_t, int16_t)

mul_u32_i16:
  lsrs r2, r0, 16
  muls r2, r1
  uxth r0, r0
  muls r0, r1
  asrs r3, r0, 31
  asrs r1, r2, 16
  lsls r2, 16
  adds r0, r2
  adcs r1, r3
  bx lr

.size mul_u32_i16, .-mul_u32_i16


.section  .text.mul_i32_u16
.global   mul_i32_u16
.type     mul_i32_u16, %function
.thumb_func

@ int64_t mul_i32_u16 (int32_t, uint16_t)

mul_i32_u16:
  asrs r2, r0, 16
  muls r2, r1
  uxth r0, r0
  muls r0, r1
  movs r3, 0
  asrs r1, r2, 16
  lsls r2, 16
  adds r0, r2
  adcs r1, r3
  bx lr

.size mul_i32_u16, .-mul_i32_u16


.section  .text.mul_i32_i16
.global   mul_i32_i16
.type     mul_i32_i16, %function
.thumb_func

@ int64_t mul_i32_i16 (int32_t, int16_t)

mul_i32_i16:
  asrs r2, r0, 16
  muls r2, r1
  uxth r0, r0
  muls r0, r1
  asrs r3, r0, 31
  asrs r1, r2, 16
  lsls r2, 16
  adds r0, r2
  adcs r1, r3
  bx lr

.size mul_i32_i16, .-mul_i32_i16


.section  .text.mul_u32_u32
.global   mul_u32_u32
.type     mul_u32_u32, %function
.thumb_func

@ uint64_t mul_u32_u32 (uint32_t, uint32_t)

mul_u32_u32:
  mov r12, r4
  uxth r2, r0     @  r2=lo(r0) r2=lo(a)
  lsrs r3, r0, 16 @  r3=hi(r0) r3=hi(a)
  uxth r4, r1     @  r4=lo(r1) r4=lo(b)
  uxth r0, r0     @  r0=lo(r0) r0=lo(a)
  muls r0, r4     @  r0*=r4    r0=lo(a)*lo(b)
  muls r4, r3     @  r4*=r3    r4=hi(a)*lo(b)
  lsrs r1, 16     @  r1=hi(r1) r1=hi(b)
  muls r2, r1     @  r2*=r1    r2=lo(a)*hi(b)
  muls r1, r3     @  r1*=r3    r1=hi(a)*hi(b)
  lsls r3, r4, 16 @  r3=lo(r4) r3=lo(hi(a)*lo(b))
  lsrs r4, 16     @  r4=hi(r4) r4=hi(hi(a)*lo(b))
  adds r0, r3     @  r0+=r3    (r0,r1)
  adcs r1, r4     @  r1+=r4+carry
  lsls r3, r2, 16 @
  lsrs r2, 16
  adds r0, r3
  adcs r1, r2
  mov r4, r12
  bx lr

.size mul_u32_u32, .-mul_u32_u32

.section  .text.mul_i32_i32
.global   mul_i32_i32
.type     mul_i32_i32, %function
.thumb_func

@ int64_t mul_i32_i32 (int32_t, int32_t)

mul_i32_i32:
  mov r12, r4
  uxth r2, r0
  asrs r3, r0, 16
  uxth r4, r1
  uxth r0, r0
  muls r0, r4
  muls r4, r3
  asrs r1, 16
  muls r2, r1
  muls r1, r3
  lsls r3, r4, 16
  asrs r4, 16
  adds r0, r3
  adcs r1, r4
  lsls r3, r2, 16
  asrs r2, 16
  adds r0, r3
  adcs r1, r2
  mov r4, r12
  bx lr

.size mul_i32_i32, .-mul_i32_i32


.section  .text.mul_u32_i32
.global   mul_u32_i32
.type     mul_u32_i32, %function
.thumb_func

@ int64_t mul_u32_i32 (uint32_t, int32_t)

mul_u32_i32:
  mov r12, r4
  uxth r2, r0
  lsrs r3, r0, 16
  uxth r4, r1
  uxth r0, r0
  muls r0, r4
  muls r4, r3
  asrs r1, 16
  muls r2, r1
  muls r1, r3
  lsls r3, r4, 16
  lsrs r4, 16
  adds r0, r3
  adcs r1, r4
  lsls r3, r2, 16
  asrs r2, 16
  adds r0, r3
  adcs r1, r2
  mov r4, r12
  bx lr

.size mul_u32_i32, .-mul_u32_i32


.section  .text.mul_u64_u32
.global   mul_u64_u32
.global   mul_i64_u32
.type     mul_u64_u32, %function
.type     mul_i64_u32, %function
.thumb_func

@ uint64_t mul_u64_u32 (uint64_t, uint32_t)
@  int64_t mul_i64_u32 ( int64_t, uint32_t)

mul_u64_u32:
mul_i64_u32:
  muls r1, r2
  mov r12, r1
  lsrs r1, r2, 16
  uxth r3, r0
  muls r3, r1
  push {r4}
  lsrs r4, r0, 16
  muls r1, r4
  uxth r2, r2
  uxth r0, r0
  muls r0, r2
  muls r2, r4
  lsls r4, r3, 16
  lsrs r3, 16
  adds r0, r4
  pop {r4}
  adcs r1, r3
  lsls r3, r2, 16
  lsrs r2, 16
  adds r0, r3
  adcs r1, r2
  add r1, r12
  bx lr

.size mul_u64_u32, .-mul_u64_u32
.size mul_i64_u32, 0


.section  .text.__aeabi_lmul
.global   mul_u64_i32
.global   mul_i64_i32
.type     mul_u64_i32, %function
.type     mul_i64_i32, %function
.thumb_func

@ int64_t mul_u64_i32 (uint64_t, int32_t)
@ int64_t mul_i64_i32 ( int64_t, int32_t)

mul_u64_i32:
mul_i64_i32:
  asrs r3, r2, 31
  @; fall through to 64x64

.size mul_u64_i32, .-mul_u64_i32
.size mul_i64_i32, 0


.global   __aeabi_lmul
.global   mul_u64_u64
.global   mul_i64_i64
.global   mul_u64_i64
.type     __aeabi_lmul, %function
.type     mul_u64_u64,  %function
.type     mul_i64_i64,  %function
.type     mul_u64_i64,  %function
.thumb_func

@ uint64_t __aeabi_lmul (uint64_t, uint64_t)
@ uint64_t  mul_u64_u64 (uint64_t, uint64_t)
@  int64_t  mul_i64_i64 ( int64_t,  int64_t)
@  int64_t  mul_u64_i64 (uint64_t,  int64_t)

__aeabi_lmul:
mul_u64_u64:
mul_i64_i64:
mul_u64_i64:
  muls r1, r2
  muls r3, r0
  adds r1, r3
  mov r12, r1
  lsrs r1, r2, 16
  uxth r3, r0
  muls r3, r1
  push {r4}
  lsrs r4, r0, 16
  muls r1, r4
  uxth r2, r2
  uxth r0, r0
  muls r0, r2
  muls r2, r4
  lsls r4, r3, 16
  lsrs r3, 16
  adds r0, r4
  pop {r4}
  adcs r1, r3
  lsls r3, r2, 16
  lsrs r2, 16
  adds r0, r3
  adcs r1, r2
  add r1, r12
  bx lr

.size __aeabi_lmul, .-__aeabi_lmul
.size mul_u64_u64, 0
.size mul_i64_i64, 0
.size mul_u64_i64, 0


.section  .text.usqrt
.global   usqrt
.type     usqrt, %function
.thumb_func

@ uint32_t usqrt (uint32_t)

usqrt:
  movs r1, 1
  lsls r1, 30
  movs r2, 0
.Lusqrt_loop:
  adds r3, r2, r1
  lsrs r2, 1
  cmp r0, r3
  bcc .Lusqrt_skip
  subs r0, r3
  adds r2, r1
.Lusqrt_skip:
  lsrs r1, 2
  bne .Lusqrt_loop
  movs r0, r2
  bx lr

.size usqrt, .-usqrt
