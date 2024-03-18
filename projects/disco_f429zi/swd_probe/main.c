
#include "delay.h"
#include "debug_printf.h"
#include "lcd.h"
#include "lcd_text.h"
#include "swd_dp.h"
#include "mem_ap.h"

static void assert_ok(enum result result)
{
  switch (result)
  {
    case WAIT_RESPONSE:   lcd_printf("WAIT_RESPONSE\n");   break;
    case ERROR_RESPONSE:  lcd_printf("ERROR_RESPONSE\n");  break;
    case PROTOCOL_ERROR:  lcd_printf("PROTOCOL_ERROR\n");  break;
    case PARITY_ERROR:    lcd_printf("PARITY_ERROR\n");    break;
    case OK:              return;
    default:              break;
  }
  for (;;);
}

int main(void)
{
  debug_uart_init();

  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  for (;;)
  {
    reset_sequence();

    uint32_t id;
    uint32_t ctrlstat;
    uint32_t dlcr;

    assert_ok(read_dpidr(&id));

    lcd_printf("id: %08X\n", (unsigned int)id);

    assert_ok(read_ctrlstat(&ctrlstat));

    lcd_printf("ct: %08X\n", (unsigned int)ctrlstat);

    assert_ok(read_dlcr(&dlcr));

    lcd_printf("dl: %08X\n", (unsigned int)dlcr);

    ctrlstat |= (1uL << 28);

    assert_ok(write_ctrlstat(ctrlstat));

    DELAY_S(1);

    for (unsigned int i = 0; i < 256; i++)
    {
      uint32_t data;

      assert_ok(set_apsel_apbank(i, 0xF));
      assert_ok(read_ap(3, &data));

      if (data != 0)
      {
        lcd_printf("ap[%u]: %08X\n", i, (unsigned int)data);
      }

      DELAY_S(1);
    }

    DELAY_S(5);
  }
}
