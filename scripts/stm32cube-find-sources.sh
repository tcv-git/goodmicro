#! /bin/bash -eu

# stm32cube-find-sources.sh
# PUBLIC DOMAIN
# https://www.purposeful.co.uk/goodmicro/


# I, Tom Vajzovic, am the author of this software and its documentation.
# I permanently abandon all copyright and other intellectual property rights
# in them.
#
# I am fairly certain that the software does what the documentation says it
# does, but I do not guarantee that it does, or that it does what you think it
# should.  I do not guarantee that it will not have undesirable side effects.
#
# If you use, modify or distribute this software then you do so at your own
# risk.  If you do not pass on this warning then you may be responsible for any
# problems encountered by those who obtain the software through you.

lf(){
 find "$@" -type f | sed 's/\/[^\/\.]\+\(\.[^\/]*\)$/\/*\1/' \
   | grep -Fv $'/iar/\n/arm/\n/_htmresc/\n/EWARM/\n/MDK-ARM/\n/*.html\n/*.md\n/*.txt' | sort -u
}

lf STM32CubeF0/Drivers/CMSIS/Device/ST/STM32F0xx
lf STM32CubeF0/Drivers/STM32F0xx_HAL_Driver
lf STM32CubeF0/Drivers/BSP/STM32F0xx-Nucleo
lf STM32CubeF0/Projects/STM32F070RB-Nucleo/Templates

lf STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx
lf STM32CubeF1/Drivers/STM32F1xx_HAL_Driver
lf STM32CubeF1/Drivers/BSP/STM32VL-Discovery
lf STM32CubeF1/Projects/STM32VL-Discovery/Templates

lf STM32CubeF2/Drivers/CMSIS/Device/ST/STM32F2xx
lf STM32CubeF2/Drivers/STM32F2xx_HAL_Driver
lf STM32CubeF2/Drivers/BSP/STM32F2xx_Nucleo_144
lf STM32CubeF2/Projects/NUCLEO-F207ZG/Templates

lf STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx
lf STM32CubeF4/Drivers/STM32F4xx_HAL_Driver
lf STM32CubeF4/Drivers/BSP/STM32F4xx-Nucleo
lf STM32CubeF4/Drivers/BSP/STM32F4-Discovery
lf STM32CubeF4/Drivers/BSP/STM32F429I-Discovery
lf STM32CubeF4/Drivers/BSP/STM324x9I_EVAL
lf STM32CubeF4/Projects/STM32F401RE-Nucleo/Templates
lf STM32CubeF4/Projects/STM32F4-Discovery/Templates
lf STM32CubeF4/Projects/STM32F429I-Discovery/Templates
lf STM32CubeF4/Projects/STM324x9I_EVAL/Templates

lf STM32CubeF7/Drivers/CMSIS/Device/ST/STM32F7xx
lf STM32CubeF7/Drivers/STM32F7xx_HAL_Driver
lf STM32CubeF7/Drivers/BSP/STM32746G-Discovery
lf STM32CubeF7/Projects/STM32746G-Discovery/Templates

lf STM32CubeH7/Drivers/CMSIS/Device/ST/STM32H7xx
lf STM32CubeH7/Drivers/STM32H7xx_HAL_Driver
lf STM32CubeH7/Drivers/BSP/STM32H7xx_Nucleo
lf STM32CubeH7/Projects/NUCLEO-H743ZI/Templates

lf STM32CubeL0/Drivers/CMSIS/Device/ST/STM32L0xx
lf STM32CubeL0/Drivers/STM32L0xx_HAL_Driver
lf STM32CubeL0/Drivers/BSP/STM32L0xx_Nucleo
lf STM32CubeL0/Projects/NUCLEO-L073RZ/Templates
