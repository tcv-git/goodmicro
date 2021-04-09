@; uptime_sysclk.s
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

.syntax   unified
.cpu      cortex-m3
.thumb

.section  .bss.uptime, "aw", %nobits
.align    2

.type     uptime_62_31, %object
.size     uptime_62_31, 4

@ static uint32_t uptime_62_31 = 0;

uptime_62_31:
        .space  4

.section  .text.uptime, "ax", %progbits

.global   uptime_sysclk
.type     uptime_sysclk, %function

@ uint64_t uptime_sysclk (void)

uptime_lo .req r0
uptime_hi .req r1
lo_ptr    .req r2
hi_ptr    .req r3
failure   .req r12

.thumb_func

uptime_sysclk:
        ldr   lo_ptr,    =0xE0001004
        ldr   hi_ptr,    =uptime_62_31
1:      ldr   uptime_lo, [lo_ptr]
        ldrex uptime_hi, [hi_ptr]
        teq   uptime_lo, uptime_hi, lsl 31
        ittt  pl
        lsrpl uptime_hi, 1
        clrexpl
        bxpl  lr
        adds  uptime_hi, 1
        strex failure, uptime_hi, [hi_ptr]
        tst   failure, failure
        bne   1b
        lsrs  uptime_hi, 1
        bx    lr

.size uptime_sysclk, .-uptime_sysclk
