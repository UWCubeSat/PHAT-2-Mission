/*
 * thm_mcp9808.c
 *
 *  Created on: Feb 19, 2020
 *      Author: tengo
 *
 *  Driver implementation for the mcp9808.
 */

#include <stdint.h>
#include <errno.h>
#include <math.h>
#include "mcp9808.h"

#include "thm_mcp9808.h"
#include "thm.h"

#include "MSP430-Library/I2C/I2C.h"
#include "MSP430-Library/I2C/comm_utils.h"

#define MAX_INSTANCES   8           // 3 address pins, 8 possible instances
#define MAX_BUFFER      3           // at most, write 1 byte and read/write 2

typedef struct _thm_mcp9808_data {
    int initialized;
    hDev device_handle;
    uint8_t address;
    uint16_t config;
} thm_mcp9808_data;

static thm_mcp9808_data instances[MAX_INSTANCES];
static uint8_t i2c_buffer[MAX_BUFFER];

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

// Writes the address of the register first, then the bytes to be written into it (msb first)
static int write_to_register(hDev inst_handle, uint8_t reg_ptr, uint8_t *bytes, uint8_t size_to_write) {
    thm_mcp9808_data instance = instances[inst_handle];
    i2c_buffer[0] = reg_ptr;
    uint8_t i;
    for (i = 0; i < size_to_write; i++) { // count down from size to write - 1 to 0
        i2c_buffer[i+1] = bytes[i];
    }
    i2c_result result = i2cMasterWrite(instance.device_handle, i2c_buffer, size_to_write + 1);

    return error_from_result(result);
}

static int write_to_config(hDev inst_handle) {
    thm_mcp9808_data instance = instances[inst_handle];
    uint8_t temp[] = { instance.config >> 8, instance.config & 0xff };
    return write_to_register(inst_handle, MCP9808_PTR_CONFIG, temp, 2);
}

static int write_to_resolution(hDev inst_handle, int resolution) {
    uint8_t res = resolution & 0xff;
    return write_to_register(inst_handle, MCP9808_PTR_RES, &res, 1);
}

int thm_mcp9808_init_full(bus_instance_i2c i2c_bus, hDev *instance, uint8_t addr_pins,
                          thm_mcp9808_res res, thm_mcp9808_hyst hyst) {
    if (addr_pins >= MAX_INSTANCES) { // address out of range
        return EINVAL;
    }
    thm_mcp9808_data thm = instances[addr_pins];
    if (thm.initialized) { // instance already initialized with this address
        return EINVAL;
    }

    uint8_t address = MCP9808_I2C_7BIT_ADDR | addr_pins;
    hDev inst_handle = addr_pins;

    i2cEnable(i2c_bus);
    thm.device_handle = i2cInit(i2c_bus, address);
    thm.address = address;

    // initialize configs
    uint16_t cfg = (int)hyst;       // hysteresis
    cfg |= ~MCP9808_CFG_SHDN;       // not shutdown, constant conversion
    cfg |= MCP9808_CFG_C_LOCK;      // locked critical temp
    cfg |= MCP9808_CFG_W_LOCK;      // locked temp limit windows
    cfg |= ~MCP9808_CFG_INT_CLR;    // no effect
    cfg |= ~MCP9808_CFG_A_STAT;     // output not asserted
    cfg |= ~MCP9808_CFG_A_CTRL;     // alert disabled
    cfg |= ~MCP9808_CFG_A_SEL;      // alert can output on window/crit thresholds
    cfg |= ~MCP9808_CFG_A_POL;      // alert active low
    cfg |= ~MCP9808_CFG_A_MODE;     // alert comparator output
    thm.config = cfg;

    int result = write_to_config(inst_handle);
    if (result) { return result; } // if failed, return error
    result = write_to_resolution(inst_handle, res);
    if (result) { return result; } // if failed, return error

    *instance = inst_handle;
    return 0;
}

int thm_mcp9808_init(bus_instance_i2c i2c_bus, uint8_t *instance, uint8_t addr_pins) {
    return thm_mcp9808_init_full(i2c_bus, instance, addr_pins, THM_MCP9808_RES_1_16, THM_MCP9808_HYST_0);
}

int thm_mcp9808_read(hDev inst_handle, float *temp, thm_conversion conversion) {
    thm_mcp9808_data instance = instances[inst_handle];

    // write ambient temp pointer to i2c
    i2c_buffer[0] = MCP9808_PTR_T_A;
    // write address from buffer index 0, read 2 bytes into indices 1 and 2
    i2c_result result = i2cMasterCombinedWriteRead(instance.device_handle, i2c_buffer, 1, &i2c_buffer[1], 2);

    if (result) {
        return error_from_result(result);
    }

    uint8_t msb = i2c_buffer[1];
    uint8_t lsb = i2c_buffer[2];

    uint16_t raw = msb << 8 | lsb;

    raw &= 0x1fff;                          // clear flags

    int16_t sign = -(raw & 0x1000);         // 0b 0001 0000 0000 0000
    uint16_t body = raw & 0x0fff;           // 0b 0000 1111 1111 1111
    float out = ldexpf(sign + body, -4);    // divide sign + body by 16

    *temp = thm_convert_from_celsius(out, conversion);
    return 0;
}
