/**
  ******************************************************************************
  * @file    stm324x9i_eval_io.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the IO pins
  *          on STM324x9I-EVAL evaluation board.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* File Info : -----------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - This driver is used to drive the IO module of the STM324x9I-EVAL evaluation
     board.
   - The STMPE1600 IO expander device component driver must be included with this
     driver in order to run the IO functionalities commanded by the IO expander
     device mounted on the evaluation board.

2. Driver description:
---------------------
  + Initialization steps:
     o Initialize the IO module using the BSP_IO_Init() function. This
       function includes the MSP layer hardware resources initialization and the
       communication layer configuration to start the IO functionalities use.

  + IO functionalities use
     o The IO pin mode is configured when calling the function BSP_IO_ConfigPin(), you
       must specify the desired IO mode by choosing the "IO_ModeTypedef" parameter
       predefined value.
     o If an IO pin is used in interrupt mode, the function BSP_IO_ITGetStatus() is
       needed to get the interrupt status. To clear the IT pending bits, you should
       call the function BSP_IO_ITClear() with specifying the IO pending bit to clear.
     o The IT is handled using the corresponding external interrupt IRQ handler,
       the user IT callback treatment is implemented on the same external interrupt
       callback.
     o To get/set an IO pin combination state you can use the functions
       BSP_IO_ReadPin()/BSP_IO_WritePin() or the function BSP_IO_TogglePin() to toggle the pin
       state.

------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm324x9i_eval_io.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM324x9I_EVAL
  * @{
  */

/** @defgroup STM324x9I_EVAL_IO STM324x9I EVAL IO
  * @{
  */

/** @defgroup STM324x9I_EVAL_IO_Private_Variables STM324x9I EVAL IO Private Variables
  * @{
  */
static IO_DrvTypeDef *io_driver;
/**
  * @}
  */

/** @defgroup STM324x9I_EVAL_IO_Private_Functions STM324x9I EVAL IO Private Functions
  * @{
  */

/**
  * @brief  Initializes and configures the IO functionalities and configures all
  *         necessary hardware resources (GPIOs, clocks..).
  * @note   BSP_IO_Init() is using HAL_Delay() function to ensure that stmpe1600
  *         IO Expander is correctly reset. HAL_Delay() function provides accurate
  *         delay (in milliseconds) based on variable incremented in SysTick ISR.
  *         This implies that if BSP_IO_Init() is called from a peripheral ISR process,
  *         then the SysTick interrupt must have higher priority (numerically lower)
  *         than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  * @retval IO_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_IO_Init(void)
{
  uint8_t ret = IO_ERROR;

  /* Read ID and verify the IO expander is ready */
  if(stmpe1600_io_drv.ReadID(IO_I2C_ADDRESS) == STMPE1600_ID)
  {
    /* Initialize the IO driver structure */
    io_driver = &stmpe1600_io_drv;
    ret = IO_OK;
  }

  if(ret == IO_OK)
  {
    io_driver->Init(IO_I2C_ADDRESS);
    io_driver->Start(IO_I2C_ADDRESS, IO_PIN_ALL);
  }
  return ret;
}

/**
  * @brief  Gets the selected pins IT status.
  * @param  IO_Pin: Selected pins to check the status.
  *          This parameter can be any combination of the IO pins.
  * @retval IO_OK if read status OK. Other value if error.
  */
uint8_t BSP_IO_ITGetStatus(uint16_t IO_Pin)
{
  /* Return the IO Pin IT status */
  return (io_driver->ITStatus(IO_I2C_ADDRESS, IO_Pin));
}

/**
  * @brief  Clears all the IO IT pending bits.
  */
void BSP_IO_ITClear(void)
{
  /* Clear all IO IT pending bits */
  io_driver->ClearIT(IO_I2C_ADDRESS, STMPE1600_PIN_ALL);
}

/**
  * @brief  Configures the IO pin(s) according to IO mode structure value.
  * @param  IO_Pin: IO pin(s) to be configured.
  *          This parameter can be one of the following values:
  *            @arg  STMPE1600_PIN_x: where x can be from 0 to 15.
  * @param  IO_Mode: IO pin mode to configure
  *          This parameter can be one of the following values:
  *            @arg  IO_MODE_INPUT
  *            @arg  IO_MODE_OUTPUT
  *            @arg  IO_MODE_IT_RISING_EDGE
  *            @arg  IO_MODE_IT_FALLING_EDGE
  * @retval IO_OK if all initializations are OK. Other value if error.
  */
uint8_t BSP_IO_ConfigPin(uint16_t IO_Pin, IO_ModeTypedef IO_Mode)
{
  /* Configure the selected IO pin(s) mode */
  io_driver->Config(IO_I2C_ADDRESS, (uint16_t )IO_Pin, IO_Mode);

  return IO_OK;
}

/**
  * @brief  Sets the selected pins state.
  * @param  IO_Pin: Selected pins to write.
  *          This parameter can be any combination of the IO pins.
  * @param  PinState: New pins state to write
  */
void BSP_IO_WritePin(uint16_t IO_Pin, uint8_t PinState)
{
  /* Set the Pin state */
  io_driver->WritePin(IO_I2C_ADDRESS, IO_Pin, PinState);
}

/**
  * @brief  Gets the selected pins current state.
  * @param  IO_Pin: Selected pins to read.
  *          This parameter can be any combination of the IO pins.
  * @retval The current pins state
  */
uint16_t BSP_IO_ReadPin(uint16_t IO_Pin)
{
 return(io_driver->ReadPin(IO_I2C_ADDRESS, IO_Pin));
}

/**
  * @brief  Toggles the selected pins state.
  * @param  IO_Pin: Selected pins to toggle.
  *          This parameter can be any combination of the IO pins.
  */
void BSP_IO_TogglePin(uint16_t IO_Pin)
{
  /* Toggle the current pin state */
  if(io_driver->ReadPin(IO_I2C_ADDRESS, IO_Pin) == 1) /* Set */
  {
    io_driver->WritePin(IO_I2C_ADDRESS, IO_Pin, 0); /* Reset */
  }
  else
  {
    io_driver->WritePin(IO_I2C_ADDRESS, IO_Pin, 1); /* Set */
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
