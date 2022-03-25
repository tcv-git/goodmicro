// stm32l0xx_simple_gpio.h
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

#ifndef STM32L0XX_SIMPLE_GPIO_H_INCLUDED
#define STM32L0XX_SIMPLE_GPIO_H_INCLUDED

#include "stm32l0xx.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  PIN0      (1u <<  0)
#define  PIN1      (1u <<  1)
#define  PIN2      (1u <<  2)
#define  PIN3      (1u <<  3)
#define  PIN4      (1u <<  4)
#define  PIN5      (1u <<  5)
#define  PIN6      (1u <<  6)
#define  PIN7      (1u <<  7)
#define  PIN8      (1u <<  8)
#define  PIN9      (1u <<  9)
#define  PIN10     (1u << 10)
#define  PIN11     (1u << 11)
#define  PIN12     (1u << 12)
#define  PIN13     (1u << 13)
#define  PIN14     (1u << 14)
#define  PIN15     (1u << 15)

#define HI(pinmask)  ((uint32_t)(pinmask))
#define LO(pinmask)  ((uint32_t)(pinmask) << 16)

#define  PIN0_HI   HI(PIN0)
#define  PIN1_HI   HI(PIN1)
#define  PIN2_HI   HI(PIN2)
#define  PIN3_HI   HI(PIN3)
#define  PIN4_HI   HI(PIN4)
#define  PIN5_HI   HI(PIN5)
#define  PIN6_HI   HI(PIN6)
#define  PIN7_HI   HI(PIN7)
#define  PIN8_HI   HI(PIN8)
#define  PIN9_HI   HI(PIN9)
#define  PIN10_HI  HI(PIN10)
#define  PIN11_HI  HI(PIN11)
#define  PIN12_HI  HI(PIN12)
#define  PIN13_HI  HI(PIN13)
#define  PIN14_HI  HI(PIN14)
#define  PIN15_HI  HI(PIN15)

#define  PIN0_LO   LO(PIN0)
#define  PIN1_LO   LO(PIN1)
#define  PIN2_LO   LO(PIN2)
#define  PIN3_LO   LO(PIN3)
#define  PIN4_LO   LO(PIN4)
#define  PIN5_LO   LO(PIN5)
#define  PIN6_LO   LO(PIN6)
#define  PIN7_LO   LO(PIN7)
#define  PIN8_LO   LO(PIN8)
#define  PIN9_LO   LO(PIN9)
#define  PIN10_LO  LO(PIN10)
#define  PIN11_LO  LO(PIN11)
#define  PIN12_LO  LO(PIN12)
#define  PIN13_LO  LO(PIN13)
#define  PIN14_LO  LO(PIN14)
#define  PIN15_LO  LO(PIN15)

#define  AF0        0
#define  AF1        1
#define  AF2        2
#define  AF3        3
#define  AF4        4
#define  AF5        5
#define  AF6        6
#define  AF7        7

/*                                                                                ( port,   pins, mode,function,type,pull,speed) */
#define GPIO_input(port,pins)                                          GPIO_setup ((port), (pins), 0, (       0), 0,   0,  0)
#define GPIO_input_pull_up(port,pins)                                  GPIO_setup ((port), (pins), 0, (       0), 0,   1,  0)
#define GPIO_input_pull_down(port,pins)                                GPIO_setup ((port), (pins), 0, (       0), 0,   2,  0)
#define GPIO_output_push_pull_slow(port,pins)                          GPIO_setup ((port), (pins), 1, (       0), 0,   0,  0)
#define GPIO_output_push_pull_medium(port,pins)                        GPIO_setup ((port), (pins), 1, (       0), 0,   0,  1)
#define GPIO_output_push_pull_fast(port,pins)                          GPIO_setup ((port), (pins), 1, (       0), 0,   0,  2)
#define GPIO_output_push_pull_vfast(port,pins)                         GPIO_setup ((port), (pins), 1, (       0), 0,   0,  3)
#define GPIO_output_open_drain_slow(port,pins)                         GPIO_setup ((port), (pins), 1, (       0), 1,   0,  0)
#define GPIO_output_open_drain_medium(port,pins)                       GPIO_setup ((port), (pins), 1, (       0), 1,   0,  1)
#define GPIO_output_open_drain_fast(port,pins)                         GPIO_setup ((port), (pins), 1, (       0), 1,   0,  2)
#define GPIO_output_open_drain_vfast(port,pins)                        GPIO_setup ((port), (pins), 1, (       0), 1,   0,  3)
#define GPIO_output_open_drain_pull_up_slow(port,pins)                 GPIO_setup ((port), (pins), 1, (       0), 1,   1,  0)
#define GPIO_output_open_drain_pull_up_medium(port,pins)               GPIO_setup ((port), (pins), 1, (       0), 1,   1,  1)
#define GPIO_output_open_drain_pull_up_fast(port,pins)                 GPIO_setup ((port), (pins), 1, (       0), 1,   1,  2)
#define GPIO_output_open_drain_pull_up_vfast(port,pins)                GPIO_setup ((port), (pins), 1, (       0), 1,   1,  3)
#define GPIO_output_open_drain_pull_down_slow(port,pins)               GPIO_setup ((port), (pins), 1, (       0), 1,   2,  0)
#define GPIO_output_open_drain_pull_down_medium(port,pins)             GPIO_setup ((port), (pins), 1, (       0), 1,   2,  1)
#define GPIO_output_open_drain_pull_down_fast(port,pins)               GPIO_setup ((port), (pins), 1, (       0), 1,   2,  2)
#define GPIO_output_open_drain_pull_down_vfast(port,pins)              GPIO_setup ((port), (pins), 1, (       0), 1,   2,  3)
#define GPIO_alternate_push_pull_slow(port,pins,function)              GPIO_setup ((port), (pins), 2, (function), 0,   0,  0)
#define GPIO_alternate_push_pull_medium(port,pins,function)            GPIO_setup ((port), (pins), 2, (function), 0,   0,  1)
#define GPIO_alternate_push_pull_fast(port,pins,function)              GPIO_setup ((port), (pins), 2, (function), 0,   0,  2)
#define GPIO_alternate_push_pull_vfast(port,pins,function)             GPIO_setup ((port), (pins), 2, (function), 0,   0,  3)
#define GPIO_alternate_pull_up_slow(port,pins,function)                GPIO_setup ((port), (pins), 2, (function), 0,   1,  0)
#define GPIO_alternate_pull_up_medium(port,pins,function)              GPIO_setup ((port), (pins), 2, (function), 0,   1,  1)
#define GPIO_alternate_pull_up_fast(port,pins,function)                GPIO_setup ((port), (pins), 2, (function), 0,   1,  2)
#define GPIO_alternate_pull_up_vfast(port,pins,function)               GPIO_setup ((port), (pins), 2, (function), 0,   1,  3)
#define GPIO_alternate_pull_down_slow(port,pins,function)              GPIO_setup ((port), (pins), 2, (function), 0,   2,  0)
#define GPIO_alternate_pull_down_medium(port,pins,function)            GPIO_setup ((port), (pins), 2, (function), 0,   2,  1)
#define GPIO_alternate_pull_down_fast(port,pins,function)              GPIO_setup ((port), (pins), 2, (function), 0,   2,  2)
#define GPIO_alternate_pull_down_vfast(port,pins,function)             GPIO_setup ((port), (pins), 2, (function), 0,   2,  3)
#define GPIO_alternate_open_drain_slow(port,pins,function)             GPIO_setup ((port), (pins), 2, (function), 1,   0,  0)
#define GPIO_alternate_open_drain_medium(port,pins,function)           GPIO_setup ((port), (pins), 2, (function), 1,   0,  1)
#define GPIO_alternate_open_drain_fast(port,pins,function)             GPIO_setup ((port), (pins), 2, (function), 1,   0,  2)
#define GPIO_alternate_open_drain_vfast(port,pins,function)            GPIO_setup ((port), (pins), 2, (function), 1,   0,  3)
#define GPIO_alternate_open_drain_pull_up_slow(port,pins,function)     GPIO_setup ((port), (pins), 2, (function), 1,   1,  0)
#define GPIO_alternate_open_drain_pull_up_medium(port,pins,function)   GPIO_setup ((port), (pins), 2, (function), 1,   1,  1)
#define GPIO_alternate_open_drain_pull_up_fast(port,pins,function)     GPIO_setup ((port), (pins), 2, (function), 1,   1,  2)
#define GPIO_alternate_open_drain_pull_up_vfast(port,pins,function)    GPIO_setup ((port), (pins), 2, (function), 1,   1,  3)
#define GPIO_alternate_open_drain_pull_down_slow(port,pins,function)   GPIO_setup ((port), (pins), 2, (function), 1,   2,  0)
#define GPIO_alternate_open_drain_pull_down_medium(port,pins,function) GPIO_setup ((port), (pins), 2, (function), 1,   2,  1)
#define GPIO_alternate_open_drain_pull_down_fast(port,pins,function)   GPIO_setup ((port), (pins), 2, (function), 1,   2,  2)
#define GPIO_alternate_open_drain_pull_down_vfast(port,pins,function)  GPIO_setup ((port), (pins), 2, (function), 1,   2,  3)
#define GPIO_analog(port,pins)                                         GPIO_setup ((port), (pins), 3, (       0), 0,   0,  0)

static inline unsigned int __attribute__((always_inline)) spread_bits (unsigned short bits)
{
  unsigned int result = bits;

  result = ((result | (result << 8)) & 0x00FF00FFu);
  result = ((result | (result << 4)) & 0x0F0F0F0Fu);
  result = ((result | (result << 2)) & 0x33333333u);
  result = ((result | (result << 1)) & 0x55555555u);

  return result;
}

static inline void __attribute__((always_inline)) GPIO_setup (GPIO_TypeDef *port,
                                                              unsigned short pins,
                                                              unsigned int mode,
                                                              unsigned int function,
                                                              unsigned int type,
                                                              unsigned int pull,
                                                              unsigned int speed)
{
  unsigned int pins2  = spread_bits (pins);
  unsigned int pins4l = spread_bits (pins2);
  unsigned int pins4h = spread_bits (pins2 >> 16);

  if ((!__builtin_constant_p (pins4l)) || (pins4l != 0))
  {
    port->AFR[0] = ((port->AFR[0] & ~(15 * pins4l)) | (function * pins4l));
  }
  if ((!__builtin_constant_p (pins4h)) || (pins4h != 0))
  {
    port->AFR[1] = ((port->AFR[1] & ~(15 * pins4h)) | (function * pins4h));
  }
  port->OSPEEDR = ((port->OSPEEDR & ~( 3 * pins2 )) | (speed    * pins2 ));
  port->OTYPER  = ((port->OTYPER  & ~(     pins  )) | (type     * pins  ));
  port->PUPDR   = ((port->PUPDR   & ~( 3 * pins2 )) | (pull     * pins2 ));
  port->MODER   = ((port->MODER   & ~( 3 * pins2 )) | (mode     * pins2 ));
}

static inline void __attribute__((always_inline)) GPIO_lock (GPIO_TypeDef *port, unsigned short pins)
{
  port->LCKR = (pins | GPIO_LCKR_LCKK);
  port->LCKR =  pins;
  port->LCKR = (pins | GPIO_LCKR_LCKK);
  (void)port->LCKR;
}

static inline void __attribute__((always_inline)) GPIO_set_reset (GPIO_TypeDef *port, unsigned int bits)
{
  port->BSRR = bits;
}

#ifdef __cplusplus
}
#endif

#endif /* STM32L0XX_SIMPLE_GPIO_H_INCLUDED */
