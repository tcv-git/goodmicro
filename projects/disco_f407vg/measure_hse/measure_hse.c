// measure_hse.c
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
#include "udiv64.h"
#include "measure_hse_loop.h"
#include "measure_hse.h"

#define HSI_VALUE_MIN  14000000u /* datasheet says 16MHz-8.0% but allow -12.5% */
#define HSI_VALUE_MAX  17600000u /* datasheet says 16MHz+4.5% but allow +10.0% */
#define HSE_VALUE_MIN   3998000u /* datasheet says  4MHz-500ppm */
#define HSE_VALUE_MAX  26013000u /* datasheet says 26MHz+500ppm */

unsigned int measure_hse (void)
{
  /* if HSI and HSE not both running */
  if ((RCC->CR & (RCC_CR_HSEON | RCC_CR_HSERDY | RCC_CR_HSION | RCC_CR_HSIRDY))
              != (RCC_CR_HSEON | RCC_CR_HSERDY | RCC_CR_HSION | RCC_CR_HSIRDY))
  {
    return 0;
  }

  /* if not running from HSI */
  if ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI)
  {
    return 0;
  }

  unsigned int hse_rtc_prediv = ((RCC->CFGR & RCC_CFGR_RTCPRE) / RCC_CFGR_RTCPRE_0);

  /* if HSE_RTC not configured */
  if (hse_rtc_prediv < 2)
  {
    return 0;
  }

  unsigned int hse_rtc_cycle_count = ((unsigned int)((0xFFFFuLL * HSE_VALUE_MIN) / HSI_VALUE_MAX) / hse_rtc_prediv);

  RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
  (void)RCC->APB2ENR;

  TIM11->CR1   = 0;
  TIM11->DIER  = 0;
  TIM11->CCMR1 = TIM_CCMR1_CC1S_TI1;
  TIM11->CCER  = TIM_CCER_CC1E;
  TIM11->CNT   = 0;
  TIM11->PSC   = 0;
  TIM11->ARR   = ~0;
  TIM11->OR    = TIM11_OR_TI1_RMP_HSE_RTC;
  TIM11->EGR   = TIM_EGR_UG;

  unsigned int hsi_cycle_count = measure_hse_loop (TIM11, hse_rtc_cycle_count);

  RCC->APB2RSTR |=  RCC_APB2RSTR_TIM11RST;
  (void)RCC->APB2RSTR;
  RCC->APB2ENR  &= ~RCC_APB2ENR_TIM11EN;
  RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM11RST;

  unsigned long long hse_hsi_product = ((unsigned long long)hse_rtc_cycle_count * (hse_rtc_prediv * HSI_VALUE));

  /* overflow (HSE_VALUE > 4.29GHz) */
  if (hsi_cycle_count <= (hse_hsi_product >> 32))
  {
    return 0;
  }

  return udiv64 ((hse_hsi_product + (hsi_cycle_count / 2)), hsi_cycle_count);
}
