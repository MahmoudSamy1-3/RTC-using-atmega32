/*
 * DIO_program.c

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h" //Bit wise manipulation library
#include "DIO_interface.h"
#include "DIO_private.h"

/**********************************************************************************/
/**************************FUNCTIONS IMPLEMENTATION*******************************/
/********************************************************************************/
void DIO_voidSetPinDir (u8 PortId , u8 PinId , u8 PinDir)
{
	/*check from allowed values for PortId & PinId*/
	if ((PortId <= DIO_PORTD) && (PinId <= DIO_PIN7))
	{
		/*check from PinDir value*/
		if(PinDir == DIO_OUTPUT)
		{
			switch(PortId)
			{
			case DIO_PORTA: SET_BIT(DDRA_REG,PinId); break;
			case DIO_PORTB: SET_BIT(DDRB_REG,PinId); break;
			case DIO_PORTC: SET_BIT(DDRC_REG,PinId); break;
			case DIO_PORTD: SET_BIT(DDRD_REG,PinId); break;
			}
		}
		else if (PinDir == DIO_INPUT)
		{
			switch(PortId)
			{
			case DIO_PORTA: CLR_BIT(DDRA_REG,PinId); break;
			case DIO_PORTB: CLR_BIT(DDRB_REG,PinId); break;
			case DIO_PORTC: CLR_BIT(DDRC_REG,PinId); break;
			case DIO_PORTD: CLR_BIT(DDRD_REG,PinId); break;
			}
		}
		else
		{
			//report error
		}
	}
	else
	{
		//report error
	}
}

void DIO_voidSetPinVal (u8 PortId , u8 PinId , u8 PinVal)
{
	/*check from allowed values for PortId & PinId*/
	if ((PortId <= DIO_PORTD) && (PinId <= DIO_PIN7))
	{
		/*check from PinDir value*/
		if(PinVal == DIO_HIGH)
		{
			switch(PortId)
			{
			case DIO_PORTA: SET_BIT(PORTA_REG,PinId); break;
			case DIO_PORTB: SET_BIT(PORTB_REG,PinId); break;
			case DIO_PORTC: SET_BIT(PORTC_REG,PinId); break;
			case DIO_PORTD: SET_BIT(PORTD_REG,PinId); break;
			}
		}
		else if (PinVal == DIO_LOW)
		{
			switch(PortId)
			{
			case DIO_PORTA: CLR_BIT(PORTA_REG,PinId); break;
			case DIO_PORTB: CLR_BIT(PORTB_REG,PinId); break;
			case DIO_PORTC: CLR_BIT(PORTC_REG,PinId); break;
			case DIO_PORTD: CLR_BIT(PORTD_REG,PinId); break;
			}
		}
		else
		{
			//report error
		}
	}
	else
	{
		//report error
	}
}

void DIO_voidSetPortDir (u8 PortId , u8 PortDir)
{
	/*check from allowed value for PortId */
	if (PortId <= DIO_PORTD)
	{
		switch(PortId)
		{
		case DIO_PORTA: DDRA_REG = PortDir; break;
		case DIO_PORTB: DDRB_REG = PortDir; break;
		case DIO_PORTC: DDRC_REG = PortDir; break;
		case DIO_PORTD: DDRD_REG = PortDir; break;
		}
	}
	else
	{
		//report error
	}
}

void DIO_voidSetPortVal (u8 PortId , u8 PortVal)
{
	/*check from allowed value for PortId */
	if (PortId <= DIO_PORTD)
	{
		switch(PortId)
		{
		case DIO_PORTA: PORTA_REG = PortVal; break;
		case DIO_PORTB: PORTB_REG = PortVal; break;
		case DIO_PORTC: PORTC_REG = PortVal; break;
		case DIO_PORTD: PORTD_REG = PortVal; break;
		}
	}
	else
	{
		//report error
	}
}

u8 DIO_u8GetPinVal (u8 PortId , u8 PinId)
{
	u8 Result;
	/*check from allowed values for PortId & PinId*/
	if ((PortId <= DIO_PORTD) && (PinId <= DIO_PIN7))
	{
		switch(PortId)
		{
		case DIO_PORTA: Result = GET_BIT(PINA_REG,PinId); break;
		case DIO_PORTB: Result = GET_BIT(PINB_REG,PinId); break;
		case DIO_PORTC: Result = GET_BIT(PINC_REG,PinId); break;
		case DIO_PORTD: Result = GET_BIT(PIND_REG,PinId); break;
		}
	}

	else
	{
		//report error
	}
	return Result;
}

void DIO_voidTogglePinVal (u8 PortId , u8 PinId )
{
	/*check from allowed values for PortId & PinId*/
	if ((PortId <= DIO_PORTD) && (PinId <= DIO_PIN7))
	{
		switch(PortId)
		{
		case DIO_PORTA: TOGGLE_BIT(PORTA_REG,PinId); break;
		case DIO_PORTB: TOGGLE_BIT(PORTB_REG,PinId); break;
		case DIO_PORTC: TOGGLE_BIT(PORTC_REG,PinId); break;
		case DIO_PORTD: TOGGLE_BIT(PORTD_REG,PinId); break;
		}
	}
	else
	{
		//report error
	}
}
