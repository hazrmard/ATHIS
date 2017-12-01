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
#include <detect.h>
#include <libsoc_gpio.h>

int main(void) {

#ifdef TEST
		printf("DEBUG\n");
#else
		printf("RELEASE\n");
#endif
	// acquire output pin for signalling
	gpio *outpin = libsoc_gpio_request(OUTPIN, LS_GPIO_SHARED);
	if (outpin == NULL) {
		printf("Could not acquire output pin.\n");
		exit(-1);
	}
	libsoc_gpio_set_direction(outpin, OUTPUT);
	if (libsoc_gpio_get_direction(outpin) != OUTPUT)
	{
		printf("Failed to set pin direction to output.\n");
		exit(-1);
	}
	struct timespec ts_alert = {ALERTDURATION / BILLION, ALERTDURATION % BILLION};

#ifdef TEST
	printf("Testing analog pin access: \n");
	int i;
	for (i=0; i<NUMAIN; i++) {
		printf("AIN%1d:\t%4d\n", i, read_pin(i));
	}

	printf("\nTesting periodic pin read: \n");
#endif

	PERIODIC p;
	p.pin = INPIN;
	p.ts.tv_sec = (int) (PERIOD / BILLION);
	p.ts.tv_nsec = PERIOD % BILLION;
	buffer_init(&p.buff, NSAMPLES);

	// start periodic pin sampling thread
	init_periodic_read(&p);

#ifdef TEST
	int vals[NSAMPLES];
	int j = 0;
	for (j=0; j<10; j++) {
		dequeue(&p.buff, vals);
		printf("Periodic sample %d of 10: ", j+1);
		for (i=0; i<NSAMPLES; i++) {
			printf("%d ", vals[i]);
		}
		printf("\n");
	}
	printf("\nTesting detection:\n");
#endif

	// start detection algorithm thread
	init_detector(&p);

	// start waiting on detection
	while (1) {
		pthread_mutex_lock(&p.lock);
		while (p.detection == 0) {
			pthread_cond_wait(&p.cond, &p.lock);
		}
		p.detection = 0;
		libsoc_gpio_set_level(outpin, HIGH);		// set outpin high on detection
#ifdef TEST
		printf("\nDETECTION!\n");
#endif
		pthread_mutex_unlock(&p.lock);
		nanosleep(&ts_alert, NULL);					// outpin remains high for ALERTDURATION
		libsoc_gpio_set_level(outpin, LOW);			// reset outpin to low
	}

	pthread_join(p.th_pread, NULL);
	pthread_join(p.th_detect, NULL);

	return 0;
}
