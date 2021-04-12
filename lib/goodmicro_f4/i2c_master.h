// i2c_master.h
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

#ifndef I2C_MASTER_H_INCLUDED
#define I2C_MASTER_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

#define I2CM_SUCCESS          0
#define I2CM_ERROR_USAGE    (-1)  // incorrect function arguments
#define I2CM_ERROR_BUSY     (-2)  // another master already has the bus
#define I2CM_ERROR_ARLO     (-3)  // arbitration lost, ie: another master took the bus just as we tried to
#define I2CM_ERROR_NACK     (-4)  // no acknowledgement from slave
#define I2CM_ERROR_TIMEOUT  (-5)  // timeout waiting for next state, probably caused by excessive bus stretching or lockup

#ifdef __cplusplus
extern "C" {
#endif

int i2cm_init(void);

int i2cm_start_write (uint8_t slave_address);
int i2cm_start_read  (uint8_t slave_address);

int i2cm_write_data (const uint8_t *data, uint32_t data_length, bool send_stop);
int i2cm_read_data  (      uint8_t *data, uint32_t data_length, bool send_stop, bool nack_last_byte);

int i2cm_write (uint8_t slave_address, const uint8_t *data, uint32_t data_length);
int i2cm_read  (uint8_t slave_address,       uint8_t *data, uint32_t data_length);

#ifdef __cplusplus
}
#endif

#endif // I2C_MASTER_H_INCLUDED
