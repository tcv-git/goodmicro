
#include <stddef.h>
#include <stdint.h>
#include "delay.h"
#include "swd_dp.h"
#include "mem_ap.h"
#include "lcd_text.h"

#define ONLY_AP 0
#define AP_CSW_PROT     0xE3000000uL
#define AP_CSW_SIZE_8   0
#define AP_CSW_SIZE_16  1
#define AP_CSW_SIZE_32  2


enum result mem_ap_connect(void)
{
  reset_sequence();

  uint32_t id;

  enum result result = read_idcode(&id);

  if (result != OK)
  {
    return result;
  }

  if (id != 0x2BA01477uL)
  {
    return UNSUPPORTED_RESPONSE;
  }

  uint32_t ctrl;

  result = read_wcr(&ctrl);

  if (result != OK)
  {
    return result;
  }

  if ((ctrl & 0xFFFFFFF8uL) != 0x00000040uL) // WIREMODE != Synchronous
  {
    return UNSUPPORTED_RESPONSE;
  }

  result = read_ctrlstat(&ctrl);

  if (result != OK)
  {
    return result;
  }

  ctrl &= (1uL << 30); // clear all but CSYSPWRUPREQ
  ctrl |= (1uL << 28); // set CDBGPWRUPREQ

  result = write_ctrlstat(ctrl);

  if (result != OK)
  {
    return result;
  }

  DELAY_MS(200);

  result = read_ctrlstat(&ctrl);

  if (result != OK)
  {
    return result;
  }

  if ((ctrl & (1uL << 29)) == 0) // CDBGPWRUPACK
  {
    return UNSUPPORTED_RESPONSE;
  }

  result = read_ap(ONLY_AP, 0xFC, &id); // IDR

  if (result != OK)
  {
    return result;
  }

  if (id != 0x24770011uL)
  {
    return UNSUPPORTED_RESPONSE;
  }

  uint32_t cfg;

  result = read_ap(ONLY_AP, 0xF4, &cfg); // CFG

  if (result != OK)
  {
    return result;
  }

  if (cfg != 0)
  {
    return UNSUPPORTED_RESPONSE;
  }

  result = read_ap(ONLY_AP, 0xE0, &cfg); // CFG1

  if (result != OK)
  {
    return result;
  }

  if (cfg != 0)
  {
    return UNSUPPORTED_RESPONSE;
  }

  result = read_ap(ONLY_AP, 0x00, &ctrl); // CSW

  if (result != OK)
  {
    return result;
  }

  if ((ctrl & (1u << 6)) == 0)  // DeviceEn
  {
    return UNSUPPORTED_RESPONSE;
  }

  return OK;
}

enum result mem_ap_read_base(uint32_t *p_data)
{
  uint32_t base;

  enum result result = read_ap(ONLY_AP, 0xF8, &base); // BASE

  if (result != OK)
  {
    return result;
  }

  if ((base & 0xFFF) != 0x003)
  {
    return UNSUPPORTED_RESPONSE;
  }

  base &= 0xFFFFF000uL;

  if (p_data)
  {
    *p_data = base;
  }

  return OK;
}

static uint32_t previous_csw = UINT32_MAX;

static enum result set_csw(uint32_t data)
{
  if (data == previous_csw)
  {
    return OK;
  }

  enum result result = write_ap(ONLY_AP, 0x00, data);

  if (result == OK)
  {
    previous_csw = data;
  }
  else
  {
    previous_csw = UINT32_MAX;
  }

  return result;
}

enum result mem_ap_read_u32(uint32_t memaddr, uint32_t *p_data)
{
  if ((memaddr & 3) != 0)
  {
    return INVALID_ARG;
  }

  enum result result = set_csw(AP_CSW_PROT | AP_CSW_SIZE_32);

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x04, memaddr); // TAR
  }

  if (result == OK)
  {
    result = read_ap(ONLY_AP, 0x0C, p_data); // DRW
  }

  return result;
}

enum result mem_ap_read_u16(uint32_t memaddr, uint16_t *p_data)
{
  if ((memaddr & 1) != 0)
  {
    return INVALID_ARG;
  }

  enum result result = set_csw(AP_CSW_PROT | AP_CSW_SIZE_16);

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x04, memaddr); // TAR
  }

  uint32_t data32;

  if (result == OK)
  {
    result = read_ap(ONLY_AP, 0x0C, &data32); // DRW
  }

  if ((result == OK) && p_data)
  {
    if ((memaddr & 2) != 0)
    {
      data32 >>= 16;
    }

    *p_data = (uint16_t)data32;
  }

  return result;
}

enum result mem_ap_read_u8(uint32_t memaddr, uint8_t *p_data)
{
  enum result result = set_csw(AP_CSW_PROT | AP_CSW_SIZE_8);

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x04, memaddr); // TAR
  }

  uint32_t data32;

  if (result == OK)
  {
    result = read_ap(ONLY_AP, 0x0C, &data32); // DRW
  }

  if ((result == OK) && p_data)
  {
    if ((memaddr & 2) != 0)
    {
      data32 >>= 16;
    }

    if ((memaddr & 1) != 0)
    {
      data32 >>= 8;
    }

    *p_data = (uint16_t)data32;
  }

  return result;
}

enum result mem_ap_write_u8(uint32_t memaddr, uint8_t  data)
{
  enum result result = set_csw(AP_CSW_PROT | AP_CSW_SIZE_8);

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x04, memaddr); // TAR
  }

  uint32_t data32 = (((uint32_t)data << 24) | (data << 16) | (data << 8) | data);

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x0C, data32); // DRW
  }

  return result;
}

enum result mem_ap_write_u16(uint32_t memaddr, uint16_t data)
{
  if ((memaddr & 1) != 0)
  {
    return INVALID_ARG;
  }

  enum result result = set_csw(AP_CSW_PROT | AP_CSW_SIZE_16);

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x04, memaddr); // TAR
  }

  uint32_t data32 = (((uint32_t)data << 16) | data);

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x0C, data32); // DRW
  }

  return result;
}

enum result mem_ap_write_u32(uint32_t memaddr, uint32_t data)
{
  if ((memaddr & 3) != 0)
  {
    return INVALID_ARG;
  }

  enum result result = set_csw(AP_CSW_PROT | AP_CSW_SIZE_32);

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x04, memaddr); // TAR
  }

  if (result == OK)
  {
    result = write_ap(ONLY_AP, 0x0C, data); // DRW
  }

  return result;
}

