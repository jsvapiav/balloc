#include <stdio.h>
#include "../src/balloc.h"

int main(void) {
	char *block;
	balloc_init();
	block = balloc_alloc();
	if (block == BALLOC_ERROR) {
		printf("Block addr: %d\n", (unsigned int) block);
		return 1;
	}
	printf("Check free\n");
	return !balloc_free(block);
}
