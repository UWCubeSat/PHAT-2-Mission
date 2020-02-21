/*
 * thm_mcp9808.h
 *
 *  Created on: Feb 19, 2020
 *      Author: tengo
 *
 *  Driver header for the mcp9808.
 */

#ifndef THM_MCP9808_H_
#define THM_MCP9808_H_

#include <stdint.h>
#include "MSP430-Library/I2C/I2C.h"
#include "thm.h"

/*
 * Represents the possible temperature resolutions on the mcp9808.
 *     THM_MCP9808_RES_1_2          1/2  C |  30 ms per measurement
 *              ...RES_1_4          1/4  C |  65 ms ...
 *              ...RES_1_8          1/8  C | 130 ms ...
 *              ...RES_1_16         1/16 C | 250 ms ...
 */
typedef enum _thm_mcp9808_res {
    THM_MCP9808_RES_1_2     = 0,     // 0.5 C, 30 ms
    THM_MCP9808_RES_1_4     = 1,     // 0.25 C, 65 ms
    THM_MCP9808_RES_1_8     = 2,     // 0.125 C, 130 ms
    THM_MCP9808_RES_1_16    = 3,     // 0.0625 C, 250 ms
} thm_mcp9808_res;

/*
 * Represents the possible hysteresis modes on the mcp9808.
 *     THM_MCP9808_HYST_0           +0 C
 *              ...HYST_1_5         +1.5 C
 *              ...HYST_3_0         +3.0 C
 *              ...HYST_6_0         +6.0 C
 */
typedef enum _thm_mcp9808_hyst
{
    THM_MCP9808_HYST_0      = 0b00 << 9,   // 0 C
    THM_MCP9808_HYST_1_5    = 0b01 << 9,   // +1.5 C
    THM_MCP9808_HYST_3_0    = 0b10 << 9,   // +3.0 C
    THM_MCP9808_HYST_6_0    = 0b11 << 9,   // +6.0 C
} thm_mcp9808_hyst;

/*
 * Initializes one instance of the mcp9808.
 *     bus_instance_i2c i2c_bus     The i2c bus instance to initialize this sensor on.
 *     hDev *instance               Pointer where the device-specific instance handle will be written.
 *     uint8_t addr_pins            The address pin states of the sensor instance, where bits 0-2 are A0-A2.
 *     thm_mcp9808_res res          The resolution code to be used by the sensor instance; by default, this will by 1/16 C.
 *     thm_mcp9808_hyst hyst        The hysteresis mode to be used by the sensor instance; by default, this will be +0 C.
 *
 * Returns the error code of the operation, where 0 is a success.
 *     EINVAL                       The given address pin state is either invalid or already in use, or there was an unknown I2C error.
 *     ETIMEDOUT                    The I2C connection to the sensor timed out.
 *     EIO                          The I2C connection resulted in non-acknowledgment.
 */
int thm_mcp9808_init(bus_instance_i2c i2c_bus, hDev *instance, uint8_t addr_pins);
int thm_mcp9808_init_full(bus_instance_i2c i2c_bus, hDev *instance, uint8_t addr_pins, thm_mcp9808_res res, thm_mcp9808_hyst hyst);

/*
 * Obtains a temperature reading from the given mcp9808 instance.
 *     hDev instance                The sensor instance to read from.
 *     float *temp                  Pointer where the temperature reading will be written.
 *     thm_conversion conversion    Temperature units the reading will be converted to.
 *
 * Returns the error code of the operation, where 0 is a success (and the temperature reading can be trusted)
 *     EINVAL                       There was an unknown I2C error.
 *     ETIMEDOUT                    The I2C connection to the sensor timed out.
 *     EIO                          The I2C connection resulted in non-acknowledgment.
 */
int thm_mcp9808_read(hDev instance, float *temp, thm_conversion conversion);

#endif /* THM_MCP9808_H_ */
