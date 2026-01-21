// main.c

#include <stdint.h>
#include <stdbool.h>
#include "stm32g4xx.h"
#include "stm32g4xx_simple_gpio.h"
#include "peripheral_enable.h"
#include "delay.h"

static void button_init(void)
{
    peripheral_enable(&RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);

    GPIO_input(GPIOC, PIN13);
}

static bool button_pressed(void)
{
    return ((GPIOC->IDR & PIN13) != 0);
}

static void led_init(void)
{
    peripheral_enable(&RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);

    GPIO_output_push_pull_slow(GPIOA, PIN5);
}

static void led_on(void)
{
    GPIO_set_reset(GPIOA, PIN5_HI);
}

static void led_off(void)
{
      GPIO_set_reset(GPIOA, PIN5_LO);
}

int main(void)
{
    led_init();
    button_init();

    for (;;)
    {
        DELAY_MS(100);
        while (!button_pressed());
        DELAY_MS(100);
        while (button_pressed());

        led_on();

        // trigger lo
        //
        // pwm on

        DELAY_MS(100);
        while (!button_pressed());
        DELAY_MS(100);
        while (button_pressed());

        // pwm off
        //
        // trigger hi

        led_off();
    }
}
