/*
 * TWI.c
 * two wire interface
 *  Created on: Aug 26, 2023
 *      Author: joey
 */
#include"TWI.h"


static volatile u8 Local_u8TWI_ERROR;




	void TWI_MasterIni()
	{

		//master dictates clock set/control;
		// Set Pre-Scaler and clock values --> 200kHz
		TWBR = 0b00001100; // TWBR = 12
		CLR_BIT(TWSR, TWPS0); //
		CLR_BIT(TWSR, TWPS1); // TWPS = 0
		// Enable ACK
		SET_BIT(TWCR, TWEA);
		// Enable interrupt
		SET_BIT(TWCR, TWIE);
		// Enable TWI itself
		SET_BIT(TWCR, TWEN);

	}

	void TWI_SlaveIni(u8 Copy_u8Address)

	{
		//no clock set/access required by slave;
		// Enable ACK
		SET_BIT(TWCR, TWEA);
		// Enable interrupt
		SET_BIT(TWCR, TWIE);
		// Set Slave Address (7 bit)
		TWAR = ((Copy_u8Address<<1)&0xFE);
		// Enable TWI
		SET_BIT(TWCR, TWEN);

	}

	void TWI_SendStartCondition()
	{
		//to start operation of TWI, TWI PIF must be cleared; (by writing a logic 1)
		SET_BIT(TWCR, TWINT);
		// Send the Start Condition (Through TWI hardware)
		SET_BIT(TWCR, TWSTA);
		// wait for PIF to go low
		while(GET_BIT(TWCR, TWINT) == 0);
		//check Status == 0x08 MT mode
		if((TWSR&0xF8) != 0x08)
		{
			Local_u8TWI_ERROR = 0xFF; // Error Debug
		}



	}

	void TWI_SendStopCondition()
	{
		//Clear flag
		SET_BIT(TWCR, TWINT);
		// Send a Stop Condition (Through TWI hardware)
		SET_BIT(TWCR, TWSTO);

	}

	void TWI_ReStartCondition()
	{
		//PIF clear
		SET_BIT(TWCR, TWINT);
		// Start Condition
		SET_BIT(TWCR, TWSTA);
		// check Status == 0x10 MT mode
		if((TWSR&0xF8) != 0x10)
		{
			Local_u8TWI_ERROR = 0xFF;
		}
		// wait for PIF
		while(GET_BIT(TWCR, TWINT) == 0);

	}

	void TWI_SendSlaveAddressWrite(u8 Copy_u8SlaveAddress)
	{
		//Function to send Address + Write control bit(0) to TWI bus
		// write data to the bus
		TWDR = (Copy_u8SlaveAddress << 1);
		// clear previous start condition that has been transmitted
		CLR_BIT(TWCR, TWSTA);
		// PIF clear
		SET_BIT(TWCR, TWINT);
		// check Status == 0x18 MT mode
		if((TWSR&0xF8) != 0x18)
		{
			Local_u8TWI_ERROR = 0xFF;
		}
		// wait for PIF
		while(GET_BIT(TWCR, TWINT) == 0);

	}

	void TWI_SendSlaveAddressRead(u8 Copy_u8SlaveAddress)
	{
		//Function to send Address + Write control bit(1) to TWI bus
		// write data to the bus register
		TWDR = ((Copy_u8SlaveAddress<<1)& 0xFF);
		// clear previous start condition that has been transmitted
		CLR_BIT(TWCR, TWSTA);
		// PIF clear
		SET_BIT(TWCR, TWINT);
		// check Status == 0x40 MR mode
		if((TWSR&0xF8) != 0x40)
		{
			Local_u8TWI_ERROR = 0xFF;
		}
		// wait for PIF
		while(GET_BIT(TWCR, TWINT) == 0);

	}

	void TWI_SendDataByte(u8 Copy_u8DataByte)
	{
		//Function to send Data to the TWI bus
		// write data to the bus register
		TWDR = Copy_u8DataByte;
		// PIF clear
		SET_BIT(TWCR, TWINT);
		// check Status == 0x28 MT mode
		if((TWSR&0xF8) != 0x28)
		{
			Local_u8TWI_ERROR = 0xFF;
		}
		// wait for PIF
		while(GET_BIT(TWCR, TWINT) == 0);

	}

	u8 	 TWI_ReadData()
	{
		//Function to read Data from the TWI bus
		// PIF clear
		SET_BIT(TWCR, TWINT);
		// wait for PIF [to receive correct message]
		while(GET_BIT(TWCR, TWINT) == 0);
		// check Status == 0x50 MR mode
		if((TWSR&0xF8) != 0x50)
		{
			Local_u8TWI_ERROR = 0xFF;
		}
		// return (read) data
		return TWDR;

	}

