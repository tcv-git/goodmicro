// lcd.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/software/goodmicro

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
#include "delay.h"
#include "lcd.h"

#define HORIZONTAL_SYNC_WIDTH      10
#define HORIZONTAL_BACK_PORCH      20
#define HORIZONTAL_FRONT_PORCH     10
#define VERTICAL_SYNC_WIDTH         2
#define VERTICAL_BACK_PORCH         2
#define VERTICAL_FRONT_PORCH        4

#define LCD_SLEEP_OUT            0x11   // Sleep out register
#define LCD_GAMMA                0x26   // Gamma register
#define LCD_DISPLAY_OFF          0x28   // Display off register
#define LCD_DISPLAY_ON           0x29   // Display on register
#define LCD_COLUMN_ADDR          0x2A   // Colomn address register
#define LCD_PAGE_ADDR            0x2B   // Page address register
#define LCD_GRAM                 0x2C   // GRAM register
#define LCD_MAC                  0x36   // Memory Access Control register
#define LCD_PIXEL_FORMAT         0x3A   // Pixel Format register
#define LCD_WDB                  0x51   // Write Brightness Display register
#define LCD_WCD                  0x53   // Write Control Display register
#define LCD_RGB_INTERFACE        0xB0   // RGB Interface Signal Control
#define LCD_FRC                  0xB1   // Frame Rate Control register
#define LCD_BPC                  0xB5   // Blanking Porch Control register
#define LCD_DFC                  0xB6   // Display Function Control register
#define LCD_POWER1               0xC0   // Power Control 1 register
#define LCD_POWER2               0xC1   // Power Control 2 register
#define LCD_VCOM1                0xC5   // VCOM Control 1 register
#define LCD_VCOM2                0xC7   // VCOM Control 2 register
#define LCD_POWERA               0xCB   // Power control A register
#define LCD_POWERB               0xCF   // Power control B register
#define LCD_PGAMMA               0xE0   // Positive Gamma Correction register
#define LCD_NGAMMA               0xE1   // Negative Gamma Correction register
#define LCD_DTCA                 0xE8   // Driver timing control A
#define LCD_DTCB                 0xEA   // Driver timing control B
#define LCD_POWER_SEQ            0xED   // Power on sequence register
#define LCD_3GAMMA_EN            0xF2   // 3 Gamma enable register
#define LCD_INTERFACE            0xF6   // Interface control register
#define LCD_PRC                  0xF7   // Pump ratio control register

unsigned int framebuffer [VERTICAL_ACTIVE_HEIGHT][HORIZONTAL_ACTIVE_WIDTH] __attribute__ ((section (".ext_bss")));

static void spi_write (unsigned char byte)
{
  while ((SPI5->SR & SPI_SR_TXE) != SPI_SR_TXE);

  GPIOC->BSRR = (1 << 18); // select

  SPI5->DR = byte;

  while ((SPI5->SR & SPI_SR_TXE) != SPI_SR_TXE);

  while ((SPI5->SR & SPI_SR_BSY) == SPI_SR_BSY);

  GPIOC->BSRR = (1 << 2); // deselect
}

static void LCD_WriteCommand (unsigned char byte)
{
  GPIOD->BSRR = (1 << 29);

  spi_write (byte);
}

static void LCD_WriteData (unsigned char byte)
{
  GPIOD->BSRR = (1 << 13);

  spi_write (byte);
}

void lcd_init (void)
{
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN
                 | RCC_AHB1ENR_GPIOBEN
                 | RCC_AHB1ENR_GPIOCEN
                 | RCC_AHB1ENR_GPIODEN
                 | RCC_AHB1ENR_GPIOFEN
                 | RCC_AHB1ENR_GPIOGEN);
  RCC->APB2ENR |= (RCC_APB2ENR_LTDCEN
                 | RCC_APB2ENR_SPI5EN);
  __DSB ();

/*
PA3     B5      LTDC data
PA4     VSYNC   LTDC sync
PA6     G2      LTDC data
PA11    R4      LTDC data
PA12    R5      LTDC data

PB0     R3      LTDC data
PB1     R6      LTDC data
PB8     B6      LTDC data
PB9     B7      LTDC data
PB10    G4      LTDC data
PB11    G5      LTDC data

PC2     CSX     serial chip select (bit banged)
PC6     HSYNC   LTDC sync
PC7     G6      LTDC data
PC10    R2      LTDC data

PD2     IM0     fixed low in hardware not used by software
PD3     G7      LTDC data
PD4     IM1     fixed high in hardware not used by software
PD5     IM2     fixed high in hardware not used by software
PD6     B2      LTDC data
PD7     IM3     fixed low in hardware not used by software
PD11    TE      tear pulse output not used by software
PD12    RDX     not use must be fixed high by software
PD13    WRX     serial select between command and data (bit banged)

PF7     SCK     serial clock
PF9     MOSI    serial data bi-directional
PF10    DE      LTDC sync

PG6     R7      LTDC data
PG7     DOTCLK  LTDC sync
PG10    G3      LTDC data
PG11    B3      LTDC data
PG12    B4      LTDC data
*/

  GPIOC->BSRR = (1 << 2); // nCS high

  GPIOA->OSPEEDR = ((GPIOA->OSPEEDR & ~0x03C033C0u) | 0x02802280u);
  GPIOB->OSPEEDR = ((GPIOB->OSPEEDR & ~0x00FF000Fu) | 0x00AA000Au);
  GPIOC->OSPEEDR = ((GPIOC->OSPEEDR & ~0x0030F030u) | 0x0020A020u);
  GPIOD->OSPEEDR = ((GPIOD->OSPEEDR & ~0x0FC0FFF0u) | 0x08002080u);
  GPIOF->OSPEEDR = ((GPIOF->OSPEEDR & ~0x003CC000u) | 0x00244000u);
  GPIOG->OSPEEDR = ((GPIOG->OSPEEDR & ~0x03F0F000u) | 0x02A0A000u);

  GPIOA->PUPDR   = ((GPIOA->PUPDR   & ~0x03C033C0u) | 0x00000000u);
  GPIOB->PUPDR   = ((GPIOB->PUPDR   & ~0x00FF000Fu) | 0x00000000u);
  GPIOC->PUPDR   = ((GPIOC->PUPDR   & ~0x0030F030u) | 0x00000000u);
  GPIOD->PUPDR   = ((GPIOD->PUPDR   & ~0x0FC0FFF0u) | 0x01000000u);
  GPIOF->PUPDR   = ((GPIOF->PUPDR   & ~0x003CC000u) | 0x00000000u);
  GPIOG->PUPDR   = ((GPIOG->PUPDR   & ~0x03F0F000u) | 0x00000000u);

  GPIOA->OTYPER  = ((GPIOA->OTYPER  & ~    0x1858u) |     0x0000u);
  GPIOB->OTYPER  = ((GPIOB->OTYPER  & ~    0x0F03u) |     0x0000u);
  GPIOC->OTYPER  = ((GPIOC->OTYPER  & ~    0x04C4u) |     0x0000u);
  GPIOD->OTYPER  = ((GPIOD->OTYPER  & ~    0x38FCu) |     0x0000u);
  GPIOF->OTYPER  = ((GPIOF->OTYPER  & ~    0x0680u) |     0x0000u);
  GPIOG->OTYPER  = ((GPIOG->OTYPER  & ~    0x1CC0u) |     0x0000u);

  GPIOA->AFR[0]  = ((GPIOA->AFR[0]  & ~0x0F0FF000u) | 0x0E0EE000u);
  GPIOB->AFR[0]  = ((GPIOB->AFR[0]  & ~0x000000FFu) | 0x00000099u);
  GPIOC->AFR[0]  = ((GPIOC->AFR[0]  & ~0xFF000F00u) | 0xEE000000u);
  GPIOD->AFR[0]  = ((GPIOD->AFR[0]  & ~0xFFFFFF00u) | 0x0E00E000u);
  GPIOF->AFR[0]  = ((GPIOF->AFR[0]  & ~0xF0000000u) | 0x50000000u);
  GPIOG->AFR[0]  = ((GPIOG->AFR[0]  & ~0xFF000000u) | 0xEE000000u);

  GPIOA->AFR[1]  = ((GPIOA->AFR[1]  & ~0x000FF000u) | 0x000EE000u);
  GPIOB->AFR[1]  = ((GPIOB->AFR[1]  & ~0x0000FFFFu) | 0x0000EEEEu);
  GPIOC->AFR[1]  = ((GPIOC->AFR[1]  & ~0x00000F00u) | 0x00000E00u);
  GPIOD->AFR[1]  = ((GPIOD->AFR[1]  & ~0x00FFF000u) | 0x00000000u);
  GPIOF->AFR[1]  = ((GPIOF->AFR[1]  & ~0x00000FF0u) | 0x00000E50u);
  GPIOG->AFR[1]  = ((GPIOG->AFR[1]  & ~0x000FFF00u) | 0x000EEE00u);

  GPIOA->MODER   = ((GPIOA->MODER   & ~0x03C033C0u) | 0x02802280u);
  GPIOB->MODER   = ((GPIOB->MODER   & ~0x00FF000Fu) | 0x00AA000Au);
  GPIOC->MODER   = ((GPIOC->MODER   & ~0x0030F030u) | 0x0020A010u);
  GPIOD->MODER   = ((GPIOD->MODER   & ~0x0FC0FFF0u) | 0x04C0EFB0u);
  GPIOF->MODER   = ((GPIOF->MODER   & ~0x003CC000u) | 0x00288000u);
  GPIOG->MODER   = ((GPIOG->MODER   & ~0x03F0F000u) | 0x02A0A000u);

  // SPI (90MHz/16) = 5.625MHz
  SPI5->CR1     = 0;
  SPI5->CR2     = 0;
  SPI5->I2SCFGR = 0;
  SPI5->CR1 = (SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE | (3 << 3) | SPI_CR1_MSTR);

  LCD_WriteCommand (0xCA);
  LCD_WriteData (0xC3);
  LCD_WriteData (0x08);
  LCD_WriteData (0x50);
  LCD_WriteCommand (LCD_POWERB);
  LCD_WriteData (0x00);
  LCD_WriteData (0xC1);
  LCD_WriteData (0x30);
  LCD_WriteCommand (LCD_POWER_SEQ);
  LCD_WriteData (0x64);
  LCD_WriteData (0x03);
  LCD_WriteData (0x12);
  LCD_WriteData (0x81);
  LCD_WriteCommand (LCD_DTCA);
  LCD_WriteData (0x85);
  LCD_WriteData (0x00);
  LCD_WriteData (0x78);
  LCD_WriteCommand (LCD_POWERA);
  LCD_WriteData (0x39);
  LCD_WriteData (0x2C);
  LCD_WriteData (0x00);
  LCD_WriteData (0x34);
  LCD_WriteData (0x02);
  LCD_WriteCommand (LCD_PRC);
  LCD_WriteData (0x20);
  LCD_WriteCommand (LCD_DTCB);
  LCD_WriteData (0x00);
  LCD_WriteData (0x00);
  LCD_WriteCommand (LCD_FRC);
  LCD_WriteData (0x00);
  LCD_WriteData (0x1B);
  LCD_WriteCommand (LCD_DFC);
  LCD_WriteData (0x0A);
  LCD_WriteData (0xA2);
  LCD_WriteCommand (LCD_POWER1);
  LCD_WriteData (0x10);
  LCD_WriteCommand (LCD_POWER2);
  LCD_WriteData (0x10);
  LCD_WriteCommand (LCD_VCOM1);
  LCD_WriteData (0x45);
  LCD_WriteData (0x15);
  LCD_WriteCommand (LCD_VCOM2);
  LCD_WriteData (0x90);
  LCD_WriteCommand (LCD_MAC);
  LCD_WriteData (0xC8);
  LCD_WriteCommand (LCD_3GAMMA_EN);
  LCD_WriteData (0x00);
  LCD_WriteCommand (LCD_RGB_INTERFACE);
  LCD_WriteData (0xC2);
  LCD_WriteCommand (LCD_DFC);
  LCD_WriteData (0x0A);
  LCD_WriteData (0xA7);
  LCD_WriteData (0x27);
  LCD_WriteData (0x04);

  // colomn address set
  LCD_WriteCommand (LCD_COLUMN_ADDR);
  LCD_WriteData (0x00);
  LCD_WriteData (0x00);
  LCD_WriteData (0x00);
  LCD_WriteData (0xEF);
  // Page Address Set
  LCD_WriteCommand (LCD_PAGE_ADDR);
  LCD_WriteData (0x00);
  LCD_WriteData (0x00);
  LCD_WriteData (0x01);
  LCD_WriteData (0x3F);
  LCD_WriteCommand (LCD_INTERFACE);
  LCD_WriteData (0x01);
  LCD_WriteData (0x00);
  LCD_WriteData (0x06);

  LCD_WriteCommand (LCD_GRAM);
  DELAY_MS (200);

  LCD_WriteCommand (LCD_GAMMA);
  LCD_WriteData (0x01);

  LCD_WriteCommand (LCD_PGAMMA);
  LCD_WriteData (0x0F);
  LCD_WriteData (0x29);
  LCD_WriteData (0x24);
  LCD_WriteData (0x0C);
  LCD_WriteData (0x0E);
  LCD_WriteData (0x09);
  LCD_WriteData (0x4E);
  LCD_WriteData (0x78);
  LCD_WriteData (0x3C);
  LCD_WriteData (0x09);
  LCD_WriteData (0x13);
  LCD_WriteData (0x05);
  LCD_WriteData (0x17);
  LCD_WriteData (0x11);
  LCD_WriteData (0x00);
  LCD_WriteCommand (LCD_NGAMMA);
  LCD_WriteData (0x00);
  LCD_WriteData (0x16);
  LCD_WriteData (0x1B);
  LCD_WriteData (0x04);
  LCD_WriteData (0x11);
  LCD_WriteData (0x07);
  LCD_WriteData (0x31);
  LCD_WriteData (0x33);
  LCD_WriteData (0x42);
  LCD_WriteData (0x05);
  LCD_WriteData (0x0C);
  LCD_WriteData (0x0A);
  LCD_WriteData (0x28);
  LCD_WriteData (0x2F);
  LCD_WriteData (0x0F);

  LCD_WriteCommand (LCD_SLEEP_OUT);
  DELAY_MS (200);
  LCD_WriteCommand (LCD_DISPLAY_ON);
  // GRAM start writing
  LCD_WriteCommand (LCD_GRAM);

  LTDC->IER = 0;
  LTDC_Layer1->CR = 0;
  LTDC_Layer2->CR = 0;

  LTDC->SSCR = (((                                                                           HORIZONTAL_SYNC_WIDTH - 1) << 16) | (                                                                      VERTICAL_SYNC_WIDTH - 1));
  LTDC->BPCR = (((                                                   HORIZONTAL_BACK_PORCH + HORIZONTAL_SYNC_WIDTH - 1) << 16) | (                                                VERTICAL_BACK_PORCH + VERTICAL_SYNC_WIDTH - 1));
  LTDC->AWCR = (((                         HORIZONTAL_ACTIVE_WIDTH + HORIZONTAL_BACK_PORCH + HORIZONTAL_SYNC_WIDTH - 1) << 16) | (                       VERTICAL_ACTIVE_HEIGHT + VERTICAL_BACK_PORCH + VERTICAL_SYNC_WIDTH - 1));
  LTDC->TWCR = (((HORIZONTAL_FRONT_PORCH + HORIZONTAL_ACTIVE_WIDTH + HORIZONTAL_BACK_PORCH + HORIZONTAL_SYNC_WIDTH - 1) << 16) | (VERTICAL_FRONT_PORCH + VERTICAL_ACTIVE_HEIGHT + VERTICAL_BACK_PORCH + VERTICAL_SYNC_WIDTH - 1));
  LTDC->GCR  = (LTDC_GCR_PCPOL | LTDC_GCR_DTEN);
  LTDC->BCCR = 0;
  LTDC->LIPCR = 0;

  LTDC_Layer1->WHPCR = (((HORIZONTAL_ACTIVE_WIDTH + HORIZONTAL_BACK_PORCH + HORIZONTAL_SYNC_WIDTH - 1) << 16) | (HORIZONTAL_BACK_PORCH + HORIZONTAL_SYNC_WIDTH));
  LTDC_Layer1->WVPCR = ((( VERTICAL_ACTIVE_HEIGHT +   VERTICAL_BACK_PORCH +   VERTICAL_SYNC_WIDTH - 1) << 16) | (  VERTICAL_BACK_PORCH +   VERTICAL_SYNC_WIDTH));
  LTDC_Layer1->CKCR = 0;
  LTDC_Layer1->PFCR = 0; // ARGB8888
  LTDC_Layer1->CACR = 0xFF;
  LTDC_Layer1->DCCR = 0xFFFFFFFFu;
  LTDC_Layer1->BFCR = 0x405; // do not use pixel alpha
  LTDC_Layer1->CFBAR = (unsigned int)&framebuffer[0][0];
  LTDC_Layer1->CFBLR = ((((unsigned int)((char*)&framebuffer[1][0] - (char*)&framebuffer[0][0])) << 16) | ((sizeof framebuffer[0]) + 3));
  LTDC_Layer1->CFBLNR = (sizeof framebuffer / sizeof framebuffer[0]);
  LTDC_Layer1->CR = LTDC_LxCR_LEN;

  LTDC->SRCR = LTDC_SRCR_IMR;

  LTDC->GCR |= LTDC_GCR_LTDCEN;
}
