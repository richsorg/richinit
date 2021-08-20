#pragma once

#include <stdint.h>

enum {
	START,
	STOP,
	RESTART,
	STATUS,
	RUNNING,
	DEAD
} typedef operation_t;

struct protocol_t {
	uint8_t name_len;
	operation_t op;
} typedef csum_t;
