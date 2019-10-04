#include <stdio.h>
#include <sys/types.h> // open
#include <sys/stat.h>  // open
#include <fcntl.h>     // open
#include <unistd.h>    // read/write usleep
#include <stdlib.h>    // exit
#include <inttypes.h>  // uint8_t, etc
#include <linux/i2c-dev.h> // I2C bus definitions
#include <sys/ioctl.h> // ioctl

int fd;
// ADS1115 defaults to 0x48
int ads_address = 0x48;
int16_t val;

uint8_t readBuf[2];

float myfloat;

const float VPS = 4.096 / 32768.0; //volts per step

/*
The resolution of the ADC in single ended 
mode we have 15 bit rather than 16 bit resolution, 
the 16th bit being the sign of the differential reading.
*/

float Ads1115(uint8_t writeBuf[3]) {
  // open device on /dev/i2c-1 
  // the default on Raspberry Pi B
  if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
    printf("Error: Couldn't open device! %d\n", fd);
    exit (1);
  }

  // connect to ads1115 as i2c slave
  if (ioctl(fd, I2C_SLAVE, ads_address) < 0) {
    printf("Error: Couldn't find device on address!\n");
    exit (1);
  }
  
  // set config register and start conversion
  // ANC1 and GND, 4.096v, 128s/s
  //writeBuf[0] = 1;    // config register is 1
  //writeBuf[1] = 0b11000011; // bit 15-8 0xD3
  // bit 15 flag bit for single shot
  // Bits 14-12 input selection:
  	// 000 : AINP = AIN0 and AINN = AIN1 (default), 100(C) : AINP = AIN0 and AINN = GND
	// 001 : AINP = AIN0 and AINN = AIN3, 101(D) : AINP = AIN1 and AINN = GND
	// 010 : AINP = AIN1 and AINN = AIN3, 110(E) : AINP = AIN2 and AINN = GND
	// 011 : AINP = AIN2 and AINN = AIN3, 111(F) : AINP = AIN3 and AINN = GND
  // Bits 11-9 Amplifier gain.
	// 000(0) : FS = +-6.144V(1)  
	// 001(2) : FS = +-4.096V(1)
	// 010(4) : FS = +-2.048V (default)
	// 011(6) : FS = +-1.024V
  // Bit 8 Operational mode of the ADS1115.
  // 0 : Continuous conversion mode
  // 1 : Power-down single-shot mode (default)

  //writeBuf[2] = 0b10000101; // bits 7-0  0x85
  // Bits 7-5 data rate default to 100 for 128SPS
  // Bits 4-0  comparator functions see spec sheet.

  // begin conversion
  if (write(fd, writeBuf, 3) != 3) {
    perror("Write to register 1");
    exit(-1);
  }

  // wait for conversion complete
  // checking bit 15
  do {
    if (read(fd, writeBuf, 2) != 2) {
      perror("Read conversion");
      exit(-1);
    }
  }
  while ((writeBuf[0] & 0x80) == 0);



  // read conversion register
  // write register pointer first
  readBuf[0] = 0;   // conversion register is 0
  if (write(fd, readBuf, 1) != 1) {
    perror("Write register select");
    exit(-1);
  }
  
  // read 2 bytes //conversion register로 변환된 레지스터의 데이터를 readBuf에 읽어옴. 16bit.
  if (read(fd, readBuf, 2) != 2) {
    perror("Read conversion");
    exit(-1);
  }

  // convert display results
  val = readBuf[0] << 8 | readBuf[1];

  if (val < 0)   val = 0;

  myfloat = val * VPS; // convert to voltage

  printf("Values: HEX 0x%02x DEC %d reading %4.3f volts.\n", val, val, myfloat);
         
  close(fd);

  return myfloat;
}