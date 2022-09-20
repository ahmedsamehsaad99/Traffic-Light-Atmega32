/*
 * Button.c
 */ 

#include "Button.h"

// Function to initialize the button created
EN_BUTTON_ERROR BUTTON_initialize(portName buttonPort, pinNumber buttonPin)
{
	if (DIO_initializePin(buttonPort, buttonPin, INPUT) == DIO_OK)
		return BUTTON_OK;
	else
		return BUTTON_FAILED;
}

// Function to return the state of the button
uint8_t BUTTON_getState(portName buttonPort, pinNumber buttonPin)
{
	return (DIO_getPinState(buttonPort, buttonPin));
}