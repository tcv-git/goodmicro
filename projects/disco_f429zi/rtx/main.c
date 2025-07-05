// main.c
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
#include "stm32f4xx_it.h"
#include "stm32f4xx_simple_gpio.h"
#include "peripheral_enable.h"
#include "delay.h"
#include "cmsis_os2.h"

#define GREEN_ON   PIN13_HI
#define GREEN_OFF  PIN13_LO
#define RED_ON     PIN14_HI
#define RED_OFF    PIN14_LO

static void __NO_RETURN task1(void *argument);
static void __NO_RETURN task2(void *argument);

static osSemaphoreId_t semaphore1;
static osSemaphoreId_t semaphore2;

int main(void)
{
    peripheral_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
    GPIO_output_push_pull_slow(GPIOG, (PIN13 | PIN14));

    osKernelInitialize();

    semaphore1 = osSemaphoreNew(1, 0, NULL);
    semaphore2 = osSemaphoreNew(1, 0, NULL);

    osThreadId_t thread1 = osThreadNew(task1, NULL, NULL);
    osThreadId_t thread2 = osThreadNew(task2, NULL, NULL);

#if 0
    osThreadSetPriority(thread1, osPriorityNormal);
    osThreadSetPriority(thread2, osPriorityAboveNormal);
#endif

    NVIC_EnableIRQ(TIM2_IRQn);

    osKernelStart();
    for (;;);
}

static void __NO_RETURN task1(void *argument)
{
    (void)argument;

    for(;;)
    {
        NVIC_SetPendingIRQ(TIM2_IRQn);
        (void)osSemaphoreAcquire(semaphore1, osWaitForever);
        GPIO_set_reset(GPIOG, GREEN_ON);
    }
}

void TIM2_IRQHandler(void)
{
    (void)osSemaphoreRelease(semaphore2);
}

static void __NO_RETURN task2(void *argument)
{
    (void)argument;

    for (;;)
    {
        (void)osSemaphoreAcquire(semaphore2, osWaitForever);
        GPIO_set_reset(GPIOG, GREEN_OFF);
        (void)osSemaphoreRelease(semaphore1);
    }
}
