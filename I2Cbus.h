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

 /**
  * @file I2Cbus.h
  * @brief
  * Header file part of libBMP085 library. It contains the prototypes of
  * functions available in the library, definitions of macros
  * and constants.
  *
  * @author Goce Boshkovski
  * @date May 9, 2016
  * @copyright GNU General Public License v2.
  *
  */

#ifndef I2CBUS_H_
#define I2CBUS_H_

/** \defgroup I2C_BUS_ERROR_CODES I2C error codes. */
/* @{ */
#define ERROR_OPEN_I2C_BUS 1
#define ERROR_CLOSE_I2C_BUS 2
#define ERROR_I2C_READ_FAILED 3
#define ERROR_I2C_WRITE_FAILED 4
/* @} */

/** \defgroup SENSE_HAT_FUNC Sense HAT functions */
/* @{ */

/**
 * @brief Opens the device file for accessing the I2C bus.
 *
 * @param [in,out] bus file descriptor assigned after successful opening of the I2C device file for R/W access.
 * @param [in] device name of the device file that represents the I2C interface on the system.
 * @return 0 for successful access to the I2C interface, error code ERROR_OPEN_I2C_BUS in case of a  failure.
 */
int openI2CBus(int *bus,char * device);

/**
 * @brief Calls close() function for closing the access to the I2C interface.
 *
 * @param [in,out] bus file descriptor assigned after a successful opening of the I2C device file.
 * @return 0 for success, ERROR_CLOSE_I2C_BUS code for failure.
 */
int closeI2CBus(int *bus);

/**
 * @brief Reads data from the sensor via I2C bus.
 *
 * @param [in] bus	file descriptor of the opened I2C device file.
 * @param [in] I2CAddress address of the sensor on the I2C bus.
 * @param [in] registry address of the registry from the sensor.
 * @param [in,out] buffer buffer for storing the data retrieved from the sensor.
 * @param [in] size number of bytes for reading.
 * @return 0 for successful data transfer, ERROR_I2C_READ_FAILED code for failure.
 */
int I2CSensor_Read(int *bus,unsigned char I2CAddress,unsigned char registry,unsigned char *buffer,int size);

/**
 * @data Sends data to the sensor by writing data on the I2C bus.
 *
 * @param [in] bus	file descriptor of the opened I2C device file.
 * @param [in] I2CAddress address of the sensor on the I2C bus.
 * @param [in] registry address of the registry from the sensor.
 * @param [in,out] value the new registry value.
 * @return 0 for successful data transfer, ERROR_I2C_WRITE_FAILED code for failure.
 */
int I2CSensor_Write(int *bus,unsigned char I2CAddress,unsigned char registry,unsigned char value);

/**
 * @brief A time delay function that introduces delays in [ms].
 *
 * Used during the temperature/pressure measurement.
 * @param interval defines the duration of the time delay.
 */
void tDelay(long interval);

/* @} */

#endif /* I2CBUS_H_ */
