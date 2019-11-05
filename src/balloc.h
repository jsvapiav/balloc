#ifndef BALLOC_H


#define BALLOC_BLOCK_SIZE (16)
#define BALLOC_BLOCK_NUM (64)

enum balloc_error {
	BALLOC_ERROR  = 0,
	BALLOC_SUCCES = 1
};

void  balloc_init();
void* balloc_alloc();
int   balloc_free(void *mem);


#define BALLOC_H
#endif
