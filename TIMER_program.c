/*
 * TIMER_program.c


 *
 *  Created on: Sep 14, 2025
 *      Author: Mahmoud Samy, Abdallah Amr, Mohamed Aboelez, Mohamed Karim
 */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "TIMER_private.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"

static void (*TIMER_apvCallBackFunc[8])(void) = {NULL};

/*************************************************************************************************************************/
/********************************************TIMER0 FUNCTIONS IMPLEMENTATION**********************************************/
/*************************************************************************************************************************/

void TIMER0_voidInit()
{
	#if TIMER0_MODE == TIMER0_NORMAL_MODE
		/* Initialize TIMER0 MODE as NORMAL MODE */
		CLR_BIT(TCCR0_REG , WGM01);
		CLR_BIT(TCCR0_REG , WGM00);

		/* Set the required Preload value */
		TCNT0_REG = TIME0_PRELOAD_VALUE;

		/* TIMER0 OVERFLOW INTERRUPT ENABLE */
		#if TIMER0_OVERFLOW_INTERRUPT == ENABLE
		SET_BIT(TIMSK_REG , TOIE0);
		#elif TIMER0_OVERFLOW_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , TOIE0);
		#else
			#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
		#endif

	#elif TIMER0_MODE == TIMER_PWM_PHASE_CORRECT_MODE
		/* Initialize TIMER0 as pwm phase correct mode */
		CLR_BIT(TCCR0_REG , WGM01);
		SET_BIT(TCCR0_REG , WGM00);

		/* Set CTC Phase Correct PWM Mode (config OC0 PIN)*/
		#if TIMER0_CTC_PHASE_CORRECT_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR0_REG , COM00);
			CLR_BIT(TCCR0_REG , COM01);
		#elif TIMER0_CTC_PHASE_CORRECT_PWM_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
			CLR_BIT(TCCR0_REG , COM00);
			SET_BIT(TCCR0_REG , COM01);
		#elif TIMER0_CTC_PHASE_CORRECT_PWM_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
			SET_BIT(TCCR0_REG , COM00);
			SET_BIT(TCCR0_REG , COM01);
		#else
			#error "Wrong TIMER0_CTC_PHASE_CORRECT_PWM Config"
		#endif

		/* Set the required CTC value */
		OCR0_REG = TIMER0_CTC_PHASE_CORRECT_PWM_VALUE;

	#elif TIMER0_MODE == TIMER_CTC_MODE
		/* Initialize TIMER0 as pwm phase correct mode */
		CLR_BIT(TCCR0_REG , WGM00);
		SET_BIT(TCCR0_REG , WGM01);

		/* Set CTC NO PWM Mode (config OC0 PIN)*/
		#if TIMER0_CTC_NO_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR0_REG , COM00);
			CLR_BIT(TCCR0_REG , COM01);
		#elif TIMER0_CTC_NO_PWM_MODE == TIMER_OC_TOGGLE
			SET_BIT(TCCR0_REG , COM00);
			CLR_BIT(TCCR0_REG , COM01);
		#elif TIMER0_CTC_NO_PWM_MODE == TIMER_OC_CLEAR
			CLR_BIT(TCCR0_REG , COM00);
			SET_BIT(TCCR0_REG , COM01);
		#elif TIMER0_CTC_NO_PWM_MODE == TIMER_OC_SET
			SET_BIT(TCCR0_REG , COM00);
			SET_BIT(TCCR0_REG , COM01);
		#else
			#error "Wrong TIMER0_CTC_NO_PWM Config"
		#endif

		/* Set the required CTC value */
		OCR0_REG = TIMER0_CTC_NO_PWM_VALUE;

		/* TIMER0 CTC INTRRUPT ENABLE */
		#if TIMER0_CTC_INTRRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE0);
		#elif TIMER0_CTC_INTRRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE0);
		#else
			#error "Wrong TIMER0_CTC_INTERRUPT Config"
		#endif

	#elif TIMER0_MODE == TIMER_FAST_PWM_MODE
		/* Initialize TIMER0 as pwm phase correct mode */
		SET_BIT(TCCR0_REG , WGM01);
		SET_BIT(TCCR0_REG , WGM00);

		/* Set CTC Phase Correct PWM Mode (config OC0 PIN)*/
		#if TIMER0_CTC_FAST_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR0_REG , COM00);
			CLR_BIT(TCCR0_REG , COM01);
		#elif TIMER0_CTC_FAST_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
			CLR_BIT(TCCR0_REG , COM00);
			SET_BIT(TCCR0_REG , COM01);
		#elif TIMER0_CTC_FAST_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
			SET_BIT(TCCR0_REG , COM00);
			SET_BIT(TCCR0_REG , COM01);
		#else
			#error "Wrong TIMER0_CTC_FAST_PWM Config"
		#endif

		/* Set the required CTC value */
		OCR0_REG = TIMER0_CTC_FAST_PWM_VALUE;

	#else
		#error"Wrong TIMER0_MODE Config"
	#endif

	/* SET THE REQUIRED TIMER0 CLOCK PRESCALER */
	/* MAKE SURE THE FIRST 3 BIT IN TCCR0 REG IS CLEARED */
	TCCR0_REG &= TIMER_PRESCALER_MASK;
	TCCR0_REG |= TIMER0_PRESCALER;

}


void TIMER0_voidSetMode(u8 u8Mode)
{
	/* check From u8Mode value */
	if( u8Mode <= TIMER_FAST_PWM_MODE)
	{
		/* Set timer mode */
		switch(u8Mode)
		{
		case TIMER_NORMAL_MODE            : CLR_BIT(TCCR0_REG , WGM00); CLR_BIT(TCCR0_REG , WGM01); break;
		case TIMER_PWM_PHASE_CORRECT_MODE : SET_BIT(TCCR0_REG , WGM00); CLR_BIT(TCCR0_REG , WGM01);	break;
		case TIMER_CTC_MODE               : CLR_BIT(TCCR0_REG , WGM00); SET_BIT(TCCR0_REG , WGM01); break;
		case TIMER_FAST_PWM_MODE          : SET_BIT(TCCR0_REG , WGM00); SET_BIT(TCCR0_REG , WGM01); break;
		}
	}
	else
	{
		//report error
	}
}


void TIMER0_voidSetPreLoad(u8 u8PreLoad)
{
	/* check from u8PreLoad value */
	if (u8PreLoad <= TIMER0_MAX_PRELOAD)
	{
		/* Put u8PreLoad value into TCNT0 Register */
		TCNT0_REG = u8PreLoad ;
	}
	else
	{
		//report error
	}
}


void TIMER0_voidSetCTC(u8 u8CompareMatch)
{
	/* Check from u8CompareMatch value */
	if (u8CompareMatch <= TIMER0_MAX_PRELOAD)
	{
		/* Put u8CompareMatch value into OCR0 Register */
		OCR0_REG = u8CompareMatch ;
	}
	else
	{
		//report error
	}
}


void TIMER0_voidEnable(u8 u8PreScaler)
{
	/* Check from u8PreScaler value */
	if (u8PreScaler <= TIMER_EXTERNAL_CLOCK_SOURCE_ON_T0_RISING )
	{
		/* Set TIMER0 clock prescaler */
		TCCR0_REG &= TIMER_PRESCALER_MASK;
		TCCR0_REG |= u8PreScaler;
	}
}


void TIMER0_voidDisable()
{
	TCCR0_REG &= TIMER_PRESCALER_MASK;
}


u8 TIMER0_u8GetTIMER0CounterVal()
{
	u8 u8ConterVal = 0;

	u8ConterVal = TCNT0_REG;

	return u8ConterVal;
}

void TIMER0_voidSetPWMDutayCycle(u8 u8DC , u8 u8PwmType)
{
	/* check from Duty Cycle & PwmType Values */
	if((u8DC <= TIMER_PWM_MAX_DUTY_CYCLE) && (u8PwmType <= TIMER_PWM_NON_INVERTING_TYPE))
	{
		/* Calculate OCR0 value FROM DutyCycle Value */
		switch(u8PwmType)
		{
		case TIMER_PWM_NON_INVERTING_TYPE :
			OCR0_REG = (((u16)TIMER0_RESOLUTION * u8DC) / 100 ) - 1;
			break;
		case TIMER_PWM_INVERTING_TYPE :
			OCR0_REG = (((u16)TIMER0_RESOLUTION * (TIMER_PWM_MAX_DUTY_CYCLE - u8DC)) / 100 ) - 1;
			break;
		}
	}
	else
	{
		// report error
	}
}


/*************************************************************************************************************************/
/********************************************TIMER1 FUNCTIONS IMPLEMENTATION**********************************************/
/************************************************************************************************************************/

void TIMER1_voidInit()
{
	/* Set TIMER1 Waveform Generation Mode */
	#if TIMER1_MODE == TIMER1_NORMAL_MODE
		/* Set TIMER1 MODE as Normal Mode */
		CLR_BIT(TCCR1B_REG , WGM13);
		CLR_BIT(TCCR1B_REG , WGM12);
		CLR_BIT(TCCR1A_REG , WGM11);
		CLR_BIT(TCCR1A_REG , WGM10);

		/* Set The Required Preload Value */
		TCNT1_REG = TIMER1_PRELOAD_VALUE ;

		/* Set TIMER1 OverFlow Interrupt Enable */
		#if TIMER1_OVERFLOW_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , TOIE1);
		#elif TIMER1_OVERFLOW_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , TOIE1);
		#else
			#error" Wrong TIMER1_OVERFLOW_INTERRUPT cofig"
		#endif
//---------------------------------------------------------------------------------------------------------------------------------------
	#elif (TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_8_BIT_MODE) || (TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_9_BIT_MODE) || (TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_10_BIT_MODE)
		#if TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_8_BIT_MODE
			/* Set TIMER1 MODE as PWM Phase Correct 8 Bit Mode */
			CLR_BIT(TCCR1B_REG , WGM13);
			CLR_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11);
			SET_BIT(TCCR1A_REG , WGM10);
		#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_9_BIT_MODE
			/* Set TIMER1 MODE as PWM Phase Correct 9 Bit Mode */
			CLR_BIT(TCCR1B_REG , WGM13);
			CLR_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11);
			CLR_BIT(TCCR1A_REG , WGM10);
		#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_10_BIT_MODE
			/* Set TIMER1 MODE as PWM Phase Correct 10 Bit Mode */
			CLR_BIT(TCCR1B_REG , WGM13);
			CLR_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11);
			SET_BIT(TCCR1A_REG , WGM10);
		#else
			/* NO OP */
		#endif

		/* Set The Required Compare Match Value */
		OCR1A_REG = TIMER1_PWM_PHASE_CORRECT_OCR1A_VALUE ;
		OCR1B_REG = TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE ;

		/* Set CTC Phase Correct PWM Mode (config OC1A PIN)*/
		#if TIMER1_FIXED_CTC_PHASE_CORRECT_PWM_OC1A_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_FIXED_CTC_PHASE_CORRECT_PWM_OC1A_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_FIXED_CTC_PHASE_CORRECT_PWM_OC1A_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#else
			#error" Wrong TIMER1_CTC_PHASE_CORRECT_PWM_OC1A_MODE Config"
		#endif

		/* Set CTC Phase Correct PWM Mode (config OC1B PIN)*/
		#if TIMER1_FIXED_CTC_PHASE_CORRECT_PWM_OC1B_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_FIXED_CTC_PHASE_CORRECT_PWM_OC1B_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_FIXED_CTC_PHASE_CORRECT_PWM_OC1B_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1B1);
			SET_BIT(TCCR1A_REG , COM1B0);
		#else
			#error" Wrong TIMER1_CTC_PHASE_CORRECT_PWM_OC1B_MODE Config"
		#endif
//-------------------------------------------------------------------------------------------------------------------------------------------
	#elif (TIMER1_MODE == TIMER1_CTC_OCR1A_MODE) || (TIMER1_MODE == TIMER1_CTC_ICR1_MODE)
		#if TIMER1_MODE == TIMER1_CTC_OCR1A_MODE
			/* Set TIMER1 MODE as CTC_OCR1 Mode */
			CLR_BIT(TCCR1B_REG , WGM13);
			SET_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11);
			CLR_BIT(TCCR1A_REG , WGM10);
		#elif TIMER1_MODE == TIMER1_CTC_ICR1_MODE
			/* Set TIMER1 Mode as CTC_ICR1 Mode */
			SET_BIT(TCCR1B_REG , WGM13);
			SET_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11);
			CLR_BIT(TCCR1A_REG , WGM10);

			/* Set The Required ICR1 Value */
			ICR1_REG = TIMER1_CTC_ICR1_VALUE ;

		#else
			/* NOP */
		#endif

		/* Set The Required Compare Match Value */
		OCR1A_REG = TIMER1_CTCA_VALUE ;
		#if (TIMER1_CTCA_VALUE >= TIMER1_CTCB_VALUE) && (TIMER1_MODE == TIMER1_CTC_OCR1A_MODE)
			OCR1B_REG = TIMER1_CTCB_VALUE ;
		#elif TIMER1_MODE == TIMER1_CTC_ICR1_MODE
			OCR1B_REG = TIMER1_CTCB_VALUE ;
		#else
			#error "Wrong TIMER1_CTCB_VALUE Config Please Make Sure (TIMER1_CTCA_VALUE > TIMER1_CTCB_VALUE) If You On TIMER1_CTC_OCR1A_MODE "
		#endif

		/* Set CTCA NO PWM Mode (config OC1A PIN)*/
		#if TIMER1_CTCA_NO_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_NO_PWM_MODE == TIMER_OC_TOGGLE
			CLR_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_NO_PWM_MODE == TIMER_OC_CLEAR
			SET_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_NO_PWM_MODE == TIMER_OC_SET
			SET_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#else
			#error"Wrong TIMER1_CTCA_NO_PWM_MODE Config"
		#endif

		/* Set CTCB NO PWM Mode (config OC1B PIN)*/
		#if TIMER1_CTCB_NO_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_NO_PWM_MODE == TIMER_OC_TOGGLE
			CLR_BIT(TCCR1A_REG , COM1B1);
			SET_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_NO_PWM_MODE == TIMER_OC_CLEAR
			SET_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_NO_PWM_MODE == TIMER_OC_SET
			SET_BIT(TCCR1A_REG , COM1B1);
			SET_BIT(TCCR1A_REG , COM1B0);
		#else
			#error"Wrong TIMER1_CTCB_NO_PWM_MODE Config"
		#endif

		/* Set TIMER1 CTCA Interrupt Enable */
		#if TIMER1_CTCA_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE1A);
		#elif TIMER1_CTCA_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE1A);
		#else
			#error "Wrong TIMER1_CTCA_INTERRUPT Config"
		#endif

		/* Set TIMER1 CTCB Interrupt Enable */
		#if TIMER1_CTCB_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE1B);
		#elif TIMER1_CTCB_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE1B);
		#else
			#error "Wrong TIMER1_CTCB_INTERRUPT Config"
		#endif

		/*Set ICR1 Interrupt Enable */
		#if TIMER1_ICR1_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , TICIE1);
		#elif TIMER1_ICR1_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , TICIE1);
		#else
			#error "Wrong TIMER1_ICR1_INTERRUPT Config"
		#endif
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	#elif (TIMER1_MODE == TIMER1_FAST_PWM_8_BIT_MODE) || (TIMER1_MODE == TIMER1_FAST_PWM_9_BIT_MODE) || (TIMER1_MODE == TIMER1_FAST_PWM_10_BIT_MODE)
		#if TIMER1_MODE == TIMER1_FAST_PWM_8_BIT_MODE
			/* Set TIMER1 MODE as FAST PWM 8 Bit Mode */
			CLR_BIT(TCCR1B_REG , WGM13);
			SET_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11);
			SET_BIT(TCCR1A_REG , WGM10);
		#elif TIMER1_MODE == TIMER1_FAST_PWM_9_BIT_MODE
			/* Set TIMER1 MODE as FAST PWM 9 Bit Mode */
			CLR_BIT(TCCR1B_REG , WGM13);
			SET_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11);
			CLR_BIT(TCCR1A_REG , WGM10);
		#elif TIMER1_MODE == TIMER1_FAST_PWM_10_BIT_MODE
			/* Set TIMER1 MODE as FAST PWM 10 Bit Mode */
			CLR_BIT(TCCR1B_REG , WGM13);
			SET_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11);
			SET_BIT(TCCR1A_REG , WGM10);
		#else
			/* NO OP */
		#endif

		/* Set The Required Compare Match Value */
		OCR1A_REG = TIMER1_FAST_PWM_OCR1A_VALUE ;
		OCR1B_REG = TIMER1_FAST_PWM_OCR1B_VALUE ;

		/* Set CTC Fast PWM Mode (config OC1A PIN)*/
		#if TIMER1_FIXED_CTC_FAST_PWM_OC1A_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_FIXED_CTC_FAST_PWM_OC1A_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
			SET_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_FIXED_CTC_FAST_PWM_OC1A_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
			SET_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#else
			#error" Wrong TIMER1_CTC_FAST_PWM_OC1A_MODE Config"
		#endif

		/* Set CTC FAST PWM Mode (config OC1B PIN)*/
		#if TIMER1_FIXED_CTC_FAST_PWM_OC1B_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_FIXED_CTC_FAST_PWM_OC1B_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
			SET_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_FIXED_CTC_FAST_PWM_OC1B_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
			SET_BIT(TCCR1A_REG , COM1B1);
			SET_BIT(TCCR1A_REG , COM1B0);
		#else
			#error" Wrong TIMER1_CTC_FAST_PWM_OC1B_MODE Config"
		#endif
//------------------------------------------------------------------------------------------------------------------------------------------------------------
	#elif (TIMER1_MODE == TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_MODE) || (TIMER1_MODE == TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_MODE)
		#if	TIMER1_MODE == TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_MODE
			/* Set TIMER1 Mode as PWM Phase & Frequency Correct ICR1 Mode */
			SET_BIT(TCCR1B_REG , WGM13);
			CLR_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11);
			CLR_BIT(TCCR1A_REG , WGM10);

			/* Set The Required ICR1 Value */
			ICR1_REG = TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_VALUE ;

		#elif TIMER1_MODE == TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_MODE
			/* Set TIMER1 Mode as PWM Phase & Frequency Correct OCR1A Mode */
			SET_BIT(TCCR1B_REG , WGM13);
			CLR_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11);
			SET_BIT(TCCR1A_REG , WGM10);
		#else
				/*NOP*/
		#endif

		/* Set The Required Compare Match Value */
		OCR1A_REG = TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_VALUE ;
		#if (TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_VALUE >= TIMER1_PHASE_FREQUENCY_CORRECT_OCR1B_VALUE) && (TIMER1_MODE == TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_MODE)
			OCR1B_REG = TIMER1_PHASE_FREQUENCY_CORRECT_OCR1B_VALUE ;
		#elif (TIMER1_MODE == TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_MODE)
			OCR1B_REG = TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE ;
		#else
			#error "Wrong TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE Config Please Make Sure (TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_VALUE > TIMER1_PHASE_FREQUENCY_CORRECT_OCR1B_VALUE) If You On TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_MODE "
		#endif

		/* Set CTCA  Phase and Frequency Correct Mode (config OC1A PIN)*/
		#if TIMER1_CTCA_PHASE_FREQ_CORRECT_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_PHASE_FREQ_CORRECT_MODE == TIMER_OC_TOGGLE
			CLR_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_PHASE_FREQ_CORRECT_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_PHASE_FREQ_CORRECT_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#else
			#error"Wrong TIMER1_CTCA_PHASE_FREQ_CORRECT_MODE Config"
		#endif

		/* Set CTCB Phase and Frequency Correct Mode (config OC1B PIN)*/
		#if TIMER1_CTCB_PHASE_FREQ_CORRECT_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_PHASE_FREQ_CORRECT_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_PHASE_FREQ_CORRECT_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1B1);
			SET_BIT(TCCR1A_REG , COM1B0);
		#else
			#error"Wrong TIMER1_CTCB_PHASE_FREQ_CORRECT_MODE Config"
		#endif

		/* Set ICR1 Interrupt Enable */
		#if TIMER1_ICR1_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , TICIE1);
		#elif TIMER1_ICR1_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , TICIE1);
		#else
			#error "Wrong TIMER1_ICR1_INTERRUPT Config"
		#endif

		/* Set TIMER1 CTCA Interrupt Enable */
		#if TIMER1_CTCA_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE1A);
		#elif TIMER1_CTCA_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE1A);
		#else
			#error "Wrong TIMER1_CTCA_INTERRUPT Config"
		#endif

		/* Set TIMER1 CTCB Interrupt Enable */
		#if TIMER1_CTCB_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE1B);
		#elif TIMER1_CTCB_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE1B);
		#else
			#error "Wrong TIMER1_CTCB_INTERRUPT Config"
		#endif
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
	#elif (TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE)
		#if	TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE
			/* Set TIMER1 Mode as PWM Phase Correct ICR1 Mode */
			SET_BIT(TCCR1B_REG , WGM13);
			CLR_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11);
			CLR_BIT(TCCR1A_REG , WGM10);

			/* Set The Required ICR1 Value */
			ICR1_REG = TIMER1_PWM_PHASE_CORRECT_ICR1_VALUE ;

		#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE
				/* Set TIMER1 Mode as PWM Phase Correct OCR1A Mode */
				SET_BIT(TCCR1B_REG , WGM13);
				CLR_BIT(TCCR1B_REG , WGM12);
				SET_BIT(TCCR1A_REG , WGM11);
				SET_BIT(TCCR1A_REG , WGM10);
		#else
			/* NOP */
		#endif

		/* Set The Required Compare Match Value */
		OCR1A_REG = TIMER1_PWM_PHASE_CORRECT_OCR1A_VALUE ;
		#if (TIMER1_PWM_PHASE_CORRECT_OCR1A_VALUE >= TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE) && (TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE)
			OCR1B_REG = TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE ;
		#elif (TIMER1_MODE == TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_MODE)
			OCR1B_REG = TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE ;
		#else
			#error "Wrong TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE Config Please Make Sure (TIMER1_PWM_PHASE_CORRECT_OCR1A_VALUE > TIMER1_PWM_PHASE_CORRECT_OCR1B_VALUE) If You On TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE "
		#endif

		/* Set CTCA  Phase Correct Mode (config OC1A PIN)*/
		#if TIMER1_CTCA_PHASE_CORRECT_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_PHASE_CORRECT_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_PHASE_CORRECT_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#else
			#error"Wrong TIMER1_CTCA_PHASE_CORRECT_MODE Config"
		#endif

		/* Set CTCB Phase Correct Mode (config OC1B PIN)*/
		#if TIMER1_CTCB_PHASE_CORRECT_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_PHASE_CORRECT_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_PHASE_CORRECT_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
			SET_BIT(TCCR1A_REG , COM1B1);
			SET_BIT(TCCR1A_REG , COM1B0);
		#else
			#error"Wrong TIMER1_CTCB_PHASE_CORRECT_MODE Config"
		#endif

		/* Set ICR1 Interrupt Enable */
		#if TIMER1_ICR1_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , TICIE1);
		#elif TIMER1_ICR1_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , TICIE1);
		#else
			#error "Wrong TIMER1_ICR1_INTERRUPT Config"
		#endif

		/* Set TIMER1 CTCA Interrupt Enable */
		#if TIMER1_CTCA_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE1A);
		#elif TIMER1_CTCA_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE1A);
		#else
			#error "Wrong TIMER1_CTCA_INTERRUPT Config"
		#endif

		/* Set TIMER1 CTCB Interrupt Enable */
		#if TIMER1_CTCB_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE1B);
		#elif TIMER1_CTCB_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE1B);
		#else
			#error "Wrong TIMER1_CTCB_INTERRUPT Config"
		#endif
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	#elif (TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE)  || (TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE)
		#if	TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE
			/* Set TIMER1 Mode as FAST PWM ICR1 Mode */
			SET_BIT(TCCR1B_REG , WGM13);
			SET_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11);
			CLR_BIT(TCCR1A_REG , WGM10);

			/* Set The Required ICR1 Value */
			ICR1_REG = TIMER1_FAST_PWM_ICR1_VALUE ;

		#elif TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE
				/* Set TIMER1 Mode as FAST PWM  OCR1A Mode */
				SET_BIT(TCCR1B_REG , WGM13);
				SET_BIT(TCCR1B_REG , WGM12);
				SET_BIT(TCCR1A_REG , WGM11);
				SET_BIT(TCCR1A_REG , WGM10);
		#else
			/* NOP */
		#endif

		/* Set The Required Compare Match Value */
		OCR1A_REG = TIMER1_FAST_PWM_OCR1A_VALUE ;
		#if (TIMER1_FAST_PWM_OCR1A_VALUE >= TIMER1_FAST_PWM_OCR1B_VALUE) && (TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE)
			OCR1B_REG = TIMER1_FAST_PWM_OCR1B_VALUE ;
		#elif (TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE)
			OCR1B_REG = TIMER1_FAST_PWM_OCR1B_VALUE ;
		#else
			#error "Wrong TIMER1_FAST_PWM_OCR1A_MODE Config Please Make Sure (TIMER1_FAST_PWM_OCR1A_VALUE > TIMER1_FAST_PWM_OCR1B_VALUE) If You On TIMER1_FAST_PWM_OCR1A_MODE "
		#endif

		/* Set CTCA  Fast PWM Mode (config OC1A PIN)*/
		#if TIMER1_CTCA_FAST_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_FAST_PWM_MODE == TIMER_OC_TOGGLE
			CLR_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_FAST_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
			SET_BIT(TCCR1A_REG , COM1A1);
			CLR_BIT(TCCR1A_REG , COM1A0);
		#elif TIMER1_CTCA_FAST_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
			SET_BIT(TCCR1A_REG , COM1A1);
			SET_BIT(TCCR1A_REG , COM1A0);
		#else
			#error"Wrong TIMER1_CTCA_FAST_PWM_MODE Config"
		#endif

		/* Set CTCB Fast PWM Mode (config OC1B PIN)*/
		#if TIMER1_CTCB_FAST_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_FAST_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
			SET_BIT(TCCR1A_REG , COM1B1);
			CLR_BIT(TCCR1A_REG , COM1B0);
		#elif TIMER1_CTCB_FAST_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
			SET_BIT(TCCR1A_REG , COM1B1);
			SET_BIT(TCCR1A_REG , COM1B0);
		#else
			#error"Wrong TIMER1_CTCB_FAST_PWM_MODE Config"
		#endif

		/* Set TIMER1 OverFlow Interrupt Enable */
		#if TIMER1_OVERFLOW_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , TOIE1);
		#elif TIMER1_OVERFLOW_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , TOIE1);
		#else
			#error" Wrong TIMER1_OVERFLOW_INTERRUPT cofig"
		#endif

		/* Set TIMER1 CTCB Interrupt Enable */
		#if TIMER1_CTCB_INTERRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE1B);
		#elif TIMER1_CTCB_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE1B);
		#else
			#error "Wrong TIMER1_CTCB_INTERRUPT Config"
		#endif

	#else
		#error"Wrong TIMER1_MODE Config"
	#endif

	/* SET THE REQUIRED TIMER0 CLOCK PRESCALER */
	/* MAKE SURE THE FIRST 3 BIT IN TCCR0 REG IS CLEARED */
	TCCR1B_REG &= TIMER_PRESCALER_MASK;
	TCCR1B_REG |= TIMER1_PRESCALER;
}


void TIMER1_voidSetMode(u8 u8Mode)
{
	/* check From u8Mode value */
	if( u8Mode <= TIMER1_FAST_PWM_OCR1A_MODE)
	{
		/* Set timer mode */
		switch(u8Mode)
		{
		case TIMER1_NORMAL_MODE :
			CLR_BIT(TCCR1B_REG , WGM13); CLR_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11); CLR_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_PWM_PHASE_CORRECT_8_BIT_MODE :
			CLR_BIT(TCCR1B_REG , WGM13); CLR_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11); SET_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_PWM_PHASE_CORRECT_9_BIT_MODE :
			CLR_BIT(TCCR1B_REG , WGM13); CLR_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11); CLR_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_PWM_PHASE_CORRECT_10_BIT_MODE :
			CLR_BIT(TCCR1B_REG , WGM13); CLR_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11); SET_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_CTC_OCR1A_MODE :
			CLR_BIT(TCCR1B_REG , WGM13); SET_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11); CLR_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_FAST_PWM_8_BIT_MODE :
			CLR_BIT(TCCR1B_REG , WGM13); SET_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11); SET_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_FAST_PWM_9_BIT_MODE :
			CLR_BIT(TCCR1B_REG , WGM13); SET_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11); CLR_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_FAST_PWM_10_BIT_MODE :
			CLR_BIT(TCCR1B_REG , WGM13); SET_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11); SET_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_PHASE_FREQUENCY_CORRECT_ICR1_MODE :
			SET_BIT(TCCR1B_REG , WGM13); CLR_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11); CLR_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_PHASE_FREQUENCY_CORRECT_OCR1A_MODE :
			SET_BIT(TCCR1B_REG , WGM13); CLR_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11); SET_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_PWM_PHASE_CORRECT_ICR1_MODE :
			SET_BIT(TCCR1B_REG , WGM13); CLR_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11); CLR_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE :
			SET_BIT(TCCR1B_REG , WGM13); CLR_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11); SET_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_CTC_ICR1_MODE :
			SET_BIT(TCCR1B_REG , WGM13); SET_BIT(TCCR1B_REG , WGM12);
			CLR_BIT(TCCR1A_REG , WGM11); CLR_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_FAST_PWM_ICR1_MODE :
			SET_BIT(TCCR1B_REG , WGM13); SET_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11); CLR_BIT(TCCR1A_REG , WGM10); break;

		case TIMER1_FAST_PWM_OCR1A_MODE :
			SET_BIT(TCCR1B_REG , WGM13); SET_BIT(TCCR1B_REG , WGM12);
			SET_BIT(TCCR1A_REG , WGM11); SET_BIT(TCCR1A_REG , WGM10); break;
		}
	}
	else
	{
		//report error
	}
}


void TIMER1_voidSetPreLoad(u16 u16PreLoad)
{
	/* check from u16PreLoad value */
	if (u16PreLoad <= TIMER1_MAX_PRELOAD)
	{
		/* Put u8PreLoad value into TCNT1 Register */
		TCNT1_REG = u16PreLoad ;
	}
	else
	{
		//report error
	}
}


void TIMER1_voidSetCTCA(u16 u16CMA)
{
	/* Check from u16CMA value */
	if (u16CMA <= TIMER1_MAX_PRELOAD)
	{
		/* Put u16CMA value into OCR1A Register */
		OCR1A_REG = u16CMA ;
	}
	else
	{
		//report error
	}
}


void TIMER1_voidSetCTCB(u16 u16CMB)
{
	/* Check from u16CMB value */
	if (u16CMB <= TIMER1_MAX_PRELOAD)
	{
		/* Put u16CMB value into OCR1B Register */
		OCR1B_REG = u16CMB ;
	}
	else
	{
		//report error
	}
}



void TIMER1_voidSetICR1(u16 u16ICR1)
{
	/* Check from u16ICR1 value */
	if (u16ICR1 <= TIMER1_MAX_PRELOAD)
	{
		/* Put u16CMB value into OCR1B Register */
		ICR1_REG = u16ICR1 ;
	}
	else
	{
		//report error
	}
}


void TIMER1_voidEnable(u8 u8PreScaler)
{
	/* Check from u8PreScaler value */
	if (u8PreScaler <= TIMER_EXTERNAL_CLOCK_SOURCE_ON_T0_RISING )
	{
		/* Set TIMER0 clock prescaler */
		TCCR1B_REG &= TIMER_PRESCALER_MASK;
		TCCR1B_REG |= u8PreScaler;
	}
	else
	{
		//report error
	}
}


void TIMER1_voidDisable()
{
	TCCR1B_REG &= TIMER_PRESCALER_MASK;
}

u16 TIMER1_u16GetTIMER1CounterVal()
{
	u16 u16ConterVal = 0;

	u16ConterVal = TCNT1_REG;

	return u16ConterVal;
}





/*************************************************************************************************************************/
/********************************************TIMER2 FUNCTIONS IMPLEMENTATION**********************************************/
/************************************************************************************************************************/


void TIMER2_voidInit()
{
	#if TIMER2_MODE == TIMER2_NORMAL_MODE
		/* Initialize TIMER2 MODE as NORMAL MODE */
		CLR_BIT(TCCR2_REG , WGM21);
		CLR_BIT(TCCR2_REG , WGM20);

		/* Set the required Preload value */
		TCNT2_REG = TIME2_PRELOAD_VALUE;

		/* TIMER2 OVERFLOW INTERRUPT ENABLE */
		#if TIMER2_OVERFLOW_INTERRUPT == ENABLE
		SET_BIT(TIMSK_REG , TOIE2);
		#elif TIMER2_OVERFLOW_INTERRUPT == DISABLE
			CLR_BIT(TIMSK_REG , TOIE2);
		#else
			#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
		#endif

	#elif TIMER2_MODE == TIMER_PWM_PHASE_CORRECT_MODE
		/* Initialize TIMER2 as pwm phase correct mode */
		CLR_BIT(TCCR2_REG , WGM21);
		SET_BIT(TCCR2_REG , WGM20);

		/* Set CTC Phase Correct PWM Mode (config OC2 PIN)*/
		#if TIMER2_CTC_PHASE_CORRECT_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR2_REG , COM20);
			CLR_BIT(TCCR2_REG , COM21);
		#elif TIMER2_CTC_PHASE_CORRECT_PWM_MODE == TIMER_CLR_ON_CTC_UP_SET_ON_CTC_DOWN
			CLR_BIT(TCCR2_REG , COM20);
			SET_BIT(TCCR2_REG , COM21);
		#elif TIMER2_CTC_PHASE_CORRECT_PWM_MODE == TIMER_SET_ON_CTC_UP_CLR_ON_CTC_DOWN
			SET_BIT(TCCR2_REG , COM20);
			SET_BIT(TCCR2_REG , COM21);
		#else
			#error "Wrong TIMER2_CTC_PHASE_CORRECT_PWM Config"
		#endif

		/* Set the required CTC value */
		OCR2_REG = TIMER2_CTC_PHASE_CORRECT_PWM_VALUE;

	#elif TIMER2_MODE == TIMER_CTC_MODE
		/* Initialize TIMER2 as pwm phase correct mode */
		CLR_BIT(TCCR2_REG , WGM20);
		SET_BIT(TCCR2_REG , WGM21);

		/* Set CTC NO PWM Mode (config OC2 PIN)*/
		#if TIMER2_CTC_NO_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR2_REG , COM20);
			CLR_BIT(TCCR2_REG , COM21);
		#elif TIMER2_CTC_NO_PWM_MODE == TIMER_OC_TOGGLE
			SET_BIT(TCCR2_REG , COM20);
			CLR_BIT(TCCR2_REG , COM21);
		#elif TIMER2_CTC_NO_PWM_MODE == TIMER_OC_CLEAR
			CLR_BIT(TCCR2_REG , COM20);
			SET_BIT(TCCR2_REG , COM21);
		#elif TIMER2_CTC_NO_PWM_MODE == TIMER_OC_SET
			SET_BIT(TCCR2_REG , COM20);
			SET_BIT(TCCR2_REG , COM21);
		#else
			#error "Wrong TIMER2_CTC_NO_PWM Config"
		#endif

		/* Set the required CTC value */
		OCR2_REG = TIMER2_CTC_NO_PWM_VALUE;

		/* TIMER2 CTC INTRRUPT ENABLE */
		#if TIMER2_CTC_INTRRUPT == ENABLE
			SET_BIT(TIMSK_REG , OCIE2);
		#elif TIMER2_CTC_INTRRUPT == DISABLE
			CLR_BIT(TIMSK_REG , OCIE2);
		#else
			#error "Wrong TIMER2_CTC_INTERRUPT Config"
		#endif

	#elif TIMER2_MODE == TIMER_FAST_PWM_MODE
		/* Initialize TIMER2 as Fast Pwm mode */
		SET_BIT(TCCR2_REG , WGM21);
		SET_BIT(TCCR2_REG , WGM20);

		/* Set CTC Fast PWM Mode (config OC2 PIN)*/
		#if TIMER2_CTC_FAST_PWM_MODE == TIMER_OC_DISCONNECTED
			CLR_BIT(TCCR2_REG , COM20);
			CLR_BIT(TCCR2_REG , COM21);
		#elif TIMER2_CTC_FAST_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
			CLR_BIT(TCCR2_REG , COM20);
			SET_BIT(TCCR2_REG , COM21);
		#elif TIMER2_CTC_FAST_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
			SET_BIT(TCCR2_REG , COM20);
			SET_BIT(TCCR2_REG , COM21);
		#else
			#error "Wrong TIMER2_CTC_FAST_PWM Config"
		#endif

		/* Set the required CTC value */
		OCR2_REG = TIMER2_CTC_FAST_PWM_VALUE;

	#else
		#error"Wrong TIMER2_MODE Config"
	#endif

	/* SET THE REQUIRED TIMER2 CLOCK PRESCALER */
	/* MAKE SURE THE FIRST 3 BIT IN TCCR2 REG IS CLEARED */
	TCCR2_REG &= TIMER_PRESCALER_MASK;
	TCCR2_REG |= TIMER2_PRESCALER;

}


void TIMER2_voidSetMode(u8 u8Mode)
{
	/* check From u8Mode value */
	if( u8Mode <= TIMER_FAST_PWM_MODE)
	{
		/* Set timer mode */
		switch(u8Mode)
		{
		case TIMER_NORMAL_MODE            : CLR_BIT(TCCR2_REG , WGM20); CLR_BIT(TCCR2_REG , WGM21); break;
		case TIMER_PWM_PHASE_CORRECT_MODE : SET_BIT(TCCR2_REG , WGM20); CLR_BIT(TCCR2_REG , WGM21);	break;
		case TIMER_CTC_MODE               : CLR_BIT(TCCR2_REG , WGM20); SET_BIT(TCCR2_REG , WGM21); break;
		case TIMER_FAST_PWM_MODE          : SET_BIT(TCCR2_REG , WGM20); SET_BIT(TCCR2_REG , WGM21); break;
		}
	}
	else
	{
		//report error
	}
}


void TIMER2_voidSetPreLoad(u8 u8PreLoad)
{
	/* check from u8PreLoad value */
	if (u8PreLoad <= TIMER2_MAX_PRELOAD)
	{
		/* Put u8PreLoad value into TCNT2 Register */
		TCNT2_REG = u8PreLoad ;
	}
	else
	{
		//report error
	}
}


void TIMER2_voidSetCTC(u8 u8CompareMatch)
{
	/* Check from u8CompareMatch value */
	if (u8CompareMatch <= TIMER2_MAX_PRELOAD)
	{
		/* Put u8CompareMatch value into OCR2 Register */
		OCR2_REG = u8CompareMatch ;
	}
	else
	{
		//report error
	}
}


void TIMER2_voidEnable(u8 u8PreScaler)
{
	/* Check from u8PreScaler value */
	if (u8PreScaler <= TIMER2_DIVISION_FACTOR_1024 )
	{
		/* Set TIMER0 clock prescaler */
		TCCR2_REG &= TIMER_PRESCALER_MASK;
		TCCR2_REG |= u8PreScaler;
	}
}


void TIMER2_voidDisable()
{
	TCCR2_REG &= TIMER_PRESCALER_MASK;
}


u8 TIMER0_u8GetTIMER2CounterVal()
{
	u8 u8ConterVal = 0;

	u8ConterVal = TCNT2_REG;

	return u8ConterVal;
}



/*************************************************************************************************************************/
/********************************************ICU FUNCTIONS IMPLEMENTATION**********************************************/
/************************************************************************************************************************/

void TIMER_voidICUInt()
{
	/* Select ICU Interrupt Edge */
	#if TIMER_ICU_EDGE == TIMER_ICU_RISING_EDGE
		SET_BIT(TCCR1B_REG , ICES1);
	#elif TIMER_ICU_EDGE == TIMER_ICU_FALLING_EDGE
		CLR_BIT(TCCR1B_REG , ICES1);
	#else
		#error "Wrong TIMER_ICU_EDGE Config"
	#endif

	/* Set ICU Noise Cancellation */
	#if TIMER_ICU_NC == ENABLE
		SET_BIT(TCCR1B_REG , ICNC1);
	#elif TIMER_ICU_NC == DISABLE
		CLR_BIT(TCCR1B_REG , ICNC1);
	#else
		"Wrong TIMER_ICU_NC Config"
	#endif

	/* Set ICU Interrupt */
	#if TIMER1_ICR1_INTERRUPT  == ENABLE
		SET_BIT(TIMSK_REG , TICIE1);
	#elif TIMER1_ICR1_INTERRUPT  == DISABLE
		CLR_BIT(TIMSK_REG , TICIE1);
	#else
		"Wrong TIMER1_ICR1_INTERRUPT Config"
	#endif
}


void TIMER_voidSetICUEdge(u8 u8Edge)
{
	/* Check From u8Edge Value */
	if (u8Edge <= TIMER_ICU_RISING_EDGE)
	{
		/* Set ICU Interrupt Edge */
		switch(u8Edge)
		{
		case TIMER_ICU_RISING_EDGE  : SET_BIT(TCCR1B_REG , ICES1); break;
		case TIMER_ICU_FALLING_EDGE : CLR_BIT(TCCR1B_REG , ICES1); break;
		}
	}
	else
	{
		//report error
	}
}


void TIMER_voidICUEnable()
{
	/* Set ICU Interrupt Enable */
	SET_BIT(TIMSK_REG , TICIE1);
}


void TIMER_voidICUDisable()
{
	/* Set ICU Interrupt Disable */
	CLR_BIT(TIMSK_REG , TICIE1);
}


u16  TIMER_u16GetICUVal()
{
	return ICR1_REG;
}



/*************************************************************************************************************************/
/********************************************WDT FUNCTIONS IMPLEMENTATION**********************************************/
/************************************************************************************************************************/

void TIMER_voidWDTInt()
{
	/* Set WDT Enable */
	SET_BIT(WDTCR_REG , WDE);

	/* Set WDT Prescaler */
	WDTCR_REG &= TIMER_WDT_PRESALE_MASK;
	WDTCR_REG |= TIMER_WDT_PRESCALE;
}


void TIMER_voidSetWDTPrescale(u8 u8SleepTime)
{
	/* Set WDT Prescaler */
	WDTCR_REG &= TIMER_WDT_PRESALE_MASK;
	WDTCR_REG |= TIMER_WDT_PRESCALE;
}


void TIMER_voidWDTDisable()
{
	/* Clear BIT 3 and 4 in the same Time */
	WDTCR_REG |= TIMER_WDT_DISABLE_MASK;

	/* Clear WDTCR_REG */
	CLR_REG(WDTCR_REG);
}



/*************************************************************************************************************************/
/********************************************TIMER CALL BACK FUNCTION IMPLEMENTATION**************************************/
/************************************************************************************************************************/

void TIMER_voidCallBack(void (*pvoidCallback)(void) , u8 u8TimerVactorId)
{
	/* Check From pvoidCallback and u8TimerVactorId values */
	if ((pvoidCallback != NULL) && (u8TimerVactorId <= TIMER2_CTC_VECTOR))
	{
		TIMER_apvCallBackFunc[u8TimerVactorId] = pvoidCallback ;
	}
	else
	{
		//report error
	}
}



/*************************************************************************************************************************/
/********************************************ISR FUNCTIONS IMPLEMENTATION**************************************/
/************************************************************************************************************************/

/* TIMER2 COMPARE MATCH (CTC MODE) ISR */
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	if (TIMER_apvCallBackFunc[TIMER2_CTC_VECTOR] != NULL)
	{
		TIMER_apvCallBackFunc[TIMER2_CTC_VECTOR]();
	}
	else
	{
		//report error
	}
}


/* TIMER2 OVERFLOW(NORMAL MODE) ISR */
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	if (TIMER_apvCallBackFunc[TIMER2_OVF_VECTOR] != NULL)
	{
		TIMER_apvCallBackFunc[TIMER2_OVF_VECTOR]();
	}
	else
	{
		//report error
	}
}

/* TIMER1 INPUT CAPTURE UNIT ISR */
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if (TIMER_apvCallBackFunc[TIMER1_ICU_VECTOR] != NULL)
	{
		TIMER_apvCallBackFunc[TIMER1_ICU_VECTOR]();
	}
	else
	{
		//report error
	}
}

/* TIMER1 COMPARE MATCH CHANNEL A (CTCA MODE) ISR */
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	if (TIMER_apvCallBackFunc[TIMER1_CTCA_VECTOR] != NULL)
	{
		TIMER_apvCallBackFunc[TIMER1_CTCA_VECTOR]();
	}
	else
	{
		//report error
	}
}

/* TIMER1 COMPARE MATCH CHANNEL B (CTCB MODE) ISR */
void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
	if (TIMER_apvCallBackFunc[TIMER1_CTCB_VECTOR] != NULL)
	{
		TIMER_apvCallBackFunc[TIMER1_CTCB_VECTOR]();
	}
	else
	{
		//report error
	}
}

/* TIMER1 OVERFLOW (NORMAL MODE) ISR */
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	if (TIMER_apvCallBackFunc[TIMER1_OVF_VECTOR] != NULL)
	{
		TIMER_apvCallBackFunc[TIMER1_OVF_VECTOR]();
	}
	else
	{
		//report error
	}
}

/* TIMER0 COMPARE MATCH (CTC MODE) ISR */
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if (TIMER_apvCallBackFunc[TIMER0_CTC_VECTOR] != NULL)
	{
		TIMER_apvCallBackFunc[TIMER0_CTC_VECTOR]();
	}
	else
	{
		//report error
	}
}

/* TIMER0 OVERFLOW(NORMAL MODE) ISR */
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if (TIMER_apvCallBackFunc[TIMER0_OVF_VECTOR] != NULL)
	{
		TIMER_apvCallBackFunc[TIMER0_OVF_VECTOR]();
	}
	else
	{
		//report error
	}
}





