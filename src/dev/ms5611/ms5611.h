
#ifndef DRIVERS_MS5561_ALTIMETER

#include <stdint.h>

#define DRIVERS_MS5525_ALTIMETER

#define MS5611_ADDRESS 				0x76 // i2c address is 0b111011c where c is complement of CSB line

#define MS5611_CMD_RESET			0x1E
#define MS5611_CMD_ADC_READ			0x00
#define MS5611_CMD_PROM_READ		0xA0
#define MS5611_CMD_CONVERT_D1		0x40
#define MS5611_CMD_CONVERT_D2		0x50

// added to MS5611_CMD_CONVERT_ for the correct type
typedef enum {
	MS5611_ULTRA_HIGH_POWER	=		0x08,
	MS5611_HIGH_POWER =				0x06,
	MS5611_NORMAL_POWER	=			0x04,
	MS5611_LOW_POWER =				0x02,
	MS5611_ULTRA_LOW_POWER =			0x00
} ms5611_osr_power;

uint32_t readD1();
uint32_t readD2();

int64_t getTemperature();
 #endif
 
