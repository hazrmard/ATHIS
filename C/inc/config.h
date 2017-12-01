/*
 * config.h
 *
 *  Created on: Nov 27, 2017
 *      Author: Ibrahim Ahmed
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#define AINROOT "/sys/bus/iio/devices/iio:device0/"
#define AIN0 AINROOT "in_voltage0_raw"
#define AIN1 AINROOT "in_voltage1_raw"
#define AIN2 AINROOT "in_voltage2_raw"
#define AIN3 AINROOT "in_voltage3_raw"
#define AIN4 AINROOT "in_voltage4_raw"
#define AIN5 AINROOT "in_voltage5_raw"
#define AIN6 AINROOT "in_voltage6_raw"

#define NUMAIN 7				// number of analog input pins
extern char *pins[NUMAIN];		// declares a global array of pin addresses defined in io.c

#define OUTPIN 7				// pin number of the digital output pin used for detection (P9.42)
#define INPIN 0				 	// index of analog pin from pins array defined in io.c

#ifdef TEST

#define PERIOD 100000000			// duration (ns) between  consecutive samplings (for TESTING)
#define THRESH 0.1				// correlation threshold at which to signal detection (for TESTING)
#define NSAMPLES 32				// number of pin readings per sample
#define TAIL 5					// number of prior average readings to store
#define ALERTDURATION 1000000000	// duration (ns) of detection alert

#else

#define PERIOD 1000000			// duration (ns) between  consecutive samplings (for USE)
#define THRESH 0.1				// correlation threshold at which to signal detection (for USE)
#define NSAMPLES 20				// number of pin readings per sample
#define TAIL 10					// number of prior average readings to store
#define ALERTDURATION 1000000000	// duration (ns) of detection alert

#endif

#define BILLION 1000000000

#endif /* INC_CONFIG_H_ */
