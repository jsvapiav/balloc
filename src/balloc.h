#ifndef BALLOC_H

#include <stdint.h>

#define BALLOC_BLOCK_SIZE 8
#define BALLOC_BLOCK_NUM 64

#define BALLOC_PREFIX_CANARY 0xBEEF
#define BALLOC_POSTFIX_CANARY 0xDEAD

enum balloc_error {
	BALLOC_ERROR  = 0,
	BALLOC_SUCCES = 1
};

struct balloc_canary {
	uint16_t canary;
};

struct balloc_block_hdr {
	int in_use;
	struct balloc_canary prefix;
};

struct balloc_mem_block {
	struct balloc_block_hdr hdr;
	uint8_t block[BALLOC_BLOCK_SIZE];
	struct balloc_canary postfix;
};

void  balloc_init();
void* balloc_alloc();
int   balloc_free(void *block);


#define BALLOC_H
#endif
