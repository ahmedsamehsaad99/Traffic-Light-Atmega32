/*
 * DIO.h
 */ 

#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/registers.h"
#include "../../Utilities/typeDefs.h"
#include "../../Utilities/bitwiseOperations.h"

// ENUM to define directions, either it's INPUT 0 or OUTPUT 1
typedef enum {
	INPUT,
	OUTPUT
} direction;
	
// ENUM to define PIN numbers from 0-7
typedef enum {
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
} pinNumber;

// ENUM to define PORT NAMES
typedef enum {
	A, B, C, D
} portName;

typedef enum {
	DIO_OK, DIO_FAILED
} EN_DIO_ERROR;

#define HIGH 1
#define LOW 0

EN_DIO_ERROR	DIO_initializePin(portName thePort, pinNumber thePin, direction theDirection);
EN_DIO_ERROR	DIO_setPinState(portName thePort, pinNumber thePin, uint8_t theState);
EN_DIO_ERROR	DIO_togglePin(portName thePort, pinNumber thePin);
uint8_t			DIO_getPinState(portName thePort, pinNumber thePin);

EN_DIO_ERROR	DIO_initializePort(portName thePort, direction theDirection);
EN_DIO_ERROR	DIO_setPortState(portName thePort, uint8_t theState);
uint8_t	DIO_getPortState(portName thePort);

#endif /* DIO_H_ */