/*
 * LED.h
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Timer/timer.h"
#include "../../MCAL/Interrupt/interrupt.h"

#define ON HIGH
#define OFF LOW

typedef enum {
	LED_OK, LED_FAILED
} EN_LED_ERROR;

EN_LED_ERROR LED_initialize(portName LEDport, pinNumber LEDpin);
EN_LED_ERROR LED_setState(portName LEDport, pinNumber LEDpin, uint8_t theState);
EN_LED_ERROR LED_blinkOne(portName LED1port, pinNumber LED1pin, uint16_t timeToStop, uint16_t milliseconds, uint8_t *externalCond);
EN_LED_ERROR LED_blinkTwo(portName LED1port, pinNumber LED1pin, portName LED2port, pinNumber LED2pin, uint16_t timeToStop, uint16_t milliseconds);

#endif /* LED_H_ */