/*
 * KPD_config.h

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

/******************************KPD CONNECTION CONFIG*****************/
/* DESCRIPTION : KPD ROWS & COLUMNS PORT
 * OPTIONS     : DIO_PORTA ~DIO_PORTD
 ***************************************/
#define KPD_ROWS_PORT                       DIO_PORTB
#define KPD_COLUMNS_PORT                    DIO_PORTB

/* DESCRIPTION : KPD NUMBER OF ROWS & COLUMNS &PINS THAT CONNECTION EACH OF THEM
 * OPTIONS     : DIO_PIN0 ~DIO_PIN7
 ***************************************/
/******************KPD NUMBER OF COLUMNS & EACH COULMN PIN**************/
#define KPD_COLUMNS                          3
#define KPD_COLUMN1                          DIO_PIN0
#define KPD_COLUMN2                          DIO_PIN1
#define KPD_COLUMN3                          DIO_PIN2



/****************KPD NUMBER OF ROWS & EACH ROW PIN******************/
#define KPD_ROWS                            2
#define KPD_ROW1                            DIO_PIN3
#define KPD_ROW2                            DIO_PIN4


/************************KPD MATRIX CONFIG***********************/
#define KPD_MATRIX                  {{'M','U','E'},{'L','D','R'}}



#endif /* KPD_CONFIG_H_ */
