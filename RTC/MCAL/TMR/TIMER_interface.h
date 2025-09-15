/*
 * TIMER_interface.h

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
/*****************************************************************/
/***********************PUBLIC MACROS****************************/
/***************************************************************/

/* MODE MACROS */
#define TIMER_NORMAL_MODE                          0
#define TIMER_PWM_PHASE_CORRECT_MODE               1
#define TIMER_CTC_MODE                             2
#define TIMER_FAST_PWM_MODE                        3


/* PRESCALER MACROS */
#define TIMER_NO_CLOCK_SOURCE                      0
#define TIMER_NO_PRESCALER_FACTOR                  1
#define TIMER_DIVISION_FACTOR_8                    2
#define TIMER_DIVISION_FACTOR_64                   3
#define TIMER_DIVISION_FACTOR_256                  4
#define TIMER_DIVISION_FACTOR_1024                 5
#define TIMER_EXTERNAL_CLOCK_SOURCE_ON_T0_FALLING  6
#define TIMER_EXTERNAL_CLOCK_SOURCE_ON_T0_RISING   7

/* TIMER2 Prescaler */
#define TIMER2_NO_CLOCK_SOURCE                     0
#define TIMER2_NO_PRESCALER_FACTOR                 1
#define TIMER2_DIVISION_FACTOR_8                   2
#define TIMER2_DIVISION_FACTOR_32                   3
#define TIMER2_DIVISION_FACTOR_64                  4
#define TIMER2_DIVISION_FACTOR_128                 5
#define TIMER2_DIVISION_FACTOR_256                 6
#define TIMER2_DIVISION_FACTOR_1024                7

/* TIMER1 MODE */
#define TIMER1_NORMAL_MODE                         0
#define TIMER1_PWM_PHASE_CORRECT_8_BIT_MODE	       1
#define TIMER1_PWM_PHASE_CORRECT_9_BIT_MODE        2
#define TIMER1_PWM_PHASE_CORRECT_10_BIT_MODE       3
#define TIMER1_CTC_OCR1A_MODE                      4
#define TIMER1_FAST_PWM_8_BIT_MODE                 5
#define TIMER1_FAST_PWM_9_BIT_MODE                 6
#define TIMER1_FAST_PWM_10_BIT_MODE                7
#define TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_MODE   8
#define TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_MODE  9
#define TIMER1_PWM_PHASE_CORRECT_ICR1_MODE         10
#define TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE        11
#define TIMER1_CTC_ICR1_MODE                       12
#define TIMER1_FAST_PWM_ICR1_MODE                  14
#define TIMER1_FAST_PWM_OCR1A_MODE                 15

/* PWM TYPES MACROS */
#define TIMER_PWM_INVERTING_TYPE                   0
#define TIMER_PWM_NON_INVERTING_TYPE               1


/* ICU EDGE MACROS */
#define TIMER_ICU_FALLING_EDGE                     0
#define TIMER_ICU_RISING_EDGE                      1

/* WDT PRESCALERS MACROS*/
#define WDT_PRESCALE_16_3_MS                       0
#define WDT_PRESCALE_32_5_MS                       1
#define WDT_PRESCALE_65_MS                         2
#define WDT_PRESCALE_0_13_S                        3
#define WDT_PRESCALE_0_26_S                        4
#define WDT_PRESCALE_0_52_S                        5
#define WDT_PRESCALE_1_0_S                         6
#define WDT_PRESCALE_2_1_S                         7

/* TIMER INTERRUPT VACTOR IDS */
#define TIMER0_OVF_VECTOR                          0
#define TIMER0_CTC_VECTOR                          1
#define TIMER1_OVF_VECTOR                          2
#define TIMER1_CTCA_VECTOR                         3
#define TIMER1_CTCB_VECTOR                         4
#define TIMER1_ICU_VECTOR                          5
#define TIMER2_OVF_VECTOR                          6
#define TIMER2_CTC_VECTOR                          7



void TIMER0_voidInit();

void TIMER0_voidSetMode(u8 u8Mode);
void TIMER0_voidSetPreLoad(u8 u8PreLoad);
void TIMER0_voidSetCTC(u8 u8CM);
void TIMER0_voidEnable(u8 u8PreScaler);
void TIMER0_voidDisable();


u8 TIMER0_u8GetTIMER0CounterVal();
void TIMER0_voidSetPWMDutayCycle(u8 u8DC , u8 u8PwmType);

void TIMER1_voidInit();


void TIMER1_voidSetMode(u8 u8Mode);


void TIMER1_voidSetPreLoad(u16 u16PreLoad);


void TIMER1_voidSetCTCA(u16 u16CMA);


void TIMER1_voidSetCTCB(u16 u16CMB);


void TIMER1_voidSetICR1(u16 u16ICR1);

void TIMER1_voidEnable(u8 u8PreScaler);


void TIMER1_voidDisable();


u16 TIMER1_u16GetTIMER1CounterVal();


void TIMER2_voidInit();


void TIMER2_voidSetMode(u8 u8Mode);

void TIMER2_voidSetPreLoad(u8 u8PreLoad);


void TIMER2_voidSetCTC(u8 u8CM);

void TIMER2_voidEnable(u8 u8PreScaler);
void TIMER2_voidDisable();


u8 TIMER2_u8GetTIMER2CounterVal();

void TIMER_voidICUInt();


void TIMER_voidSetICUEdge(u8 u8Edge);


void TIMER_voidICUEnable();


void TIMER_voidICUDisable();

u16  TIMER_u16GetICUVal();




void TIMER_voidWDTInt();


void TIMER_voidWDTEnable(u8 u8SleepTime);

void TIMER_voidWDTDisable();

void TIMER_voidCallBack(void (*pvoidCallback)(void) , u8 u8TimerVactorId);



#endif /* TIMER_INTERFACE_H_ */
