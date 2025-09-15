/*
 * KPD_interface.h

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_
/**************************************************************/
/*********************PUBLIC MACROS***************************/
/***********************************************************/
#define NULL  '\0'

/************************************************************/
/***********************PUBLIC FUNCTION*********************/
/*********************************************************/
/*DESCRIPTION : GET PUSH BUTTON PRESSSED
 * INPUT      : void
 * RETURN     : u8 ,Range: 0~255
 *************************************************************/
u8 KPD_u8GetKeyPressed(void);



#endif /* KPD_INTERFACE_H_ */
