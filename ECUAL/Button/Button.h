/*
 * Button.h
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO/DIO.h"

#define PRESSED HIGH
#define RELEASED LOW

typedef enum EN_BUTTON_ERROR{BUTTON_OK, BUTTON_FAILED}EN_BUTTON_ERROR;
	
EN_BUTTON_ERROR BUTTON_initialize(portName buttonPort, pinNumber buttonPin);
uint8_t BUTTON_getState(portName buttonPort, pinNumber buttonPin);


#endif /* BUTTON_H_ */