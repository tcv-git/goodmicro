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

  volatile int8_t value = 0;

  int result;

  result = atomic_set_i8_if_le_zero(&value, 4);      lcd_printf("result %i value %i\n", result, value);
  result = atomic_set_i8_if_le_zero(&value, 7);      lcd_printf("result %i value %i\n", result, value);

  value = -1;

  result = atomic_set_i8_if_le_zero(&value, 5);      lcd_printf("result %i value %i\n", result, value);

  value = 9;

  result = atomic_set_i8_if_le_zero(&value, 3);      lcd_printf("result %i value %i\n", result, value);

  for (;;);
}
