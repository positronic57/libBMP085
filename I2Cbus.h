/*
 * BMP085 library
 * I2Cbus.h
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

#ifndef I2CBUS_H_
#define I2CBUS_H_

#define ERROR_OPEN_I2C_BUS 1
#define ERROR_CLOSE_I2C_BUS 2
#define ERROR_I2C_READ_FAILED 3
#define ERROR_I2C_WRITE_FAILED 4


int openI2CBus(int *bus,char * device);
int closeI2CBus(int *bus);
int I2CSensor_Read(int *bus,unsigned char I2CAddress,unsigned char registry,unsigned char *buffer,int size);
int I2CSensor_Write(int *bus,unsigned char I2CAddress,unsigned char registry,unsigned char value);
void tDelay(long interval);

#endif /* I2CBUS_H_ */
