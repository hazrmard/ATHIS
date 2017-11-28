/*
 * io.c
 *
 *  Created on: Nov 12, 2017
 *      Author: esdev
 */


#include <stdio.h>
#include <config.h>


char *pins[NUMAIN] = {AIN0, AIN1, AIN2, AIN3, AIN4, AIN5};


int read_pin(int pin) {
	int val;
	int res;
	FILE *f = fopen(pins[pin], "r");
	if (f != NULL) {
		res = fscanf(f, "%d", &val);
		if (res == 0) {
			fclose(f);
			return -1;
		}
	}
	else {
		return -1;
	}
	return val;
}
