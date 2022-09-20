/*
 * LED.c
 */ 

#include "LED.h"

// Function to initialize a new LED
EN_LED_ERROR LED_initialize(portName LEDport, pinNumber LEDpin)
{
	if (DIO_initializePin(LEDport, LEDpin, OUTPUT) == DIO_OK)
		return LED_OK;
	else
		return LED_FAILED;
}

// Function to either turn an LED ON or OFF
EN_LED_ERROR LED_setState(portName LEDport, pinNumber LEDpin, uint8_t theState)
{
	if (DIO_setPinState(LEDport, LEDpin, theState) == DIO_OK)
		return LED_OK;
	else
		return LED_FAILED;
}

// Function used to blink one LED, while entering the time to stop blinking and blinking frequency as well as an external condition to stop blinking
EN_LED_ERROR LED_blinkOne(portName LED1port, pinNumber LED1pin, uint16_t timeToStop, uint16_t milliseconds, uint8_t *externalCond)
{
	for (uint8_t i = 0; i < timeToStop/milliseconds; i++)
	{
		if (*externalCond == 1)
			break;
		if (DIO_togglePin(LED1port, LED1pin) == DIO_OK)
		{
			TIMER_delay(TIMER0, milliseconds);
		}
	}
	return LED_OK;
}

// Function used to blink two LEDs at the same time, while entering the time to stop blinking and blinking frequency
EN_LED_ERROR LED_blinkTwo(portName LED1port, pinNumber LED1pin, portName LED2port, pinNumber LED2pin, uint16_t timeToStop, uint16_t milliseconds)
{
	for (uint8_t i = 0; i < timeToStop/milliseconds; i++)
	{
		if (DIO_togglePin(LED1port, LED1pin) == DIO_OK)
		{	
			if (DIO_togglePin(LED2port, LED2pin) == DIO_OK)
			{
				TIMER_delay(TIMER2, milliseconds);
			}
		}
	}
	return LED_OK;
}