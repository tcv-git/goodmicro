// system_stm32h7xx_nucleo_h743zi2.c
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

/*
The STM32Cube template project startup does:

  Reset_Handler:
    set stack pointer
    ExitRun0Mode:
      enable LDO
      wait until ACTVOSRDY
    SystemInit:
      enable FPU
      set default flash latency
      system and bus clock sources to default
      if stm32h7 revY then change the switch matrix read issuing capability to 1 for the AXI SRAM target
      enable D2 SRAM
      disable FMC bank 1
      set vector address to constant
    fill bss
    copy data
    __libc_init_array:
      call constructors
    main:
      MPU_Config:
        setup MPU
      CPU_CACHE_Enable:
        enable I cache
        enable D cache
      HAL_Init:
        set priority grouping
        update SystemCoreClock variable, bus clock global variables
        init systick (inc set priority)
        HAL_MspInit:
          (weak empty function)
      SystemClock_Config:
        setup regulators
        setup oscilators and PLL
        setup bus dividers, system clock source, flash wait states
        (commented out:) enable IO compensation cell
      MX_GPIO_Init:
        enable GPIO clocks

This project uses this arrangement:

  Reset_Handler:
    enable ldo and wait until ready
    fill bss
    copy data
    SystemInit:
      system clock source to default
      setup oscilators and PLLs
      enable regulator scale 0 overdrive
      set bus dividers
      set dedicated clock sources
      set flash wait states
      system clock from PLL
      enable systick counter without interrupt
      enable debug cycle counter
      set vector address using symbol
      enable fault interrupts
      enable FPU
      enable I cache
      enable D cache
      enable IO compensation cell
    main:
      set priority grouping
      enable systick interrupt if required
*/

#include <stdint.h>
#include "stm32h7xx.h"
#include "system_stm32h7xx.h"


// crystal/clock input frequency in Hz:
#define HSE_VALUE      (8u * 1000 * 1000)

// PLL parameters:
#define PLL1_RGE        1
#define PLL1_VCOSEL     0
#define PLL1_M          2
#define PLL1_N        240
#define PLL1_FRACN      0
#define PLL1_P          2  // core
#define PLL1_Q          4  // RNG, SPI1,2,3
#define PLL1_R         16  // trace
#define PLL1_P_EN       1
#define PLL1_Q_EN       1
#define PLL1_R_EN       0

#define PLL2_RGE        1
#define PLL2_VCOSEL     0
#define PLL2_M          2
#define PLL2_N        240
#define PLL2_FRACN      0
#define PLL2_P         10  // ADC
#define PLL2_Q          8  // FDCAN
#define PLL2_R          4  // SDMMC, QSPI, SPDIF
#define PLL2_P_EN       0
#define PLL2_Q_EN       0
#define PLL2_R_EN       0

#define PLL3_RGE        1
#define PLL3_VCOSEL     0
#define PLL3_M          2
#define PLL3_N        240
#define PLL3_FRACN      0
#define PLL3_P          6  // SAI
#define PLL3_Q          8  // nothing
#define PLL3_R          8  // LTDC
#define PLL3_P_EN       0
#define PLL3_Q_EN       0
#define PLL3_R_EN       0

#define RCC_D1CFGR_D1CPRE_Value   RCC_D1CFGR_D1CPRE_DIV1  // core
#define RCC_D1CFGR_HPRE_Value     RCC_D1CFGR_HPRE_DIV2    // AXI and AHB buses
#define RCC_D1CFGR_D1PPRE_Value   RCC_D1CFGR_D1PPRE_DIV1  // (APB3) WWDG, LTDC
#define RCC_D2CFGR_D2PPRE1_Value  RCC_D2CFGR_D2PPRE1_DIV2 // (APB1) CEC, CRS, DAC, FDCAN, I2C1,2,3, LPTIM1, MDIO, OPAMP, SPDIF, SPI2,3, SWP, TIM2-7,12-14, UART3,4,5,7,8
#define RCC_D2CFGR_D2PPRE2_Value  RCC_D2CFGR_D2PPRE2_DIV2 // (APB2) DFSDM, HRTIM, SAI123, SPI1,4,5, TIM1,8,15-16, USART1,6
#define RCC_D3CFGR_D3PPRE_Value   RCC_D3CFGR_D3PPRE_DIV4  // (APB4) SAI4, RTC, VREF, COMP1,2, LPTIM2,3,4,5, I2C4, SPI6, LPUART1, SYSCFG

#define RCC_D1CCIPR_CKPERSEL_Value      2  // HSE -> per_ck
#define RCC_D1CCIPR_SDMMCSEL_Value      1  // PLL2_R
#define RCC_D1CCIPR_QSPISEL_Value       2  // PLL2_R
#define RCC_D1CCIPR_FMCSEL_Value        0  // HCLK

#define RCC_D2CCIP1R_SWPSEL_Value       0  // APB1CLK
#define RCC_D2CCIP1R_FDCANSEL_Value     2  // PLL2_Q
#define RCC_D2CCIP1R_DFSDM1SEL_Value    0  // APB2CLK
#define RCC_D2CCIP1R_SPDIFSEL_Value     1  // PLL2_R
#define RCC_D2CCIP1R_SPI45SEL_Value     0  // APB2CLK
#define RCC_D2CCIP1R_SPI123SEL_Value    0  // PLL1_Q
#define RCC_D2CCIP1R_SAI23SEL_Value     2  // PLL3_P
#define RCC_D2CCIP1R_SAI1SEL_Value      2  // PLL3_P

#define RCC_D2CCIP2R_LPTIM1SEL_Value    0  // APB1CLK
#define RCC_D2CCIP2R_CECSEL_Value       0  // LSE
#define RCC_D2CCIP2R_USBSEL_Value       0  // disabled
#define RCC_D2CCIP2R_I2C123SEL_Value    0  // APB1CLK
#define RCC_D2CCIP2R_RNGSEL_Value       1  // PLL1_Q
#define RCC_D2CCIP2R_USART16SEL_Value   0  // APB2CLK
#define RCC_D2CCIP2R_USART28SEL_Value   0  // APB1CLK

#define RCC_D3CCIPR_SPI6SEL_Value       0  // APB4
#define RCC_D3CCIPR_SAI4BSEL_Value      2  // PLL3_P
#define RCC_D3CCIPR_SAI4ASEL_Value      2  // PLL3_P
#define RCC_D3CCIPR_ADCSEL_Value        0  // PLL2_P
#define RCC_D3CCIPR_LPTIM345SEL_Value   0  // APB4
#define RCC_D3CCIPR_LPTIM2SEL_Value     0  // APB4
#define RCC_D3CCIPR_I2C4SEL_Value       0  // APB4
#define RCC_D3CCIPR_LPUART1SEL_Value    0  // APB4

#define RCC_CFGR_TIMPRE_Value           RCC_CFGR_TIMPRE   // TIMx at maximum speed
#define RCC_CFGR_HRTIMSEL_Value         RCC_CFGR_HRTIMSEL // HRTIM at core speed

#define FLASH_ACR_WRHIGHFREQ_Value      FLASH_ACR_WRHIGHFREQ_1
#define FLASH_ACR_LATENCY_Value         FLASH_ACR_LATENCY_4WS


/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (480u * 1000 * 1000);

/* System interrupt vector
 */
extern uint32_t g_pfnVectors[];


/* System initialization
 */
void SystemInit(void)
{
  // disable clock interrupts
  RCC->CIER = 0;

  // HSI on
  RCC->CR |= RCC_CR_HSION;

  // wait until HSI ready
  while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

  // SYSCLK from HSI
  RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_HSI);

  // wait until SYSCLK from HSI
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);

  // PLLs and CSS off
  RCC->CR &= ~(RCC_CR_PLL1ON | RCC_CR_PLL2ON | RCC_CR_PLL3ON | RCC_CR_CSSHSEON);

  // wait until PLLs stopped
  while ((RCC->CR & (RCC_CR_PLL1RDY | RCC_CR_PLL2RDY | RCC_CR_PLL3RDY)) != 0);

  // HSE, CSI and HSI48 off
  RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSION | RCC_CR_HSI48ON);

  // wait until HSE, CSI and HSI48 stopped
  while ((RCC->CR & (RCC_CR_HSERDY | RCC_CR_CSIRDY | RCC_CR_HSI48RDY)) != 0);

  // HSE on with bypass, keep HSI on
  RCC->CR = (RCC_CR_HSION | RCC_CR_HSEON | RCC_CR_HSEBYP);

  // wait until HSE ready
  while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

  // configure PLLs
  RCC->PLLCKSELR = (RCC_PLLCKSELR_PLLSRC_HSE
        | (PLL1_M << RCC_PLLCKSELR_DIVM1_Pos)
        | (PLL2_M << RCC_PLLCKSELR_DIVM2_Pos)
        | (PLL3_M << RCC_PLLCKSELR_DIVM3_Pos));

  RCC->PLL1DIVR = (((PLL1_N - 1) << RCC_PLL1DIVR_N1_Pos)
                 | ((PLL1_P - 1) << RCC_PLL1DIVR_P1_Pos)
                 | ((PLL1_Q - 1) << RCC_PLL1DIVR_Q1_Pos)
                 | ((PLL1_R - 1) << RCC_PLL1DIVR_R1_Pos));

  RCC->PLL2DIVR = (((PLL2_N - 1) << RCC_PLL2DIVR_N2_Pos)
                 | ((PLL2_P - 1) << RCC_PLL2DIVR_P2_Pos)
                 | ((PLL2_Q - 1) << RCC_PLL2DIVR_Q2_Pos)
                 | ((PLL2_R - 1) << RCC_PLL2DIVR_R2_Pos));

  RCC->PLL3DIVR = (((PLL3_N - 1) << RCC_PLL3DIVR_N3_Pos)
                 | ((PLL3_P - 1) << RCC_PLL3DIVR_P3_Pos)
                 | ((PLL3_Q - 1) << RCC_PLL3DIVR_Q3_Pos)
                 | ((PLL3_R - 1) << RCC_PLL3DIVR_R3_Pos));

  RCC->PLL1FRACR = (PLL1_FRACN << RCC_PLL1FRACR_FRACN1_Pos);
  RCC->PLL2FRACR = (PLL2_FRACN << RCC_PLL2FRACR_FRACN2_Pos);
  RCC->PLL3FRACR = (PLL3_FRACN << RCC_PLL3FRACR_FRACN3_Pos);

  RCC->PLLCFGR = ((PLL1_P_EN << RCC_PLLCFGR_DIVP1EN_Pos)
                | (PLL1_Q_EN << RCC_PLLCFGR_DIVQ1EN_Pos)
                | (PLL1_R_EN << RCC_PLLCFGR_DIVR1EN_Pos)
                | (PLL2_P_EN << RCC_PLLCFGR_DIVP2EN_Pos)
                | (PLL2_Q_EN << RCC_PLLCFGR_DIVQ2EN_Pos)
                | (PLL2_R_EN << RCC_PLLCFGR_DIVR2EN_Pos)
                | (PLL3_P_EN << RCC_PLLCFGR_DIVP3EN_Pos)
                | (PLL3_Q_EN << RCC_PLLCFGR_DIVQ3EN_Pos)
                | (PLL3_R_EN << RCC_PLLCFGR_DIVR3EN_Pos)
                | ((PLL1_FRACN != 0) << RCC_PLLCFGR_PLL1FRACEN_Pos)
                | ((PLL2_FRACN != 0) << RCC_PLLCFGR_PLL2FRACEN_Pos)
                | ((PLL3_FRACN != 0) << RCC_PLLCFGR_PLL3FRACEN_Pos)
                | (PLL1_RGE << RCC_PLLCFGR_PLL1RGE_Pos)
                | (PLL2_RGE << RCC_PLLCFGR_PLL2RGE_Pos)
                | (PLL3_RGE << RCC_PLLCFGR_PLL3RGE_Pos)
                | (PLL1_VCOSEL << RCC_PLLCFGR_PLL1RGE_Pos)
                | (PLL2_VCOSEL << RCC_PLLCFGR_PLL2RGE_Pos)
                | (PLL3_VCOSEL << RCC_PLLCFGR_PLL3RGE_Pos));

  unsigned int pll1_on = (PLL1_P_EN || PLL1_Q_EN || PLL1_R_EN);
  unsigned int pll2_on = (PLL2_P_EN || PLL2_Q_EN || PLL2_R_EN);
  unsigned int pll3_on = (PLL3_P_EN || PLL3_Q_EN || PLL3_R_EN);

  // PLLs on, CSS on
  RCC->CR = (RCC_CR_HSION
           | RCC_CR_HSEON
           | RCC_CR_HSEBYP
           | RCC_CR_CSSHSEON
           | (pll1_on << RCC_CR_PLL1ON_Pos)
           | (pll2_on << RCC_CR_PLL2ON_Pos)
           | (pll3_on << RCC_CR_PLL3ON_Pos));

  uint32_t plls_rdy = ((pll1_on << RCC_CR_PLL1RDY_Pos)
                     | (pll2_on << RCC_CR_PLL2RDY_Pos)
                     | (pll3_on << RCC_CR_PLL3RDY_Pos));

  // wait until PLL ready
  while ((RCC->CR & (RCC_CR_PLL1RDY | RCC_CR_PLL2RDY | RCC_CR_PLL3RDY)) != plls_rdy);

  // set VOS scale 1
  PWR->D3CR = PWR_D3CR_VOS;

  // wait until VOS scale 1 ready
  while ((PWR->D3CR & PWR_D3CR_VOSRDY) != PWR_D3CR_VOSRDY);

  // enable system configuration interface
  RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;
  (void)RCC->APB4ENR;

  // enable regulator overdrive
  SYSCFG->PWRCR |= SYSCFG_PWRCR_ODEN;

  // wait until VOS scale 0 ready
  while ((PWR->D3CR & PWR_D3CR_VOSRDY) != PWR_D3CR_VOSRDY);

  // set bus clock dividers
  RCC->D1CFGR = (RCC_D1CFGR_D1CPRE_Value | RCC_D1CFGR_D1PPRE_Value | RCC_D1CFGR_HPRE_Value);
  RCC->D2CFGR = (RCC_D2CFGR_D2PPRE1_Value | RCC_D2CFGR_D2PPRE2_Value);
  RCC->D3CFGR = (RCC_D3CFGR_D3PPRE_Value);

  RCC->D1CCIPR  = ((RCC_D1CCIPR_CKPERSEL_Value    << RCC_D1CCIPR_CKPERSEL_Pos)
                 | (RCC_D1CCIPR_SDMMCSEL_Value    << RCC_D1CCIPR_SDMMCSEL_Pos)
                 | (RCC_D1CCIPR_QSPISEL_Value     << RCC_D1CCIPR_QSPISEL_Pos)
                 | (RCC_D1CCIPR_FMCSEL_Value      << RCC_D1CCIPR_FMCSEL_Pos));

  RCC->D2CCIP1R = ((RCC_D2CCIP1R_SWPSEL_Value     << RCC_D2CCIP1R_SWPSEL_Pos)
                 | (RCC_D2CCIP1R_FDCANSEL_Value   << RCC_D2CCIP1R_FDCANSEL_Pos)
                 | (RCC_D2CCIP1R_DFSDM1SEL_Value  << RCC_D2CCIP1R_DFSDM1SEL_Pos)
                 | (RCC_D2CCIP1R_SPDIFSEL_Value   << RCC_D2CCIP1R_SPDIFSEL_Pos)
                 | (RCC_D2CCIP1R_SPI45SEL_Value   << RCC_D2CCIP1R_SPI45SEL_Pos)
                 | (RCC_D2CCIP1R_SPI123SEL_Value  << RCC_D2CCIP1R_SPI123SEL_Pos)
                 | (RCC_D2CCIP1R_SAI23SEL_Value   << RCC_D2CCIP1R_SAI23SEL_Pos)
                 | (RCC_D2CCIP1R_SAI1SEL_Value    << RCC_D2CCIP1R_SAI1SEL_Pos));

  RCC->D2CCIP2R = ((RCC_D2CCIP2R_LPTIM1SEL_Value  << RCC_D2CCIP2R_LPTIM1SEL_Pos)
                 | (RCC_D2CCIP2R_CECSEL_Value     << RCC_D2CCIP2R_CECSEL_Pos)
                 | (RCC_D2CCIP2R_USBSEL_Value     << RCC_D2CCIP2R_USBSEL_Pos)
                 | (RCC_D2CCIP2R_I2C123SEL_Value  << RCC_D2CCIP2R_I2C123SEL_Pos)
                 | (RCC_D2CCIP2R_RNGSEL_Value     << RCC_D2CCIP2R_RNGSEL_Pos)
                 | (RCC_D2CCIP2R_USART16SEL_Value << RCC_D2CCIP2R_USART16SEL_Pos)
                 | (RCC_D2CCIP2R_USART28SEL_Value << RCC_D2CCIP2R_USART28SEL_Pos));

  RCC->D3CCIPR  = ((RCC_D3CCIPR_SPI6SEL_Value     << RCC_D3CCIPR_SPI6SEL_Pos)
                 | (RCC_D3CCIPR_SAI4BSEL_Value    << RCC_D3CCIPR_SAI4BSEL_Pos)
                 | (RCC_D3CCIPR_SAI4ASEL_Value    << RCC_D3CCIPR_SAI4ASEL_Pos)
                 | (RCC_D3CCIPR_ADCSEL_Value      << RCC_D3CCIPR_ADCSEL_Pos)
                 | (RCC_D3CCIPR_LPTIM345SEL_Value << RCC_D3CCIPR_LPTIM345SEL_Pos)
                 | (RCC_D3CCIPR_LPTIM2SEL_Value   << RCC_D3CCIPR_LPTIM2SEL_Pos)
                 | (RCC_D3CCIPR_I2C4SEL_Value     << RCC_D3CCIPR_I2C4SEL_Pos)
                 | (RCC_D3CCIPR_LPUART1SEL_Value  << RCC_D3CCIPR_LPUART1SEL_Pos));

  // configure flash write timing and wait states
  FLASH->ACR = (FLASH_ACR_WRHIGHFREQ_Value | FLASH_ACR_LATENCY_Value);

  // wait for timings to be applied
  while ((FLASH->ACR & (FLASH_ACR_WRHIGHFREQ | FLASH_ACR_LATENCY)) != (FLASH_ACR_WRHIGHFREQ_Value | FLASH_ACR_LATENCY_Value));

  // default clock outputs, timers run at full speed, SYSCLK from PLL
  RCC->CFGR = (RCC_CFGR_TIMPRE_Value
             | RCC_CFGR_HRTIMSEL_Value
             | ((HSE_VALUE / (1000u * 1000)) << RCC_CFGR_RTCPRE_Pos)
             | RCC_CFGR_SW_PLL1);

  // wait until SYSCLK from PLL
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL1);

  // HSI off
  RCC->CR &= ~RCC_CR_HSION;

  // wait until HSI stopped
  while ((RCC->CR & RCC_CR_HSIRDY) != 0);

  // SysTick on with no interrupt
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
  SysTick->VAL  = 0;
  SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

  // debug cycle counter on
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->LAR          = 0xC5ACCE55u;
  DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT       = 0;

  // set vector address
  SCB->VTOR = (uint32_t)&g_pfnVectors[0];

  // enable faults
  SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk);

  // trap integer divide by zero
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;

  // enable FPU (set CP10 and CP11 full access)
  SCB->CPACR |= ((3u << (10 * 2)) | (3u << (11 * 2)));

  // enable instruction and data cache
  SCB_EnableICache();
  SCB_EnableDCache();

  // CSI on (required by compensation cell)
  RCC->CR |= RCC_CR_CSION;

  // wait until CSI ready
  while ((RCC->CR & RCC_CR_CSIRDY) != RCC_CR_CSIRDY);

  // enable IO compensation cell
  SYSCFG->CCCSR = SYSCFG_CCCSR_EN;

  // wait until IO compensation cell is ready
  while ((SYSCFG->CCCSR & SYSCFG_CCCSR_READY) != SYSCFG_CCCSR_READY);
}
