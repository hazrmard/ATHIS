/*
 * io.h
 *
 *  Created on: Nov 27, 2017
 *      Author: esdev
 */

#ifndef INC_IO_H_
#define INC_IO_H_


#include <pthread.h>
#include <buffer.h>

typedef int PIN;

typedef struct {
	pthread_mutex_t lock;			// lock that protects the conditional variable
	pthread_cond_t	cond;			// conditional variable for detection flag
	int detection;					// flag indicating detection
	pthread_t th_pread, th_detect;	// handles for pin reading and detection threads
	struct timespec ts;				// contains pin sampling rate information
	PIN pin;						// handle to the pin being read
	Buffer buff;					// Buffer object containing read samples passed b/w read/detect
} PERIODIC;


int read_pin(PIN pin);

void init_periodic_read(PERIODIC *p);

void *_reader(void *args);


#endif /* INC_IO_H_ */
