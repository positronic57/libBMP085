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

#define BMP085_CALIBRATION_TABLE 0xAA
#define BMP085_DATA_REG_MSB 0xF6
#define BMP085_DATA_REG_LSB 0xF7
#define BMP085_DATA_REG_XLASB 0xF8
#define BMP085_CONTROL_REG 0xF4

#define BMP085_START_TEMPERATURE_MEASUREMENT 0x2E
#define BMP085_START_PRESSURE_MEASUREMENT 0x34

typedef enum oversampling
{
	ultraLowPower = 0,
	standard,
	highResolution,
	ultraHighResolution
} overSampling;

typedef struct bmp085
{
	char I2CAddress;
	int I2CBus;
	unsigned char calibrationCoeficients[22];
	unsigned char rawPressureData[3];
	unsigned char rawTemperatureData[2];
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
int BMP085_initSensor(BMP085 *sensor,int *I2Cbus,unsigned char I2CAddress,overSampling oss);


/*
 * Read the current temperature and pressure from the sensor.
 * The function returns 0 in case of successful reading, or 1
 * if there is error during the communication with the sensor.
 * readBMP085CalibrationTable function must be called before
 * taking the measurement.
 */
int BMP085_takeMeasurement(BMP085 *sensor);

/*
 * The function prints the calibration table of the BMP085 sensor.
 * readBMP085CalibrationTable must be called first.
 */
void BMP085_printCalibrationTable(BMP085 *sensor);

#endif /* LIBBMP085_H_ */
