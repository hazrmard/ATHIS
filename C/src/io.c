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
#include <buffer.h>

char *pins[NUMAIN] = {	AIN0,	// P9.39
						AIN1,	// P9.40
						AIN2,	// P9.37
						AIN3,	// P9.38
						AIN4,	// P9.33
						AIN5,	// P9.36
						AIN6	// P9.35
					};


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
	pthread_create(&p->th_pread, NULL, _reader, p);
}

void *_reader(void *args) {
#ifdef TEST
	printf("Reader thread running...\n");
#endif
	PERIODIC *p = (PERIODIC *) args;
	int level;
	int i;
	while (1) {
		level = read_pin(p->pin);
		enqueue(&p->buff, level);
		nanosleep(&p->ts, NULL);
		++i;
	}
	return NULL;
}
