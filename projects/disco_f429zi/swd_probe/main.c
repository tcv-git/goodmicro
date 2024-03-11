// main.c
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

#include "delay.h"
#include "debug_printf.h"
#include "lcd.h"
#include "lcd_text.h"
#include "swd.h"

int main(void)
{
  debug_uart_init();

  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  for (;;)
  {
    reset_sequence();

    uint32_t id;
    enum result result = read_word(DP, ADDR_DP_R_IDCODE, &id);

    switch (result)
    {
      case WAIT_RESPONSE:   lcd_printf("WAIT_RESPONSE\n");   break;
      case ERROR_RESPONSE:  lcd_printf("ERROR_RESPONSE\n");  break;
      case PROTOCOL_ERROR:  lcd_printf("PROTOCOL_ERROR\n");  break;
      case PARITY_ERROR:    lcd_printf("PARITY_ERROR\n");    break;
      case OK:
        lcd_printf("id: %08X\n", (unsigned int)id);
    }

    DELAY_S(5);
  }
}
