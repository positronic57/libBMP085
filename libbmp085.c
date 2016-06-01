/*
 * BMP085 library
 * libbmp085.c
 *
 * Copyright (c) 2014  Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 */

/** @file libbmp085.c
 *  @brief Implements the functions defined in the header file libbmp085.h.
 *
 *  @author Goce Boshkovski
 */
#include "libbmp085.h"

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "I2Cbus.h"

const long BMP085_PressureConversionTime[]={ 5000000L, 8000000L, 14000000L, 26000000L };

/* Sensor initialization. */
int BMP085_initSensor(BMP085 *sensor,int *I2Cbus,unsigned char I2CAddress,overSampling oss)
{
	sensor->I2CBus=*I2Cbus;
	sensor->oss=oss;
	sensor->I2CAddress=I2CAddress;
	return I2CSensor_Read(&(sensor->I2CBus),sensor->I2CAddress,BMP085_CALIBRATION_TABLE,sensor->calibrationCoeficients,22);
}

/* Starts a temperature and pressure sampling. */
int BMP085_takeMeasurement(BMP085 *sensor)
{
	long rawTemperature,temperature = 0;
    long rawPressure = 0, pressure = 0;

    long x1, x2, x3, b3, b5, b6 = 0;
    unsigned long b4, b7 = 0;

    short ac1 = createSword(sensor->calibrationCoeficients[0],sensor->calibrationCoeficients[1]);
    short ac2 = createSword(sensor->calibrationCoeficients[2],sensor->calibrationCoeficients[3]);
    short ac3 = createSword(sensor->calibrationCoeficients[4],sensor->calibrationCoeficients[5]);
    unsigned short ac4 = createUword(sensor->calibrationCoeficients[6],sensor->calibrationCoeficients[7]);
    unsigned short ac5 = createUword(sensor->calibrationCoeficients[8],sensor->calibrationCoeficients[9]);
    unsigned short ac6 = createUword(sensor->calibrationCoeficients[10],sensor->calibrationCoeficients[11]);
    short b1 = createSword(sensor->calibrationCoeficients[12],sensor->calibrationCoeficients[13]);
    short b2 = createSword(sensor->calibrationCoeficients[14],sensor->calibrationCoeficients[15]);
    short mc = createSword(sensor->calibrationCoeficients[18],sensor->calibrationCoeficients[19]);
    short md = createSword(sensor->calibrationCoeficients[20],sensor->calibrationCoeficients[21]);

    // Send the command to start the temperature measurement.
    if (I2CSensor_Write(&(sensor->I2CBus),sensor->I2CAddress,BMP085_CONTROL_REG,BMP085_START_TEMPERATURE_MEASUREMENT))
    	return 1;

    // wait 4.5ms and then read the temperature raw value
    tDelay(BMP085_PressureConversionTime[sensor->oss]);

    // Read the temperature raw value
    if (I2CSensor_Read(&(sensor->I2CBus),sensor->I2CAddress,BMP085_DATA_REG_MSB,sensor->rawTemperatureData,2))
    	return 1;
    rawTemperature = (long)((sensor->rawTemperatureData[0]<<8)+sensor->rawTemperatureData[1]);

	// Send the command to start the pressure measurement.
    if (I2CSensor_Write(&(sensor->I2CBus),sensor->I2CAddress,BMP085_CONTROL_REG,(BMP085_START_PRESSURE_MEASUREMENT+(sensor->oss<<6))))
    	return 1;

	// Wait for the pressure conversion to be done.
	tDelay(BMP085_PressureConversionTime[sensor->oss]);

	// Read the pressure raw value.
	if (I2CSensor_Read(&(sensor->I2CBus),sensor->I2CAddress,BMP085_DATA_REG_MSB,sensor->rawPressureData,2))
		return 1;
    if (I2CSensor_Read(&(sensor->I2CBus),sensor->I2CAddress,BMP085_DATA_REG_XLASB,&(sensor->rawPressureData[2]),1))
    	return 1;
	rawPressure = ((sensor->rawPressureData[0]<<16) + (sensor->rawPressureData[1]<<8) + sensor->rawPressureData[2])>>(8-sensor->oss);

	//calculate the real temperature value
    x1 = ((rawTemperature - ac6)*ac5)>>15;
    x2 = (mc << 11)/(x1 + md);
    b5 = x1 + x2;
    temperature = (b5 + 8)>>4;
    sensor->temperature = temperature * 0.1;

	//calculate the real pressure value in Pa
	b6 = b5 - 4000;
	x1 = (b2 * ((b6 * b6) >> 12)) >> 11;
	x2 = (ac2 * b6) >> 11;
	x3 = x1 + x2;
	b3 = ((( ac1 * 4 + x3 ) << sensor->oss) + 2 ) / 4;
	x1 = (ac3 * b6) >> 13;
	x2 = (b1 * ((b6 * b6) >> 12)) >> 16;
	x3 = ((x1+x2)+2) >> 2;
	b4 = (ac4 * (unsigned long)(x3 + 32768)) >> 15;
	b7 = ((unsigned long)rawPressure-b3)*(50000>>sensor->oss);
	if (b7<0x80000000)
		pressure=(b7*2)/b4;
	else
		pressure=(b7/b4)*2;
	x1=(pressure >> 8)* (pressure >> 8);
	x1=(x1*3038)>>16;
	x2=(-7357*pressure)>>16;
	pressure+=((x1+x2+3791)>>4);
	sensor->pressure = pressure;

	return 0;
}

/* Prints the calibration table of the sensor on the standard output. */
void BMP085_printCalibrationTable(BMP085 *sensor)
{
	const char *calCoefName[] = {"AC1","AC2","AC3","AC4","AC5","AC6","B1","B2","MB","MC","MD"};
	unsigned char i;

	for(i=0;i<11;i++)
	{
		switch (i)
		{
			case 3:
			case 4:
			case 5:
				printf("%s = \t%d\n",calCoefName[i],createUword(sensor->calibrationCoeficients[i*2],sensor->calibrationCoeficients[i*2+1]));
				break;
			default:
				printf("%s = \t%d\n",calCoefName[i],createSword(sensor->calibrationCoeficients[i*2],sensor->calibrationCoeficients[i*2+1]));
		}
	}
	printf("\n");

}

/* Calculates the relative altitude changes based on pressure differences at two measurement points. */
int BMP085_Altitude(double lastPressureReading,double baseLinePressure)
{
	return round(44330*(1-pow((lastPressureReading/baseLinePressure),(1/5.255))));
}

