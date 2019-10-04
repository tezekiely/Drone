// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADS1115
// This code is designed to work with the ADS1115_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1115_I2CADC#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

void main() 
{
	while(1){
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, ADS1115 I2C address is 0x48(72)
	ioctl(file, I2C_SLAVE, 0x48);

	// Select configuration register(0x01)
	// AINP = AIN0 and AINN = GND, +/- 2.048V
	// Continuous conversion mode, 128 SPS(0x84, 0x83)
	char config0[3] = {0};
	config0[0] = 0x01;
	config0[1] = 0xC4;
	config0[2] = 0x83;
	write(file, config0, 3);

	// Read 2 bytes of data from register(0x00)
	// raw_adc msb, raw_adc lsb
	char reg0[1] = {0x00};
	write(file, reg0, 1);
	char data0[2]={0};
	if(read(file, data0, 2) != 2)
	{
		printf("Error : Input/Output Error \n");
	}
	else 
	{
		// Convert the data
		int raw_adc0 = (data0[0] * 256 + data0[1]);
		if (raw_adc0 > 32767)
		{
			raw_adc0 -= 65535;
		}

		// Output data to screen
		printf("Digital Value of Analog Input on AIN0: %d \n", raw_adc0);
	}

	// Select configuration register(0x01)
	// AINP = AIN1 and AINN = GND, +/- 2.048V
	// Continuous conversion mode, 128 SPS(0x84, 0x83)
	char config1[3] = {0};	
	config1[0] = 0x01;		
	config1[1] = 0xD4;
	config1[2] = 0x83;
	write(file, config1, 3);

	// Read 2 bytes of data from register(0x00)
	// raw_adc msb, raw_adc lsb
	char reg1[1] = {0x00};	
	write(file, reg1, 1);
	char data1[2]={0};		
	if(read(file, data1, 2) != 2)	
	{
		printf("Error : Input/Output Error \n");
	}
	else 
	{
		// Convert the data
		int raw_adc1 = (data1[0] * 256 + data1[1]);
		if (raw_adc1 > 32767)
		{
			raw_adc1 -= 65535;
		}

		// Output data to screen
		printf("Digital Value of Analog Input on AIN1: %d \n", raw_adc1);
	}

	// Select configuration register(0x01)
	// AINP = AIN2 and AINN = GND, +/- 2.048V
	// Continuous conversion mode, 128 SPS(0x84, 0x83)
	char config2[3] = {0};
	config2[0] = 0x01;
	config2[1] = 0xE4;
	config2[2] = 0x83;
	write(file, config2, 3);

	// Read 2 bytes of data from register(0x00)
	// raw_adc msb, raw_adc lsb
	char reg2[1] = {0x00};
	write(file, reg2, 1);
	char data2[2]={0};
	if(read(file, data2, 2) != 2)
	{
		printf("Error : Input/Output Error \n");
	}
	else 
	{
		// Convert the data
		int raw_adc2 = (data2[0] * 256 + data2[1]);
		if (raw_adc2 > 32767)
		{
			raw_adc2 -= 65535;
		}

		// Output data to screen
		printf("Digital Value of Analog Input on AIN2: %d \n", raw_adc2);
	}

	// Select configuration register(0x01)
	// AINP = AIN3 and AINN = GND, +/- 2.048V
	// Continuous conversion mode, 128 SPS(0x84, 0x83)
	char config3[3] = {0};
	config3[0] = 0x01;
	config3[1] = 0xF4;
	config3[2] = 0x83;
	write(file, config3, 3);

	// Read 2 bytes of data from register(0x00)
	// raw_adc msb, raw_adc lsb
	char reg3[1] = {0x00};
	write(file, reg3, 1);
	char data3[2]={0};
	if(read(file, data3, 2) != 2)
	{
		printf("Error : Input/Output Error \n");
	}
	else 
	{
		// Convert the data
		int raw_adc3 = (data3[0] * 256 + data3[1]);
		if (raw_adc3 > 32767)
		{
			raw_adc3 -= 65535;
		}

		// Output data to screen
		printf("Digital Value of Analog Input on AIN3: %d \n", raw_adc3);
	}

	sleep(3);
	printf("\n");
	}
}