/*
 * TWI.h
 * two wire interface
 *  Created on: Aug 26, 2023
 *      Author: joey
 */
#ifndef TWI_H
#define TWI_H

#include "../../0-LIB/bit_op.h"
#include "../../0-LIB/std.h"
#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

void TWI_MasterIni();
void TWI_SlaveIni(u8 Copy_u8Address);
void TWI_SendStartCondition();
void TWI_SendStopCondition();
void TWI_ReStartCondition();
void TWI_SendSlaveAddressWrite(u8 Copy_u8SlaveAddress);
void TWI_SendSlaveAddressRead(u8 Copy_u8SlaveAddress);
void TWI_SendDataByte(u8 Copy_u8DataByte);
u8 	 TWI_ReadData();

#endif
