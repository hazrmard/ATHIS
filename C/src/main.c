/*
 * main.c
 *
 *  Created on: Nov 5, 2017
 *      Author: Ibrahim Ahmed
 */


#include <stdio.h>
#include <pthread.h>
#include <config.h>
#include <io.h>

int main(void) {
	int i;
	for (i=0; i<NUMAIN; i++) {
		printf("AIN%1d:\t%4d\n", i, read_pin(i));
	}
	return 0;
}
