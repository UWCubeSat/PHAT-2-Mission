#include <msp430.h> 
#include "../../../MSP430-Library/I2C/I2C.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	i2c_init(1, 0x1E);
	while(1){
	    i2cMasterRead(hDev device, uint8_t * buff, uint8_t szToRead);
	    __delay_cycles(1000);
	}
	
	return 0;
}
