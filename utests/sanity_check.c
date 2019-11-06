#include <stdio.h>
#include "../src/balloc.h"

int main(void) {
	char *block;
	balloc_init();
	block = balloc_alloc();
	if (block == BALLOC_ERROR) {
		return 1;
	}
	return !balloc_free((void **) &block) || block;
}
