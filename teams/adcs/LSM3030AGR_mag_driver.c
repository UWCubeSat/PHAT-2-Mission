/*
 * LSM303AGR_mag_driver.c
 *
 *  Created on: Jan 30, 2020
 *      Author: shubhkarmansingh
 */

#include "LSM303AGR_magnetometer.h"

/* Imported function prototypes ----------------------------------------------*/
extern uint8_t LSM303AGR_MAG_io_write(void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite);
extern uint8_t LSM303AGR_MAG_io_read(void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead);

/*******************************************************************************
* Function Name     : LSM303AGR_MAG_read_reg
* Description       : Generic Reading function. It must be fullfilled with either
*                   : I2C or SPI reading functions
* Input             : Register Address
* Output            : Data REad
* Return            : None
*******************************************************************************/
mems_status_t LSM303AGR_MAG_read_reg( void *handle, u8_t Reg, u8_t* Data ) {

  if (LSM303AGR_MAG_io_read(handle, Reg, Data, 1))
  {
    return MEMS_ERROR;
  }
  else
  {
    return MEMS_SUCCESS;
  }
}

/*******************************************************************************
* Function Name     : LSM303AGR_MAG_write_reg
* Description       : Generic Writing function. It must be fullfilled with either
*                   : I2C or SPI writing function
* Input             : Register Address, Data to be written
* Output            : None
* Return            : None
*******************************************************************************/
mems_status_t LSM303AGR_MAG_write_reg( void *handle, u8_t Reg, u8_t Data ) {

  if (LSM303AGR_MAG_io_write(handle, Reg, &Data, 1))
  {
    return MEMS_ERROR;
  }
  else
  {
    return MEMS_SUCCESS;
  }
}

