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
#include "stm32f4xx_simple_gpio.h"


void test_sequence        (uint32_t sysclk_periods, volatile uint32_t *bsrr_ptr, uint32_t bsrr_value1, uint32_t bsrr_value2);
void just_return_sequence (uint32_t sysclk_periods, volatile uint32_t *bsrr_ptr, uint32_t bsrr_value1, uint32_t bsrr_value2);
void nop_sequence         (uint32_t sysclk_periods, volatile uint32_t *bsrr_ptr, uint32_t bsrr_value1, uint32_t bsrr_value2);
void nonop_sequence       (uint32_t sysclk_periods, volatile uint32_t *bsrr_ptr, uint32_t bsrr_value1, uint32_t bsrr_value2);
void nomov_sequence       (uint32_t sysclk_periods, volatile uint32_t *bsrr_ptr, uint32_t bsrr_value1, uint32_t bsrr_value2);

#define REAPEATS_DELAY      1
#define REAPEATS_OTHER  10000


int main(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_vfast(GPIOD, PIN12);

  for (;;)
  {
    unsigned int i;

    for (i = 0; i < REAPEATS_DELAY; i++) {

      test_sequence        (500000, &GPIOD->BSRR, PIN12_HI, PIN12_LO);
    }

    for (i = 0; i < REAPEATS_OTHER; i++) {

      just_return_sequence (0, &GPIOD->BSRR, PIN12_HI, PIN12_LO);
    }

    for (i = 0; i < REAPEATS_OTHER; i++) {

      nop_sequence         (0, &GPIOD->BSRR, PIN12_HI, PIN12_LO);
    }

    for (i = 0; i < REAPEATS_OTHER; i++) {

      nonop_sequence       (0, &GPIOD->BSRR, PIN12_HI, PIN12_LO);
    }

    for (i = 0; i < REAPEATS_OTHER; i++) {

      nomov_sequence       (0, &GPIOD->BSRR, PIN12_HI, PIN12_LO);
    }
  }
}
