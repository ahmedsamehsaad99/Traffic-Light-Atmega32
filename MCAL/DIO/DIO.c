/*
 * DIO.c
 */ 

#include "DIO.h"

// Function to initialize a new PIN either it's an INPUT or OUTPUT
EN_DIO_ERROR DIO_initializePin(portName thePort, pinNumber thePin, direction theDirection)
{
	switch (thePort)
	{
	case A:
		setBitState(DDRA, thePin, theDirection);
		break;
	case B:
		setBitState(DDRB, thePin, theDirection);
		break;
	case C:
		setBitState(DDRC, thePin, theDirection);
		break;
	case D:
		setBitState(DDRD, thePin, theDirection);
		break;
	}
	
	return DIO_OK;
}

// Function to set an output PIN, either it's an HIGH or LOW
EN_DIO_ERROR DIO_setPinState(portName thePort, pinNumber thePin, uint8_t theState)
{
	switch (thePort)
	{
		case A:
			setBitState(PORTA, thePin, theState);
			break;
		case B:
			setBitState(PORTB, thePin, theState);
			break;
		case C:
			setBitState(PORTC, thePin, theState);
			break;
		case D:
			setBitState(PORTD, thePin, theState);
			break;
	}
	
	return DIO_OK;
}

// Function to toggle an output PIN
EN_DIO_ERROR DIO_togglePin(portName thePort, pinNumber thePin)
{
	switch (thePort)
	{
		case A:
			toggleBit(PORTA, thePin);
			break;
		case B:
			toggleBit(PORTB, thePin);
			break;
		case C:
			toggleBit(PORTC, thePin);
			break;
		case D:
			toggleBit(PORTD, thePin);
			break;
	}	
	
	return DIO_OK;
}

// Function to return a state of an input PIN
uint8_t	DIO_getPinState(portName thePort, pinNumber thePin)
{
	switch (thePort)
	{
		case A:
			return getBit(PINA, thePin);
			break;
		case B:
			return getBit(PINB, thePin);
			break;
		case C:
			return getBit(PINC, thePin);
			break;
		case D:
			return getBit(PIND, thePin);
			break;
		default:
			return 0;
	}
}

// Function to initialize a port at once, either it's an input or output
EN_DIO_ERROR DIO_initializePort(portName thePort, direction theDirection)
{
	switch (thePort)
	{
		case A:
			DDRA = ((theDirection == OUTPUT) ? 0xFF : 0x0);
			break;
		case B:
			DDRB = ((theDirection == OUTPUT) ? 0xFF : 0x0);
			break;
		case C:
			DDRC = ((theDirection == OUTPUT) ? 0xFF : 0x0);
			break;
		case D:
			DDRD = ((theDirection == OUTPUT) ? 0xFF : 0x0);
			break;
	}
	
	return DIO_OK;
}

// Function to set the value of a port at once
EN_DIO_ERROR DIO_setPortState(portName thePort, uint8_t theState)
{
	switch (thePort)
	{
		case A:
			PORTA = theState;
			break;
		case B:
			PORTB = theState;
			break;
		case C:
			PORTC = theState;
			break;
		case D:
			PORTD = theState;
			break;
	}
	
	return DIO_OK;
}

// Function to return the value of a port at once
uint8_t	DIO_getPortState(portName thePort)
{
	switch (thePort)
	{
		case A:
			return PINA;
			break;
		case B:
			return PINB;
			break;
		case C:
			return PINC;
			break;
		case D:
			return PIND;
			break;
		default:
			return 0;
	}
}