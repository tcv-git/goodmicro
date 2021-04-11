// disco_f429zi_sdram.c
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

// set up external SDRAM for STM32F429I-Discovery board

#include "stm32f4xx.h"
#include "delay.h"

// this function is to be called from assembler so it has no header:
void extram_init (void);

void extram_init (void)
{
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN);
  RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
  (void)RCC->AHB3ENR;

  GPIOB->OSPEEDR = ((GPIOB->OSPEEDR & ~0x00003C00u) | 0x00002800u);     // PB5      CKE1
  GPIOC->OSPEEDR = ((GPIOC->OSPEEDR & ~0x00000003u) | 0x00000002u);     // PB6      NE1
  GPIOD->OSPEEDR = ((GPIOD->OSPEEDR & ~0xF03F000Fu) | 0xA02A000Au);     // PC0      WE
  GPIOE->OSPEEDR = ((GPIOE->OSPEEDR & ~0xFFFFC00Fu) | 0xAAAA800Au);     // PD0      D2
  GPIOF->OSPEEDR = ((GPIOF->OSPEEDR & ~0xFFC00FFFu) | 0xAA800AAAu);     // PD1      D3
  GPIOG->OSPEEDR = ((GPIOG->OSPEEDR & ~0xC0030F0Fu) | 0x80020A0Au);     // PD8      D13
                                                                        // PD9      D14
  GPIOB->PUPDR &= ~0x00003C00u;                                         // PD10     D15
  GPIOC->PUPDR &= ~0x00000003u;                                         // PD14     D0
  GPIOD->PUPDR &= ~0xF03F000Fu;                                         // PD15     D1
  GPIOE->PUPDR &= ~0xFFFFC00Fu;                                         // PE0      BL0
  GPIOF->PUPDR &= ~0xFFC00FFFu;                                         // PE1      BL1
  GPIOG->PUPDR &= ~0xC0030F0Fu;                                         // PE7      D4
                                                                        // PE8      D5
  GPIOB->OTYPER &= ~0x0060;                                             // PE9      D6
  GPIOC->OTYPER &= ~0x0001;                                             // PE10     D7
  GPIOD->OTYPER &= ~0xC703;                                             // PE11     D8
  GPIOE->OTYPER &= ~0xFF83;                                             // PE12     D9
  GPIOF->OTYPER &= ~0xF83F;                                             // PE13     D10
  GPIOG->OTYPER &= ~0x8133;                                             // PE14     D11
                                                                        // PE15     D12
  GPIOB->AFR[0] = ((GPIOB->AFR[0] & ~0x0FF00000u) | 0x0CC00000u);       // PF0      A0
  GPIOC->AFR[0] = ((GPIOC->AFR[0] & ~0x0000000Fu) | 0x0000000Cu);       // PF1      A1
  GPIOD->AFR[0] = ((GPIOD->AFR[0] & ~0x000000FFu) | 0x000000CCu);       // PF2      A2
  GPIOE->AFR[0] = ((GPIOE->AFR[0] & ~0xF00000FFu) | 0xC00000CCu);       // PF3      A3
  GPIOF->AFR[0] = ((GPIOF->AFR[0] & ~0x00FFFFFFu) | 0x00CCCCCCu);       // PF4      A4
  GPIOG->AFR[0] = ((GPIOG->AFR[0] & ~0x00FF00FFu) | 0x00CC00CCu);       // PF5      A5
                                                                        // PF11     RAS
  GPIOB->AFR[1] = ((GPIOB->AFR[1] & ~0x00000000u) | 0x00000000u);       // PF12     A6
  GPIOC->AFR[1] = ((GPIOC->AFR[1] & ~0x00000000u) | 0x00000000u);       // PF13     A7
  GPIOD->AFR[1] = ((GPIOD->AFR[1] & ~0xFF000FFFu) | 0xCC000CCCu);       // PF14     A8
  GPIOE->AFR[1] = ((GPIOE->AFR[1] & ~0xFFFFFFFFu) | 0xCCCCCCCCu);       // PF15     A9
  GPIOF->AFR[1] = ((GPIOF->AFR[1] & ~0xFFFFF000u) | 0xCCCCC000u);       // PG0      A10
  GPIOG->AFR[1] = ((GPIOG->AFR[1] & ~0xF000000Fu) | 0xC000000Cu);       // PG1      A11
                                                                        // PG4      BA0
  GPIOB->MODER = ((GPIOB->MODER & ~0x00003C00u) | 0x00002800u);         // PG5      BA1
  GPIOC->MODER = ((GPIOC->MODER & ~0x00000003u) | 0x00000002u);         // PG8      CLK
  GPIOD->MODER = ((GPIOD->MODER & ~0xF03F000Fu) | 0xA02A000Au);         // PG15     CAS
  GPIOE->MODER = ((GPIOE->MODER & ~0xFFFFC00Fu) | 0xAAAA800Au);
  GPIOF->MODER = ((GPIOF->MODER & ~0xFFC00FFFu) | 0xAA800AAAu);
  GPIOG->MODER = ((GPIOG->MODER & ~0xC0030F0Fu) | 0x80020A0Au);

  FMC_Bank5_6->SDCR[0] = ((0 << 13)     // RPIPE extra delay 0
                        | (1 << 12)     // enable read burst
                        | (2 << 10)     // CLK=HCLK/2
                        | (1 <<  9)     // write protect on
                        | (2 <<  7)     // CAS 2
                        | (1 <<  6)     // 4 banks per chip select
                        | (1 <<  4)     // 16 bit data
                        | (1 <<  2)     // 12 bit row address
                        | (0 <<  0));   // 8 bit column address

  FMC_Bank5_6->SDCR[1] = ((0 << 13)     // RPIPE extra delay 0
                        | (1 << 12)     // enable read burst
                        | (2 << 10)     // CLK=HCLK/2
                        | (0 <<  9)     // write protect off
                        | (2 <<  7)     // CAS 2
                        | (1 <<  6)     // 4 banks per chip select
                        | (1 <<  4)     // 16 bit data
                        | (1 <<  2)     // 12 bit row address
                        | (0 <<  0));   // 8 bit column address

  FMC_Bank5_6->SDTR[0] = ((1 << 24)     // tRCD     = 2 CLK @ 90MHz = 22ns >= 15ns
                        | (1 << 20)     // tRP      = 2 CLK @ 90MHz = 22ns >= 15ns
                        | (1 << 16)     // tWR/tDPL = 2 CLK (datasheet value in CLK)
                        | (5 << 12)     // tRC      = 6 CLK @ 90MHz = 66ns >= 63ns
                        | (3 <<  8)     // tRAS     = 4 CLK @ 90MHz = 44ns >= 42ns
                        | (6 <<  4)     // tXSR     = 7 CLK @ 90MHz = 77ns >= 70ns
                        | (1 <<  0));   // tMRD     = 2 CLK (datasheet value in CLK)

  FMC_Bank5_6->SDTR[1] = ((1 << 24)     // tRCD     = 2 CLK @ 90MHz = 22ns >= 15ns
                        | (1 << 20)     // tRP      = 2 CLK @ 90MHz = 22ns >= 15ns
                        | (1 << 16)     // tWR/tDPL = 2 CLK (datasheet value in CLK)
                        | (5 << 12)     // tRC      = 6 CLK @ 90MHz = 66ns >= 63ns
                        | (3 <<  8)     // tRAS     = 4 CLK @ 90MHz = 44ns >= 42ns
                        | (6 <<  4)     // tXSR     = 7 CLK @ 90MHz = 77ns >= 70ns
                        | (1 <<  0));   // tMRD     = 2 CLK (datasheet value in CLK)

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  FMC_Bank5_6->SDCMR = (FMC_SDCMR_CTB2 | 1); // bank 2, mode 1 = enable clock

  DELAY_US(100);

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  FMC_Bank5_6->SDCMR = (FMC_SDCMR_CTB2 | 2); // bank 2, mode 2 = precharge all

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  FMC_Bank5_6->SDCMR = (((2 - 1) << 5) | FMC_SDCMR_CTB2 | 3); // bank 2, mode 3 = auto refresh, two times

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  // 0x220 = write burst disabled, CAS=2, sequential burst, read burst length 1
  FMC_Bank5_6->SDCMR = ((0x220 << 9) | FMC_SDCMR_CTB2 | 4); // bank 2, mode 4 = load mode register

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);

  FMC_Bank5_6->SDRTR = (1386 << 1); // 1386 CLK = 15.4us @ 90MHz; x 4096 rows = 63.08 ms

  while ((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) != 0);
}
