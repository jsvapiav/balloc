#include "balloc.h"
#include <assert.h>

#define BALLOC_MEM_BLOCK_SIZE (sizeof(struct balloc_mem_block))
#define BALLOC_POOL_SIZE (sizeof(struct balloc_mem_block) * BALLOC_BLOCK_NUM)

int     balloc_allocated;
uint8_t balloc_mem_pool[BALLOC_POOL_SIZE];

void  balloc_init() {
	struct balloc_mem_block mem_init = {
		{0, {BALLOC_PREFIX_CANARY}},
		{0},
		{BALLOC_POSTFIX_CANARY}
	};
	int n;

	balloc_allocated = 0;

	for (n = 0; n != BALLOC_BLOCK_NUM; ++n)
		*((struct balloc_mem_block*) &balloc_mem_pool[n * BALLOC_MEM_BLOCK_SIZE]) = mem_init;
}

void* balloc_alloc() {
	if (balloc_allocated == BALLOC_BLOCK_NUM)
		return (void *) BALLOC_ERROR;

	assert (balloc_allocated <= BALLOC_BLOCK_NUM);

	return (void *) BALLOC_SUCCES;
}

int   balloc_free(void *block) {
	if (balloc_allocated == 0)
		return BALLOC_ERROR;

	return BALLOC_SUCCES;
}
