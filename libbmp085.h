/*
 * BMP085 library
 * libbmp085.h
 *
 * Copyright (c) 2014  Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 */

#ifndef LIBBMP085_H_
#define LIBBMP085_H_

#define createUword(MSB,LSB) (unsigned short)((MSB << 8) | LSB)
#define createSword(MSB,LSB) (short)((MSB << 8) | LSB)

#define STARTTEMPMEAS 0x2EF4
#define CALTABLEADDR 0xAA
#define TEMPADDR 0xF6

typedef enum oversampling
{
	ultraLowPower = 0,
	standard,
	highResolution,
	ultraHighResolution
} overSampling;

typedef struct bmp085
{
	char i2cAddress;
	unsigned char calibrationCoeficients[22];
	float temperature;
	long pressure;
	overSampling oss;
} BMP085;


/*
 * The function reads the calibration table of BMP085.
 * It returns 1 in case of communication error or 0
 * for successful data retrieval. Call this function
 * before taking the measurement.
 *
 */
int readBMP085CalibrationTable(int, BMP085 *);

/*
 * Read the current temperature and pressure from the sensor.
 * The function returns 0 in case of successful reading, or 1
 * if there is error during the communication with the sensor.
 * readBMP085CalibrationTable function must be called before
 * taking the measurement.
 */
int BMP085takeMeasurement(int, BMP085 *);

/*
 * The function prints the calibration table of the BMP085 sensor.
 * readBMP085CalibrationTable must be called first.
 */
void printBMP085CalibrationTable(BMP085 *);

/*
 * Establish connection with the BMP085 server.
 * Returns 0 for successful connection, 1 for error.
 */
int connect2BMP085(int *,char *,char);

#endif /* LIBBMP085_H_ */
