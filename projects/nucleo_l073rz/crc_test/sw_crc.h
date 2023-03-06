/**
 * @file crc.h
 */

#ifndef __CRC_H__
#define __CRC_H__

#include <stdint.h>

uint16_t crc_CalcCrc(const uint8_t *buffer, uint32_t bufferSize);

#endif // __CRC_H__
