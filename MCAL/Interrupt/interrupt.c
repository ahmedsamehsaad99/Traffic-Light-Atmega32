/*
 * interrupt.c
 */ 

#include "interrupt.h"

// FUNCTION TO ENABLE GLOBAL INTERRUPTS
EN_INTERRUPT_ERROR INTERRUPT_enableGlobalInterrupts()
{
	setBitState(SREG, 7, 1);
	return INTERRUPT_OK;
}

// FUNCTION TO SET EXTERNAL INTERRUPT SENSING
EN_INTERRUPT_ERROR INTERRUPT_setExternalInterruptSense(extInterruptNumber intNumber, interruptSense intSense)
{
	switch (intNumber)
	{
		case EXT_0:
		switch (intSense)
		{
			case LOW_LEVEL:
				setBitState(MCUCR, 0, 0); 
				setBitState(MCUCR, 1, 0); 
				break;
			case LOGICAL_CHANGE:
				setBitState(MCUCR, 0, 1);
				setBitState(MCUCR, 1, 0);
				break;
			case FALLING_EDGE:
				setBitState(MCUCR, 0, 0);
				setBitState(MCUCR, 1, 1);
				break;
			case RISING_EDGE:
				setBitState(MCUCR, 0, 1);
				setBitState(MCUCR, 1, 1);
				break;
		}
		break;
		
		case EXT_1:
			switch (intSense)
			{
				case LOW_LEVEL:
					setBitState(MCUCR, 2, 0);
					setBitState(MCUCR, 3, 0);
					break;
				case LOGICAL_CHANGE:
					setBitState(MCUCR, 2, 1);
					setBitState(MCUCR, 3, 0);
					break;
				case FALLING_EDGE:
					setBitState(MCUCR, 2, 0);
					setBitState(MCUCR, 3, 1);
					break;
				case RISING_EDGE:
					setBitState(MCUCR, 2, 1);
					setBitState(MCUCR, 3, 1);
					break;
			}
			break;
		break;
		
		case EXT_2:
		switch (intSense)
		{
			case FALLING_EDGE:
				setBitState(MCUCSR, 6, 0);
				break;
			case RISING_EDGE:
				setBitState(MCUCSR, 6, 1);
				break;
			default:
				setBitState(MCUCSR, 6, 0);
				break;
		}
		break;
	}
	return INTERRUPT_OK;
}

// FUNCTION TO ENABLE A SPECIFIC EXTERNAL INTERRUPT
EN_INTERRUPT_ERROR INTERRUPT_enableExternalInterrupt(extInterruptNumber intNumber)
{
	switch(intNumber)
	{
		case EXT_0:
			setBitState(GICR, 6, 1);
			break;
		case EXT_1:
			setBitState(GICR, 7, 1);
			break;
		case EXT_2:
			setBitState(GICR, 5, 1);
			break;
	}
	return INTERRUPT_OK;
}

// FUNCTION TO INITIALIZE A SPECIFIC EXTERNAL INTERRUPT
EN_INTERRUPT_ERROR INTERRUPT_initialize(extInterruptNumber intNumber, interruptSense intSense)
{
	INTERRUPT_enableGlobalInterrupts();
	INTERRUPT_setExternalInterruptSense(intNumber, intSense);
	INTERRUPT_enableExternalInterrupt(intNumber);
	return INTERRUPT_OK;
}

// FUNCTION TO RETURN INTERRUPT FLAG STATE
uint8_t INTERRUPT_getInterruptFlag(extInterruptNumber intNumber)
{
	switch(intNumber)
	{
		case EXT_0:
			return getBit(GIFR, 6);
		case EXT_1:
			return getBit(GIFR, 7);
		case EXT_2:
			return getBit(GIFR, 5);
		default:
			return 0;
	}
}