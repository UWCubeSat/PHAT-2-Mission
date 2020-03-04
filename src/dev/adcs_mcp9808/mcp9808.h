/*
 * mcp9808.h
 *
 *  Created on: Feb 14, 2020
 *      Author: tengo
 *
 *  Device header for the mcp9808.
 */

#ifndef MCP9808_H_
#define MCP9808_H_

#define MCP9808_I2C_7BIT_ADDR   0x18 // address = 0x18 + 0b[xyz], where [xyz] comes from address pins

// Register pointers
#define MCP9808_PTR_CONFIG      0x01  // config
#define MCP9808_PTR_T_UPPER     0x02  // upper threshold temperature
#define MCP9808_PTR_T_LOWER     0x03  // lower threshold temperature
#define MCP9808_PTR_T_CRIT      0x04  // critical temperature
#define MCP9808_PTR_T_A         0x05  // ambient temperature
#define MCP9808_PTR_RES         0x08  // resolution

// Configuration bits
#define MCP9808_CFG_T_HYST      0x600 // 11 << 9  | hysteresis limit bits
#define MCP9808_CFG_SHDN        0x100 //  1 << 8  | shutdown
#define MCP9808_CFG_C_LOCK      0x080 //  1 << 7  | crit temp register locked
#define MCP9808_CFG_W_LOCK      0x040 //  1 << 6  | upper/lower registers locked
#define MCP9808_CFG_INT_CLR     0x020 //  1 << 5  | clear interrupt
#define MCP9808_CFG_A_STAT      0x010 //  1 << 4  | alert output status
#define MCP9808_CFG_A_CTRL      0x008 //  1 << 3  | alert output control
#define MCP9808_CFG_A_SEL       0x004 //  1 << 2  | alert output select
#define MCP9808_CFG_A_POL       0x002 //  1 << 1  | alert output polarity
#define MCP9808_CFG_A_MODE      0x001 //  1 << 0  | alert output mode

// Bitmasks for the flag bits returned when reading
typedef enum ambient_flag_mask
{
    UPPER = 0b100,
    LOWER = 0b010,
    CRIT  = 0b001,
} amb_flag_mask;

#endif /* MCP9808_H_ */
