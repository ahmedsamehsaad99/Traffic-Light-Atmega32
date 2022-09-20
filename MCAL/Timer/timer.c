/*
 * timer.c
 */ 

#include "timer.h"

// FUNCTION TO SET MODE FOR TIMERS
EN_TIMER_ERROR TIMER_setMode(timerNumber timer, timerMode theMode)
{
	volatile uint8_t* timerRegister = NULL;
	
	switch (timer)
	{
		case TIMER0:
			timerRegister = &TCCR0;
			break;
		case TIMER1:
			break;
		case TIMER2:
			timerRegister = &TCCR2;
			break;
	}
	
	switch (theMode)
	{
		case NORMAL:
			*timerRegister = 0x00;
			break;
		case PWM_PHASE_CORRECT:
			*timerRegister = 0x40;
			break;
		case CTC:
			*timerRegister = 0x08;
			break;
		case FAST_PWM:
			*timerRegister = 0x48;
			break;
	}
	
	return TIMER_OK;
}

// FUNCTION TO SET INITIAL VALUE FOR TIMERS
EN_TIMER_ERROR TIMER_setInitialValue(timerNumber timer, uint16_t initialValue)
{	
	switch (timer)
	{
		case TIMER0:
			TCNT0 = initialValue;
			break;
		case TIMER1:
			TCNT1H = initialValue>>8;
			TCNT1L = initialValue;
			break;
		case TIMER2:
			TCNT2 = initialValue;
			break;
	}
	
	return TIMER_OK;
}

// FUNCTION TO SET THE PRESCALER, THEREFORE STARTING THE TIMER
EN_TIMER_ERROR TIMER_start(timerNumber timer, prescalerChoice thePrescaler)
{
	switch (timer)
	{
		case TIMER0:
			switch (thePrescaler)
			{
				case NO_PRESCALER:
					setBitState(TCCR0, 0, 1); // CS00
					setBitState(TCCR0, 1, 0); // CS01
					setBitState(TCCR0, 2, 0); // CS02
					break;
				case PRESCALER_8:
					setBitState(TCCR0, 0, 0);
					setBitState(TCCR0, 1, 1);
					setBitState(TCCR0, 2, 0);
					break;
				case PRESCALER_64:
					setBitState(TCCR0, 0, 1);
					setBitState(TCCR0, 1, 1);
					setBitState(TCCR0, 2, 0);
					break;
				case PRESCALER_256:
					setBitState(TCCR0, 0, 0);
					setBitState(TCCR0, 1, 0);
					setBitState(TCCR0, 2, 1);
					break;
				case PRESCALER_1024:
					setBitState(TCCR0, 0, 1);
					setBitState(TCCR0, 1, 0);
					setBitState(TCCR0, 2, 1);
					break;
			}
			break;
			
		case TIMER1:
			switch (thePrescaler)
			{
				case NO_PRESCALER:
					setBitState(TCCR1B, 0, 1);
					setBitState(TCCR1B, 1, 0);
					setBitState(TCCR1B, 2, 0);
					break;
				case PRESCALER_8:
					setBitState(TCCR1B, 0, 0);
					setBitState(TCCR1B, 1, 1);
					setBitState(TCCR1B, 2, 0);
					break;
				case PRESCALER_64:
					setBitState(TCCR1B, 0, 1);
					setBitState(TCCR1B, 1, 1);
					setBitState(TCCR1B, 2, 0);
					break;
				case PRESCALER_256:
					setBitState(TCCR1B, 0, 0);
					setBitState(TCCR1B, 1, 0);
					setBitState(TCCR1B, 2, 1);
					break;
				case PRESCALER_1024:
					setBitState(TCCR1B, 0, 1);
					setBitState(TCCR1B, 1, 0);
					setBitState(TCCR1B, 2, 1);
					break;
			}
			break;

		case TIMER2:
			switch (thePrescaler)
			{
				case NO_PRESCALER:
					setBitState(TCCR2, 0, 1); // CS20
					setBitState(TCCR2, 1, 0); // CS21
					setBitState(TCCR2, 2, 0); // CS22
					break;
				case PRESCALER_8:
					setBitState(TCCR2, 0, 0);
					setBitState(TCCR2, 1, 1);
					setBitState(TCCR2, 2, 0);
					break;
				case PRESCALER_64:
					setBitState(TCCR2, 0, 0);
					setBitState(TCCR2, 1, 0);
					setBitState(TCCR2, 2, 1);
					break;
				case PRESCALER_256:
					setBitState(TCCR2, 0, 0);
					setBitState(TCCR2, 1, 1);
					setBitState(TCCR2, 2, 1);
					break;
				case PRESCALER_1024:
					setBitState(TCCR2, 0, 1);
					setBitState(TCCR2, 1, 1);
					setBitState(TCCR2, 2, 1);
					break;
			}
			break;
	}
	
	return TIMER_OK;
}

// FUNCTION TO RETURN THE OVERFLOW FLAG
uint8_t TIMER_getOverflowFlag(timerNumber timer) 
{	
	switch (timer)
	{
		case TIMER0:
			return (getBit(TIFR, 0));
			break;
		case TIMER1:
			return (getBit(TIFR, 2));
			break;
		case TIMER2:
			return (getBit(TIFR, 6));
			break;
	}
	return 0;
}

// FUNCTION TO CLEAR THE OVERFLOW FLAG
EN_TIMER_ERROR TIMER_clearOverflowFlag(timerNumber timer)
{	
	switch (timer)
	{
		case TIMER0:
			setBitState(TIFR, 1, 0);
			break;
		case TIMER1:
			setBitState(TIFR, 2, 1);
			break;
		case TIMER2:
			setBitState(TIFR, 6, 1);
			break;
	}
	return TIMER_OK;
}

// FUNCTION TO STOP THE TIMER
EN_TIMER_ERROR TIMER_stop(timerNumber timer)
{	
	switch (timer)
	{
		case TIMER0:
			TCCR0 = 0x00;
			break;
		case TIMER1:
			TCCR1A = 0x00;
			TCCR1B = 0x00;
			break;
		case TIMER2:
			TCCR2 = 0x00;
			break;
	}
	return TIMER_OK;
}
/*
void TIMER_setTimerForInterrupt(timerNumber timer, uint16_t milliseconds)
{
	setBitState(SREG, 7, 1);	// ENABLE GLOBAL INTERRUPTS
	if (timer == TIMER0)
		setBitState(TIMSK, 0, 1); // TIMER 2 = 6
	else if (timer == TIMER2)
		setBitState(TIMSK, 6, 1);
		
	TIMER_setMode(timer, NORMAL);
	TIMER_setInitialValue(timer, 256 - (milliseconds - 262.144*(milliseconds/262))/1.024);
	TIMER_start(timer, PRESCALER_1024);
}
*/

// FUNCTION TO DELAY USING TIMER (BUSY-WAIT)
EN_TIMER_ERROR TIMER_delay(timerNumber timer, uint16_t milliseconds) // WITHOUT INTERRPUTS, USING NORMAL MODE
{
	if (TIMER_setMode(timer, NORMAL) != TIMER_OK)
		return TIMER_FAILED;
	
	//float tickTime = 1024 / FCPU; // 1.024 MILLIS
	//float maxDelay8bits = 256 * tickTime; // 262.144 MILLIS
	// float maxDelay16bits = 65536 * 1.024 = 67108.864 (67 SECS)
	uint16_t overflowNumber;
	uint8_t overFlowsCount = 0;
	
	if (timer == TIMER0 || timer == TIMER2) // 8 BIT TIMERS
	{
		overflowNumber = milliseconds/262.144;
		if (overflowNumber != 0) // IN CASE OF OVERFLOWS
			TIMER_setInitialValue(timer, 256 - (milliseconds - 262.144 * overflowNumber)/1.024);
		else // // IN CASE OF NO OVERFLOWS
			TIMER_setInitialValue(timer, (256 - (milliseconds/1.024)));
	}
	else // TIMER1 16 BITS
	{
		overflowNumber = milliseconds/67108.864;
		if (overflowNumber != 0)
			TIMER_setInitialValue(timer, 65536 - (milliseconds - 67108.864 * overflowNumber)/1.024);
		else
			TIMER_setInitialValue(timer, 65536 - (milliseconds/1.024));
	}
	
	while (overFlowsCount <= overflowNumber)
	{
		overFlowsCount++;
		TIMER_start(timer, PRESCALER_1024);
		while (TIMER_getOverflowFlag(timer) == 0);
		TIMER_clearOverflowFlag(timer);
	}
	
	overFlowsCount = 0;
	TIMER_stop(timer);
	return TIMER_OK;
}
