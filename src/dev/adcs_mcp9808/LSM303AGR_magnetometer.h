/*
 * LSM303AGR_magnetometer.h
 *
 *  Created on: Jan 12, 2020
 *      Author: shubhkarmansingh
 */

#ifndef LSM303AGR_MAGNETOMETER_H_
#define LSM303AGR_MAGNETOMETER_H_

/* Public Function Prototypes -------------------------------------------------------*/
 
mems_status_t LSM303AGR_MAG_read_reg( void *handle, u8_t Reg, u8_t* Data );
mems_status_t LSM303AGR_MAG_write_reg( void *handle, u8_t Reg, u8_t Data ); 

// Register addresses

#define MAG_LSM303AGR_STATUS_REG_AUX_A          0x07

// Output registers
#define MAG_LSM303AGR_OUT_TEMP_L_A              0x0C
#define MAG_LSM303AGR_OUT_TEMP_H_A              0x0D

#define MAG_LSM303AGR_INT_COUNTER_REG_A         0x0E

// Dummy register
#define MAG_LSM303AGR_WHO_AM_I_A                0x0F

#define MAG_LSM303AGR_TEMP_CFG_REG_A            0x1F

//Accelerometer control registers
#define MAG_LSM303AGR_CTRL_REG1_A               0x20
#define MAG_LSM303AGR_CTRL_REG2_A               0x21
#define MAG_LSM303AGR_CTRL_REG3_A               0x22
#define MAG_LSM303AGR_CTRL_REG4_A               0x23
#define MAG_LSM303AGR_CTRL_REG5_A               0x24
#define MAG_LSM303AGR_CTRL_REG6_A               0x25

#define MAG_LSM303AGR_REFERENCE/DATACAPTURE_A   0x26

//Accelerometer status register
#define MAG_LSM303AGR_STATUS_REG_A              0x27

//Accelerometer output registers
#define MAG_LSM303AGR_OUT_X_L_A                 0x28
#define MAG_LSM303AGR_OUT_X_H_A                 0x29
#define MAG_LSM303AGR_OUT_Y_L_A                 0x2A
#define MAG_LSM303AGR_OUT_Y_H_A                 0x2B
#define MAG_LSM303AGR_OUT_Z_L_A                 0x2C
#define MAG_LSM303AGR_OUT_Z_H_A                 0x2D

//FIFO registers
#define MAG_LSM303AGR_FIFO_CTRL_REG_A           0x2E
#define MAG_LSM303AGR_FIFO_SRC_REG_A            0x2F

//Interrupt 1 registers
#define MAG_LSM303AGR_INT1_CFG_A                0x30
#define MAG_LSM303AGR_INT1_SRC_A                0x31
#define MAG_LSM303AGR_INT1_THS_A                0x32
#define MAG_LSM303AGR_INT1_DURATION_A           0x33

//Interrupt 2 registers
#define MAG_LSM303AGR_INT2_CFG_A                0x34
#define MAG_LSM303AGR_INT2_SRC_A                0x35
#define MAG_LSM303AGR_INT2_THS_A                0x36
#define MAG_LSM303AGR_INT2_DURATION_A           0x37

// Additional registers
#define MAG_LSM303AGR_CLICK_CFG_A               0x38
#define MAG_LSM303AGR_CLICK_SRC_A               0x39
#define MAG_LSM303AGR_CLICK_THS_A               0x3A
#define MAG_LSM303AGR_TIME_LIMIT_A              0x3B
#define MAG_LSM303AGR_TIME_LATENCY_A            0x3C
#define MAG_LSM303AGR_TIME_WINDOW_A             0x3D
#define MAG_LSM303AGR_Act_THS_A                 0x3E
#define MAG_LSM303AGR_Act_DUR_A                 0x3F

//Magnetometer hard-iron registers
#define MAG_LSM303AGR_OFFSET_X_REG_L_M          0x45
#define MAG_LSM303AGR_OFFSET_X_REG_H_M          0x46
#define MAG_LSM303AGR_OFFSET_Y_REG_L_M          0x47
#define MAG_LSM303AGR_OFFSET_Y_REG_H_M          0x48
#define MAG_LSM303AGR_OFFSET_Z_REG_L_M          0x49
#define MAG_LSM303AGR_OFFSET_Z_REG_H_M          0x4A

#define MAG_LSM303AGR_WHO_AM_I_M                0x4F

//Magnetometer configuration registers
#define MAG_LSM303AGR_CFG_REG_A_M               0x60
#define MAG_LSM303AGR_CFG_REG_B_M               0x61
#define MAG_LSM303AGR_CFG_REG_C_M               0x62

//Magnetometer interrupt configuration registers
#define MAG_LSM303AGR_INT_CRTL_REG_M            0x63
#define MAG_LSM303AGR_INT_SOURCE_REG_M          0x64
#define MAG_LSM303AGR_INT_THS_L_REG_M           0x65
#define MAG_LSM303AGR_INT_THS_H_REG_M           0x66

#define MAG_LSM303AGR_STATUS_REG_M              0x67

//Magnetometer output registers
#define MAG_LSM303AGR_OUTX_L_REG_M              0x68
#define MAG_LSM303AGR_OUTX_H_REG_M              0x69
#define MAG_LSM303AGR_OUTY_L_REG_M              0x6A
#define MAG_LSM303AGR_OUTY_H_REG_M              0x6B
#define MAG_LSM303AGR_OUTZ_L_REG_M              0x6C
#define MAG_LSM303AGR_OUTZ_H_REG_M              0x6D

#endif /* LSM303AGR_MAGNETOMETER_H_ */
