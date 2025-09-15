/*
 * KPD_program.c

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#include "LIB/STD_TYPES.h"
#include <avr/delay.h>
#define F_CPU 8000000UL
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"
#include "KPD_interface.h"

static u8 au8KeyPressed[KPD_ROWS][KPD_COLUMNS] = KPD_MATRIX;

u8 KPD_u8GetKeyPressed(void)
{
	u8 u8ColIterator;
	u8 u8RowIterator;
	u8 u8KeyPressed = NULL;
	/* Loop over keypad columns to apply output"LOW" */
	for(u8ColIterator = KPD_COLUMN1 ; u8ColIterator < (KPD_COLUMNS + KPD_COLUMN1) ; u8ColIterator++)
	{
		/* reset column pin */
		DIO_voidSetPinVal(KPD_COLUMNS_PORT , u8ColIterator ,DIO_LOW);
		for(u8RowIterator = KPD_ROW1 ; u8RowIterator < (KPD_ROWS + KPD_ROW1) ; u8RowIterator++)
		{
			/* get row pin status and check if it (HIGH OR LOW) to get key preesed */
			if(DIO_u8GetPinVal(KPD_ROWS_PORT,u8RowIterator) == DIO_LOW)
			{
				/* get the key pressed value */
				u8KeyPressed = au8KeyPressed[u8RowIterator-KPD_ROW1][u8ColIterator-KPD_COLUMN1];
				/* stuck here until key not pressed */
				while(DIO_u8GetPinVal(KPD_ROWS_PORT,u8RowIterator) == DIO_LOW);
				_delay_ms(10);
			}
		}
		/* set column pin */
		DIO_voidSetPinVal(KPD_COLUMNS_PORT , u8ColIterator ,DIO_HIGH);
	}
	return u8KeyPressed;
}
