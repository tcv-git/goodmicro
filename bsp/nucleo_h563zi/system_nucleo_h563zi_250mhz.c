// system_nucleo_h563zi_250mhz.c
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

#include <stdint.h>
#include "stm32h5xx.h"
#include "system_stm32h5xx.h"

/******************************************************************************/
/*                              IMPORTANT                                     */
/*                                                                            */
/* This configuration assumes a modified board, with SB3 and SB4 closed and   */
/* SB48, SB49 and SB50 open, to connect the on-board 25MHz crystal to HSE.    */
/*                                                                            */
/******************************************************************************/


// PLL parameters:
#define PLL1_SRC        3 // HSE
#define PLL1_RGE        3 // 8-16 MHz
#define PLL1_VCOSEL     0 // 192-836 MHz
#define PLL1_M          2
#define PLL1_N         40
#define PLL1_FRACN      0
#define PLL1_P          2  // core
#define PLL1_Q          2
#define PLL1_R          2
#define PLL1_P_EN       1
#define PLL1_Q_EN       0
#define PLL1_R_EN       0

#define PLL2_SRC        0 // disabled
#define PLL2_RGE        3 // 8-16 MHz
#define PLL2_VCOSEL     0 // 192-836 MHz
#define PLL2_M          0 // disabled
#define PLL2_N         40
#define PLL2_FRACN      0
#define PLL2_P          2
#define PLL2_Q          2
#define PLL2_R          2
#define PLL2_P_EN       0
#define PLL2_Q_EN       0
#define PLL2_R_EN       0

#define PLL3_SRC        0 // disabled
#define PLL3_RGE        3 // 8-16 MHz
#define PLL3_VCOSEL     0 // 192-836 MHz
#define PLL3_M          0 // disabled
#define PLL3_N         40
#define PLL3_FRACN      0
#define PLL3_P          2
#define PLL3_Q          2
#define PLL3_R          2
#define PLL3_P_EN       0
#define PLL3_Q_EN       0
#define PLL3_R_EN       0

// flash timings:
#define FLASH_ACR_LATENCY_Value     FLASH_ACR_LATENCY_5WS
#define FLASH_ACR_WRHIGHFREQ_Value  FLASH_ACR_WRHIGHFREQ_1

/* CMSIS required global variable containing system core speed in Hz.
 */
uint32_t SystemCoreClock = (250u * 1000 * 1000);

/* System interrupt vector
 */
extern uint32_t g_pfnVectors[];


/* System initialization
 */
void SystemInit(void)
{
    // disable clock interrupts
    RCC->CIER = 0;

    // configure flash prefetch, write timing and wait states
    FLASH->ACR = (FLASH_ACR_PRFTEN | FLASH_ACR_WRHIGHFREQ_Value | FLASH_ACR_LATENCY_Value);

    // wait for wait-states to be applied
    while ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_Value);

    // set VOS scale 0 (maximum performance)
    PWR->VOSCR = PWR_VOSCR_VOS;

    // wait until VOS ready
    while ((PWR->VOSSR & PWR_VOSSR_VOSRDY) != PWR_VOSSR_VOSRDY);

    // HSI on
    RCC->CR |= RCC_CR_HSION;

    // wait until HSI ready
    while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

    // MCOs off, HSE to RTC divider off, timers at default speed, SYSCLK from HSI
    RCC->CFGR1 = 0;

    // wait until SYSCLK from HSI
    while ((RCC->CFGR1 & RCC_CFGR1_SWS) != 0);

    // enable all host and peripheral busses at undivided HCLK speed
    RCC->CFGR2 = 0;

    // PLLs and CSS off
    RCC->CR &= ~(RCC_CR_PLL1ON | RCC_CR_PLL2ON | RCC_CR_PLL3ON | RCC_CR_HSECSSON);

    // wait until PLLs stopped
    while ((RCC->CR & (RCC_CR_PLL1RDY | RCC_CR_PLL2RDY | RCC_CR_PLL3RDY)) != 0);

    // HSE, CSI and HSI48 off
    RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSION | RCC_CR_CSIKERON | RCC_CR_HSI48ON);

    // wait until HSE, CSI and HSI48 stopped
    while ((RCC->CR & (RCC_CR_HSERDY | RCC_CR_CSIRDY | RCC_CR_HSI48RDY)) != 0);

    // HSE bypass off
    RCC->CR &= ~(RCC_CR_HSEBYP | RCC_CR_HSEEXT);

    // HSE on
    RCC->CR |= RCC_CR_HSEON;

    // wait until HSE ready
    while ((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

    // configure PLLs
    RCC->PLL1CFGR = ((PLL1_SRC          << RCC_PLL1CFGR_PLL1SRC_Pos)
                   | (PLL1_RGE          << RCC_PLL1CFGR_PLL1RGE_Pos)
                   | (PLL1_VCOSEL       << RCC_PLL1CFGR_PLL1VCOSEL_Pos)
                   | (PLL1_M            << RCC_PLL1CFGR_PLL1M_Pos)
                   | ((PLL1_FRACN != 0) << RCC_PLL1CFGR_PLL1FRACEN_Pos)
                   | (PLL1_P_EN         << RCC_PLL1CFGR_PLL1PEN_Pos)
                   | (PLL1_Q_EN         << RCC_PLL1CFGR_PLL1QEN_Pos)
                   | (PLL1_R_EN         << RCC_PLL1CFGR_PLL1REN_Pos));

    RCC->PLL2CFGR = ((PLL2_SRC          << RCC_PLL2CFGR_PLL2SRC_Pos)
                   | (PLL2_RGE          << RCC_PLL2CFGR_PLL2RGE_Pos)
                   | (PLL2_VCOSEL       << RCC_PLL2CFGR_PLL2VCOSEL_Pos)
                   | (PLL2_M            << RCC_PLL2CFGR_PLL2M_Pos)
                   | ((PLL2_FRACN != 0) << RCC_PLL2CFGR_PLL2FRACEN_Pos)
                   | (PLL2_P_EN         << RCC_PLL2CFGR_PLL2PEN_Pos)
                   | (PLL2_Q_EN         << RCC_PLL2CFGR_PLL2QEN_Pos)
                   | (PLL2_R_EN         << RCC_PLL2CFGR_PLL2REN_Pos));

    RCC->PLL3CFGR = ((PLL3_SRC          << RCC_PLL3CFGR_PLL3SRC_Pos)
                   | (PLL3_RGE          << RCC_PLL3CFGR_PLL3RGE_Pos)
                   | (PLL3_VCOSEL       << RCC_PLL3CFGR_PLL3VCOSEL_Pos)
                   | (PLL3_M            << RCC_PLL3CFGR_PLL3M_Pos)
                   | ((PLL3_FRACN != 0) << RCC_PLL3CFGR_PLL3FRACEN_Pos)
                   | (PLL3_P_EN         << RCC_PLL3CFGR_PLL3PEN_Pos)
                   | (PLL3_Q_EN         << RCC_PLL3CFGR_PLL3QEN_Pos)
                   | (PLL3_R_EN         << RCC_PLL3CFGR_PLL3REN_Pos));

    RCC->PLL1DIVR = (((PLL1_N - 1) << RCC_PLL1DIVR_PLL1N_Pos)
                   | ((PLL1_P - 1) << RCC_PLL1DIVR_PLL1P_Pos)
                   | ((PLL1_Q - 1) << RCC_PLL1DIVR_PLL1Q_Pos)
                   | ((PLL1_R - 1) << RCC_PLL1DIVR_PLL1R_Pos));

    RCC->PLL2DIVR = (((PLL2_N - 1) << RCC_PLL2DIVR_PLL2N_Pos)
                   | ((PLL2_P - 1) << RCC_PLL2DIVR_PLL2P_Pos)
                   | ((PLL2_Q - 1) << RCC_PLL2DIVR_PLL2Q_Pos)
                   | ((PLL2_R - 1) << RCC_PLL2DIVR_PLL2R_Pos));

    RCC->PLL3DIVR = (((PLL3_N - 1) << RCC_PLL3DIVR_PLL3N_Pos)
                   | ((PLL3_P - 1) << RCC_PLL3DIVR_PLL3P_Pos)
                   | ((PLL3_Q - 1) << RCC_PLL3DIVR_PLL3Q_Pos)
                   | ((PLL3_R - 1) << RCC_PLL3DIVR_PLL3R_Pos));

    RCC->PLL1FRACR = (PLL1_FRACN << RCC_PLL1FRACR_PLL1FRACN_Pos);
    RCC->PLL2FRACR = (PLL2_FRACN << RCC_PLL2FRACR_PLL2FRACN_Pos);
    RCC->PLL3FRACR = (PLL3_FRACN << RCC_PLL3FRACR_PLL3FRACN_Pos);

    unsigned int pll1_on = (PLL1_P_EN || PLL1_Q_EN || PLL1_R_EN);
    unsigned int pll2_on = (PLL2_P_EN || PLL2_Q_EN || PLL2_R_EN);
    unsigned int pll3_on = (PLL3_P_EN || PLL3_Q_EN || PLL3_R_EN);

    // PLLs on, CSS on
    RCC->CR |= ((pll1_on << RCC_CR_PLL1ON_Pos)
              | (pll2_on << RCC_CR_PLL2ON_Pos)
              | (pll3_on << RCC_CR_PLL3ON_Pos)
              | RCC_CR_HSECSSON);

    uint32_t plls_rdy = ((pll1_on << RCC_CR_PLL1RDY_Pos)
                       | (pll2_on << RCC_CR_PLL2RDY_Pos)
                       | (pll3_on << RCC_CR_PLL3RDY_Pos));

    // wait until PLLs ready
    while ((RCC->CR & (RCC_CR_PLL1RDY | RCC_CR_PLL2RDY | RCC_CR_PLL3RDY)) != plls_rdy);

    // SYSCLK from PLL1_P
    RCC->CFGR1 = RCC_CFGR1_SW;

    // wait until SYSCLK from PLL
    while ((RCC->CFGR1 & RCC_CFGR1_SWS) != RCC_CFGR1_SWS);

    // HSI off
    RCC->CR &= ~(RCC_CR_HSION | RCC_CR_HSIKERON | RCC_CR_HSIDIV);

    // wait until HSI stopped
    while ((RCC->CR & RCC_CR_HSIRDY) != 0);

    // SysTick on with no interrupt
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
    SysTick->VAL  = 0;
    SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

    // debug cycle counter on
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
#if 0 // FIXME
    DWT->LAR          = 0xC5ACCE55u;
#endif
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

    // enable system config interface
    RCC->APB3ENR |= RCC_APB3ENR_SBSEN;
    (void)RCC->APB3ENR;

    // disable FPU interrupts except invalid operation and divide by zero
    SBS->FPUIMR = (SBS_FPUIMR_FPU_IE_1 | SBS_FPUIMR_FPU_IE_0);

    // CSI on (required by compensation cell)
    RCC->CR |= RCC_CR_CSION;

    // wait until CSI ready
    while ((RCC->CR & RCC_CR_CSIRDY) != RCC_CR_CSIRDY);

    // enable IO compensation cell
    SBS->CCCSR = (SBS_CCCSR_EN1 | SBS_CCCSR_EN2);

    // wait until IO compensation cell is ready
    while ((SBS->CCCSR & (SBS_CCCSR_RDY1 | SBS_CCCSR_RDY2)) != (SBS_CCCSR_RDY1 | SBS_CCCSR_RDY2));

    // enable instruction cache
    ICACHE->CR |= ICACHE_CR_EN;
}
