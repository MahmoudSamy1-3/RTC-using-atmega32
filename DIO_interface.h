/*
 * DIO_interface.h

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/************************************************************************************/
/***********************************PUBLIC MACROS***********************************/
/**********************************************************************************/

/*****PORTS MACROS******/
#define DIO_PORTA       0
#define DIO_PORTB       1
#define DIO_PORTC       2
#define DIO_PORTD       3

/******PINS MACROS*****/
#define DIO_PIN0        0
#define DIO_PIN1        1
#define DIO_PIN2        2
#define DIO_PIN3        3
#define DIO_PIN4        4
#define DIO_PIN5        5
#define DIO_PIN6        6
#define DIO_PIN7        7

/*****OUTPUTS MACROS*****/
#define DIO_LOW         0
#define DIO_HIGH        1
#define DIO_PORT_HIGH   0xFF
#define DIO_PORT_LOW    0x00

/*****DIRECTIONS MACROS*****/
#define DIO_INPUT       0
#define DIO_OUTPUT      1
#define DIO_PORT_OUTPUT 0xFF
#define DIO_PORT_INPUT  0x00

/************************************************************************************/
/*********************************** PUBLIC FUNCTIONS ******************************/
/**********************************************************************************/
/* Description: This Function Setting Pin Direction
 * INPUT      : PortId, Range: 0~255 [DIO_PORTA~PORTD]
 *              PinId , Range: 0~255[DIO_PIN0~DIO_PIN7]
 *              PinDir, Range: 0~255[DIO_INPUT , DIO_OUTPUT]
 * Return     : void
 **************************************************************/
void DIO_voidSetPinDir (u8 PortId , u8 PinId , u8 PinDir);

/* Description: This Function Setting Pin Value
 * INPUT      : PortId, Range: 0~255 [DIO_PORTA~PORTD]
 *              PinId , Range: 0~255[DIO_PIN0~DIO_PIN7]
 *              PinVal, Range: 0~255[DIO_HIGH , DIO_LOW]
 * Return     : void
 **************************************************************/
void DIO_voidSetPinVal (u8 PortId , u8 PinId , u8 PinVal);

/* Description: This Function Setting Port Direction
 * INPUT      : PortId, Range: 0~255 [DIO_PORTA~PORTD]
 *              PinDir, Range: 0~255[DIO_INPUT , DIO_OUTPUT]
 * Return     : void
 **************************************************************/
void DIO_voidSetPortDir (u8 PortId , u8 PortDir);

/* Description: This Function Setting Port Value
 * INPUT      : PortId, Range: 0~255 [DIO_PORTA~PORTD]
 *              PinVal, Range: 0~255[DIO_HIGH , DIO_LOW]
 * Return     : void
 **************************************************************/
void DIO_voidSetPortVal (u8 PortId , u8 PortVal);

/* Description: This Function Setting Pin Direction
 * INPUT      : PortId, Range: 0~255 [DIO_PORTA~PORTD]
 *              PinId , Range: 0~255[DIO_PIN0~DIO_PIN7]
 * Return     : u8
 **************************************************************/
u8 DIO_u8GetPinVal (u8 PortId , u8 PinId);

/* Description: This Function Toggle Pin Value
 * INPUT      : PortId, Range: 0~255 [DIO_PORTA~PORTD]
 *              PinId , Range: 0~255[DIO_PIN0~DIO_PIN7]
 * Return     : void
 **************************************************************/
void DIO_voidTogglePinVal (u8 PortId , u8 PinId );


#endif /* DIO_INTERFACE_H_ */
