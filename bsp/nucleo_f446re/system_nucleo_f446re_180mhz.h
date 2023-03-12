// system_nucleo_f446re_180mhz.h
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

#define HSE_VALUE           (  8u * 1000 * 1000)
#define SYSCLK              (180u * 1000 * 1000)
#define HCLK                SYSCLK
#define APB1_CLK            (HCLK / 4)
#define APB2_CLK            (HCLK / 2)
#define APB1_TIM_CLK        HCLK
#define APB2_TIM_CLK        HCLK
#define TIM1_CLK            APB2_TIM_CLK
#define TIM2_CLK            APB1_TIM_CLK
#define TIM3_CLK            APB1_TIM_CLK
#define TIM4_CLK            APB1_TIM_CLK
#define TIM5_CLK            APB1_TIM_CLK
#define TIM6_CLK            APB1_TIM_CLK
#define TIM7_CLK            APB1_TIM_CLK
#define TIM8_CLK            APB2_TIM_CLK
#define TIM9_CLK            APB2_TIM_CLK
#define TIM10_CLK           APB2_TIM_CLK
#define TIM11_CLK           APB2_TIM_CLK
#define TIM12_CLK           APB1_TIM_CLK
#define TIM13_CLK           APB1_TIM_CLK
#define TIM14_CLK           APB1_TIM_CLK
