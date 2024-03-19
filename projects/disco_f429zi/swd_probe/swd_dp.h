
#pragma once

#include <stdint.h>

enum result
{
  OK,
  INVALID_ARG,
  WAIT_RESPONSE,
  ERROR_RESPONSE,
  PROTOCOL_ERROR,
  PARITY_ERROR,
  UNSUPPORTED_RESPONSE,
};

void reset_sequence(void);

enum result read_idcode   (uint32_t *p_data);
enum result read_ctrlstat (uint32_t *p_data);
enum result read_wcr      (uint32_t *p_data);
enum result read_resend   (uint32_t *p_data);
enum result read_rdbuff   (uint32_t *p_data);

enum result write_abort    (uint32_t data);
enum result write_ctrlstat (uint32_t data);
enum result write_wcr      (uint32_t data);
enum result write_select   (uint32_t data);

enum result read_ap(uint8_t apsel, uint8_t address, uint32_t *p_data);
enum result write_ap(uint8_t apsel, uint8_t address, uint32_t data);
