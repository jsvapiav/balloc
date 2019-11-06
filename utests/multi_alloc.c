#include <stdio.h>
#include "../src/balloc.h"

int main(void) {
	char *blocks[BALLOC_BLOCK_NUM];
	char *block, *block_prev = (void *) BALLOC_ERROR;
	int n;

	balloc_init();
	for (n = 0; n != BALLOC_BLOCK_NUM; ++n) {
		block = balloc_alloc();
		if(block == block_prev)
			return 1;
		block_prev = block;
		blocks[n] = block;
	}

	for (n = 0; n != BALLOC_BLOCK_NUM; ++n) {
		if (balloc_free((void **) &blocks[n]) != BALLOC_SUCCES || blocks[n]) {
			return 1;
		}
	}
	return  !(balloc_free((void **) &block) == BALLOC_ERROR) ||
		!(balloc_free((void **) &block_prev) == BALLOC_ERROR);
}
