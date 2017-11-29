/*
 * buffer.c
 *
 *  Created on: Nov 28, 2017
 *      Author: Ibrahim Ahmed
 */

#include <stdio.h>
#include <stdlib.h>
#include <buffer.h>


void buffer_init(Buffer *b, int N) {
	b->q = malloc(N * sizeof(int));
	b->N = N;
	b->n = 0;
	b->w = 0;
	b->r = 0;
	pthread_mutex_init(&b->lock, NULL);
	pthread_cond_init(&b->cond, NULL);
}

void buffer_destroy(Buffer *b) {
	free(b->q);
	pthread_cond_destroy(&b->cond);
	pthread_mutex_destroy(&b->lock);
}

void enqueue(Buffer *b, int value) {
	pthread_mutex_lock(&b->lock);
	while (b->n >= b->N) {
		pthread_cond_wait(&b->cond, &b->lock);
	}
	b->q[b->w] = value;
	b->w = (b->w+1) % b->N;
	b->n++;
	pthread_cond_broadcast(&b->cond);
	pthread_mutex_unlock(&b->lock);
}

void dequeue(Buffer *b, int values[]) {
	pthread_mutex_lock(&b->lock);
	while (b->n < b->N) {
		pthread_cond_wait(&b->cond, &b->lock);
	}
	int i;
	for (i=0; i<b->N; i++) {
		values[i] = b->q[i];
	}
	b->r = 0;
	b->n = 0;
	pthread_cond_broadcast(&b->cond);
	pthread_mutex_unlock(&b->lock);
}
