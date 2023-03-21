// eval_f429ni_sdram.c
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

// set up external SDRAM for STM32429I-EVAL board

#include "stm32f4xx.h"
#include "delay.h"

// this function is to be called from assembler so it has no header:
void extram_init (void);

void extram_init (void)
{
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOHEN | RCC_AHB1ENR_GPIOIEN);
  RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
  (void)RCC->AHB3ENR;

  GPIOD->OSPEEDR = ((GPIOD->OSPEEDR & ~0xF03F000Fu) | 0xA02A000Au);
  GPIOE->OSPEEDR = ((GPIOE->OSPEEDR & ~0xFFFFC00Fu) | 0xAAAA800Au);
  GPIOF->OSPEEDR = ((GPIOF->OSPEEDR & ~0xFFC00FFFu) | 0xAA800AAAu);
  GPIOG->OSPEEDR = ((GPIOG->OSPEEDR & ~0xC0030F0Fu) | 0x80020A0Au);
  GPIOH->OSPEEDR = ((GPIOH->OSPEEDR & ~0xFFFF0CF0u) | 0xAAAA08A0u);
  GPIOI->OSPEEDR = ((GPIOI->OSPEEDR & ~0x003CFFFFu) | 0x0028AAAAu);

  GPIOD->PUPDR  &= ~0xF03F000Fu;
  GPIOE->PUPDR  &= ~0xFFFFC00Fu;
  GPIOF->PUPDR  &= ~0xFFC00FFFu;
  GPIOG->PUPDR  &= ~0xC0030F0Fu;
  GPIOH->PUPDR  &= ~0xFFFF0CF0u;
  GPIOI->PUPDR  &= ~0x003CFFFFu;

  GPIOD->OTYPER &= ~0xC703u;
  GPIOE->OTYPER &= ~0xFF83u;
  GPIOF->OTYPER &= ~0xF83Fu;
  GPIOG->OTYPER &= ~0x8133u;
  GPIOH->OTYPER &= ~0xFF2Cu;
  GPIOI->OTYPER &= ~0x06FFu;

  GPIOD->AFR[0]  = ((GPIOD->AFR[0]  & ~0x000000FFu) | 0x000000CCu);
  GPIOE->AFR[0]  = ((GPIOE->AFR[0]  & ~0xF00000FFu) | 0xC00000CCu);
  GPIOF->AFR[0]  = ((GPIOF->AFR[0]  & ~0x00FFFFFFu) | 0x00CCCCCCu);
  GPIOG->AFR[0]  = ((GPIOG->AFR[0]  & ~0x00FF00FFu) | 0x00CC00CCu);
  GPIOH->AFR[0]  = ((GPIOH->AFR[0]  & ~0x00F0FF00u) | 0x00C0CC00u);
  GPIOI->AFR[0]  = ((GPIOI->AFR[0]  & ~0xFFFFFFFFu) | 0xCCCCCCCCu);

  GPIOD->AFR[1]  = ((GPIOD->AFR[1]  & ~0xFF000FFFu) | 0xCC000CCCu);
  GPIOE->AFR[1]  = ((GPIOE->AFR[1]  & ~0xFFFFFFFFu) | 0xCCCCCCCCu);
  GPIOF->AFR[1]  = ((GPIOF->AFR[1]  & ~0xFFFFF000u) | 0xCCCCC000u);
  GPIOG->AFR[1]  = ((GPIOG->AFR[1]  & ~0xF000000Fu) | 0xC000000Cu);
  GPIOH->AFR[1]  = ((GPIOH->AFR[1]  & ~0xFFFFFFFFu) | 0xCCCCCCCCu);
  GPIOI->AFR[1]  = ((GPIOI->AFR[1]  & ~0x00000FF0u) | 0x00000CC0u);

  GPIOD->MODER   = ((GPIOD->MODER   & ~0xF03F000Fu) | 0xA02A000Au);
  GPIOE->MODER   = ((GPIOE->MODER   & ~0xFFFFC00Fu) | 0xAAAA800Au);
  GPIOF->MODER   = ((GPIOF->MODER   & ~0xFFC00FFFu) | 0xAA800AAAu);
  GPIOG->MODER   = ((GPIOG->MODER   & ~0xC0030F0Fu) | 0x80020A0Au);
  GPIOH->MODER   = ((GPIOH->MODER   & ~0xFFFF0CF0u) | 0xAAAA08A0u);
  GPIOI->MODER   = ((GPIOI->MODER   & ~0x003CFFFFu) | 0x0028AAAAu);

  FMC_Bank5_6->SDCR[0] = ((0 << 13)     // RPIPE extra delay 0
                        | (1 << 12)     // enable read burst
                        | (2 << 10)     // CLK=HCLK/2
                        | (0 <<  9)     // write protect off
                        | (2 <<  7)     // CAS 2
                        | (1 <<  6)     // 4 banks per chip select
                        | (2 <<  4)     // 32 bit data
                        | (1 <<  2)     // 12 bit row address
                        | (1 <<  0));   // 9 bit column address

  FMC_Bank5_6->SDTR[0] = ((1 << 24)     // tRCD     = 2 CLK @ 90MHz = 22ns >= 18ns
                        | (1 << 20)     // tRP      = 2 CLK @ 90MHz = 22ns >= 18ns
                        | (1 << 16)     // tWR/tDPL = 2 CLK @ 90MHz = 22ns >= 12ns
                        | (5 << 12)     // tRC      = 6 CLK @ 90MHz = 66ns >= 60ns
                        | (3 <<  8)     // tRAS     = 4 CLK @ 90MHz = 44ns >= 42ns
                        | (6 <<  4)     // tXSR     = 7 CLK @ 90MHz = 77ns >= 70ns
                        | (1 <<  0));   // tMRD     = 2 CLK @ 90MHz = 22ns >= 12ns

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  FMC_Bank5_6->SDCMR = (FMC_SDCMR_CTB1 | 1); // bank 1, mode 1 = enable clock

  DELAY_US(100);

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  FMC_Bank5_6->SDCMR = (FMC_SDCMR_CTB1 | 2); // bank 1, mode 2 = precharge all

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  FMC_Bank5_6->SDCMR = (((2 - 1) << 5) | FMC_SDCMR_CTB1 | 3); // bank 1, mode 3 = auto refresh, two times

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  // 0x220 = write burst disabled, CAS=2, sequential burst, read burst length 1
  FMC_Bank5_6->SDCMR = ((0x220 << 9) | FMC_SDCMR_CTB1 | 4); // bank 1, mode 4 = load mode register

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  FMC_Bank5_6->SDRTR = (1386 << 1); // 1386 CLK = 15.4us @ 90MHz; x 4096 rows = 63.08 ms

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);
}
