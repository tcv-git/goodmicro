// main.c
// Copyright Green Energy Options Ltd.

#include "lcd.h"
#include "lcd_text.h"
#include "delay.h"
#include "atomic_test_and_set.h"

int main(void)
{
  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  lcd_printf("hello\n");

#if 0
  volatile int8_t value = 0;

  int result;

  result = atomic_set_i8_if_le_zero(&value, 4);      lcd_printf("result %i value %i\n", result, value);
  result = atomic_set_i8_if_le_zero(&value, 7);      lcd_printf("result %i value %i\n", result, value);

  value = -1;

  result = atomic_set_i8_if_le_zero(&value, 5);      lcd_printf("result %i value %i\n", result, value);

  value = 9;

  result = atomic_set_i8_if_le_zero(&value, 3);      lcd_printf("result %i value %i\n", result, value);
#endif

#if 0
  volatile uint32_t word = 0x10030800uL;

  lcd_printf("result %08X\n", word);

  atomic_or_u32(&word, 0xFF);

  lcd_printf("result %08X\n", word);

  atomic_or_u32(&word, (1 << 20));

  lcd_printf("result %08X\n", word);

  atomic_or_u32(&word, (1 << 17));

  lcd_printf("result %08X\n", word);
#endif

#if 1
  volatile uint32_t word = 0xFFFFFFFFuL;
  volatile uint8_t test;

  int result;

  test = 3; result = atomic_bic_u32_if_u8_eq_zero(&word, (1u << 6), &test); lcd_printf("result %i value %08X\n", result, word);

  test = 0; result = atomic_bic_u32_if_u8_eq_zero(&word, (1u << 6), &test); lcd_printf("result %i value %08X\n", result, word);

  test = 0; result = atomic_bic_u32_if_u8_eq_zero(&word, (1u << 31), &test); lcd_printf("result %i value %08X\n", result, word);

  test = -1; result = atomic_bic_u32_if_u8_eq_zero(&word, (1u << 30), &test); lcd_printf("result %i value %08X\n", result, word);
  test = +1; result = atomic_bic_u32_if_u8_eq_zero(&word, (1u << 30), &test); lcd_printf("result %i value %08X\n", result, word);

  test = 42; result = atomic_bic_u32_if_u8_eq_zero(&word, 0xFF00, &test); lcd_printf("result %i value %08X\n", result, word);

  test = 0; result = atomic_bic_u32_if_u8_eq_zero(&word, 0xF000, &test); lcd_printf("result %i value %08X\n", result, word);

#endif

  for (;;);
}
