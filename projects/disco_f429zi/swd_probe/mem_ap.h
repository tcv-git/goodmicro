
#pragma once

#include <stdint.h>
#include "swd_dp.h"

enum result mem_ap_connect(void);
enum result mem_ap_read_base(uint32_t *p_data);

enum result mem_ap_read_u8  (uint32_t memaddr, uint8_t  *p_data);
enum result mem_ap_read_u16 (uint32_t memaddr, uint16_t *p_data);
enum result mem_ap_read_u32 (uint32_t memaddr, uint32_t *p_data);
enum result mem_ap_write_u8 (uint32_t memaddr, uint8_t  data);
enum result mem_ap_write_u16(uint32_t memaddr, uint16_t data);
enum result mem_ap_write_u32(uint32_t memaddr, uint32_t data);
