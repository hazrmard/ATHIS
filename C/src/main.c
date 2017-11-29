/*
 * main.c
 *
 *  Created on: Nov 5, 2017
 *      Author: Ibrahim Ahmed
 */


#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <config.h>
#include <io.h>
#include <buffer.h>

int main(void) {
#ifdef TEST

	printf("Testing pin access: \n");
	int i;
	for (i=0; i<NUMAIN; i++) {
		printf("AIN%1d:\t%4d\n", i, read_pin(i));
	}

	printf("\nTesting periodic pin read: \n");
	PERIODIC p;
	p.pin = 0;
	p.ts.tv_sec = (int) (PERIOD / BILLION);
	p.ts.tv_nsec = PERIOD % BILLION;
	p.enabled = 1;

	int vals[NSAMPLES];
	init_periodic_read(&p);
	int j = 0;
	for (j=0; j<3; j++) {
		dequeue(&p.buff, &vals);
		int i;
		for (i=0; i<NSAMPLES; i++) {
			printf("%d ", vals[i]);
		}
		printf("\n\n");
	}

	pthread_join(p.th_pread, NULL);

	return 0;

#else

	printf("This is release configuration.\n");

#endif
}
