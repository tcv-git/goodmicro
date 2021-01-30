// main.c
// PUBLIC DOMAIN
// http:///www.purposeful.co.uk/software/goodmicro

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all copyright and other intellectual property rights
  in them.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  If you use, modify or distribute this software then you do so at your own
  risk.  If you do not pass on this warning then you may be responsible for any
  problems encountered by those who obtain the software through you.
*/

#include <stdint.h>
#include "stm32f4xx.h"
#include "system_stm32f405-439.h"
#include "debug_printf.h"
#include "hwrand.h"

#define CLOCK_RATIO   1000
#define COURSE_CLOCK  (SYSTEM_CORE_CLOCK / CLOCK_RATIO)


uint64_t test_delay_sysclk_long(uint64_t delay, volatile uint32_t *coarse_clock, volatile uint32_t *fine_clock);

void coarse_clock_init(void);
void coarse_clock_init(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
  RCC->APB1ENR;

  TIM5->CR1   = 0;
  TIM5->CR2   = 0;
  TIM5->SMCR  = 0;
  TIM5->DIER  = 0;
  TIM5->CCMR1 = 0;
  TIM5->CCMR2 = 0;
  TIM5->CCER  = 0;
  TIM5->CNT   = 0;
  TIM5->PSC   = ((TIM5_CLK / COURSE_CLOCK) - 1);
  TIM5->ARR   = -1;
  TIM5->OR    = 0;
  TIM5->EGR   = TIM_EGR_UG;
  TIM5->CR1   = TIM_CR1_CEN;
}

static uint64_t time_delay_sysclk_long(uint64_t delay, volatile uint32_t *coarse_clock, volatile uint32_t *fine_clock, uint32_t clock_ratio)
{
  uint64_t packed_result = test_delay_sysclk_long(delay, coarse_clock, fine_clock);

  uint32_t coarse_time = (packed_result & UINT32_MAX);
  uint32_t fine_time = (packed_result >> 32);

  uint64_t coarse_time_fine_units = ((uint64_t)coarse_time * clock_ratio);

  uint64_t absolute_fine_time;

  if (fine_time < (UINT32_MAX / 3))
  {
    absolute_fine_time = ((((coarse_time_fine_units + (1uL << 31)) >> 32) << 32) | fine_time);
  }
  else if (fine_time < ((UINT32_MAX * 2uLL) / 3))
  {
    absolute_fine_time = (((coarse_time_fine_units >> 32) << 32) | fine_time);
  }
  else
  {
    absolute_fine_time = ((((coarse_time_fine_units - (1uL << 31)) >> 32) << 32) | fine_time);
  }

  debug_printf("%15llu %10u %10u %15llu %15llu\n", (unsigned long long int)delay,
                                                   (unsigned int)coarse_time,
                                                   (unsigned int)fine_time,
                                                   (unsigned long long int)coarse_time_fine_units,
                                                   (unsigned long long int)absolute_fine_time);
  return absolute_fine_time;
}

int main (void)
{
  debug_uart_init();

  hwrand_init();

  coarse_clock_init();

  for (;;)
  {
    uint64_t delay = (((uint64_t)hwrand32() << 5) ^ hwrand32());
   // uint64_t delay = ((uint64_t)hwrand32() & 0xFFFF);

    time_delay_sysclk_long(delay, &TIM5->CNT, &DWT->CYCCNT, CLOCK_RATIO);
  }
}
