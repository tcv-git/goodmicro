
#pragma once

#include <stdint.h>
#include "swd_dp.h"

enum result read_ap(enum address address, uint32_t *p_data);

#if 0
enum result memap_write_u8 (uint32_t memaddr, uint8_t  data);
enum result memap_write_u16(uint32_t memaddr, uint16_t data);
enum result memap_write_u32(uint32_t memaddr, uint32_t data);
enum result memap_read_u8 (uint32_t memaddr, uint8_t  *p_data);
enum result memap_read_u16(uint32_t memaddr, uint16_t *p_data);
enum result memap_read_u32(uint32_t memaddr, uint32_t *p_data);
#endif
