// i2c_pinout.h
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

#ifndef I2C_PINOUT_H_INCLUDED
#define I2C_PINOUT_H_INCLUDED

#define I2CM_SCL_PORT           GPIOA
#define I2CM_SCL_PORT_ENR       RCC->AHB1ENR
#define I2CM_SCL_PORT_ENR_BIT   RCC_AHB1ENR_GPIOAEN
#define I2CM_SCL_PINMASK        PIN8
#define I2CM_SCL_AFn            AF4
#define I2CM_SDA_PORT           GPIOC
#define I2CM_SDA_PORT_ENR       RCC->AHB1ENR
#define I2CM_SDA_PORT_ENR_BIT   RCC_AHB1ENR_GPIOCEN
#define I2CM_SDA_PINMASK        PIN9
#define I2CM_SDA_AFn            AF4
#define I2CM_ENR                RCC->APB1ENR
#define I2CM_ENR_BIT            RCC_APB1ENR_I2C3EN
#define I2CM_RSTR               RCC->APB1RSTR
#define I2CM_RSTR_BIT           RCC_APB1RSTR_I2C3RST
#define I2CM                    I2C3
#define I2CM_APB_CLK            APB1_CLK

#endif // I2C_PINOUT_H_INCLUDED
