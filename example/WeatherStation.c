/*
 * LibBMP085 example.
 *
 * Created: 10.05.2016
 * Author:	Goce Boshkovski
 *
 * Copyright (c) 2013  Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 *
 * Demonstrates the use of libBMP085 library for
 * temperature and barometric temperature measurement
 * on Raspberry Pi and Adafruit BMP085 sensor module.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "I2Cbus.h"
#include "libbmp085.h"

void print_usage(const char *);
void parse_opts(int argc, char *argv[]);

char I2CAddress;
char *device = "/dev/i2c-0";
int measureTemperature,measurePressure = 0;
int addressPresent, printSensorCalibrationTable = 0;
int mode = 1;

int main(int argc, char **argv)
{
    int I2CBus;

	parse_opts(argc,argv);	

	if (!addressPresent)
	{
		printf("Device address is not defined.\n");
		print_usage(argv[0]);
		exit(1);
	}

	if (mode<0 || mode>3)
	{
		printf("Unsupported measurement mode %d!\n",mode);
		print_usage(argv[0]);
		exit (1);
	}

	BMP085 *sensor;
	sensor = (BMP085 *) malloc(sizeof(BMP085));
	
	if (openI2CBus(&I2CBus,device))
	{
		printf("Failed to open I2C bus via device: %s.\n",device);
		return 1;
	}
	
	if (BMP085_initSensor(sensor,&I2CBus,I2CAddress,mode))
	{
		printf("Failed to init BMP085 sensor.\n");
		return 1;
	}


	if (printSensorCalibrationTable)
	{
		printf("Table of calibration coefficients:\n");
		BMP085_printCalibrationTable(sensor);
	}

    if (measureTemperature+measurePressure)
	{
    	if (BMP085_takeMeasurement(sensor))
		{
			printf("Failed to retrieve sensor data.\n");
			exit(1);
		}
		if (measureTemperature)
			printf("Temperature = %+5.2f%cC\n",sensor->temperature,176);
		if (measurePressure)
			printf("Pressure = %.2fhPa\n",(float)sensor->pressure/100.0);
	}


	free(sensor);

	closeI2CBus(&I2CBus);

    return 0;

}

void print_usage(const char *prog)
{
        printf("Usage: %s [-adtTpm]\n", prog);
        puts("  -a --address\t\t mandatory, sets the I2C bus address of the BMP085 sensor;\n"
             "  -d --device\t\t set the I2C device (default is /dev/i2c-0);\n"
             "  -t --table\t\t print calibration table;\n"
             "  -T --temperature\t measure temperature and print the value in C;\n"
             "  -p --pressure\t\t measure the atmospheric pressure and print the value;\n"
        	 "  -m --mode\t\t sets the measurement mode. Default value 1 = STANDARD. Allowed values:\n"
	         "                                            0 = ULTRA LOW POWER\n"
             "                                            1 = STANDARD\n"
             "                                            2 = HIGH RESOLUTION\n"
             "                                            3 = ULTRA HIGH RESOLUTION\n");
	    		
	exit(1);
}

void parse_opts(int argc, char *argv[])
{
        while (1) {
        	static const struct option lopts[] = {
                        { "address", required_argument, NULL, 'a' },
                        { "device", required_argument, NULL, 'd' },
						{ "mode", required_argument, NULL, 'm' },
                        { "table", no_argument, NULL, 't' },
                        { "temperature", no_argument, NULL, 'T' },
                        { "pressure", no_argument, NULL, 'p' },
                        { NULL, 0, 0, 0 },
        	};

        	int c;

            c = getopt_long(argc, argv, "a:d:m:tTp", lopts, NULL);

            if (c == -1)
            	break;

                switch (c) {
                	case 'd':
                        device = optarg;
                        break;
                	case 'a':
                		{
                        	I2CAddress = (char)strtol(optarg,NULL,0);
                        	addressPresent = 1;
                		}
                		break;
                	case 'm':
                		mode = atoi(optarg);
                		break;
                	case 'T':
                        measureTemperature = 1;
                        break;
                	case 't':
                		printSensorCalibrationTable = 1;
                		break;
                	case 'p':
                        measurePressure = 1;
                        break;
                	default:
                        print_usage(argv[0]);
                        break;
                }
        }
}
