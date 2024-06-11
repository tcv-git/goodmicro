
#include "delay.h"
#include "debug_printf.h"
#include "lcd.h"
#include "lcd_text.h"
#include "swd_dp.h"
#include "mem_ap.h"

#define DHCSR 0xE000EDF0uL
#define DCRSR 0xE000EDF4uL
#define DCRDR 0xE000EDF8uL
#define DEMCR 0xE000EDFCuL
#define DBGKEY 0xA05F0000uL

static void assert_ok(enum result result)
{
  switch (result)
  {
    case WAIT_RESPONSE:         lcd_printf("WAIT_RESPONSE\n");          break;
    case INVALID_ARG:           lcd_printf("INVALID_ARG\n");            break;
    case ERROR_RESPONSE:        lcd_printf("ERROR_RESPONSE\n");         break;
    case PROTOCOL_ERROR:        lcd_printf("PROTOCOL_ERROR\n");         break;
    case PARITY_ERROR:          lcd_printf("PARITY_ERROR\n");           break;
    case UNSUPPORTED_RESPONSE:  lcd_printf("UNSUPPORTED_RESPONSE\n");   break;
    case OK:              return;
    default:              break;
  }
  for (;;);
}

static uint32_t read_reg(uint32_t regsel);

int main(void)
{
  debug_uart_init();

  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  assert_ok(mem_ap_connect());

  lcd_printf("connect ok\n");

#if 0
  uint32_t base;

  assert_ok(mem_ap_read_base(&base));

  lcd_printf("BASE %08X\n", (unsigned int)base);
#endif

#if 0
  uint32_t addr;

  for (addr = 0; addr < 16; addr++)
  {
    uint8_t data;

    assert_ok(mem_ap_read_u8(addr, &data));

    lcd_printf("u8 [0x%02X] 0x%02X\n", (unsigned int)addr, (unsigned int)data);
  }

  for (addr = 0; addr < 16; addr += 2)
  {
    uint16_t data;

    assert_ok(mem_ap_read_u16(addr, &data));

    lcd_printf("u16[0x%02X] 0x%04X\n", (unsigned int)addr, (unsigned int)data);
  }

  for (addr = 0; addr < 16; addr += 4)
  {
    uint32_t data;

    assert_ok(mem_ap_read_u32(addr, &data));

    lcd_printf("u32[0x%02X] 0x%08X\n", (unsigned int)addr, (unsigned int)data);
  }
#endif

#if 0
  uint32_t addr = 0x04010000uL;
  uint32_t data32;

  assert_ok(mem_ap_write_u32(addr, 0x03020100uL));

  assert_ok(mem_ap_read_u32(addr, &data32));

  lcd_printf("%08X\n", (unsigned int)data32);

  assert_ok(mem_ap_write_u16(addr + 2, 0x7766));

  assert_ok(mem_ap_read_u32(addr, &data32));

  lcd_printf("%08X\n", (unsigned int)data32);

  assert_ok(mem_ap_write_u8(addr + 3, 0xFF));

  assert_ok(mem_ap_read_u32(addr, &data32));

  lcd_printf("%08X\n", (unsigned int)data32);
#endif

#if 1
  uint32_t dhcsr;

  assert_ok(mem_ap_read_u32(DHCSR, &dhcsr));

  if ((dhcsr & 0xC0000uL) != 0)
  {
    lcd_printf("lockup/sleep\n");
    lcd_printf("DHCSR %08X\n", (unsigned int)dhcsr);
  }

  assert_ok(mem_ap_write_u32(DHCSR, (DBGKEY | 3)));  // set C_DEBUGEN and C_HALT

  DELAY_MS(50);

  assert_ok(mem_ap_read_u32(DHCSR, &dhcsr));

  if ((dhcsr & 0x20000uL) == 0) // S_HALT
  {
    lcd_printf("failed to halt\n");
    lcd_printf("DHCSR %08X\n", (unsigned int)dhcsr);

    assert_ok(mem_ap_write_u32(DHCSR, (DBGKEY | 0x23)));  // set C_DEBUGEN, C_HALT and C_SNAPSTALL

    DELAY_MS(50);

    assert_ok(mem_ap_read_u32(DHCSR, &dhcsr));

    if ((dhcsr & 0x20000uL) == 0) // S_HALT
    {
      lcd_printf("failed to force halt\n");
      for (;;);
    }
  }

  uint32_t sp = read_reg(13);
  uint32_t lr = read_reg(14);
  uint32_t pc = read_reg(15);

  lcd_printf("sp %08X\n", (unsigned int)sp);
  lcd_printf("lr %08X\n", (unsigned int)lr);
  lcd_printf("pc %08X\n", (unsigned int)pc);

  assert_ok(mem_ap_write_u32(DHCSR, (DBGKEY | 0)));
#endif

  lcd_printf("disconnect ok\n");

  for (;;);
}

static uint32_t read_reg(uint32_t regsel)
{
  uint32_t dhcsr, data;

  assert_ok(mem_ap_write_u32(DCRSR, regsel));

  DELAY_MS(50);

  assert_ok(mem_ap_read_u32(DHCSR, &dhcsr));

  if ((dhcsr & 0x10000uL) == 0)
  {
    lcd_printf("failed to read register\n");
    for (;;);
  }

  assert_ok(mem_ap_read_u32(DCRDR, &data));

  return data;
}
