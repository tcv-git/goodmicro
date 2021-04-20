#! /bin/bash -eu

# stm32cube-correct-tabs.sh
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


# script to correct the mixed-size tabs in source imported from STM32Cube


expand_t2(){
  for f in "$@"
  do
    expand -t2 <"$f" >tmp && cat <tmp >"$f"
  done
}
expand_t4(){
  for f in "$@"
  do
    expand -t4 <"$f" >tmp && cat <tmp >"$f"
  done
}

expand_t8(){
  for f in "$@"
  do
    expand -t8 <"$f" >tmp && cat <tmp >"$f"
  done
}

expand_t2 bsp/STM32746G-Discovery/stm32746g_discovery_lcd.h
expand_t2 bsp/STM32746G-Discovery/stm32746g_discovery_ts.c
expand_t2 bsp/STM32F0xx-Nucleo/stm32f0xx_nucleo.h
expand_t2 bsp/STM32L0xx_Nucleo/stm32l0xx_nucleo.h
expand_t2 lib/Device_STM32F2xx/Include/stm32f205xx.h
expand_t2 lib/Device_STM32F2xx/Include/stm32f207xx.h
expand_t2 lib/Device_STM32F2xx/Include/stm32f215xx.h
expand_t2 lib/Device_STM32F2xx/Include/stm32f217xx.h
expand_t2 lib/Device_STM32L0xx/Include/stm32l011xx.h
expand_t2 lib/Device_STM32L0xx/Include/stm32l021xx.h
expand_t2 lib/Device_STM32L0xx/Include/stm32l031xx.h
expand_t2 lib/Device_STM32L0xx/Include/stm32l041xx.h
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l051xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l052xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l053xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l062xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l063xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l071xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l072xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l073xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l081xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l082xx.s
expand_t2 lib/Device_STM32L0xx/Source/startup_stm32l083xx.s
expand_t2 lib/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c
expand_t2 lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_utils.c
expand_t2 lib/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc.c
expand_t2 lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
expand_t2 lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
expand_t2 lib/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_adc.h
expand_t2 lib/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_pwr.h
expand_t2 lib/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_pwr_ex.h
expand_t2 lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.c
expand_t2 lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c
expand_t2 lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mmc.c
expand_t2 lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c
expand_t2 lib/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_eth.h
expand_t2 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth.c
expand_t2 lib/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_dac_ex.c
expand_t2 lib/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_firewall.c
expand_t2 projects/disco_f746ng/.template/system_stm32f7xx.c
expand_t2 projects/nucleo_l073rz/.template/startup_stm32l073xx.s
expand_t2 projects/nucleo_l073rz/.template/syscalls.c

expand_t4 bsp/STM32746G-Discovery/stm32746g_discovery.c
expand_t4 bsp/STM32746G-Discovery/stm32746g_discovery.h
expand_t4 bsp/STM32F2xx_Nucleo_144/stm32f2xx_nucleo_144.c
expand_t4 bsp/STM32F4-Discovery/stm32f4_discovery_audio.c
expand_t4 bsp/STM32F429I-Discovery/stm32f429i_discovery_lcd.c
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f401xc.s
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f401xe.s
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f411xe.s
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f427xx.s
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f429xx.s
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f437xx.s
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f439xx.s
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f469xx.s
expand_t4 lib/Device_STM32F4xx/Source/startup_stm32f479xx.s
expand_t4 lib/Device_STM32F7xx/Include/stm32f765xx.h
expand_t4 lib/Device_STM32F7xx/Include/stm32f767xx.h
expand_t4 lib/Device_STM32F7xx/Include/stm32f769xx.h
expand_t4 lib/Device_STM32F7xx/Include/stm32f777xx.h
expand_t4 lib/Device_STM32F7xx/Include/stm32f779xx.h
expand_t4 lib/Device_STM32H7xx/Source/system_stm32h7xx.c
expand_t4 lib/Device_STM32H7xx/Source/system_stm32h7xx_dualcore_boot_cm4_cm7.c
expand_t4 lib/Device_STM32H7xx/Source/system_stm32h7xx_dualcore_bootcm4_cm7gated.c
expand_t4 lib/Device_STM32H7xx/Source/system_stm32h7xx_dualcore_bootcm7_cm4gated.c
expand_t4 lib/Device_STM32H7xx/Source/system_stm32h7xx_singlecore.c
expand_t4 lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cec.c
expand_t4 lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
expand_t4 lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_mmc.c
expand_t4 lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_smartcard.c
expand_t4 lib/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_mmc.c
expand_t4 lib/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_smartcard.c
expand_t4 lib/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_adc.h
expand_t4 lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_mmc.c
expand_t4 lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.c
expand_t4 lib/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_gpio_ex.h
expand_t4 lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c
expand_t4 lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_nand.c
expand_t4 lib/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_adc.h
expand_t4 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc.c
expand_t4 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_comp.c
expand_t4 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cryp.c
expand_t4 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c
expand_t4 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c
expand_t4 lib/STM32L0xx_HAL_Driver/Src/stm32l0xx_hal_lcd.c
expand_t4 projects/disco_f429zi/.template/startup_stm32f429xx.s
expand_t4 projects/disco_f746ng/.template/startup_stm32f746xx.s
expand_t4 projects/eval_f429ni/.template/startup_stm32f429xx.s
expand_t4 projects/eval_f429ni/.template/startup_stm32f439xx.s
expand_t4 projects/nucleo_f070rb/.template/STM32F070RBTx_FLASH.ld
expand_t4 projects/nucleo_f401re/.template/startup_stm32f401xe.s

expand_t8 lib/STM32F2xx_HAL_Driver/Inc/stm32f2xx_hal_rcc_ex.h
expand_t8 lib/STM32F7xx_HAL_Driver/Inc/stm32f7xx_hal_mdios.h
expand_t8 lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_mdios.c
expand_t8 lib/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_mdios.h
expand_t8 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_otfdec.c
expand_t8 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
expand_t8 lib/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c

rm tmp
