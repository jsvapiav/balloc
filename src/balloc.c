#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "balloc.h"
#include "platform.h"

#ifdef __GNUC__
#define member_type(type, member) __typeof__ (((type *)0)->member)
#else
#define member_type(type, member) const void
#endif

#define container_of(ptr, type, member) ((type *)( \
	(char *)(member_type(type, member) *){ ptr } - offsetof(type, member)))

struct balloc_canary {
	balloc_platform_canary_int canary;
};

struct balloc_block_hdr {
	union {
		balloc_platform_fast_uint in_use;
		balloc_platform_fast_uint block_num;
	} state;
	struct balloc_canary prefix;
};

struct balloc_mem_block {
	struct balloc_block_hdr hdr;
	uint8_t block[BALLOC_BLOCK_SIZE];
	struct balloc_canary postfix;
};

#define BALLOC_MEM_BLOCK_SIZE (sizeof(struct balloc_mem_block))
#define BALLOC_POOL_SIZE (sizeof(struct balloc_mem_block) * BALLOC_BLOCK_NUM)

uint8_t balloc_mem_pool[BALLOC_POOL_SIZE];

void  balloc_init() {
	struct balloc_mem_block mem_init = {
		{{0}, {BALLOC_PLATFORM_PREFIX_CANARY}},
		{0},
		{BALLOC_PLATFORM_POSTFIX_CANARY}
	};
	int n;

	for (n = 0; n != BALLOC_BLOCK_NUM; ++n)
		*((struct balloc_mem_block*) &balloc_mem_pool[n * BALLOC_MEM_BLOCK_SIZE]) = mem_init;
}

void* balloc_alloc() {
	int n;
	struct balloc_mem_block *block = (struct balloc_mem_block*) &balloc_mem_pool;

	for (n = 0; n != BALLOC_BLOCK_NUM; ++n) {
		if (balloc_platform_compare_and_set(&block[n].hdr.state.in_use, 0, n + 1)) {
			assert(block[n].hdr.state.in_use == n + 1);
			return (void *) block[n].block;
		}
	}

	return (void *) BALLOC_ERROR;
}

int   balloc_free(void **mem) {
	struct balloc_mem_block *block;

	block = container_of(*mem, struct balloc_mem_block, block);

	if (block->hdr.prefix.canary != BALLOC_PLATFORM_PREFIX_CANARY ||
		block->postfix.canary != BALLOC_PLATFORM_POSTFIX_CANARY ||
		block->hdr.state.in_use == 0) {
		return BALLOC_ERROR;
	}

	block->hdr.state.in_use = 0;
	*mem = NULL;

	return BALLOC_SUCCES;
}

#undef container_of
#undef member_type
