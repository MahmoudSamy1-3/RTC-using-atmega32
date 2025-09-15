/*
 * main.c
 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#include "LIB/STD_TYPES.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include "GLOBINT_interface.h"
#include "TIMER_interface.h"
#include "APP.h"

/* Global Variable */
volatile u16 u16Counter1 = 0;
volatile u8 u8Counter2   = 0;
u8 u8Seconds             = 0;
u8 u8Minutes             = 0;
u8 u8Hours               = 1;
u8 u8Day                 = 1;
u8 u8Month               = 0;
u8 u8Key                 = 0;
u8 u8Icon                = 0;
u8 u8TimeForm            = 0;
u8 u8TimeSetting         = 0;
u8 u8TimeChange          = 0;
u8 u8DateSetting         = 0;
u8 u8AlarmSetting        = 0;
u8 u8TimerSetting        = 0;
u8 u8TimerBuzzer         = 0;
u8 u8AlarmStatus         = 0;
u8 u8AlarmForm           = 0;
u8 u8Cursor              = 0;
u8 u8StartStopWatch      = 0;
u8 u8StartTimer          = 0;
u8 au8Alarm[3]           = {1 , 0 , 0};
u8 au8TimeSetting[3]     = {1 , 0 , 0};
u8 au8Timer[3]           = {0};
u8 au8StopWatch[3]       = {0};
u8 au8AlarmSymbol[]      = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
u8 au8TimerSymbol[]      = {0x1F, 0x1F, 0x1F, 0x0E, 0x15, 0x11, 0x1F, 0x00};
u8 au8Months[][4]        = {"Jan" , "Feb" , "Mar" , "Apr" , "May" , "Jun" , "Jul" , "AUG" , "Sep" , "Oct" , "Nov" , "Dec"};
u8 au8TimeForm[][3]      = {"PM" , "AM"};
u8 au8AlarmForm[][3]     = {"PM" , "AM"};
u16 u16Year              = 2024;

void GetTime(void);


void main(void)
{
	//Initializations
	u8 u8Str0[] = "     SETUP      "; //Icon1
	u8 u8Str1[] = "      TIME      "; //Icon2
	u8 u8Str2[] = "      DATE      "; //Icon3
	u8 u8Str3[] = "   STOPWATCH    "; //Icon4
	u8 u8Str4[] = "     ALARM      "; //Icon5
	u8 u8Str5[] = "    ALARM ON    "; //Icon6
	u8 u8Str6[] = "    ALARM OFF   "; //Icon7
    u8 u8Str7[] = "     TIMER      "; //Icon8
	u8 u8Str8[] = "   TIMER SET    "; //Icon9
	u8 u8Str9[] = "   TIMER CLR    "; //Icon10
	/* DIO Initialization */
	/* LCD */
	DIO_voidSetPortDir(DIO_PORTC , DIO_PORT_OUTPUT);
	DIO_voidSetPinDir(DIO_PORTD ,DIO_PIN0 ,DIO_OUTPUT);
	DIO_voidSetPinDir(DIO_PORTD ,DIO_PIN1 ,DIO_OUTPUT);
	DIO_voidSetPinDir(DIO_PORTD ,DIO_PIN2 ,DIO_OUTPUT);
	/* KPD*/
	DIO_voidSetPinDir(DIO_PORTB ,DIO_PIN0 ,DIO_OUTPUT);
	DIO_voidSetPinDir(DIO_PORTB ,DIO_PIN1 ,DIO_OUTPUT);
	DIO_voidSetPinDir(DIO_PORTB ,DIO_PIN2 ,DIO_OUTPUT);
	DIO_voidSetPinDir(DIO_PORTB ,DIO_PIN3 ,DIO_INPUT);
	DIO_voidSetPinDir(DIO_PORTB ,DIO_PIN4 ,DIO_INPUT);
	DIO_voidSetPortVal(DIO_PORTB ,DIO_PORT_HIGH);
	/* BUZZER */
	DIO_voidSetPinDir(DIO_PORTB ,DIO_PIN7 ,DIO_OUTPUT);
	DIO_voidSetPinVal(DIO_PORTB ,DIO_PIN7 ,DIO_LOW);

	/* LCD Initialization */
	LCD_voidCreateChar(au8AlarmSymbol , LCD_CUSTOM_CHAR1);
	LCD_voidCreateChar(au8TimerSymbol , LCD_CUSTOM_CHAR2);
	LCD_voidInit();
	LCD_voidClearDisplay();
	/* TIMER Initialization */
	TIMER0_voidInit();
	TIMER_voidCallBack(GetTime,TIMER0_CTC_VECTOR);

	/* GLOBAL INTERRUPT Initialization */
	GLOBINT_voidEnable();


	//LOOP
	while(1)
	{
		u8Key = KPD_u8GetKeyPressed();
		/* Time */
		if (u8Seconds > 59)
		{
			u8Seconds = 0;
			u8Minutes++;
		}

		if(u8Minutes > 59)
		{
			u8Minutes = 0;
			u8Hours ++ ;
		}

		if((u8Hours == 12) && (u8Minutes == 0) && (u8Seconds == 0))
		{
			if(u8TimeChange == 0 )
			{
				if (u8TimeForm == 1)
				{
					u8TimeForm = 0;
				}
				else
				{
					u8TimeForm = 1;
					u8Day++;
				}
				u8TimeChange = 1;
			}
		}
		else u8TimeChange = 0;

		if(u8Hours > 12)
		{
			u8Hours = 1;
		}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
		/* Date */
		if (u8Day <= 32)
		{
			if ((u8Day == 30) && (u8Month == FEB) &&(u16Year % 4 == 0 ))
			{
				u8Day = 1;
				u8Month++;
			}
			else if((u8Day == 29) && (u8Month == FEB) &&(u16Year % 4 != 0 ))
			{
				u8Day = 1;
				u8Month++;
			}
			else if((u8Day == 31) && ((u8Month == APR)||(u8Month == JUN)||(u8Month == SEP)||(u8Month == NOV)))
			{
				u8Day = 1;
				u8Month++;
			}
			else if ((u8Day == 32) && ((u8Month == JAN)||(u8Month == MAR)||(u8Month == MAY)||(u8Month == JUL)||(u8Month == AUG)||(u8Month == OCT)||(u8Month == DEC)))
			{
				u8Day = 1;
				u8Month++;
			}
		}

		if (u8Month > DEC)
		{
			u8Month = JAN;
			u16Year++;
		}
//----------------------------------------------------------------------------------------------------------------------------------------------------
		/* Alarm */
		if (u8AlarmStatus == 1)
		{
			LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM16);
			LCD_voidSendData(LCD_CUSTOM_CHAR1);
			if((u8Hours == au8Alarm[HOURS]) && (u8Minutes == au8Alarm[MINUTES]) && (u8TimeForm == u8AlarmForm) && (u8Seconds == au8Alarm[SECONDS]))
			{
				DIO_voidSetPinVal(DIO_PORTB ,DIO_PIN7 ,DIO_HIGH);
			}
			else if(((u8Hours == au8Alarm[HOURS]) && (u8Minutes > au8Alarm[MINUTES] ) && (u8TimeForm == u8AlarmForm) && (u8Seconds >= au8Alarm[SECONDS])) || (u8Key == 'E'))
			{
				DIO_voidSetPinVal(DIO_PORTB ,DIO_PIN7 ,DIO_LOW);
				u8AlarmStatus = 0;
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM16);
				LCD_voidSendData(' ');
			}
		}
//---------------------------------------------------------------------------------------------------------------------------------------------------
		/* Timer */
		if(u8StartTimer == 1)
		{
			LCD_voidSetPosition(LCD_LINE2 , LCD_COLUM16);
			LCD_voidSendData(LCD_CUSTOM_CHAR2);
			if(au8Timer[SECONDS] == 0)
			{
				if(au8Timer[MINUTES] > 0)
				{
					au8Timer[MINUTES] --;
					au8Timer[SECONDS] = 59;
				}
				else
				{
					if(au8Timer[HOURS] > 0)
					{
						au8Timer[HOURS] --;
						au8Timer[MINUTES] = 59;
						au8Timer[SECONDS] = 59;
					}
					else
					{
						if (u8TimerBuzzer == 0)
						{
							DIO_voidSetPinVal(DIO_PORTB , DIO_PIN7 , DIO_HIGH);
							au8Timer[SECONDS] = 10;
							u8TimerBuzzer = 1;
						}
						else
						{
							DIO_voidSetPinVal(DIO_PORTB , DIO_PIN7 , DIO_LOW);
							u8StartTimer = 0;
							LCD_voidSetPosition(LCD_LINE2 , LCD_COLUM16);
							LCD_voidSendData(' ');
							u8TimerBuzzer = 0;
						}
					}
				}
			}
			if ((u8Key == 'E') && (u8TimerBuzzer == 1))
			{
				DIO_voidSetPinVal(DIO_PORTB , DIO_PIN7 , DIO_LOW);
				u8StartTimer = 0;
				LCD_voidSetPosition(LCD_LINE2 , LCD_COLUM16);
				LCD_voidSendData(' ');
				u8TimerBuzzer = 0;
			}
		}
//***********************************************************************************************************************************
		/* Main Icon */
		if(u8Icon == 0)
		{
			LCD_voidDisableCursor();
			/* Time Show */
			if(u8Hours < 10)
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM3);
				LCD_voidSendData('0');
				LCD_voidSendInteger(u8Hours);
				LCD_voidSendData(':');
			}
			else
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM3);
				LCD_voidSendInteger(u8Hours);
				LCD_voidSendData(':');
			}

			if(u8Minutes < 10)
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM6);
				LCD_voidSendData('0');
				LCD_voidSendInteger(u8Minutes);
				LCD_voidSendData(':');
			}
			else
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM6);
				LCD_voidSendInteger(u8Minutes);
				LCD_voidSendData(':');
			}

			if(u8Seconds < 10)
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM9);
				LCD_voidSendData('0');
				LCD_voidSendInteger(u8Seconds);
				LCD_voidSendString(" ");
				LCD_voidSendString(&au8TimeForm[u8TimeForm]);
				LCD_voidSendString("  ");
			}
			else
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM9);
				LCD_voidSendInteger(u8Seconds);
				LCD_voidSendString(" ");
				LCD_voidSendString(&au8TimeForm[u8TimeForm]);
				LCD_voidSendString("  ");
			}

			/* Date Show */
			if(u8Day < 10)
			{
				LCD_voidSetPosition(LCD_LINE2 , LCD_COLUM4);
				LCD_voidSendData('0');
				LCD_voidSendInteger(u8Day);
				LCD_voidSendString(&au8Months[u8Month]);
				LCD_voidSendInteger(u16Year);
			}
			else
			{
				LCD_voidSetPosition(LCD_LINE2 , LCD_COLUM4);
				LCD_voidSendInteger(u8Day);
				LCD_voidSendString(&au8Months[u8Month]);
				LCD_voidSendInteger(u16Year);
			}

			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' :LCD_voidClearDisplay(); LCD_voidSendString(u8Str0); u8Icon = 1; break;
				}
			}
		}
//*************************************************************************************************************************************
		/* SETUP Icon */
		else if (u8Icon == 1)
		{
			LCD_voidDisableCursor();
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); u8Icon = 0; break;
				case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8Icon = 2; break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str3); u8Icon = 4; break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str7); u8Icon = 8; break;
				}
			}
		}
//***********************************************************************************************************************************************************************
		/* Time Setting Icon */
		else if(u8Icon == 2)
		{
			LCD_voidDisableCursor();
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str0); u8Icon = 1;                                                                                 break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str2); u8Icon = 3;                                                                                 break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str2); u8Icon = 3;                                                                                 break;
				case 'E' : LCD_voidClearDisplay(); au8TimeSetting[HOURS] = u8Hours; au8TimeSetting[MINUTES] = u8Minutes; au8TimeSetting[SECONDS] = u8Seconds; u8Icon = 14; break;
				}
			}
		}
//**************************************************************************************************************************************************************************
		/*  Date Setting Icon */
		else if(u8Icon == 3)
		{
			LCD_voidDisableCursor();
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str0); u8Icon = 1; break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8Icon = 2; break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8Icon = 2; break;
				case 'E' : LCD_voidClearDisplay();                             u8Icon =12; break;
				}
			}
		}
//***********************************************************************************************************************************
		/* STOPWATCH ICON */
		else if (u8Icon == 4)
		{
			LCD_voidDisableCursor();
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay();                              u8Icon = 0;  break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str4);  u8Icon = 5;  break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str0);  u8Icon = 1;  break;
				case 'E' : LCD_voidClearDisplay();                              u8Icon = 13; break;
				}
			}
		}
//**************************************************************************************************************************************
		/* Alarm Setting Icon */
		else if (u8Icon == 5)
		{
			LCD_voidDisableCursor();
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); u8Icon = 0; break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str7);  u8Icon = 8;  break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str3);  u8Icon = 4;  break;
				case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5);  u8Icon = 6;  break;
				}
			}
		}
//****************************************************************************************************************************************************
		/* Alarm on Icon */
		else if (u8Icon == 6)
		{
			LCD_voidDisableCursor();
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str4);  u8Icon = 5; break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str6);  u8Icon = 7; break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str6);  u8Icon = 7; break;
				case 'E' : LCD_voidClearDisplay();                              u8Icon = 11;break;
				}
			}
		}
//**********************************************************************************************************************************************************
		/* Alarm off Icon */
		else if (u8Icon == 7)
		{
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str4);  u8Icon = 5; break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5);  u8Icon = 6; break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5);  u8Icon = 6; break;
				case 'E' : LCD_voidClearDisplay(); u8Icon = 0;           u8AlarmStatus = 0; break;
				}
			}
		}
//**********************************************************************************************************************************************************
		/* TIMER Setting Icon */
		else if(u8Icon == 8)
		{
			LCD_voidDisableCursor();
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); u8Icon = 0;                              break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str0);  u8Icon = 1; break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str4);  u8Icon = 5; break;
				case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str8);  u8Icon = 9; break;
				}
			}
		}
//************************************************************************************************************************************************************
		/* Timer Set Icon */
		else if(u8Icon == 9)
		{
			LCD_voidDisableCursor();
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str7);  u8Icon = 8;  break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str9);  u8Icon = 10; break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str9);  u8Icon = 10; break;
				case 'E' : LCD_voidClearDisplay();                              u8Icon = 15; break;
				}
			}
		}
//********************************************************************************************************************************************************************
		/* Timer Clear Icon */
		else if(u8Icon == 10)
		{
			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str7);  u8Icon = 8;                   break;
				case 'R' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str8);  u8Icon = 9;                   break;
				case 'L' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str8);  u8Icon = 9;                   break;
				case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str7);  u8Icon = 8; u8StartTimer = 0; break;
				}
			}
		}
//**********************************************************************************************************************************************************
		/* Alarm Setting */
		else if (u8Icon == 11)
		{
			LCD_voidEnableCursor();
			if (u8AlarmSetting == 0)
			{
				if(au8Alarm[0] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM3);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8Alarm[HOURS]);
					LCD_voidSendData(':');
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM3);
					LCD_voidSendInteger(au8Alarm[HOURS]);
					LCD_voidSendData(':');
				}

				if(au8Alarm[1] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM6);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8Alarm[MINUTES]);
					LCD_voidSendData(':');
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM6);
					LCD_voidSendInteger(au8Alarm[MINUTES]);
					LCD_voidSendData(':');
				}

				if(au8Alarm[2] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM9);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8Alarm[SECONDS]);
					LCD_voidSendData(' ');
					LCD_voidSendString(&au8AlarmForm[u8AlarmForm]);
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM9);
					LCD_voidSendInteger(au8Alarm[SECONDS]);
					LCD_voidSendData(' ');
					LCD_voidSendString(&au8AlarmForm[u8AlarmForm]);
				}
				u8AlarmSetting = 1;
			}

			if (u8Cursor == 0)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM4);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5); u8Cursor = 0; u8Icon = 6; u8AlarmSetting = 0;                   break;
					case 'R' : u8Cursor = 1; u8AlarmSetting = 0;                                                                                   break;
					case 'L' : u8Cursor = 3; u8AlarmSetting = 0;                                                                                   break;
					case 'U' : au8Alarm[HOURS]++; if (au8Alarm[HOURS] == 13) au8Alarm[HOURS] = 1;  u8AlarmSetting = 0;                             break;
					case 'D' : if (au8Alarm[HOURS] == 1) au8Alarm[HOURS] = 13;  au8Alarm[HOURS]--; u8AlarmSetting = 0;                             break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5); u8Cursor = 0; u8Icon =6; u8AlarmStatus = 1; u8AlarmSetting = 0; break;
					}
				}
			}
			else if(u8Cursor == 1)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM7);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5); u8Cursor = 0; u8Icon = 6; u8AlarmSetting = 0;                   break;
					case 'R' : u8Cursor = 2; u8AlarmSetting = 0;                                                                                   break;
					case 'L' : u8Cursor = 0; u8AlarmSetting = 0;                                                                                   break;
					case 'U' : au8Alarm[MINUTES]++; if (au8Alarm[MINUTES] == 60) au8Alarm[MINUTES] = 0;  u8AlarmSetting = 0;                       break;
					case 'D' : if (au8Alarm[MINUTES] == 0) au8Alarm[MINUTES] = 60;  au8Alarm[MINUTES]--; u8AlarmSetting = 0;                       break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5); u8Cursor = 0; u8Icon =6; u8AlarmStatus = 1; u8AlarmSetting = 0; break;
					}
				}
			}
			else if (u8Cursor == 2)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM10);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5); u8Cursor = 0; u8Icon = 6; u8AlarmSetting = 0;                    break;
					case 'R' : u8Cursor = 3; u8AlarmSetting = 0;                                                                                    break;
					case 'L' : u8Cursor = 1; u8AlarmSetting = 0;                                                                                    break;
					case 'U' : au8Alarm[SECONDS]++; if(au8Alarm[SECONDS] == 60) au8Alarm[SECONDS] = 0;    u8AlarmSetting = 0;                       break;
					case 'D' : if (au8Alarm[SECONDS] == 0) au8Alarm[SECONDS] = 60;  au8Alarm[SECONDS]--;  u8AlarmSetting = 0;                       break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5); u8Cursor = 0; u8Icon =6; u8AlarmStatus = 1;  u8AlarmSetting = 0; break;
					}
				}
			}
			else if(u8Cursor == 3)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM12);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5); u8Cursor = 0;  u8Icon = 6; u8AlarmSetting = 0;                  break;
					case 'R' : u8Cursor = 0;   u8AlarmSetting = 0;                              												   break;
					case 'L' : u8Cursor = 2;   u8AlarmSetting = 0;                            													   break;
					case 'U' : u8AlarmForm =1; u8AlarmSetting = 0;                           													   break;
					case 'D' : u8AlarmForm =0; u8AlarmSetting = 0;                           													   break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str5); u8Cursor = 0; u8Icon =6; u8AlarmStatus = 1; u8AlarmSetting = 0; break;
					}
				}
			}
		}
//***********************************************************************************************************************************************************************************************************************************************************
		/* Date Setting */
		else if (u8Icon == 12)
		{
			LCD_voidEnableCursor();
			if(u8DateSetting == 0)
			{
				if(u8Day < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM4);
					LCD_voidSendData('0');
					LCD_voidSendInteger(u8Day);
					LCD_voidSendString(&au8Months[u8Month]);
					LCD_voidSendInteger(u16Year);
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM4);
					LCD_voidSendInteger(u8Day);
					LCD_voidSendString(&au8Months[u8Month]);
					LCD_voidSendInteger(u16Year);
				}
				u8DateSetting = 1;
			}

			if (u8Cursor == 0)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM5);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str2); u8Cursor = 0; u8Icon = 3; u8DateSetting = 0; break;
					case 'R' : u8Cursor = 1; u8DateSetting = 0; break;
					case 'L' : u8Cursor = 2; u8DateSetting = 0; break;
					case 'U' :
						u8Day++;
						if((u8Day == 30) && (u8Month == FEB) && ((u16Year % 4) == 0 )) u8Day = 1;
						else if ((u8Day == 29) && (u8Month == FEB) && ((u16Year % 4) != 0 )) u8Day = 1;
						else if ((u8Day == 31) && ((u8Month == APR)||(u8Month == JUN)||(u8Month == SEP)||(u8Month == NOV))) u8Day = 1;
						else if (u8Day == 32) u8Day = 1; u8DateSetting = 0; break;
					case 'D' :
						if((u8Day == 1) && (u8Month == FEB) && ((u16Year % 4) == 0 )) u8Day = 30;
						else if ((u8Day == 1) && (u8Month == FEB) && ((u16Year % 4) != 0 )) u8Day = 29;
						else if ((u8Day == 1) && ((u8Month == APR)||(u8Month == JUN)||(u8Month == SEP)||(u8Month == NOV))) u8Day = 31;
						else if ((u8Day == 1) && ((u8Month == JAN)||(u8Month == MAR)||(u8Month == MAY)||(u8Month == JUL)||(u8Month == AUG)||(u8Month == OCT)||(u8Month == DEC))) u8Day = 32;
						u8Day-- ; u8DateSetting = 0; break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str2); u8Cursor = 0; u8Icon =3; u8DateSetting = 0; break;
					}
				}
			}

			else if(u8Cursor == 1)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM8);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str2); u8Cursor = 0; u8Icon = 3; u8DateSetting = 0; break;
					case 'R' : u8Cursor = 2; u8DateSetting = 0;                              									break;
					case 'L' : u8Cursor = 0; u8DateSetting = 0;                              								    break;
					case 'U' : u8Month++; if ( u8Month > DEC) u8Month = JAN; u8DateSetting = 0;                                 break;
					case 'D' : if (u8Month == JAN) u8Month = DEC + 1;  u8Month--; u8DateSetting = 0;                            break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str2); u8Cursor = 0; u8Icon =3; u8DateSetting = 0;  break;
					}
				}
			}
			else if (u8Cursor == 2)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM12);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str2); u8Cursor = 0; u8Icon = 3; u8DateSetting = 0;  break;
					case 'R' : u8Cursor = 0; u8DateSetting = 0;                               									 break;
					case 'L' : u8Cursor = 1; u8DateSetting = 0;                               									 break;
					case 'U' : u16Year++; u8DateSetting = 0;                                                                     break;
					case 'D' : u16Year--; u8DateSetting = 0;                                                                     break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str2); u8Cursor = 0; u8Icon =3; u8DateSetting = 0;   break;
					}
				}
			}
		}
//***********************************************************************************************************************************************************************************************************************************************************
		/* Stop Watch Show */
		else if (u8Icon == 13)
		{
			if(au8StopWatch[SW_MINUTES] < 10)
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM5);
				LCD_voidSendData('0');
				LCD_voidSendInteger(au8StopWatch[SW_MINUTES]);
				LCD_voidSendString(":");
			}
			else if (au8StopWatch[SW_MINUTES] < 60)
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM5);
				LCD_voidSendInteger(au8StopWatch[SW_MINUTES]);
				LCD_voidSendString(":");
			}
			else
			{
				au8StopWatch[SW_MINUTES] = 0;
			}

			if(au8StopWatch[SW_SECONDS] < 10)
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM8);
				LCD_voidSendData('0');
				LCD_voidSendInteger(au8StopWatch[SW_SECONDS]);
				LCD_voidSendString(":");
			}
			else if (au8StopWatch[SW_SECONDS] < 60)
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM8);
				LCD_voidSendInteger(au8StopWatch[SW_SECONDS]);
				LCD_voidSendString(":");
			}
			else
			{
				au8StopWatch[SW_SECONDS] = 0;
				au8StopWatch[SW_MINUTES]++;
			}

			if(au8StopWatch[MILLI_SECONDS] < 100)
			{
				LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM11);
				if (au8StopWatch[MILLI_SECONDS] == 0) LCD_voidSendData('0');
				LCD_voidSendInteger(au8StopWatch[2]);
			}
			else
			{
				au8StopWatch[MILLI_SECONDS] = 0;
				au8StopWatch[SW_SECONDS]++;
			}

			if(u8Key != NULL)
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str3);  u8Icon = 4; u8StartStopWatch = 0; au8StopWatch[SW_MINUTES] = 0; au8StopWatch[SW_SECONDS] = 0; au8StopWatch[MILLI_SECONDS] = 0;  break;
				case 'E' : u8StartStopWatch = 1;                                                                  																                                break;
				}
			}

		}
//*****************************************************************************************************************************************************************************************************************************************************************
		/* Time Setting */
		else if (u8Icon == 14)
		{
			LCD_voidEnableCursor();
			if (u8TimeSetting == 0)
			{
				if(au8TimeSetting[HOURS] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM3);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8TimeSetting[HOURS]);
					LCD_voidSendData(':');
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM3);
					LCD_voidSendInteger(au8TimeSetting[HOURS]);
					LCD_voidSendData(':');
				}

				if(au8TimeSetting[MINUTES] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM6);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8TimeSetting[MINUTES]);
					LCD_voidSendData(':');
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM6);
					LCD_voidSendInteger(au8TimeSetting[MINUTES]);
					LCD_voidSendData(':');
				}

				if(au8TimeSetting[SECONDS] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM9);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8TimeSetting[SECONDS]);
					LCD_voidSendData(' ');
					LCD_voidSendString(&au8TimeForm[u8TimeForm]);
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM9);
					LCD_voidSendInteger(au8TimeSetting[SECONDS]);
					LCD_voidSendData(' ');
					LCD_voidSendString(&au8TimeForm[u8TimeForm]);
				}
				u8TimeSetting = 1;
			}

			if (u8Cursor == 0)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM4);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8Cursor = 0; u8Icon = 2; u8TimeSetting = 0;                                                                                                            break;
					case 'R' : u8Cursor = 1; u8TimeSetting = 0;                                                                                          																                   break;
					case 'L' : u8Cursor = 3; u8TimeSetting = 0;                                                                                          	  															               	   break;
					case 'U' : au8TimeSetting[HOURS]++; if (au8TimeSetting[HOURS] == 13) au8TimeSetting[HOURS] = 1;      u8TimeSetting = 0;                                                                                                break;
					case 'D' : if (au8TimeSetting[HOURS] == 1) au8TimeSetting[HOURS] = 13;  au8TimeSetting[HOURS]--;     u8TimeSetting = 0;                                                                                                break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8TimeSetting = 0; u8Cursor = 0; u8Icon = 2; u8Hours = au8TimeSetting[HOURS]; u8Minutes = au8TimeSetting[MINUTES]; u8Seconds = au8TimeSetting[SECONDS]; break;
					}
				}
			}
			else if(u8Cursor == 1)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM7);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8Cursor = 0; u8Icon = 2; u8TimeSetting = 0;   																						                   break;
					case 'R' : u8Cursor = 2; u8TimeSetting = 0;                    																																			               break;
					case 'L' : u8Cursor = 0; u8TimeSetting = 0;                      																																		               break;
					case 'U' : au8TimeSetting[MINUTES]++; if (au8TimeSetting[MINUTES] == 60) au8TimeSetting[MINUTES] = 0;      u8TimeSetting = 0;                            														       break;
					case 'D' : if (au8TimeSetting[MINUTES] == 0) au8TimeSetting[MINUTES] = 60; au8TimeSetting[MINUTES]--;      u8TimeSetting = 0;                                              											   break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8TimeSetting = 0; u8Cursor = 0; u8Icon = 2; u8Hours = au8TimeSetting[HOURS]; u8Minutes = au8TimeSetting[MINUTES]; u8Seconds = au8TimeSetting[SECONDS]; break;
					}
				}
			}
			else if (u8Cursor == 2)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM10);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8Cursor = 0; u8Icon = 2; u8TimeSetting = 0;																							   				   break;
					case 'R' : u8Cursor = 3; u8TimeSetting = 0;                       																	                                                              	   				   break;
					case 'L' : u8Cursor = 1; u8TimeSetting = 0;                      																		                                                                			   break;
					case 'U' : au8TimeSetting[SECONDS]++; if (au8TimeSetting[SECONDS] == 60 ) au8TimeSetting[SECONDS] = 0 ; u8TimeSetting = 0;                              															   break;
					case 'D' : if (au8TimeSetting[SECONDS] == 0) au8TimeSetting[SECONDS] = 60;  au8TimeSetting[SECONDS]--;  u8TimeSetting = 0;                                           												   break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8TimeSetting = 0; u8Cursor = 0; u8Icon = 2; u8Hours = au8TimeSetting[HOURS]; u8Minutes = au8TimeSetting[MINUTES]; u8Seconds = au8TimeSetting[SECONDS]; break;
					}
				}
			}
			else if(u8Cursor == 3)
			{
				LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM13);
				if(u8Key != NULL)
				{
					switch(u8Key)
					{
					case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8Cursor = 0;  u8Icon = 2; u8TimeSetting = 0;																						                   break;
					case 'R' : u8Cursor = 0; u8TimeSetting = 0;                     																																		               break;
					case 'L' : u8Cursor = 2; u8TimeSetting = 0;                      																																		               break;
					case 'U' : u8TimeForm =1;u8TimeSetting = 0;                       																																		               break;
					case 'D' : u8TimeForm =0;u8TimeSetting = 0;                      																																	                   break;
					case 'E' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str1); u8TimeSetting = 0; u8Cursor = 0; u8Icon = 2; u8Hours = au8TimeSetting[HOURS]; u8Minutes = au8TimeSetting[MINUTES]; u8Seconds = au8TimeSetting[SECONDS]; break;
					}
				}
			}
		}
//******************************************************************************************************************************************************************************************************************************************************
		/* Timer Show and Setting */
		else if (u8Icon == 15)
		{
			if (u8StartTimer == 1) LCD_voidDisableCursor();
			else LCD_voidEnableCursor();
			if(u8TimerSetting == 0)
			{
				if(au8Timer[HOURS] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM5);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8Timer[HOURS]);
					LCD_voidSendString(":");
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM5);
					LCD_voidSendInteger(au8Timer[HOURS]);
					LCD_voidSendString(":");
				}

				if(au8Timer[MINUTES] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM8);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8Timer[MINUTES]);
					LCD_voidSendString(":");
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM8);
					LCD_voidSendInteger(au8Timer[MINUTES]);
					LCD_voidSendString(":");
				}

				if(au8Timer[SECONDS] < 10)
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM11);
					LCD_voidSendData('0');
					LCD_voidSendInteger(au8Timer[2]);
				}
				else
				{
					LCD_voidSetPosition(LCD_LINE1 , LCD_COLUM11);
					LCD_voidSendInteger(au8Timer[SECONDS]);
				}

				if (u8StartTimer == 1) u8TimerSetting = 0;
				else u8TimerSetting = 1;
			}

			if(u8StartTimer == 0)
			{
				if (u8Cursor == 0)
				{
					LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM6);
					if(u8Key != NULL)
					{
						switch(u8Key)
						{
						case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str8); u8Cursor = 0; u8Icon = 9; u8TimerSetting = 0; break;
						case 'R' : u8Cursor = 1; u8TimerSetting = 0;                               									 break;
						case 'L' : u8Cursor = 2; u8TimerSetting = 0;                              									 break;
						case 'U' : au8Timer[HOURS]++; if (au8Timer[HOURS] == 25) au8Timer[HOURS] = 0;  u8TimerSetting = 0;           break;
						case 'D' : if (au8Timer[HOURS] == 0) au8Timer[HOURS] = 25;  au8Timer[HOURS]--; u8TimerSetting = 0;           break;
						case 'E' : u8StartTimer = 1;                                       u8TimerSetting = 0;                       break;
						}
					}
				}
				else if(u8Cursor == 1)
				{
					LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM9);
					if(u8Key != NULL)
					{
						switch(u8Key)
						{
						case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str8); u8Cursor = 0; u8Icon = 9; u8TimerSetting = 0; break;
						case 'R' : u8Cursor = 2; u8TimerSetting = 0;                                								 break;
						case 'L' : u8Cursor = 0; u8TimerSetting = 0;                               									 break;
						case 'U' : au8Timer[MINUTES]++; if(au8Timer[MINUTES] == 60) au8Timer[MINUTES] = 0;  u8TimerSetting = 0;      break;
						case 'D' : if (au8Timer[MINUTES] == 0) au8Timer[MINUTES] = 60; au8Timer[MINUTES]--; u8TimerSetting = 0;      break;
						case 'E' : u8StartTimer = 1;                                      u8TimerSetting = 0;                        break;
						}
					}
				}
				else if (u8Cursor == 2)
				{
					LCD_voidSetPosition(LCD_LINE1 ,LCD_COLUM12);
					if(u8Key != NULL)
					{
						switch(u8Key)
						{
						case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str8); u8Cursor = 0; u8Icon = 9; u8TimerSetting = 0; break;
						case 'R' : u8Cursor = 0; u8TimerSetting = 0;                            									 break;
						case 'L' : u8Cursor = 1;  u8TimerSetting = 0;                         										 break;
						case 'U' : au8Timer[SECONDS]++; if (au8Timer[SECONDS] == 60) au8Timer[SECONDS] = 0;  u8TimerSetting = 0;     break;
						case 'D' : if (au8Timer[SECONDS] == 0) au8Timer[SECONDS] = 60;  au8Timer[SECONDS]--; u8TimerSetting = 0;     break;
						case 'E' : u8StartTimer = 1;                                       u8TimerSetting = 0;                       break;
						}
					}
				}
			}
			else
			{
				switch(u8Key)
				{
				case 'M' : LCD_voidClearDisplay(); LCD_voidSendString(u8Str8); u8Cursor = 0; u8Icon = 9; u8TimerSetting = 0; break;
				}
			}
		}
	}
}

/* ISR FUNCTION */
void GetTime(void)
{
	u16Counter1++;
	if (u16Counter1 == 1000)
	{
		u16Counter1 = 0;
		u8Seconds++;
		if((u8StartTimer == 1) && (au8Timer[2] > 0)) au8Timer[2]--;
	}
	if (u8StartStopWatch == 1)
	{
		u8Counter2++;
		if(u8Counter2 == 10)
		{
			u8Counter2 = 0;
			au8StopWatch[2]++;
		}
	}
}
