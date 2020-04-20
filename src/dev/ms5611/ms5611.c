//***************************************************************************************
//  MS5611 ALTIMETER TEMPERATURE PRESSURE SENSOR
//
//                MS5611
//             -----------------
//         /|\|              PS |---> HIGH for i2c
//          | |                 |
//          --|RST          CSB |<--- HIGH for 0 address, LOW for 1 address
//            |                 |
//            |         SDI/SDA |<--> only SDA used for i2c
//            |                 |
//            |             SDO |--->
//            |                 |
//            |            SCLK |<---
//             -----------------
//
//***************************************************************************************

#include <msp430.h>
#include "ms5611.h"
#include "MSP430-Library/I2C/I2C.h"
#include "MSP430-Library/I2C/comm_utils.h"

#include <stdint.h>
#include <math.h>

#define MAX_INSTANCES 2

type struct _ms5611_data {
    int initialized;
    hDev hSensor;

    uint16_t sensorCoefficients[7];

} ms5611_data;

static ms5611_data instances[MAX_INSTANCES];

static int error_from_result(i2c_result result) {
    switch (result) {
        case i2cRes_noerror:
            return 0;
        case i2cRes_startTimeout:
        case i2cRes_stopTimeout:
        case i2cRes_transmitTimeout:
            return ETIMEDOUT;
        case i2cRes_nack:
            return EIO;
        default:
            return EINVAL;
    }
}

void altimeterInit(bus_instance_i2c i2cbus, uint8_t addr_pin)
{
    if (addr_pin >= MAX_INSTANCES) {
        return EINVAL;
    }

    ms5611_data altimeter = ms5611_data[addr_pin];

    if (altimeter.initialized) {
        return EINVAL;
    }

    i2cEnable(i2cbus);

    altimeter.initialized = 1;
    altimeter.hSensor = i2cInit(i2cbus, MS5611_ADDRESS | addr_pin);

    readProm(addr_pin);
}

static void readPROM(uint8_t addr_pin) {
    ms5611_data altimeter = ms5611_data[addr_pin];

    for (int i = 0; i <= 6; i++) {
       uint8_t cmd = MS5611_CMD_PROM_READ + i;

       uint16_t res;
       i2cMasterCombinedWriteRead(altimeter.hSensor, cmd, 1, res, 2); // assume size to read/write in bytes
       altimeter.sensorCoefficients[i] = res;
    }
}

uint32_t readD1() {
    uint32_t d1 = 0;
    i2cMasterCombinedWriteRead(hSensor, MS5611_CMD_CONVERT_D1 + MS5611_ULTRA_HIGH_POWER, 1, d1, 4);
    return d1;
}

uint32_t readD2() {
    uint32_t d2 = 0;
    i2cMasterCombinedWriteRead(hSensor, MS5611_CMD_CONVERT_D2 + MS5611_ULTRA_HIGH_POWER, 1, d2, 4);
    return d2;
}


/**
 * Celcius. (no freedom units :)))
 */
double getAltitude(uint8_t addr_pin) {
    ms5611_data altimeter = ms5611_data[addr_pin];

    uint32_t D1 = readD1();
    uint32_t D2 = readD2();

    int32_t dT = D2 - altimeter.sensorCoefficients[5] * 2;
    int32_t temp = 20 + dT * altimeter.sensorCoefficients[6] / (1l << 22);


    int64_t off = (int64_t) altimeter.sensorCoefficients[2] + (1l << 15) + ((int64_t) altimeter.sensorCoefficients[4] * dT) / (1l << 6);
    int64_t sens = (int64_t) sensorCoefficients[1] * (1l << 14) + ((int64_t) altimeter.sensorCoefficients[3] * dT) / (1l << 7);

    uint32_t pressure = (D1 * sens / (1l << 20) - off) / (1l << 14);
    return (44330.0f * (1.0f - pow((double)pressure / (double)seaLevelPressure, 0.1902949f)));
}

