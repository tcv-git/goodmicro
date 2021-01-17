
#include "stm32f4xx_simple_gpio.h"
#include "delay.h"

#define GREEN_ON   PIN12_HI
#define GREEN_OFF  PIN12_LO
#define ORANGE_ON  PIN13_HI
#define ORANGE_OFF PIN13_LO
#define RED_ON     PIN14_HI
#define RED_OFF    PIN14_LO
#define BLUE_ON    PIN15_HI
#define BLUE_OFF   PIN15_LO

int main(void)
{
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN);
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_slow(GPIOD, (PIN12 | PIN13 | PIN14 | PIN15));
  GPIO_input(GPIOA, PIN0);

  for (;;)
  {
    GPIO_set_reset(GPIOD, (GREEN_ON | RED_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOD, (BLUE_ON | ORANGE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOD, (RED_ON | GREEN_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOD, (ORANGE_ON | BLUE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
  }
}