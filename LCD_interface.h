/*
 * LCD_interface.h

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/***************************************************************/
/*************************PUBLIC MACROS************************/
/*************************************************************/
/*******LCD CONTROL COMMANDS******/
#define LCD_CLEAR                      0x01   // CLEAR LCD DISPLAY
#define LCD_RETURN_HOME                0x02   // RETURN CURSOR TO FIRST POSITION FIRST LINE
#define LCD_ENTERY_MODE                0x06   // shift cursor from left to right on read/write
#define LCD_ENTERY_MODE2               0x04   // shift cursor from right to left on read/write
#define LCD_DISPLAY_OFF                0x08   // display off
#define LCD_DISP_ON_CURSOR_ON          0x0E   // display on , cursor on ,  blinking off
#define LCD_DISP_ON_CURSOR_OFF         0x0C   // display on , cursor off , blinking off
#define LCD_DIS_ON_CURSOR_BLINKING     0x0F   // display on , cursor on ,  blinking on
#define LCD_FUNCTION_SET_8BIT          0x38   // 8bit mode ,2-line . 5*8 dots FONT
#define LCD_FUNCTION_SET_4BIT          0x28   // 4bit mode ,2-line . 5*8 dots FONT
#define LCD_CURSOR_SET                 0x80   // cursor position
#define LCD_DISP_SHIFT_LEFT            0x18   // shift the entire display to left
#define LCD_DISP_SHIFT_RIGHT           0x1C   // shift the entire display to right
#define LCD_CUR_SHIFT_LEFT             0x10   // shift the cursor position to left
#define LCD_CUR_SHIFT_RIGHT            0x14   // shift the cursor position to right
#define LCD_FIRST_CUSTOM_CHAR          0x40   // access first location in CG_Ram

/**************LCD CONNECTION MODE*****************/
#define LCD_4BIT_MODE                  4
#define LCD_8BIT_MODE                  8

/**************LCD SCREEN POSITION*****************/
/******ROW********/
#define LCD_LINE1     0
#define LCD_LINE2     1

/******COLUM******/
#define LCD_COLUM1    0
#define LCD_COLUM2    1
#define LCD_COLUM3    2
#define LCD_COLUM4    3
#define LCD_COLUM5    4
#define LCD_COLUM6    5
#define LCD_COLUM7    6
#define LCD_COLUM8    7
#define LCD_COLUM9    8
#define LCD_COLUM10   9
#define LCD_COLUM11   10
#define LCD_COLUM12   11
#define LCD_COLUM13   12
#define LCD_COLUM14   13
#define LCD_COLUM15   14
#define LCD_COLUM16   15

/************ CUSTOM CHARACTER LOCATIONS***********/
#define LCD_CUSTOM_CHAR1  0
#define LCD_CUSTOM_CHAR2  1
#define LCD_CUSTOM_CHAR3  2
#define LCD_CUSTOM_CHAR4  3
#define LCD_CUSTOM_CHAR5  4
#define LCD_CUSTOM_CHAR6  5
#define LCD_CUSTOM_CHAR7  6
#define LCD_CUSTOM_CHAR8  7

/***************************************************************/
/***********************PUBLIC FUNCTIONS***********************/
/*************************************************************/
/* DESCRIPTION : LCD Initialization
 * INPUT       : void
 * RETURN      : void
 *************************************************/
void LCD_voidInit(void);

/* DESCRIPTION : Send Command to LCD
 * INPUT       : Control Command
 * RETURN      : void
 *************************************************/
void LCD_voidSendCommand(u8 u8cmd);

/* DESCRIPTION : Send Char to LCD For Display on Screen
 * INPUT       : u8CharData, Rang: 0~255
 * RETURN      : void
 *************************************************/
void LCD_voidSendData(u8 u8CharData);

/* DESCRIPTION : Set Position of Cursor on screen
 * INPUT       : u8Row , Range: 0~255 [LCD_LINE1 , LCD_LINE2]
 *               u8Col , Range: 0~255 [LCD_COLUM1 ~ LCD_COLUM16]
 * RETURN      : void
 *************************************************/
void LCD_voidSetPosition(u8 u8Row , u8 u8Col);

/* DESCRIPTION : Send StringData to LCD For Display on Screen
 * INPUT       : pointer to Char Array
 * RETURN      : void
 *************************************************/
void LCD_voidSendString(u8* pu8Str);

/* DESCRIPTION : Clear LCD Screen
 * INPUT       : void
 * RETURN      : void
 *************************************************/
void LCD_voidClearDisplay(void);

/* DESCRIPTION : Clear specific Line on LCD Screen
 * INPUT       : u8LineNum, Rang: 0~255 [LCD_LINE1 , LCD_LINE2]
 * RETURN      : void
 *************************************************/
void LCD_voidClearLine(u8 u8LineNum);

/* DESCRIPTION : Create Custom Character to display it on LCD Screen
 * INPUT       : pointer to custom char
 *               u8CharLocation ,Range: 0~255 [LCD_CUSTOM_CHAR1 ~ LCD_CUSTOM_CHER8]
 * RETURN      : void
 *************************************************/
void LCD_voidCreateChar(u8* pu8CustomChar , u8 u8CharLocation);

/* DESCRIPTION : Send Integer to LCD for Display On Screen(print until 9 digits)
 * INPUT       : u32IntData , Rang: 0~4294967296
 * RETURN      : void
 *************************************************/
void LCD_voidSendInteger(u32 u32IntData);

void LCD_voidDisableCursor();
void LCD_voidEnableCursor();

#endif /* LCD_INTERFACE_H_ */
