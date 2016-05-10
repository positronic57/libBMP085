/*
 * BMP085 library
 * I2Cbus.c
 *
 * Created on: May 9, 2016
 * Author: Goce Boshkovski
 *
 * Copyright (c) 2016  Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 */

#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <fcntl.h>
#include "I2Cbus.h"

int openI2CBus(int *bus,char * device)
{
        *bus = open(device, O_RDWR);
        if (*bus<0)
	        return ERROR_OPEN_I2C_BUS;

        return 0;
}

int closeI2CBus(int *bus)
{
	if (*bus)
		return close(*bus);
	else
		return ERROR_CLOSE_I2C_BUS;

}

int I2CSensor_Read(int *bus,unsigned char I2CAddress,unsigned char registry,unsigned char *buffer,int size)
{
	/*Select the sensor on the I2C bus with an address as a slave device.*/
	if (ioctl(*bus,I2C_SLAVE,I2CAddress)<0)
		return ERROR_I2C_READ_FAILED;

	/* Place the registry address on I2C bus */
	if (write(*bus,&registry,1)!=1)
		return ERROR_I2C_READ_FAILED;

	/* Read the data from the I2C bus */
	if (read(*bus,buffer,size)!=size)
		return ERROR_I2C_READ_FAILED;

	return 0;
}

int I2CSensor_Write(int *bus,unsigned char I2CAddress,unsigned char registry,unsigned char value)
{
	unsigned char tbuffer[2] = { registry, value };

	/*Select the sensor on the I2C bus with an address as a slave device.*/
	if (ioctl(*bus,I2C_SLAVE,I2CAddress)<0)
		return ERROR_I2C_WRITE_FAILED;

	/* Place the register address and its value on I2C bus */
	if (write(*bus,tbuffer,2)!=2)
		return ERROR_I2C_WRITE_FAILED;

	return 0;
}

void tDelay(long interval)
{
    struct timespec timer;

    timer.tv_sec = 0;
    timer.tv_nsec = interval;

    nanosleep(&timer, NULL);
}
