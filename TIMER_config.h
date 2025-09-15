/*
 * TIMER_config.h

 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*******************************************************************************************************************/
/******************************************************TIMER0 CONFIG***********************************************/
/*****************************************************************************************************************/

/* DESCRIPION : Set TIMER0 PRESCALER
 * OPTIONS    : TIMER_NO_CLOCK_SOURCE     - TIMER_NO_PRESCALER_FACTOR  - TIMER_DIVISION_FACTOR_8 -
 *              TIMER_DIVISION_FACTOR_256 - TIMER_DIVISION_FACTOR_1024 - TIMER_DIVISION_FACTOR_64
 *              TIMER_EXTERNAL_CLOCK_SOURCE_ON_T0_FALLING              - TIMER_EXTERNAL_CLOCK_SOURCE_ON_T0_RISING
 ********************************************************************************************************************/
#define TIMER0_PRESCALER                        TIMER_DIVISION_FACTOR_64

/* DESCRIPION : Set TIMER0 Waveform Generation Mode
 * OPTIONS    : TIMER_NORMAL_MODE - TIMER_PWM_PHASE_CORRECT_MODE - TIMER_CTC_MODE - TIMER_FAST_PWM_MODE
 *******************************************************************************************************/
#define TIMER0_MODE                        TIMER_CTC_MODE

/* DESCRIPION : Set TIMER0 Overflow Interrupt
 * OPTIONS    : ENABLE - DISABLE
 *******************************************************************************************************/
#define TIMER0_OVERFLOW_INTERRUPT                DISABLE

/* DESCRIPION : Set TIMER0 CTC Interrupt
 * OPTIONS    : ENABLE - DISABLE
 *******************************************************************************************************/
#define TIMER0_CTC_INTRRUPT                        ENABLE

/* DESCRIPION : Set The Required Preload Value When The TIMER0 Mode is Normal Mode
 * OPTIONS    : 0 ~ 255
 *******************************************************************************************************/
#define TIME0_PRELOAD_VALUE                      0

/* DESCRIPION : Set TIMER0 CTC PHASE CORRECT PWM MODE  (config behavior of OC0 PIN )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN - TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
 *****************************************************************************************************************/
#define TIMER0_CTC_PHASE_CORRECT_PWM_MODE        TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required Compare Match Value When The TIMER0 Mode is PWM Phase Correct Mode
 * OPTIONS    : 0 ~ 255
 *******************************************************************************************************/
#define TIMER0_CTC_PHASE_CORRECT_PWM_VALUE          0

/* DESCRIPION : Set TIMER0 CTC NO PWM MODE  (config behavior of OC0 PIN )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_OC_TOGGLE - TIMER_OC_CLEAR - TIMER_OC_SET
 ******************************************************************************************************/
#define TIMER0_CTC_NO_PWM_MODE                   TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required Compare Match Value When The TIMER0 Mode is CTC Mode
 * OPTIONS    : 0 ~ 255
 *******************************************************************************************************/
#define TIMER0_CTC_NO_PWM_VALUE                     124

/* DESCRIPION : Set TIMER0 CTC FAST PWM MODE  (config behavior of OC0 PIN )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_SET_ON_TOP - TIMER_SET_ON_CTC_CLR_ON_TOP
 ******************************************************************************************************/
#define TIMER0_CTC_FAST_PWM_MODE                 TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required Compare Match Value When The TIMER0 Mode is FAST PWM  Mode
 * OPTIONS    : 0 ~ 255
 *******************************************************************************************************/
#define TIMER0_CTC_FAST_PWM_VALUE                    0





/******************************************************************************************************************/
/******************************************************TIMER1 CONFIG***********************************************/
/*****************************************************************************************************************/

/* DESCRIPION : Set TIMER1 PRESCALER
 * OPTIONS    : TIMER_NO_CLOCK_SOURCE     - TIMER_NO_PRESCALER_FACTOR  - TIMER_DIVISION_FACTOR_8 -
 *              TIMER_DIVISION_FACTOR_256 - TIMER_DIVISION_FACTOR_1024 - TIMER_DIVISIO_FACTOR_64
 *              TIMER_EXTERNAL_CLOCK_SOURCE_ON_T0_FALLING              - TIMER_EXTERNAL_CLOCK_SOURCE_ON_T0_RISING
 ********************************************************************************************************************/
#define TIMER1_PRESCALER                        TIMER_NO_CLOCK_SOURCE

/* DESCRIPION : Set TIMER1 Waveform Generation Mode
 * OPTIONS    : TIMER1_NORMAL_MODE                   - TIMER1_PWM_PHASE_CORRECT_8_BIT_MODE - TIMER1_PWM_PHASE_CORRECT_9_BIT_MODE
 *              TIMER1_PWM_PHASE_CORRECT_10_BIT_MODE - TIMER1_CTC_OCR1A_MODE               - TIMER1_FAST_PWM_8_BIT_MODE
 *              TIMER1_FAST_PWM_9_BIT_MODE           - TIMER1_FAST_PWM_10_BIT_MODE         - TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_MODE
 *              TIMER1_PWM_PHASE_CORRECT_ICR1_MODE   - TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE - TIMER1_CTC_ICR1_MODE
 *              TIMER1_FAST_PWM_ICR1_MODE            - TIMER1_FAST_PWM_OCR1A_MODE                                                                           - TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_MODE -
 ****************************************************************************************************************/
#define TIMER1_MODE                        TIMER1_FAST_PWM_OCR1A_MODE

/* DESCRIPION : Set TIMER1 Overflow Interrupt
 * OPTIONS    : ENABLE - DISABLE
 *******************************************************************************************************/
#define TIMER1_OVERFLOW_INTERRUPT                   DISABLE

/* DESCRIPION : Set TIMER1 CTC Interrupt FOR Channel A and Channel B  (CTCA , CTCB)
 * OPTIONS    : ENABLE - DISABLE
 *******************************************************************************************************/
#define TIMER1_CTCA_INTERRUPT                        DISABLE
#define TIMER1_CTCB_INTERRUPT                        DISABLE

/* DESCRIPION : Set TIMER1 ICR1 Interrupt
 * OPTIONS    : ENABLE - DISABLE
 *******************************************************************************************************/
#define TIMER1_ICR1_INTERRUPT                        DISABLE

/* DESCRIPION : Set The Required Preload Value When The TIMER1 Mode is Normal Mode
 * OPTIONS    : 0 ~ 65536
 *******************************************************************************************************/
#define TIMER1_PRELOAD_VALUE                      0

/* DESCRIPION : Set TIMER1 FIXED BITS CTC PHASE CORRECT PWM MODE (8BIT-9BIT-10BIT) (config behavior of OC1A & OC1B PINS )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN - TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
 **************************************************************************************************************************/
#define TIMER1_FIXED_CTC_PHASE_CORRECT_PWM_OC1A_MODE        TIMER_OC_DISCONNECTED
#define TIMER1_FIXED_CTC_PHASE_CORRECT_PWM_OC1B_MODE        TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required Compare Match Values When The TIMER1 Mode is CTC_OCR1A Mode for (A & B) TIMER1 Channels
 * OPTIONS    : 0 ~ 65536
 **********************************************************************************************************************/
#define TIMER1_CTCA_VALUE                     0
#define TIMER1_CTCB_VALUE                     0

/* DESCRIPION : Set TIMER1 CTC NO PWM MODE  (config behavior of OC1A & OC1B PINs )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_OC_TOGGLE - TIMER_OC_CLEAR - TIMER_OC_SET
 ******************************************************************************************************/
#define TIMER1_CTCA_NO_PWM_MODE                   TIMER_OC_DISCONNECTED
#define TIMER1_CTCB_NO_PWM_MODE                   TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required ICR1 Value When The TIMER1 Mode is CTC_ICR1 Mode
 * OPTIONS    : 0 ~ 65536
 *******************************************************************************************************/
#define TIMER1_CTC_ICR1_VALUE                         0



/* DESCRIPION : Set TIMER1 FIXED BITS CTC FAST PWM MODE (8BIT-9BIT-10BIT) (config behavior of OC1A & OC1B PINS )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_SET_ON_TOP - TIMER_SET_ON_CTC_CLR_ON_TOP
 **************************************************************************************************************************/
#define TIMER1_FIXED_CTC_FAST_PWM_OC1A_MODE        TIMER_OC_DISCONNECTED
#define TIMER1_FIXED_CTC_FAST_PWM_OC1B_MODE        TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required ICR1 Value When The TIMER1 Mode is CTC Phase and Frequency CORRECT ICR Mode
 * OPTIONS    : 0 ~ 65536
 *************************************************************************************************************************/
#define TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_VALUE                      0

/* DESCRIPION : Set The Required Compare Match Values When The TIMER1 Mode is CTC Phase and Frequency CORRECT OCR1A Mode for (A & B) TIMER1 Channels
 * OPTIONS    : 0 ~ 65536
 *********************************************************************************************************************************************/
#define TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_VALUE                     0
#define TIMER1_PHASE_FREQUENCY_CORRECT_OCR1B_VALUE                     0

/* DESCRIPION : Set TIMER1 CTC PHASE AND FREQUENCY CORRECT PWM MODE  (config behavior of OC1A & OC1B PINS )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN - TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN - TIMER_OC_TOGGLE
 * HINT       : " TIMER_OC_TOGGLE" OPTION IS THE ADDITIONAL OPTION FOR CTCA ONLY
 **************************************************************************************************************************/
#define TIMER1_CTCA_PHASE_FREQ_CORRECT_MODE        TIMER_OC_DISCONNECTED
#define TIMER1_CTCB_PHASE_FREQ_CORRECT_MODE        TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required ICR1 Value When The TIMER1 Mode is CTC Phase CORRECT ICR Mode
 * OPTIONS    : 0 ~ 65536
 *******************************************************************************************************/
#define TIMER1_PWM_PHASE_CORRECT_ICR1_VALUE                     0

/* DESCRIPION : Set The Required Compare Match Values When The TIMER1 Mode is CTC Phase CORRECT OCR1A Mode for (A & B) TIMER1 Channels
 * OPTIONS    : 0 ~ 65536
 *********************************************************************************************************************************************/
#define TIMER1_PWM_PHASE_CORRECT_OCR1A_VALUE                     0
#define TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE                     0

/* DESCRIPION : Set TIMER1 CTC PHASE CORRECT PWM MODE  (config behavior of OC1A & OC1B PINS )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN - TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
 **************************************************************************************************************************/
#define TIMER1_CTCA_PHASE_CORRECT_MODE        TIMER_OC_DISCONNECTED
#define TIMER1_CTCB_PHASE_CORRECT_MODE        TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required ICR1 Value When The TIMER1 Mode is FAST PWM ICR Mode
 * OPTIONS    : 0 ~ 65536
 *******************************************************************************************************/
#define TIMER1_FAST_PWM_ICR1_VALUE                         0

/* DESCRIPION : Set The Required Compare Match Values When The TIMER1 Mode is FAST PWM OCR1A Mode for (A & B) TIMER1 Channels
 * OPTIONS    : 0 ~ 65536
 *********************************************************************************************************************************************/
#define TIMER1_FAST_PWM_OCR1A_VALUE                     0
#define TIMER1_FAST_PWM_OCR1B_VALUE                     0

/* DESCRIPION : Set TIMER1 CTC FAST PWM MODE (config behavior of OC1A & OC1B PINS )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_SET_ON_TOP - TIMER_SET_ON_CTC_CLR_ON_TOP - TIMER_OC_TOGGLE
 * HINT       : " TIMER_OC_TOGGLE" OPTION IS THE ADDITIONAL OPTION FOR CTCA ONLY
 **************************************************************************************************************************/
#define TIMER1_CTCA_FAST_PWM_MODE        TIMER_OC_DISCONNECTED
#define TIMER1_CTCB_FAST_PWM_MODE        TIMER_OC_DISCONNECTED





/******************************************************************************************************************/
/******************************************************TIMER2 CONFIG***********************************************/
/*****************************************************************************************************************/



/* DESCRIPION : Set TIMER2 PRESCALER
 * OPTIONS    : TIMER2_NO_CLOCK_SOURCE     - TIMER2_NO_PRESCALER_FACTOR - TIMER2_DIVISION_FACTOR_8
 *              TIMER2_DIVISIO_FACTOR_32   - TIMER2_DIVISIO_FACTOR_64   - TIMER2_DIVISIO_FACTOR_128
 *              TIMER2_DIVISIO_FACTOR_256  - TIMER2_DIVISIO_FACTOR_256  - TIMER2_DIVISIO_FACTOR_1024
 ********************************************************************************************************************/
#define TIMER2_PRESCALER                        TIMER2_NO_CLOCK_SOURCE

/* DESCRIPION : Set TIMER2 Waveform Generation Mode
 * OPTIONS    : TIMER_NORMAL_MODE - TIMER_PWM_PHASE_CORRECT_MODE - TIMER_CTC_MODE - TIMER_FAST_PWM_MODE
 *******************************************************************************************************/
#define TIMER2_MODE                        TIMER_CTC_MODE

/* DESCRIPION : Set TIMER2 Overflow Interrupt
 * OPTIONS    : ENABLE - DISABLE
 *******************************************************************************************************/
#define TIMER2_OVERFLOW_INTERRUPT                DISABLE

/* DESCRIPION : Set TIMER2 CTC Interrupt
 * OPTIONS    : ENABLE - DISABLE
 *******************************************************************************************************/
#define TIMER2_CTC_INTRRUPT                        DISABLE

/* DESCRIPION : Set The Required Preload Value When The TIMER2 Mode is Normal Mode
 * OPTIONS    : 0 ~ 255
 *******************************************************************************************************/
#define TIME2_PRELOAD_VALUE                      0

/* DESCRIPION : Set TIMER2 CTC PHASE CORRECT PWM MODE  (config behavior of OC2 PIN )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN - TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
 *****************************************************************************************************************/
#define TIMER2_CTC_PHASE_CORRECT_PWM_MODE        TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required Compare Match Value When The TIMER2 Mode is PWM Phase Correct Mode
 * OPTIONS    : 0 ~ 255
 *******************************************************************************************************/
#define TIMER2_CTC_PHASE_CORRECT_PWM_VALUE          0

/* DESCRIPION : Set TIMER2 CTC NO PWM MODE  (config behavior of OC2 PIN )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_OC_TOGGLE - TIMER_OC_CLEAR - TIMER_OC_SET
 ******************************************************************************************************/
#define TIMER2_CTC_NO_PWM_MODE                   TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required Compare Match Value When The TIMER2 Mode is CTC Mode
 * OPTIONS    : 0 ~ 255
 *******************************************************************************************************/
#define TIMER2_CTC_NO_PWM_VALUE                     0

/* DESCRIPION : Set TIMER2 CTC FAST PWM MODE  (config behavior of OC2 PIN )
 * OPTIONS    : TIMER_OC_DISCONNECTED - TIMER_CLR_ON_CTC_SET_ON_TOP - TIMER_SET_ON_CTC_CLR_ON_TOP
 ******************************************************************************************************/
#define TIMER2_CTC_FAST_PWM_MODE                 TIMER_OC_DISCONNECTED

/* DESCRIPION : Set The Required Compare Match Value When The TIMER2 Mode is FAST PWM  Mode
 * OPTIONS    : 0 ~ 255
 *******************************************************************************************************/
#define TIMER2_CTC_FAST_PWM_VALUE                    0



/******************************************************************************************************************/
/******************************************************ICU CONFIG*************************************************/
/****************************************************************************************************************/

/* DESCRIPTION : Set ICU Interrupt Edge
 * OPTITIONS   : TIMER_ICU_FALLING_EDGE - TIMER_ICU_RISING_EDGE
 *******************************************************************/
#define TIMER_ICU_EDGE                  TIMER_ICU_RISING_EDGE

/* DESCRIPTION : Set ICU Noise Cancellation
 * OPTITIONS   : ENABLE - DISABLE
 *******************************************************************/
#define TIMER_ICU_NC                       DISABLE



/******************************************************************************************************************/
/******************************************************WDT CONFIG*************************************************/
/****************************************************************************************************************/

/* DESCRIPTION : Set WDT Prescaler
 * OPTITIONS   : WDT_PRESCALE_16_3_MS - WDT_PRESCALE_32_5_MS - WDT_PRESCALE_65_MS  - WDT_PRESCALE_0_13_S
 * 				 WDT_PRESCALE_0_26_S  - WDT_PRESCALE_0_52_S  - WDT_PRESCALE_1_0_S  - WDT_PRESCALE_2_1_S
 *******************************************************************/
#define TIMER_WDT_PRESCALE                     WDT_PRESCALE_16_3_MS




#endif /* TIMER_CONFIG_H_ */
