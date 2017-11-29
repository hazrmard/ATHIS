/*
 * io.c
 *
 *  Created on: Nov 12, 2017
 *      Author: esdev
 */


#include <stdio.h>
#include <time.h>
#include <config.h>
#include <io.h>

char *pins[NUMAIN] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5};


int read_pin(PIN pin) {
	int val;
	int res;
	FILE *f = fopen(pins[pin], "r");
	if (f == NULL) return -1;
	res = fscanf(f, "%d", &val);
	fclose(f);
	if (res == 0) return -1;
	return val;
}

void init_periodic_read(PERIODIC *p) {
	buffer_init(&p->buff, NSAMPLES);
	pthread_create(&p->th_pread, NULL, _reader, p);
}

void end_periodic_read(PERIODIC *p) {
	pthread_mutex_lock(&p->lock);
	p->enabled = 0;
	pthread_mutex_unlock(&p->lock);

	pthread_mutex_lock(&(p->buff).lock);
	pthread_cond_broadcast(&(p->buff).cond);
	pthread_mutex_unlock(&(p->buff).lock);
}

void *_reader(void *args) {
	PERIODIC *p = (PERIODIC *) args;
	int level;
	int i;
	while (1) {
		pthread_mutex_lock(&p->lock);
		if (p->enabled == 0) break;
		pthread_mutex_unlock(&p->lock);

		level = read_pin(p->pin);
		enqueue(&p->buff, level);
//		printf("%d:\t%d\n", i, level);
		nanosleep(&p->ts, NULL);
		++i;
	}
	return NULL;
}
