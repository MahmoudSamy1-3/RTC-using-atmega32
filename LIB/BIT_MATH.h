/*
 * BIT_MATH.h


 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef BIT_MATH_H
#define  BIT_MATH_H
/* Bitwise */
#define  SET_BIT(Byte,n)           (Byte |= (  1 << n  ))
#define  TOGGLE_BIT(Byte,n)        (Byte ^= (  1 << n  ))
#define  CLR_BIT(Byte,n)           (Byte &= ~( 1 << n  ))
#define  GET_BIT(Byte,n)           ( (Byte >> n ) & 1 )

/* Low Nibble(Least 4 Bits) */
#define SET_LOW_NIB(Reg)            (Reg |= 0x0F)
#define GET_LOW_NIB(Reg)            (Reg & 0x0F)
#define CLR_LOW_NIB(Reg)            (Reg &= 0xF0)
#define TOGGLE_LOW_NIB(Reg)         (Reg ^= 0x0F)
#define ASSIGN_LOW_NIB(Reg,value)   (Reg = (Reg & 0xF0) | (value & 0x0F))

/* High Nibble(Highest 4 Bits) */
#define SET_HIGH_NIB(Reg)            (Reg |= 0xF0)
#define GET_HIGH_NIB(Reg)            ((Reg & 0xF0) >> 4)
#define CLR_HIGH_NIB(Reg)            (Reg &= 0x0F)
#define TOGGLE_HIGH_NIB(Reg)         (Reg ^= 0xF0)
#define ASSIGN_HIGH_NIB(Reg,value)   (Reg = (Reg & 0x0F) | (value << 4))

/* FULL REG (All 8 Bits) */
#define  SET_REG(Reg)              (Reg = 0xFF)
#define  GET_REG(Reg)              (Reg)
#define  CLR_REG(Reg)              (Reg = 0x00)
#define  TOGGLE_REG(Reg)           (Reg ^= 0XFF)
#define  ASSIGN_REG(Reg,value)     (Reg = value)

#endif
