/**
 * @file crc.c
 */

#include "sw_crc.h"

/**
 * Update a CRC based on a new byte input value.
 *
 * Implements CRC-16-IBM.
 *
 * @param crc The current CRC value.
 * @param byteValue The byte value to update the CRC with.
 *
 * @return the updated CRC value.
 */
static uint16_t crc_UpdateCrc(uint16_t crc, uint8_t byteValue)
{
	int i;

	crc ^= (uint16_t)byteValue;

	for (i = 0; i < 8; i++) {
		if (crc & 0x0001) {
			crc = (crc >> 1) ^ 0xA001;
		} else {
			crc >>= 1;
		}
	}

	return crc;
}

/**
 * Calculate a CRC over a buffer.
 *
 * Implements CRC-16-IBM.
 *
 * @param buffer Pointer to the buffer to calculate.
 * @param bufferSize The size of the buffer, in bytes.
 *
 * @return crc for the buffer.
 */
uint16_t crc_CalcCrc(const uint8_t *buffer, uint32_t bufferSize)
{
	uint16_t crc = 0;

	while (bufferSize) {
		crc = crc_UpdateCrc(crc, *buffer);

		// Next byte
		buffer++;
		bufferSize--;
	}

	// Return the CRC
	return crc;
}
