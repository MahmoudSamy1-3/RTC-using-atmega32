/*
 * TIMER_private.h

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/*********************************************************/
/***********************PRIVATE MACROS*******************/
/*******************************************************/
/* REGISTERS MACROS*/
#define TIMSK_REG                         *((volatile u8*) 0x59)
#define TIFR_REG                          *((volatile u8*) 0x58)
#define WDTCR_REG                         *((volatile u8*) 0x41)
/* TIMER0 */
#define TCCR0_REG                         *((volatile u8*) 0x53)
#define TCNT0_REG                         *((volatile u8*) 0x52)
#define OCR0_REG                          *((volatile u8*) 0x5C)

/* TIMER1 */
#define TCCR1A_REG                        *((volatile u8*) 0x4F)
#define TCCR1B_REG                        *((volatile u8*) 0x4E)
#define TCNT1H_REG                        *((volatile u8*) 0x4D)
#define TCNT1L_REG                        *((volatile u8*) 0x4C)
#define TCNT1_REG                         *((volatile u16*) 0x4C)
#define OCR1AH_REG                        *((volatile u8*) 0x4B)
#define OCR1AL_REG                        *((volatile u8*) 0x4A)
#define OCR1A_REG                         *((volatile u16*) 0x4A)
#define OCR1BH_REG                        *((volatile u8*) 0x49)
#define OCR1BL_REG                        *((volatile u8*) 0x48)
#define OCR1B_REG                         *((volatile u16*) 0x48)
#define ICR1H_REG                         *((volatile u8*) 0x47)
#define ICR1L_REG                         *((volatile u8*) 0x46)
#define ICR1_REG                          *((volatile u16*) 0x46)

/* TIMER2 */
#define TCCR2_REG                         *((volatile u8*) 0x45)
#define TCNT2_REG                         *((volatile u8*) 0x44)
#define OCR2_REG                          *((volatile u8*) 0x43)

/* REGISTER BITS */
/* TIMSK_REG */
#define TOIE0                0
#define OCIE0                1
#define TOIE1                2
#define OCIE1B               3
#define OCIE1A               4
#define TICIE1               5
#define TOIE2                6
#define OCIE2                7

/* TIFR_REG */
#define TOV0                 0
#define OCF0                 1
#define TOV1                 2
#define OCF1B                3
#define OCF1A                4
#define ICF1                 5
#define TOV2                 6
#define OCF2                 7

/* TIMER0 REGISTERS */
/* TCCR0_REG*/
#define CS00                 0
#define CS01                 1
#define CS02                 2
#define WGM01                3
#define COM00                4
#define COM01                5
#define WGM00                6
#define FOC0                 7

/* TIMER1 REGISTERS */
/* TCCR1A_REG*/
#define WGM10                0
#define WGM11                1
#define FOC1B                2
#define FOC1A                3
#define COM1B0               4
#define COM1B1               5
#define COM1A0               6
#define COM1A1               7

/* TCCR1B_REG */
#define CS10                 0
#define CS11                 1
#define CS12                 2
#define WGM12                3
#define WGM13                4
#define ICES1                6
#define ICNC1                7

/* TIMER2 REGISTERS */
/* TCCR0_REG*/
#define CS20                 0
#define CS21                 1
#define CS22                 2
#define WGM21                3
#define COM20                4
#define COM21                5
#define WGM20                6
#define FOC2                 7

/* WDTCR_REG  */
#define WDP0                 0
#define WDP1                 1
#define WDP2                 2
#define WDE                  3
#define WDTOE                4

/* NEEDED MACROS */
#define TIMER0_MAX_PRELOAD                     0xFF
#define TIMER1_MAX_PRELOAD                     0xFFFF
#define TIMER2_MAX_PRELOAD                     0xFF
#define TIMER_PRESCALER_MASK                   0xF8
#define TIMER_WDT_PRESALE_MASK                 0xF8
#define TIMER_WDT_DISABLE_MASK                 0x18
#define ENABLE                                 1
#define DISABLE                                0
#define TIMER_PWM_MAX_DUTY_CYCLE               100
#define TIMER0_RESOLUTION                      256
#define NULL                                   0

/* OCx PIN MACROS */
/* CTC NO PWM */
#define TIMER_OC_DISCONNECTED                      0
#define TIMER_OC_TOGGLE                            1
#define TIMER_OC_CLEAR                             2
#define TIMER_OC_SET                               3

/* CTC FAST PWM */
#define TIMER_CLR_ON_CTC_SET_ON_TOP                2
#define TIMER_SET_ON_CTC_CLR_ON_TOP                3

/* CTC PHASE CORRECT PWM */
#define TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN        2
#define TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN        3



#endif /* TIMER_PRIVATE_H_ */
