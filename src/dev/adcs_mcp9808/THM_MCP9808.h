/*
 * THM_MCP9808.h
 *
 *  Created on: Feb 10, 2020
 *      Author: Sebastian S
 */

#ifndef THM_MCP9808_H_
#define THM_MCP9808_H_

#include <stdint.h>

#define THM_MCP9808_I2C_7BIT_ADDR   0x18 // from datasheet: 0x18 + 0b[xyz]; for us, x, y, z are pulled to ground

// Register pointers
#define THM_MCP9808_PTR_CONFIG      0x01  // config
#define THM_MCP9808_PTR_T_UPPER     0x02  // upper threshold
#define THM_MCP9808_PTR_T_LOWER     0x03  // lower threshold
#define THM_MCP9808_PTR_T_CRIT      0x04  // critical temperature
#define THM_MCP9808_PTR_T_A         0x05  // ambient temperature
#define THM_MCP9808_PTR_RES         0x08  // resolution

// Configuration bits
#define THM_MCP9808_CFG_T_HYST      0x600 // 11 << 9  | limit hysteresis
#define THM_MCP9808_CFG_SHDN        0x100 //  1 << 8  | shutdown
#define THM_MCP9808_CFG_C_LOCK      0x080 //  1 << 7  | crit temp register locked
#define THM_MCP9808_CFG_W_LOCK      0x040 //  1 << 6  | upper/lower registers locked
#define THM_MCP9808_CFG_INT_CLR     0x020 //  1 << 5  | clear interrupt
#define THM_MCP9808_CFG_A_STAT      0x010 //  1 << 4  | alert output status
#define THM_MCP9808_CFG_A_CTRL      0x008 //  1 << 3  | alert output control
#define THM_MCP9808_CFG_A_SEL       0x004 //  1 << 2  | alert output select
#define THM_MCP9808_CFG_T_POL       0x002 //  1 << 1  | alert output polarity
#define THM_MCP9808_CFG_T_MODE      0x001 //  1 << 0  | alert output mode

typedef enum hysteresis_mode
{
    HYST_0      = 0b00 << 9,   // 0.5 C    | 30  ms
    HYST_1_5    = 0b01 << 9,   // 0.25 C   | 65  ms
    HYST_3_0    = 0b10 << 9,   // 0.125 C  | 130 ms
    HYST_6_0    = 0b11 << 9,   // 0.0625 C | 250 ms
} hyst_mode;

typedef enum ambient_flag_mask
{
    UPPER = 0b100,
    LOWER = 0b010,
    CRIT  = 0b001,
} amb_flag_mask;

// Data
typedef struct
{
    float       ambient_converted;  // floating point conversion to C, per datasheet
    uint16_t    ambient_raw;        // raw 13 bit signed int
    char        ambient_flags;      // ambient comparison flags, 3 bit
} THM_MCP9808_data;

void THM_MCP9808_init();
void THM_MCP9808_send_cfg();
void THM_MCP9808_send_shutdown();
void THM_MCP9808_send_turn_on();
int THM_MCP9808_send_get_cfg_state(uint16_t mask); // given a bitmask, returns true if the config bits in that mask are not 0

THM_MCP9808_data *THM_MCP9808_read();

#endif /* THM_MCP9808_H_ */
