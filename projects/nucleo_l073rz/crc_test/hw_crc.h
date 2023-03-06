// Hardware CRC calculator driver
// Copyright Green Energy Options Ltd.

#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void crc_init(void);
uint16_t crc_calc(const uint8_t *data, uint32_t count);

#ifdef __cplusplus
}
#endif

#endif // CRC_H_INCLUDED
