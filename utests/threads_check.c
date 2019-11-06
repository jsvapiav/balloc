#include <stdio.h>
#include <pthread.h>
#include "../src/balloc.h"
#ifdef __APPLE__
#include "pthread_barrier.h"
#endif

#define N_THREADS (10)
#define N_OF_CIRLCES (15)

typedef struct thread_ags {
	int id;
	char **block;
} thread_args_t;

static pthread_barrier_t barrier0, barrier1;

void *thread(void *args) {
	int n;
	int status0, status1;
	int id = ((thread_args_t *) args)->id;
	char **block = ((thread_args_t *) args)->block;

	n = 0;
	while (n < N_OF_CIRLCES) {
		*block = balloc_alloc();
		if (*block)
			*block[0] = id;

		status0 = pthread_barrier_wait(&barrier0);
		status1 = pthread_barrier_wait(&barrier1);
		n++;
	}
	if (status0 == PTHREAD_BARRIER_SERIAL_THREAD) {
		pthread_barrier_destroy(&barrier0);
	}

	if (status1 == PTHREAD_BARRIER_SERIAL_THREAD) {
		pthread_barrier_destroy(&barrier1);
	}

	return NULL;
}

int main(void) {
	char *blocks[BALLOC_BLOCK_NUM];
	char *t_blocks[N_THREADS];
	pthread_t threads[N_THREADS];
	thread_args_t args[N_THREADS];
	int n;
	int status0, status1;

	if (pthread_barrier_init(&barrier0, NULL, N_THREADS + 1))
		return 1;

	if (pthread_barrier_init(&barrier1, NULL, N_THREADS + 1))
		return 1;

	balloc_init();

	for (n = 3; n != BALLOC_BLOCK_NUM-5; ++n) {
		blocks[n] = balloc_alloc();
		if(!blocks[n])
			return 1;
	}

	for (n = 0; n != N_THREADS; ++n) {
		args[n].id = n + 1;
		args[n].block = &t_blocks[n];
		if (pthread_create(&threads[n], NULL, thread, (void *) &args[n]))
			return 1;
	}

	n = 0;
	while (n < N_OF_CIRLCES) {
		status0 = pthread_barrier_wait(&barrier0);

		int i;
		int k = 0;
		for (i = 0; i != N_THREADS; ++i) {
			if (t_blocks[i] && t_blocks[i][0] == i + 1) {
				t_blocks[i][0] = 0;
				balloc_free((void **) &t_blocks[i]);
				k++;
			}
		}

		if (k != (N_THREADS - 2))
			return 1;

		status1 = pthread_barrier_wait(&barrier1);

		n++;
	}

	if (status0 == PTHREAD_BARRIER_SERIAL_THREAD) {
		pthread_barrier_destroy(&barrier0);
	}
	if (status1 == PTHREAD_BARRIER_SERIAL_THREAD) {
		pthread_barrier_destroy(&barrier0);
	}

	return 0;

}

