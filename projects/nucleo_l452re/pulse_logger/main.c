// main.c
// https://www.purposeful.co.uk/goodmicro/

#include <stdint.h>
#include <stdbool.h>
#include "stm32l4xx.h"
#include "stm32l4xx_simple_gpio.h"
#include "peripheral_enable.h"
#include "debug_printf.h"

int main(void)
{
  debug_uart_init();

  debug_printf("booted\n");

  peripheral_enable(&RCC->AHB2ENR, (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN));

  peripheral_reset_enable(&RCC->APB1RSTR1, &RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN);

  GPIO_alternate_push_pull_slow(GPIOA, PIN5, AF1);
  GPIO_alternate_push_pull_slow(GPIOB, PIN10, AF1);

  TIM2->CR1 = 0;
  TIM2->CR2 = 0;
  TIM2->SMCR = 0;
  TIM2->DIER = 0;

  // input capture 1 channel 1 positive
  // input capture 2 channel 1 inverse
  // input capture 3 channel 3 positive
  // input capture 4 channel 3 inverse
  TIM2->CCMR1 = (TIM_CCMR1_CC2S_1 | TIM_CCMR1_CC1S_0);
  TIM2->CCMR2 = (TIM_CCMR2_CC4S_1 | TIM_CCMR2_CC3S_0);
  TIM2->CCER = (TIM_CCER_CC4E | TIM_CCER_CC4P | TIM_CCER_CC3E
              | TIM_CCER_CC2E | TIM_CCER_CC2P | TIM_CCER_CC1E);

  TIM2->PSC = ((SystemCoreClock / 1000000) - 1); // 1MHz clock
  TIM2->ARR = UINT32_MAX;
  TIM2->CNT = 0;
  TIM2->EGR = TIM_EGR_UG;
  TIM2->CR1 = TIM_CR1_CEN;

  (void)TIM2->SR;
  TIM2->SR = 0;

  uint32_t wrap_count = 0;

  uint64_t last_time1 = 0;
  uint64_t last_time2 = 0;
  uint64_t last_time3 = 0;
  uint64_t last_time4 = 0;

  for (;;)
  {
    uint32_t flags = TIM2->SR;
    uint32_t capture1;
    uint32_t capture2;
    uint32_t capture3;
    uint32_t capture4;

    if (flags & TIM_SR_CC1IF){ capture1 = TIM2->CCR1; }
    if (flags & TIM_SR_CC2IF){ capture2 = TIM2->CCR2; }
    if (flags & TIM_SR_CC3IF){ capture3 = TIM2->CCR3; }
    if (flags & TIM_SR_CC4IF){ capture4 = TIM2->CCR4; }

    TIM2->SR = ~flags;

    bool wrap_flag = ((flags & TIM_SR_UIF  ) != 0);
    bool flag1     = ((flags & TIM_SR_CC1IF) != 0);
    bool flag2     = ((flags & TIM_SR_CC2IF) != 0);
    bool flag3     = ((flags & TIM_SR_CC3IF) != 0);
    bool flag4     = ((flags & TIM_SR_CC4IF) != 0);
    bool overflow1 = ((flags & TIM_SR_CC1OF) != 0);
    bool overflow2 = ((flags & TIM_SR_CC2OF) != 0);
    bool overflow3 = ((flags & TIM_SR_CC3OF) != 0);
    bool overflow4 = ((flags & TIM_SR_CC4OF) != 0);

    uint64_t time1;
    uint64_t time2;
    uint64_t time3;
    uint64_t time4;

    if (flag1){ time1 = (((uint64_t)wrap_count << 32) + capture1); }
    if (flag2){ time2 = (((uint64_t)wrap_count << 32) + capture2); }
    if (flag3){ time3 = (((uint64_t)wrap_count << 32) + capture3); }
    if (flag4){ time4 = (((uint64_t)wrap_count << 32) + capture4); }

    // if we capture less than half scale, assume we captured after the wrap
    if (wrap_flag && (capture1 < (uint32_t)INT32_MAX)){ time1 += (1uLL << 32); }
    if (wrap_flag && (capture2 < (uint32_t)INT32_MAX)){ time2 += (1uLL << 32); }
    if (wrap_flag && (capture3 < (uint32_t)INT32_MAX)){ time3 += (1uLL << 32); }
    if (wrap_flag && (capture4 < (uint32_t)INT32_MAX)){ time4 += (1uLL << 32); }

    if (wrap_flag){ wrap_count++; }

    if (overflow1){ debug_printf("1: overflow\n"); }
    if (overflow2){ debug_printf("2: overflow\n"); }
    if (overflow3){ debug_printf("3: overflow\n"); }
    if (overflow4){ debug_printf("4: overflow\n"); }

    uint64_t period1;
    uint64_t period2;
    uint64_t period3;
    uint64_t period4;

    if (flag1){ period1 = (time1 - last_time2); }
    if (flag2){ period2 = (time2 - last_time1); }
    if (flag3){ period3 = (time3 - last_time4); }
    if (flag4){ period4 = (time4 - last_time3); }

    if (flag1){ last_time1 = time1; }
    if (flag2){ last_time2 = time2; }
    if (flag3){ last_time3 = time3; }
    if (flag4){ last_time4 = time4; }

    if (flag1){ debug_printf("1: %llu\n", (unsigned long long int)period1); }
    if (flag3){ debug_printf("3: %llu\n", (unsigned long long int)period3); }
  }
}
