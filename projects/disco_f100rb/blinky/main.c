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

#include "stm32vl_discovery.h"

void SysTick_Handler(void);

int main(void)
{
  HAL_Init();

  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_BLUE);

  BSP_LED_On(LED_GREEN);
  BSP_LED_Off(LED_BLUE);

  for(;;)
  {
    if (BSP_PB_GetState(BUTTON_USER))
    {
      HAL_Delay(100);
    }
    else
    {
      HAL_Delay(300);
    }

    BSP_LED_Toggle(LED_GREEN);
    BSP_LED_Toggle(LED_BLUE);
  }
}

void SysTick_Handler(void)
{
  HAL_SYSTICK_IRQHandler();
}

void HAL_SYSTICK_Callback(void)
{
  HAL_IncTick();
}
