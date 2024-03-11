
#pragma once

#include <stdint.h>

enum port
{
	DP,
	AP,
};

enum address
{
	ADDR_DP_R_IDCODE = 0,
	ADDR_DP_W_ABORT  = 0,
	ADDR_DP_RW_CTRL  = 1,
	ADDR_DP_R_RESEND = 2,
	ADDR_DP_W_SELECT = 2,
	ADDR_DP_R_RDBUFF = 3,
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

enum result read_register(enum port port, enum address address, uint32_t *p_data);

enum result read_register_via_buffer(enum port port, enum address address, uint32_t *p_data);
