/*
 * LCD_program.c

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#include <avr/delay.h>
#include "LIB/STD_TYPES.h"
#include "DIO_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#define F_CBU 8000000UL

void LCD_voidInit(void)
{
	/* wait for more than 30ms to ensure mc initialization */
	_delay_ms(50);

	/* Function Set Command*/
	LCD_voidSendCommand(LCD_FUNCTION_SET_8BIT);
	_delay_ms(1);

	/* Display ON/OFF */
	LCD_voidSendCommand(LCD_DISP_ON_CURSOR_ON);
	_delay_ms(15);

	 /* RETURN CURSOR TO FIRST POSITION FIRST LINE */
	LCD_voidSendCommand(LCD_RETURN_HOME );
	_delay_ms(15);

	/* Entry Mode Command */
	LCD_voidSendCommand(LCD_ENTERY_MODE);
	_delay_ms(2);
}

void LCD_voidSendCommand(u8 u8cmd)
{
	/* Clear RS Pin	 */
	DIO_voidSetPinVal(LCD_CONTROL_PORT , LCD_RS_PIN , DIO_LOW);

	/* Clear RW Pin */
	DIO_voidSetPinVal(LCD_CONTROL_PORT , LCD_RW_PIN , DIO_LOW);

	/* Load Command to the Data Pins */
	DIO_voidSetPortVal(LCD_DATA_PORT , u8cmd);

	/* Set E Pin to High */
	DIO_voidSetPinVal(LCD_CONTROL_PORT , LCD_E_PIN , DIO_HIGH);
	_delay_ms(5);

	/* Clear E Pin */
	DIO_voidSetPinVal(LCD_CONTROL_PORT , LCD_E_PIN , DIO_LOW);
	_delay_ms(5);
}

void LCD_voidSendData(u8 u8CharData)
{
	/* Set RS Pin to High	 */
	DIO_voidSetPinVal(LCD_CONTROL_PORT , LCD_RS_PIN , DIO_HIGH);

	/* Clear RW Pin */
	DIO_voidSetPinVal(LCD_CONTROL_PORT , LCD_RW_PIN , DIO_LOW);

	/* Load Command to the Data Pins */
	DIO_voidSetPortVal(LCD_DATA_PORT , u8CharData);

	/* Set E Pin to High */
	DIO_voidSetPinVal(LCD_CONTROL_PORT , LCD_E_PIN , DIO_HIGH);
	_delay_ms(5);

	/* Clear E Pin */
	DIO_voidSetPinVal(LCD_CONTROL_PORT , LCD_E_PIN , DIO_LOW);
	_delay_ms(5);
}

void LCD_voidSetPosition(u8 u8Row , u8 u8Col)
{
	if((u8Row <= LCD_LINE2) && (u8Col <= LCD_COLUM16))
	{
		switch(u8Row)
		{
		case LCD_LINE1: LCD_voidSendCommand(LCD_CURSOR_SET + u8Col); break;
		case LCD_LINE2: LCD_voidSendCommand(0xC0 + u8Col);           break;
		}
	}

}

void LCD_voidSendString(u8* pu8Str)
{
	u8 u8Iterator = 0;
	while(pu8Str[u8Iterator] != '\0')
	{
		LCD_voidSendData(pu8Str[u8Iterator]);
		u8Iterator++;
	}
}

void LCD_voidClearDisplay(void)
{
	LCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(5);
}

void LCD_voidClearLine(u8 u8LineNum)
{

	if(u8LineNum <= LCD_LINE2)
	{
		LCD_voidSetPosition(u8LineNum , LCD_COLUM1); // set cursor position on LineNum first column
		switch(u8LineNum)
		{
		case LCD_LINE1: LCD_voidSendString("                "); break;
		case LCD_LINE2: LCD_voidSendString("                "); break;
		}
	}
}

void LCD_voidCreateChar(u8* pu8CustomChar , u8 u8CharLocation)
{
	u8 u8Iterator;
	if(u8CharLocation <= LCD_CUSTOM_CHAR8)
	{
		LCD_voidSendCommand((u8CharLocation * 8) + LCD_FIRST_CUSTOM_CHAR);   // 0x40 is the first location in CGRAM every location 8bit
		for(u8Iterator = 0 ; u8Iterator < 8 ; u8Iterator++)
		{
			LCD_voidSendData(pu8CustomChar[u8Iterator]);
		}
	}

}

void LCD_voidSendInteger(u32 u32IntData)
{
	u8 au8IntToCharConvert[NUMBER_OF_DIGITS] = {};
	u8 u8Iterator;
	u8 u8Quotient;
	u8 u8LastIndex;    //Number of  Digits for Entry number
	u8 u8Flag = 1;    //For Get u8LastIndex
	u32 u32Remainder;
	u32 u32Divisor;

	for(u8Iterator = NUMBER_OF_DIGITS ; u8Iterator >= 1 ; u8Iterator--)
	{
		u32Divisor = u32Power(BASE,u8Iterator);
		/********Get Number of Digits For Entry Number******/
		if(u32IntData < u32Divisor)
		{
			continue;
		}
		else
		{
			if(u8Flag == 1)
			{
				u8LastIndex = u8Iterator;
			}
			u8Flag = 0;
			u8Quotient  = u32IntData / u32Divisor;
			u32 u32Remainder = u32IntData % u32Divisor;
			/*************Print Multiples of 10*************/
			if((u32Remainder == 0) && (u8Iterator >= 1))
			{
				au8IntToCharConvert[u8LastIndex - u8Iterator] = u8Quotient +'0';
				while(u8Iterator != 0)
				{
					u8Iterator --;
					au8IntToCharConvert[u8LastIndex - u8Iterator] = '0';
				}
				LCD_voidSendString(au8IntToCharConvert);
				break;
			}
			/************Print 0 in Middle of Number**********/
			if(u32Remainder < (u32Divisor /BASE))
			{
				au8IntToCharConvert[u8LastIndex - u8Iterator] = u8Quotient +'0';
				while(u32Remainder < (u32Divisor /BASE))
				{
					u8Iterator--;
					u32Divisor /= BASE;
					au8IntToCharConvert[u8LastIndex - u8Iterator] = '0';
				}
				if(u8Iterator > 1)
				{
					u32IntData = u32Remainder;
					continue;
				}
				else
				{
					au8IntToCharConvert[u8LastIndex] = u32Remainder + '0';
					LCD_voidSendString(au8IntToCharConvert);
					break;
				}

			}
			/* print Normal Number without zeros in it*/
			au8IntToCharConvert[u8LastIndex - u8Iterator] = u8Quotient +'0';
			if(u8Iterator > 1)
			{
				u32IntData = u32Remainder;
				continue;
			}
			else
			{
				au8IntToCharConvert[u8LastIndex] = u32Remainder + '0';
				LCD_voidSendString(au8IntToCharConvert);
				break;
			}
		}
	}
	/* print Integer Number if it One Digit */
	if(u8Flag == 1)
	{
		LCD_voidSendData((u32IntData + '0'));
	}
}


void LCD_voidDisableCursor()
{
	/* Disable Cursor */
	LCD_voidSendCommand(LCD_DISP_ON_CURSOR_OFF);
	_delay_ms(15);
}


void LCD_voidEnableCursor()
{
	/* Enable Cursor */
	LCD_voidSendCommand(LCD_DISP_ON_CURSOR_ON);
	_delay_ms(15);
}


u32 u32Power(u8 u8Base , u8 u8Exp)
{
	u32 u32Result = 1;
	while (u8Exp != 0)
	{
		u32Result *= u8Base;
		u8Exp--;
	}
	return u32Result;
}
