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

static void trigger_init(void)
{
    peripheral_enable(&RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);

    GPIO_set_reset(GPIOC, PIN9_HI);
    GPIO_output_open_drain_pull_up_slow(GPIOC, PIN9);
}

static void trigger_on(void)
{
    GPIO_set_reset(GPIOC, PIN9_LO);
}

static void trigger_off(void)
{
    GPIO_set_reset(GPIOC, PIN9_HI);
}

static void encoder_init(void)
{
    peripheral_enable(&RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);

    peripheral_reset_enable(&RCC->APB1RSTR1, &RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN);

    GPIO_alternate_open_drain_pull_up_slow(GPIOC, (PIN6 | PIN8), AF2);

    // ch1 is pwm mode 2 centre aligned, threshold to half max
    // ch3 is asymetric pwm mode 2, with threshold above max so always on
    // ch4 is always off (copied to ch3 when counting down)

    TIM3->PSC   = 84;
    TIM3->ARR   = 999;

    TIM3->CCR1  = 500;
    TIM3->CCR3  = 1001;

    TIM3->CCMR1 = (6 << TIM_CCMR1_OC1M_Pos);
    TIM3->CCMR2 = (TIM_CCMR2_OC3M_3 | (6 << TIM_CCMR2_OC3M_Pos) | (4 << TIM_CCMR2_OC4M_Pos));
    TIM3->CCER = (TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E);

    TIM3->EGR = TIM_EGR_UG;
}

static void encoder_on(void)
{
    TIM3->CR1 = (TIM_CR1_CMS | TIM_CR1_CEN);
}

static void encoder_off(void)
{
    TIM3->CR1 = TIM_CR1_CMS;
}

int main(void)
{
    led_init();
    button_init();
    trigger_init();
    encoder_init();

    for (;;)
    {
        DELAY_MS(100);
        while (!button_pressed());
        DELAY_MS(100);
        while (button_pressed());

        led_on();
        trigger_on();
        DELAY_MS(10);
        encoder_on();

        DELAY_MS(100);
        while (!button_pressed());
        DELAY_MS(100);
        while (button_pressed());

        encoder_off();
        DELAY_MS(10);
        trigger_off();

        led_off();
    }
}
