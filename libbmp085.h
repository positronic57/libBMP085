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

 /**
  * @file libbmp085.h
  * @brief
  * Header file part of libBMP085 library. It contains the prototypes of
  * functions available in the library, definitions of macros
  * and constants.
  *
  * @author Goce Boshkovski
  * @copyright GNU General Public License v2.
  *
  */

#ifndef LIBBMP085_H_
#define LIBBMP085_H_

/** \defgroup libMacros libBMP085 library macros */
/* @{ */
/**
 * @def createUword(MSB,LSB)
 * Creates a 16-bit long unsigned word from
 * \a as most significant byte and \a as least significant byte.
 */
#define createUword(MSB,LSB) (unsigned short)((MSB << 8) | LSB)
/**
 * @def createSword(MSB,LSB)
 * Creates a 16-bit long signed word from
 * \a as most significant byte and \a as least significant byte.
 */
#define createSword(MSB,LSB) (short)((MSB << 8) | LSB)
/* @} */

/** \defgroup SENSOR_ADDR_DEF Bosch BMP085 sensor address map */
/* @{ */
#define BMP085_CALIBRATION_TABLE 0xAA
#define BMP085_DATA_REG_MSB 0xF6
#define BMP085_DATA_REG_LSB 0xF7
#define BMP085_DATA_REG_XLASB 0xF8
#define BMP085_CONTROL_REG 0xF4
/* @} */

/** \defgroup SENSOR_CMD Bosch BMP085 commands (CONTROL register values). */
/* @{ */
#define BMP085_START_TEMPERATURE_MEASUREMENT 0x2E
#define BMP085_START_PRESSURE_MEASUREMENT 0x34
/* @} */

/**
 * @brief Barometric pressure measurement modes.
 */
typedef enum oversampling
{
	ultraLowPower = 0,
	standard,
	highResolution,
	ultraHighResolution
} overSampling;

/**
 * @brief Represents Bosch BMP085 sensor readings and configuration.
 */
typedef struct bmp085
{
	char I2CAddress;	/**< I2C address of the Bosch BMP085 sensor.*/
	int I2CBus;	/**< File descriptor for accessing I2C bus.*/
	unsigned char calibrationCoeficients[22];	/**< Bosch BMP085 calibration table.*/
	unsigned char rawPressureData[3]; /**< Buffer for the raw pressure data reading from the sensor.*/
	unsigned char rawTemperatureData[2];	/**< Buffer for the raw pressure data reading from the sensor.*/
	float temperature;	/**< Last temperature reading in degrees Celsius. */
	long pressure;	/**< Last barometric pressure reading in Pa. */
	overSampling oss;	/**< Bosch BMP085 sensor mode of operation for the pressure measurement. */
} BMP085;


/** \defgroup SENSE_HAT_FUNC Sense HAT functions */
/* @{ */

/**
 * @brief Sensor initialization.
 *
 * The function assigns the file descriptor for accessing I2C bus to the sensor.
 * Defines the I2C address and the mode of operation.
 * After that it reads the sensor calibration table used later on for
 * calculating the temperature and pressure values.
 * Call this function first, before any other function related to the sensor.
 *
 * @param[in,out] sensor pointer to the structure that represents the sensor.
 * @param[in] I2Cbus pointer to the file descriptor of the I2C bus present on the system.
 * @param[in] I2CAddress address of the sensor on the I2C bus.
 * @param[in] defining the over sampling mode of the sensor for the pressure measurement.
 * @return int returns 0 for successful operation, 1 for failure.
 */
int BMP085_initSensor(BMP085 *sensor,int *I2Cbus,unsigned char I2CAddress,overSampling oss);


/**
 * @brief Starts the process of temperature and pressure measurement.
 *
 * After the raw temperature and pressure data are retrieved from the sensor,
 * the function calculates the temperature values in degrees Celsius and
 * barometric pressure in [Pa].
 *
 * @param[in,out] sensor pointer to the structure that represents the sensor.
 * @return int returns 0 for successful operation, 1 for failure.
 */
int BMP085_takeMeasurement(BMP085 *sensor);

/**
 * @brief The function prints the calibration table of the BMP085 sensor on the standard output.
 *
 * The function should be called after BMP085_initSensor() function.
 * Otherwise it will print random values for the coefficients.
 *
 * @param[in] sensor pointer to the structure that represents the sensor.
 */
void BMP085_printCalibrationTable(BMP085 *sensor);
/* @} */

#endif /* LIBBMP085_H_ */
