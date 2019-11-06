#include <stdio.h>
#include "../src/balloc.h"

int main(void) {
	char *blocks[BALLOC_BLOCK_NUM];
	char *block, *block_prev = NULL;
	char *block_fail = NULL;
	int n;

	balloc_init();

	printf("check blocks alloc\n");
	for (n = 0; n != BALLOC_BLOCK_NUM; ++n) {
		block = balloc_alloc();
		if(block == block_prev)
			return 1;
		block_prev = block;
		blocks[n] = block;
	}

	printf("check alloc fail\n");
	block_fail = balloc_alloc();
	if (block_fail)
		return 1;

	printf("free one block\n");
	if (balloc_free((void **) &blocks[BALLOC_BLOCK_NUM/2]) != BALLOC_SUCCES || blocks[BALLOC_BLOCK_NUM/2]) {
		return 1;
	}

	printf("check one block alloc\n");
	blocks[BALLOC_BLOCK_NUM/2] = balloc_alloc();
	if (!blocks[BALLOC_BLOCK_NUM/2])
		return 1;

	printf("check all blocks free\n");
	for (n = 0; n != BALLOC_BLOCK_NUM; ++n) {
		if (balloc_free((void **) &blocks[n]) != BALLOC_SUCCES || blocks[n]) {
			return 1;
		}
	}

	printf("check blocks free fail\n");
	return  !(balloc_free((void **) &block) == BALLOC_ERROR) ||
		!(balloc_free((void **) &block_prev) == BALLOC_ERROR);
}
