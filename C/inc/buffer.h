/*
 * buffer.h
 *
 *  Created on: Nov 28, 2017
 *      Author: Ibrahim Ahmed
 */

#ifndef INC_BUFFER_H_
#define INC_BUFFER_H_

#include <pthread.h>
#include <config.h>

typedef struct Buffer {
	int *q;					// array of integer values
	int r;					// index of Element at front of queue
	int w;					// index where new Element is written
	int N;					// size of queue
	int n;					// number of Elements enqueued
	pthread_mutex_t lock;
	pthread_cond_t cond;
} Buffer;

void buffer_init(Buffer *b, int N);

void buffer_destroy(Buffer *b);

void enqueue(Buffer *b, int value);

void dequeue(Buffer *b, int values[]);

#endif /* INC_BUFFER_H_ */
