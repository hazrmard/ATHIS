/*
 * io.h
 *
 *  Created on: Nov 27, 2017
 *      Author: esdev
 */

#ifndef INC_IO_H_
#define INC_IO_H_

#include <time.h>
#include <pthread.h>
#include <buffer.h>

typedef int PIN;

typedef struct {
	pthread_mutex_t lock;
	pthread_t th_pread, th_fourier;
	struct timespec ts;
	int enabled;
	PIN pin;
	Buffer buff;
} PERIODIC;

//PIN request_pin(int pin);

int read_pin(PIN pin);

//int release_pin(PIN pin);

void init_periodic_read(PERIODIC *p);

void end_periodic_read(PERIODIC *p);

void *_reader(void *args);


#endif /* INC_IO_H_ */
