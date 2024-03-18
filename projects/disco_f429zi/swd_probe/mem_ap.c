
#include <stddef.h>
#include <stdint.h>
#include "swd_dp.h"
#include "mem_ap.h"

enum result read_ap(enum address address, uint32_t *p_data)
{
  enum result result = read_word(AP, address, NULL);

  if (result == OK)
  {
    result = read_word(DP, ADDR_DP_R_RDBUFF, p_data);
  }

  return result;
}
