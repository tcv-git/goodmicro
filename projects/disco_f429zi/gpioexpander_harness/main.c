// main.c
// Copyright Green Energy Options Ltd.

#include "stm32f4xx_simple_gpio.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_text.h"

#define PIR_ACTIVE      HI(PIN13)
#define PIR_INACTIVE    LO(PIN13)
#define MINUS_PRESS     LO(PIN11)
#define MINUS_RELEASE   HI(PIN11)
#define PLUS_PRESS      LO(PIN12)
#define PLUS_RELEASE    HI(PIN12)

int main(void)
{
  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  lcd_printf("hello\n");

  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN);
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_slow(GPIOC, (PIN11 | PIN12 | PIN13));
  GPIO_input(GPIOA, PIN0);

  GPIO_set_reset(GPIOC, (PIR_INACTIVE | PLUS_RELEASE | MINUS_RELEASE));

  for (;;)
  {
    while ((GPIOA->IDR & PIN0) == 0);
    DELAY_MS(10);

    lcd_printf("press PC11\n");

    GPIO_set_reset(GPIOC, MINUS_PRESS);
    DELAY_MS(9);
    GPIO_set_reset(GPIOC, MINUS_RELEASE);
    DELAY_MS(9);

    GPIO_set_reset(GPIOC, MINUS_PRESS);
    DELAY_MS(5);
    GPIO_set_reset(GPIOC, PLUS_PRESS);
    DELAY_MS(5);
    GPIO_set_reset(GPIOC, PIR_ACTIVE);

    while ((GPIOA->IDR & PIN0) != 0);
    DELAY_MS(10);

    lcd_printf("release PC11\n");

    GPIO_set_reset(GPIOC, MINUS_RELEASE);
    DELAY_MS(5);
    GPIO_set_reset(GPIOC, PLUS_RELEASE);
    DELAY_MS(5);
    GPIO_set_reset(GPIOC, PIR_INACTIVE);
  }
}
