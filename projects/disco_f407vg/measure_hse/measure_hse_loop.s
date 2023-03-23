@; measure_hse_loop.s
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

.section  .text.measure_hse_loop

.global   measure_hse_loop
.type     measure_hse_loop, %function
.align 2
.thumb_func

@; unsigned int measure_hse_loop (TIM_TypeDef *tim, unsigned int count)

timer  .req r0
count  .req r1
status .req r2
start  .req r3
end    .req r4

measure_hse_loop:
        push    {r4, lr}               @; make some space
        ldr     status, [timer, 0x00]  @; status    = TIMx_CR1
        orrs    status, 1              @; status   |= TIM_CR1_CEN
        movs    end   , 0              @; end = 0 (used in a bit)
        str     status, [timer, 0x00]  @; TIMx_CR1 = status
1:      ldr     status, [timer, 0x10]  @; status = TIMx_SR
        lsrs    status, 2              @; status >>= 2; APSR.C = (status & TIM_SR_CC1F)
        bcc     1b                     @; if (!APSR.C) goto load TIMx_SR
        str     end   , [timer, 0x10]  @; TIMx_SR = end (zero; clear CC1OF)
        ldr     start , [timer, 0x34]  @; start = TIMx_CC1R
1:      ldr     status, [timer, 0x10]  @; status = TIMx_SR
        lsrs    status, 2              @; status >>= 2; APSR.C = (status & TIM_SR_CC1F)
        bcc     1b                     @; if (!APSR.C) goto load TIMx_SR
        ldr     end   , [timer, 0x34]  @; end = TIMx_CC1R
        subs    count , 1              @; count -= 1
        bne     1b                     @; if (count != 0) goto load TIMx_SR
        ldr     status, [timer, 0x10]  @; status = TIMx_SR
        lsrs    status, 10             @; status >>= 10; APSR.C = (status & TIM_SR_CC1OF)
        ite     cc                     @; if (APSR.C)
        subcc   r0    , end, start     @; then return value = (end - start)
        movcs   r0    , 0              @; else return value = 0
        pop     {r4, pc}               @; return

.size  measure_hse_loop, .-measure_hse_loop
