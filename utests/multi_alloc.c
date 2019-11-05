#include <stdio.h>
#include "../src/balloc.h"

int main(void) {
        char *block, *block_prev = (void *) BALLOC_ERROR;
	int n;

        balloc_init();
	for (n = 0; n != BALLOC_BLOCK_NUM; ++n) {
        	block = balloc_alloc();
		if(block == block_prev)
			return 1;
		block_prev = block;
	}

	for (n = 0; n != BALLOC_BLOCK_NUM; ++n) {
		;;
	}
        return !balloc_free(block) && !balloc_free(block_prev);
}
