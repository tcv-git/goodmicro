// buzzer.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

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

#include "stm32f4xx.h"
#include "stm32f4xx_missing.h"
#include "stm32f4xx_simple_gpio.h"
#include "system_stm32f405-439.h"
#include "buzzer.h"

#define MINIMUM_FREQUENCY  500u
#define MAXIMUM_FREQUENCY 8000u

#if TIM10_CLK > (MINIMUM_FREQUENCY << 17)

#define HALF_PERIOD  ((TIM10_CLK + (MINIMUM_FREQUENCY << 16)) / (MINIMUM_FREQUENCY << 17))
#else
#define HALF_PERIOD  1u
#endif

void buzzer_init(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  (void)RCC->AHB1ENR;

  TIM10->CR1   = 0;
  TIM10->DIER  = 0;
  TIM10->PSC   = 0;
  TIM10->ARR   = ((HALF_PERIOD * 2) - 1);
  TIM10->CCR1  = HALF_PERIOD;
  TIM10->CCMR1 = (TIM_CCMR1_OC1M_FORCE_INACTIVE | TIM_CCMR1_CC1S_OC1);
  TIM10->CCER  = TIM_CCER_CC1E;
  TIM10->CR1   = TIM_CR1_CEN;

  GPIO_alternate_push_pull_medium(GPIOB, PIN8, AF3);
}

void buzzer_sound(unsigned int frequency)
{
  if ((frequency < MINIMUM_FREQUENCY) || (frequency > MAXIMUM_FREQUENCY))
  {
    TIM10->CCMR1 = (TIM_CCMR1_OC1M_FORCE_INACTIVE | TIM_CCMR1_CC1S_OC1);
  }
  else
  {
    unsigned int half_divisor = (frequency * HALF_PERIOD);

    unsigned int prescaler = ((TIM10_CLK + half_divisor) / (half_divisor * 2));

    if (prescaler < 1)
    {
      prescaler = 1;
    }

    if (prescaler > (1u << 16))
    {
      prescaler = (1u << 16);
    }

    TIM10->PSC = (prescaler - 1);
    TIM10->CCMR1 = (TIM_CCMR1_OC1M_PWM_MODE1 | TIM_CCMR1_CC1S_OC1);
  }
}
