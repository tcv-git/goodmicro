#! /bin/bash -eu

# stm32cube-extract.sh
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


# script to extract parts of STM32Cube packages used in goodmicro repository


copyto(){

  dest="$1"
  shift

  mkdir -p "$dest"

  for f in "$@"
  do
    if ! iconv -f UTF-8 -t US-ASCII//TRANSLIT <"$f" >tmp 2>/dev/null
    then
      iconv -f WINDOWS-1252 -t US-ASCII//TRANSLIT <"$f" >tmp
    fi

    tr -d '\r' <tmp | sed 's/\s\+$//' >"$dest"/"$(basename "$f")"
  done
}

copyto lib/Device_STM32F0xx/Include        STM32CubeF0/Drivers/CMSIS/Device/ST/STM32F0xx/Include/*.h
copyto lib/Device_STM32F0xx/Source         STM32CubeF0/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/*.c
copyto lib/Device_STM32F0xx/Source         STM32CubeF0/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/*.s
copyto lib/STM32F0xx_HAL_Driver/Inc        STM32CubeF0/Drivers/STM32F0xx_HAL_Driver/Inc/*.h
copyto lib/STM32F0xx_HAL_Driver/Inc/Legacy STM32CubeF0/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy/*.h
copyto lib/STM32F0xx_HAL_Driver/Src        STM32CubeF0/Drivers/STM32F0xx_HAL_Driver/Src/*.c
copyto lib/STM32F0xx_HAL_Driver/Src/Legacy STM32CubeF0/Drivers/STM32F0xx_HAL_Driver/Src/Legacy/*.c
copyto bsp/STM32F0xx-Nucleo                STM32CubeF0/Drivers/BSP/STM32F0xx-Nucleo/*.c
copyto bsp/STM32F0xx-Nucleo                STM32CubeF0/Drivers/BSP/STM32F0xx-Nucleo/*.h
copyto projects/nucleo_f070rb/.template    STM32CubeF0/Projects/STM32F070RB-Nucleo/Templates/Inc/*.h
copyto projects/nucleo_f070rb/.template    STM32CubeF0/Projects/STM32F070RB-Nucleo/Templates/Src/*.c
copyto projects/nucleo_f070rb/.template    STM32CubeF0/Projects/STM32F070RB-Nucleo/Templates/SW4STM32/*.s
copyto projects/nucleo_f070rb/.template    STM32CubeF0/Projects/STM32F070RB-Nucleo/Templates/SW4STM32/STM32F070RB-Nucleo/*.ld
copyto projects/nucleo_f070rb/.template    STM32CubeF0/Projects/STM32F070RB-Nucleo/Templates/SW4STM32/STM32F070RB-Nucleo/.project
copyto projects/nucleo_f070rb/.template    STM32CubeF0/Projects/STM32F070RB-Nucleo/Templates/SW4STM32/STM32F070RB-Nucleo/.cproject

copyto lib/Device_STM32F1xx/Include        STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Include/*.h
copyto lib/Device_STM32F1xx/Source         STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/*.c
copyto lib/Device_STM32F1xx/Source         STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/*.s
copyto lib/Device_STM32F1xx/Linker         STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/linker/*.ld
copyto lib/STM32F1xx_HAL_Driver/Inc        STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Inc/*.h
copyto lib/STM32F1xx_HAL_Driver/Inc/Legacy STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy/*.h
copyto lib/STM32F1xx_HAL_Driver/Src        STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/*.c
copyto lib/STM32F1xx_HAL_Driver/Src/Legacy STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/Legacy/*.c
copyto bsp/STM32VL-Discovery               STM32CubeF1/Drivers/BSP/STM32VL-Discovery/*.c
copyto bsp/STM32VL-Discovery               STM32CubeF1/Drivers/BSP/STM32VL-Discovery/*.h
copyto projects/disco_f100rb/.template     STM32CubeF1/Projects/STM32VL-Discovery/Templates/Inc/*.h
copyto projects/disco_f100rb/.template     STM32CubeF1/Projects/STM32VL-Discovery/Templates/Src/*.c

copyto lib/Device_STM32F2xx/Include        STM32CubeF2/Drivers/CMSIS/Device/ST/STM32F2xx/Include/*.h
copyto lib/Device_STM32F2xx/Source         STM32CubeF2/Drivers/CMSIS/Device/ST/STM32F2xx/Source/Templates/*.c
copyto lib/Device_STM32F2xx/Source         STM32CubeF2/Drivers/CMSIS/Device/ST/STM32F2xx/Source/Templates/gcc/*.s
copyto lib/STM32F2xx_HAL_Driver/Inc        STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Inc/*.h
copyto lib/STM32F2xx_HAL_Driver/Inc/Legacy STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Inc/Legacy/*.h
copyto lib/STM32F2xx_HAL_Driver/Src        STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/*.c
copyto lib/STM32F2xx_HAL_Driver/Src/Legacy STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/Legacy/*.c
copyto bsp/STM32F2xx_Nucleo_144            STM32CubeF2/Drivers/BSP/STM32F2xx_Nucleo_144/*.c
copyto bsp/STM32F2xx_Nucleo_144            STM32CubeF2/Drivers/BSP/STM32F2xx_Nucleo_144/*.h
copyto projects/nucleo_f207zg/.template    STM32CubeF2/Projects/NUCLEO-F207ZG/Templates/Inc/*.h
copyto projects/nucleo_f207zg/.template    STM32CubeF2/Projects/NUCLEO-F207ZG/Templates/Src/*.c
copyto projects/nucleo_f207zg/.template    STM32CubeF2/Projects/NUCLEO-F207ZG/Templates/SW4STM32/*.s
copyto projects/nucleo_f207zg/.template    STM32CubeF2/Projects/NUCLEO-F207ZG/Templates/SW4STM32/STM32F207xG_Nucleo/*.ld
copyto projects/nucleo_f207zg/.template    STM32CubeF2/Projects/NUCLEO-F207ZG/Templates/SW4STM32/STM32F207xG_Nucleo/.project
copyto projects/nucleo_f207zg/.template    STM32CubeF2/Projects/NUCLEO-F207ZG/Templates/SW4STM32/STM32F207xG_Nucleo/.cproject

copyto lib/Device_STM32F4xx/Include        STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include/*.h
copyto lib/Device_STM32F4xx/Source         STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/*.c
copyto lib/Device_STM32F4xx/Source         STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/*.s
copyto lib/STM32F4xx_HAL_Driver/Inc        STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc/*.h
copyto lib/STM32F4xx_HAL_Driver/Inc/Legacy STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy/*.h
copyto lib/STM32F4xx_HAL_Driver/Src        STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/*.c
copyto lib/STM32F4xx_HAL_Driver/Src/Legacy STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/*.c
copyto bsp/STM32F4xx-Nucleo                STM32CubeF4/Drivers/BSP/STM32F4xx-Nucleo/*.c
copyto bsp/STM32F4xx-Nucleo                STM32CubeF4/Drivers/BSP/STM32F4xx-Nucleo/*.h
copyto bsp/STM32F4-Discovery               STM32CubeF4/Drivers/BSP/STM32F4-Discovery/*.c
copyto bsp/STM32F4-Discovery               STM32CubeF4/Drivers/BSP/STM32F4-Discovery/*.h
copyto bsp/STM32F429I-Discovery            STM32CubeF4/Drivers/BSP/STM32F429I-Discovery/*.c
copyto bsp/STM32F429I-Discovery            STM32CubeF4/Drivers/BSP/STM32F429I-Discovery/*.h
copyto bsp/STM324x9I_EVAL                  STM32CubeF4/Drivers/BSP/STM324x9I_EVAL/*.c
copyto bsp/STM324x9I_EVAL                  STM32CubeF4/Drivers/BSP/STM324x9I_EVAL/*.h
copyto projects/nucleo_f401re/.template    STM32CubeF4/Projects/STM32F401RE-Nucleo/Templates/Inc/*.h
copyto projects/nucleo_f401re/.template    STM32CubeF4/Projects/STM32F401RE-Nucleo/Templates/Src/*.c
copyto projects/nucleo_f401re/.template    STM32CubeF4/Projects/STM32F401RE-Nucleo/Templates/SW4STM32/*.s
copyto projects/nucleo_f401re/.template    STM32CubeF4/Projects/STM32F401RE-Nucleo/Templates/SW4STM32/STM32F4xx-Nucleo/*.ld
copyto projects/nucleo_f401re/.template    STM32CubeF4/Projects/STM32F401RE-Nucleo/Templates/SW4STM32/STM32F4xx-Nucleo/.project
copyto projects/nucleo_f401re/.template    STM32CubeF4/Projects/STM32F401RE-Nucleo/Templates/SW4STM32/STM32F4xx-Nucleo/.cproject
copyto projects/disco_f407vg/.template     STM32CubeF4/Projects/STM32F4-Discovery/Templates/Inc/*.h
copyto projects/disco_f407vg/.template     STM32CubeF4/Projects/STM32F4-Discovery/Templates/Src/*.c
copyto projects/disco_f407vg/.template     STM32CubeF4/Projects/STM32F4-Discovery/Templates/SW4STM32/*.s
copyto projects/disco_f407vg/.template     STM32CubeF4/Projects/STM32F4-Discovery/Templates/SW4STM32/STM32F4-Discovery/*.ld
copyto projects/disco_f407vg/.template     STM32CubeF4/Projects/STM32F4-Discovery/Templates/SW4STM32/STM32F4-Discovery/.project
copyto projects/disco_f407vg/.template     STM32CubeF4/Projects/STM32F4-Discovery/Templates/SW4STM32/STM32F4-Discovery/.cproject
copyto projects/disco_f429zi/.template     STM32CubeF4/Projects/STM32F429I-Discovery/Templates/Inc/*.h
copyto projects/disco_f429zi/.template     STM32CubeF4/Projects/STM32F429I-Discovery/Templates/Src/*.c
copyto projects/disco_f429zi/.template     STM32CubeF4/Projects/STM32F429I-Discovery/Templates/SW4STM32/*.s
copyto projects/disco_f429zi/.template     STM32CubeF4/Projects/STM32F429I-Discovery/Templates/SW4STM32/STM32F429I_DISCO/*.ld
copyto projects/disco_f429zi/.template     STM32CubeF4/Projects/STM32F429I-Discovery/Templates/SW4STM32/STM32F429I_DISCO/.project
copyto projects/disco_f429zi/.template     STM32CubeF4/Projects/STM32F429I-Discovery/Templates/SW4STM32/STM32F429I_DISCO/.cproject
copyto projects/eval_f429ni/.template      STM32CubeF4/Projects/STM324x9I_EVAL/Templates/Inc/*.h
copyto projects/eval_f429ni/.template      STM32CubeF4/Projects/STM324x9I_EVAL/Templates/Src/*.c
copyto projects/eval_f429ni/.template      STM32CubeF4/Projects/STM324x9I_EVAL/Templates/SW4STM32/*.s
copyto projects/eval_f429ni/.template      STM32CubeF4/Projects/STM324x9I_EVAL/Templates/SW4STM32/STM32429I_EVAL/*.ld
copyto projects/eval_f429ni/.template      STM32CubeF4/Projects/STM324x9I_EVAL/Templates/SW4STM32/STM32429I_EVAL/.project
copyto projects/eval_f429ni/.template      STM32CubeF4/Projects/STM324x9I_EVAL/Templates/SW4STM32/STM32429I_EVAL/.cproject

copyto lib/Device_STM32F7xx/Include        STM32CubeF7/Drivers/CMSIS/Device/ST/STM32F7xx/Include/*.h
copyto lib/Device_STM32F7xx/Source         STM32CubeF7/Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/*.c
copyto lib/Device_STM32F7xx/Source         STM32CubeF7/Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/gcc/*.s
copyto lib/STM32F7xx_HAL_Driver/Inc        STM32CubeF7/Drivers/STM32F7xx_HAL_Driver/Inc/*.h
copyto lib/STM32F7xx_HAL_Driver/Inc/Legacy STM32CubeF7/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy/*.h
copyto lib/STM32F7xx_HAL_Driver/Src        STM32CubeF7/Drivers/STM32F7xx_HAL_Driver/Src/*.c
copyto lib/STM32F7xx_HAL_Driver/Src/Legacy STM32CubeF7/Drivers/STM32F7xx_HAL_Driver/Src/Legacy/*.c
copyto bsp/STM32746G-Discovery             STM32CubeF7/Drivers/BSP/STM32746G-Discovery/*.c
copyto bsp/STM32746G-Discovery             STM32CubeF7/Drivers/BSP/STM32746G-Discovery/*.h
copyto projects/disco_f746ng/.template     STM32CubeF7/Projects/STM32746G-Discovery/Templates/Inc/*.h
copyto projects/disco_f746ng/.template     STM32CubeF7/Projects/STM32746G-Discovery/Templates/Src/*.c
copyto projects/disco_f746ng/.template     STM32CubeF7/Projects/STM32746G-Discovery/Templates/SW4STM32/*.s
copyto projects/disco_f746ng/.template     STM32CubeF7/Projects/STM32746G-Discovery/Templates/SW4STM32/STM32746G_Discovery_ITCM-FLASH/*.ld
copyto projects/disco_f746ng/.template     STM32CubeF7/Projects/STM32746G-Discovery/Templates/SW4STM32/STM32746G_Discovery_ITCM-FLASH/.project
copyto projects/disco_f746ng/.template     STM32CubeF7/Projects/STM32746G-Discovery/Templates/SW4STM32/STM32746G_Discovery_ITCM-FLASH/.cproject

copyto lib/Device_STM32H7xx/Include        STM32CubeH7/Drivers/CMSIS/Device/ST/STM32H7xx/Include/*.h
copyto lib/Device_STM32H7xx/Source         STM32CubeH7/Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/*.c
copyto lib/Device_STM32H7xx/Source         STM32CubeH7/Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/*.s
copyto lib/Device_STM32H7xx/Linker         STM32CubeH7/Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/linker/*.ld
copyto lib/STM32H7xx_HAL_Driver/Inc        STM32CubeH7/Drivers/STM32H7xx_HAL_Driver/Inc/*.h
copyto lib/STM32H7xx_HAL_Driver/Inc/Legacy STM32CubeH7/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy/*.h
copyto lib/STM32H7xx_HAL_Driver/Src        STM32CubeH7/Drivers/STM32H7xx_HAL_Driver/Src/*.c
copyto bsp/STM32H7xx_Nucleo                STM32CubeH7/Drivers/BSP/STM32H7xx_Nucleo/*.c
copyto bsp/STM32H7xx_Nucleo                STM32CubeH7/Drivers/BSP/STM32H7xx_Nucleo/*.h
copyto projects/nucleo_h743zi/.template    STM32CubeH7/Projects/NUCLEO-H743ZI/Templates/Inc/*.h
copyto projects/nucleo_h743zi/.template    STM32CubeH7/Projects/NUCLEO-H743ZI/Templates/Src/*.c
copyto projects/nucleo_h743zi/.template    STM32CubeH7/Projects/NUCLEO-H743ZI/Templates/SW4STM32/*.s
copyto projects/nucleo_h743zi/.template    STM32CubeH7/Projects/NUCLEO-H743ZI/Templates/SW4STM32/STM32H743ZI-Nucleo/*.ld
copyto projects/nucleo_h743zi/.template    STM32CubeH7/Projects/NUCLEO-H743ZI/Templates/SW4STM32/STM32H743ZI-Nucleo/.project
copyto projects/nucleo_h743zi/.template    STM32CubeH7/Projects/NUCLEO-H743ZI/Templates/SW4STM32/STM32H743ZI-Nucleo/.cproject

copyto lib/Device_STM32L0xx/Include        STM32CubeL0/Drivers/CMSIS/Device/ST/STM32L0xx/Include/*.h
copyto lib/Device_STM32L0xx/Source         STM32CubeL0/Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/*.c
copyto lib/Device_STM32L0xx/Source         STM32CubeL0/Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/*.s
copyto lib/STM32L0xx_HAL_Driver/Inc        STM32CubeL0/Drivers/STM32L0xx_HAL_Driver/Inc/*.h
copyto lib/STM32L0xx_HAL_Driver/Inc/Legacy STM32CubeL0/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy/*.h
copyto lib/STM32L0xx_HAL_Driver/Src        STM32CubeL0/Drivers/STM32L0xx_HAL_Driver/Src/*.c
copyto bsp/STM32L0xx_Nucleo                STM32CubeL0/Drivers/BSP/STM32L0xx_Nucleo/*.c
copyto bsp/STM32L0xx_Nucleo                STM32CubeL0/Drivers/BSP/STM32L0xx_Nucleo/*.h
copyto projects/nucleo_l073rz/.template    STM32CubeL0/Projects/NUCLEO-L073RZ/Templates/Inc/*.h
copyto projects/nucleo_l073rz/.template    STM32CubeL0/Projects/NUCLEO-L073RZ/Templates/Src/*.c
copyto projects/nucleo_l073rz/.template    STM32CubeL0/Projects/NUCLEO-L073RZ/Templates/SW4STM32/*.c
copyto projects/nucleo_l073rz/.template    STM32CubeL0/Projects/NUCLEO-L073RZ/Templates/SW4STM32/*.s
copyto projects/nucleo_l073rz/.template    STM32CubeL0/Projects/NUCLEO-L073RZ/Templates/SW4STM32/STM32L073RZ_NUCLEO/*.ld
copyto projects/nucleo_l073rz/.template    STM32CubeL0/Projects/NUCLEO-L073RZ/Templates/SW4STM32/STM32L073RZ_NUCLEO/.project
copyto projects/nucleo_l073rz/.template    STM32CubeL0/Projects/NUCLEO-L073RZ/Templates/SW4STM32/STM32L073RZ_NUCLEO/.cproject

copyto lib/Device_STM32L4xx/Include        STM32CubeL4/Drivers/CMSIS/Device/ST/STM32L4xx/Include/*.h
copyto lib/Device_STM32L4xx/Source         STM32CubeL4/Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates/*.c
copyto lib/Device_STM32L4xx/Source         STM32CubeL4/Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates/gcc/*.s
copyto lib/STM32L4xx_HAL_Driver/Inc        STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Inc/*.h
copyto lib/STM32L4xx_HAL_Driver/Inc/Legacy STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/*.h
copyto lib/STM32L4xx_HAL_Driver/Src        STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Src/*.c
copyto lib/STM32L4xx_HAL_Driver/Src/Legacy STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Src/Legacy/*.c
copyto bsp/STM32L4xx-Nucleo                STM32CubeL4/Drivers/BSP/STM32L4xx_Nucleo/*.c
copyto bsp/STM32L4xx-Nucleo                STM32CubeL4/Drivers/BSP/STM32L4xx_Nucleo/*.h
copyto projects/nucleo_l452re/.template    STM32CubeL4/Projects/NUCLEO-L452RE/Templates/Inc/*.h
copyto projects/nucleo_l452re/.template    STM32CubeL4/Projects/NUCLEO-L452RE/Templates/Src/*.c
copyto projects/nucleo_l452re/.template    STM32CubeL4/Projects/NUCLEO-L452RE/Templates/SW4STM32/*.s
copyto projects/nucleo_l452re/.template    STM32CubeL4/Projects/NUCLEO-L452RE/Templates/SW4STM32/STM32L452RE_NUCLEO/*.ld
copyto projects/nucleo_l452re/.template    STM32CubeL4/Projects/NUCLEO-L452RE/Templates/SW4STM32/STM32L452RE_NUCLEO/.project
copyto projects/nucleo_l452re/.template    STM32CubeL4/Projects/NUCLEO-L452RE/Templates/SW4STM32/STM32L452RE_NUCLEO/.cproject

rm tmp
