#include <stdio.h>
#include <pthread.h>
#include "../src/balloc.h"

#define N_THREADS (3)
#define N_OF_CIRLCES (5)

typedef struct thread_ags {
	int id;
	char *block;
} thread_args_t;

static pthread_barrier_t barrier;

void *thread(void *args) {
	int n;
	int status;
	int id = ((thread_args_t *) args)->id;
	char *block = ((thread_args_t *) args)->block;

	n = 0;
	while (n < N_OF_CIRLCES) {

		status = pthread_barrier_wait(&barrier);
		n++;
	}
	if (status == PTHREAD_BARRIER_SERIAL_THREAD) {
		pthread_barrier_destroy(&barrier);
	}

	return NULL;
}

int main(void) {
	char *blocks[BALLOC_BLOCK_NUM];
	char *t_blocks[N_THREADS];
	pthread_t threads[N_THREADS];
	thread_args_t args[N_THREADS];
	int n;
	int status;

	if (pthread_barrier_init(&barrier, NULL, N_THREADS + 1))
		return 1;

	balloc_init();

	printf("check blocks alloc\n");
	for (n = 1; n != BALLOC_BLOCK_NUM-1; ++n) {
		blocks[n] = balloc_alloc();
		if(!blocks[n])
			return 1;
	}

	for (n = 0; n != N_THREADS; ++n) {
		args[n].id = n;
		args[n].block = t_blocks[n];
		if (pthread_create(&threads[n], NULL, thread, (void *) &args[n]))
			return 1;
	}

	n = 0;
	while (n < N_OF_CIRLCES) {

		status = pthread_barrier_wait(&barrier);
		n++;
	}
	if (status == PTHREAD_BARRIER_SERIAL_THREAD) {
		pthread_barrier_destroy(&barrier);
	}

}

