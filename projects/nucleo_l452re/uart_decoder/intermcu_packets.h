// Intermcu packet decoder
// Copyright Green Energy Options Ltd.

#ifndef INTERMCU_PACKETS_H_INCLUDED
#define INTERMCU_PACKETS_H_INCLUDED

#include <stdint.h>
#include "linebuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function to describe an intermcu packet
// the function should output text to the linebuffer argument
// the data argument points to the packet header (excluding the sync bytes)
// the count argument includes the header and payload but not the sync bytes or trailing CRC
// the function should return one of normal_color or bold_color depending how important or unusual the packet is
uint8_t intermcu_packet(struct linebuffer *lb,
                        const uint8_t     *data,
                        uint32_t           count,
                        uint8_t            normal_color,
                        uint8_t            bold_color);

#ifdef __cplusplus
}
#endif

#endif // INTERMCU_PACKETS_H_INCLUDED
