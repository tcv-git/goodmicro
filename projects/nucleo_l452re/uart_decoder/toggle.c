// Toggle button and LED driver
// Copyright Green Energy Options Ltd.

#include <stdint.h>
#include <stdbool.h>
#include "stm32l4xx.h"
#include "stm32l4xx_simple_gpio.h"
#include "toggle.h"

static bool button_state;
static bool toggle_state;

void toggle_init(void)
{
  /*
  PC13 Button B1 active low
  PA5  LED LD2 (green) active high
  */
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN);
  (void)RCC->AHB2ENR;

  GPIO_output_push_pull_slow(GPIOA, PIN5);
  GPIO_input(GPIOC, PIN13);
}

void toggle_poll(void)
{
  bool new_button_state = !(GPIOC->IDR & PIN13);

  if (new_button_state && !button_state)
  {
    toggle_state = !toggle_state;
  }

  button_state = new_button_state;

  GPIO_set_reset(GPIOA, (toggle_state ? PIN5_HI : PIN5_LO));
}

bool toggle_get(void)
{
  return toggle_state;
}
