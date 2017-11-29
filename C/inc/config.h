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

#define NUMAIN 6

#define BILLION 1000000000
#define PERIOD 1000000
#define NSAMPLES 10

extern char *pins[NUMAIN];

#endif /* INC_CONFIG_H_ */
