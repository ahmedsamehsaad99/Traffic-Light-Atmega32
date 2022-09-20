/*
 * interrupt.h
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "../../Utilities/registers.h"
#include "../../Utilities/typeDefs.h"
#include "../../Utilities/bitwiseOperations.h"

// ENUM to define EXTERNAL INTERRUPT numbers
typedef enum extInterruptNumber {
	EXT_0, EXT_1, EXT_2
} extInterruptNumber;

// ENUM to define EXTERNAL INTERRUPT sensing
typedef enum interruptSense {
	LOW_LEVEL, LOGICAL_CHANGE, FALLING_EDGE, RISING_EDGE
} interruptSense;

typedef enum {
	INTERRUPT_OK, INTERRUPT_FAILED
} EN_INTERRUPT_ERROR;

// External Interrupts Handler
#define EXT_INT_0 __vector_1
#define EXT_INT_1 __vector_2
#define EXT_INT_2 __vector_3
#define TIMER2_OVF_vect	__vector_5
#define TIMER0_OVF_vect	__vector_11

// INTERRUPT SERVICE ROUTINE DECLARATION
#define ISR(INTERRUPT_VECTOR)	void INTERRUPT_VECTOR (void) __attribute__ ((signal, used));\
void INTERRUPT_VECTOR(void)

EN_INTERRUPT_ERROR INTERRUPT_enableGlobalInterrupts();
EN_INTERRUPT_ERROR INTERRUPT_setExternalInterruptSense(extInterruptNumber intNumber, interruptSense intSense);
EN_INTERRUPT_ERROR INTERRUPT_enableExternalInterrupt(extInterruptNumber intNumber);
uint8_t INTERRUPT_getInterruptFlag(extInterruptNumber intNumber);
EN_INTERRUPT_ERROR INTERRUPT_initialize(extInterruptNumber intNumber, interruptSense intSense);


#endif /* INTERRUPT_H_ */