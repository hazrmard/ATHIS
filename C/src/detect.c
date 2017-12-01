/*
 * detect.c
 *
 *  Created on: Nov 30, 2017
 *      Author: Ibrahim Ahmed
 */


#include <math.h>
#include <config.h>
#include <detect.h>
#include <stdio.h>
#include <pthread.h>


void init_detector(PERIODIC *p) {
	pthread_create(&p->th_detect, NULL, _detector, p);
}

void _detector(void *arg) {
#ifdef TEST
	printf("Detector thread running...\n");
#endif

	PERIODIC *p = (PERIODIC *) arg;
	pthread_mutex_init(&p->lock, NULL);
	pthread_cond_init(&p->cond, NULL);
	p->detection = 0;

	int vals[NSAMPLES] = {0};		// stores a set of sampled pin readings
	double totals[TAIL][2] = {0};	// stores summed real and imaginary components of fourier transform
	double means[TAIL];				// stores mean fourier magnitudes for sets of samples
	double meanofmeans = 0;			// the average of the mean frequencies of sample sets;
	int tailmean = TAIL *  (TAIL + 1) / 2;	// average of 1,2,3...,TAIL
	double c, s, a, smt, sm, st;	// cos, sin, argument, covariance, std. dev, std. dev
	double dm, dt, corr;			// mean - meanofmeans, 1,2,3... - TAIL, correlation
	int curr = 0;					// current index of means buffer
	int i, j;						// indices

	while (1) {
		dequeue(&p->buff, vals);

		// take fourier transform. This is O(n^2).
		for (i=0; i<NSAMPLES; i++){
			totals[i][0] = 0;
			totals[i][1] = 0;
			for (j=0; j<NSAMPLES; j++) {
				a = 2*PI*i*j/NSAMPLES;
				c = cos(a);
				s = sin(a);
				totals[i][0] += vals[j] * c;
				totals[i][1] += vals[j] * s;
			}
		}
		// store average frequency for current samples
		curr = curr % TAIL;
		meanofmeans -= means[curr] / TAIL;
		means[curr] = 0;
		for (j=0; j<NSAMPLES; j++) {
			means[curr] += j * totals[j][0] * totals[j][0] + totals[j][1] * totals[j][1];
		}
		means[curr] /= NSAMPLES;
		meanofmeans += means[curr] / TAIL;
		++curr;

		// calculate correlation among means of current and prior sample sets
		smt = 0; sm=0; st=0;
		for (j=0; j<TAIL; j++) {
			dt = (j - tailmean);
			dm = (means[j] - meanofmeans);
			smt += dt * dm;
			st += dt * dt;
			sm += dm * dm;
		}
		corr = smt / sqrt(st * sm);

		// signal on detection
		if (corr >= THRESH) {
#ifdef TEST
			printf("Corr: %10.3f\n", corr);
#endif
			pthread_mutex_lock(&p->lock);
			p->detection = 1;
			pthread_cond_broadcast(&p->cond);
			pthread_mutex_unlock(&p->lock);
		}
	}
}
