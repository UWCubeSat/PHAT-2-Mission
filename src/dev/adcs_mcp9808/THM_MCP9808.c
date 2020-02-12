/*
 * thm_MCP9808.c
 *
 *  Created on: Feb 10, 2020
 *      Author: Sebastian S
 */

#include <stdint.h>
#include <math.h>

#include "thm_MCP9808.h"
#include "MSP430-Library/I2C/I2C.h"
#include "MSP430-Library/I2C/comm_utils.h"

#define MAX_BUFF_SIZE 3

static hDev hSensor;
static uint8_t i2c_buff[MAX_BUFF_SIZE];

static uint16_t cfg;
static int stale_cfg = 1;           // if 1, the stored cfg is stale and must be refreshed before accessing it
static hyst_mode hyst = HYST_0;

static thm_MCP9808_data data;

void thm_MCP9808_init(bus_instance_i2c i2c_bus)
{
    // initialize i2c
    i2cEnable(i2c_bus);
    hSensor = i2cInit(i2c_bus, THM_MCP9808_I2C_7BIT_ADDR);

    // initialize configs (ignore staleness of cfg for first boot)
    cfg = (THM_MCP9808_CFG_T_HYST & (int)hyst); // 0 hysteresis
    cfg |= ~THM_MCP9808_CFG_SHDN;               // not shutdown, constant conversion
    cfg |= THM_MCP9808_CFG_C_LOCK;              // locked critical temp
    cfg |= THM_MCP9808_CFG_W_LOCK;              // locked temp limit windows
    cfg |= ~THM_MCP9808_CFG_INT_CLR;            // no effect
    cfg |= ~THM_MCP9808_CFG_A_STAT;             // output not asserted
    cfg |= ~THM_MCP9808_CFG_A_CTRL;             // alert disabled
    cfg |= ~THM_MCP9808_CFG_A_SEL;              // alert can output on window/crit thresholds
    cfg |= ~THM_MCP9808_CFG_T_POL;              // alert active low
    cfg |= ~THM_MCP9808_CFG_T_MODE;             // alert comparator output
    stale_cfg = 1;
    thm_MCP9808_send_cfg();
}

// Writes to the config register with the stored 16 bit configuration.
void thm_MCP9808_send_cfg()
{
    i2c_buff[0] = THM_MCP9808_PTR_CONFIG;
    i2c_buff[1] = (uint8_t)(cfg >> 8);      // msb first
    i2c_buff[2] = (uint8_t)(cfg & 0xff);
    //i2c_result result = i2cMasterWrite(hSensor, i2c_buff, 3);
    if (i2cMasterWrite(hSensor, i2c_buff, 3) == i2cRes_noerror)
    {
        stale_cfg = 0;
    }
}

thm_MCP9808_data *thm_MCP9808_read()
{
    // write ambient temp pointer to i2c
    i2c_buff[0] = THM_MCP9808_PTR_T_A;
    // write address from buffer index 0, read 2 bytes into indices 1 and 2
    i2c_result result = i2cMasterCombinedWriteRead(hSensor, i2c_buff, 1, &i2c_buff[1], 2);

    if (result != i2cRes_noerror)
    {
        // error!
    }

    uint8_t msb = i2c_buff[1];          // msb first
    uint8_t lsb = i2c_buff[2];

    uint16_t raw = msb << 8 | lsb;

    data.ambient_flags = (raw >> 13);   // first 3 flag bits

    raw &= 0x1F00;                      // clear flags
    data.ambient_raw = raw;             // 13 bit 2's complement

    int16_t sign = -(raw & 0x1000);     // 0b 0001 0000 0000 0000
    uint16_t body = raw & 0x0fff;       // 0b 0000 1111 1111 1111
    data.ambient_converted = ldexpf(sign + body, -4); // divide sign + body by 16

    return &data;
}

// Sets the shutdown bit of the sensor if the sensor is not currently shut down
static void thm_MCP9808_send_shutdown()
{
    if (!thm_MCP9808_send_get_cfg_state(THM_MCP9808_CFG_SHDN))
    {
        cfg |= THM_MCP9808_CFG_SHDN;
        stale_cfg = 1;
        thm_MCP9808_send_cfg();
    }
}

// Clears the shutdown bit of the sensor if the sensor is currently shut down
static void thm_MCP9808_send_turn_on()
{
    if (thm_MCP9808_send_get_cfg_state(THM_MCP9808_CFG_SHDN))
    {
        cfg &= ~THM_MCP9808_CFG_SHDN;
        stale_cfg = 1;
        thm_MCP9808_send_cfg();
    }

}

// Returns whether the config bits in the mask are set.
// If the config bits are stale, reads them from the config register.
int thm_MCP9808_send_get_cfg_state(uint16_t mask)
{
    if (stale_cfg)
    {
        i2c_buff[0] = THM_MCP9808_PTR_CONFIG;
        i2cMasterRead(hSensor, i2c_buff, 2);
        cfg = ((uint16_t)i2c_buff[0] << 8) | i2c_buff[1];
        stale_cfg = 0;
    }
    return (cfg & mask) == mask;
}

