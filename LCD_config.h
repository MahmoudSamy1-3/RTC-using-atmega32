/*
 * LCD_config.h

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
/***********************************LCD CONNECTION CONFIG **************************/
/* DESCRIPION : LCD DATA_PORT & CONTROL_PPRT CONFIG
 * OPTIONS    : DIO_PORTA ~ DIO_PORTD
 ******************************************/
#define LCD_DATA_PORT       DIO_PORTC
#define LCD_CONTROL_PORT    DIO_PORTD

/* DESCRIPION : LCD CONTRO PIN CONFIG
 * OPTIONS    : DIO_PIN0 ~ DIO_PIN7
 ******************************************/
#define LCD_RS_PIN          DIO_PIN2
#define LCD_RW_PIN          DIO_PIN1
#define LCD_E_PIN           DIO_PIN0

/**************************************LCD INITILAZATION CONIG*********************/
/* DESCRIPTION : LCD CONNECTION MODE
 * OPTIONS     : LCD_8BIT_MODE , LCD_4BIT_MODE
 */
#define LCD_MODE            LCD_8BIT_MODE

/* DESCIPTION : NUMBER OF INTERGER DIGITS THAT YOU WANT PRINT ON LCD SCREEN
 * OPTIONS    : 1 ~ 9
 *************************************************************************/
#define NUMBER_OF_DIGITS          9
#endif /* LCD_CONFIG_H_ */
