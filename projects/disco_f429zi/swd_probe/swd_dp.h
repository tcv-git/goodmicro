
#pragma once

#include <stdint.h>

enum port
{
  DP = 0,
  AP = 1,
};

enum address
{
  ADDR_DP_R_DPIDR     = 0,
  ADDR_DP_W_ABORT     = 0,
  ADDR_DP_RW_CTRLSTAT = 1,
  ADDR_DP_R_RESEND    = 2,
  ADDR_DP_W_SELECT    = 2,
  ADDR_DP_R_RDBUFF    = 3,
};

enum result
{
  OK,
  WAIT_RESPONSE,
  ERROR_RESPONSE,
  PROTOCOL_ERROR,
  PARITY_ERROR,
};

void reset_sequence(void);

enum result write_word(enum port port, enum address address, uint32_t data);
enum result read_word(enum port port, enum address address, uint32_t *p_data);

enum result read_dpidr    (uint32_t *p_data);
enum result read_ctrlstat (uint32_t *p_data);
enum result read_dlcr     (uint32_t *p_data);
enum result read_resend   (uint32_t *p_data);
enum result read_rdbuff   (uint32_t *p_data);

enum result write_abort    (uint32_t data);
enum result write_ctrlstat (uint32_t data);
enum result write_dlcr     (uint32_t data);
enum result write_select   (uint32_t data);

enum result set_apsel(uint8_t apsel);
enum result set_apbank(uint8_t apbank);
enum result set_dpbank(uint8_t dpbank);
enum result set_apsel_apbank(uint8_t apsel, uint8_t apbank);
enum result set_apsel_apbank_dbank(uint8_t apsel, uint8_t apbank, uint8_t dpbank);
