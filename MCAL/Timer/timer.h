/*
 * timer.h
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/registers.h"
#include "../../Utilities/typeDefs.h"
#include "../../Utilities/bitwiseOperations.h"
#include "../Interrupt/interrupt.h"

#define FCPU 1000000

typedef enum timerMode {
	NORMAL, PWM_PHASE_CORRECT, CTC, FAST_PWM
} timerMode;

typedef enum prescalerChoice {
	NO_PRESCALER, PRESCALER_8, PRESCALER_64, PRESCALER_256, PRESCALER_1024
} prescalerChoice;

typedef enum timerNumber {
	TIMER0, TIMER1, TIMER2
}timerNumber;

typedef enum {
	TIMER_OK, TIMER_FAILED
}EN_TIMER_ERROR;

EN_TIMER_ERROR TIMER_setMode(timerNumber timer, timerMode theMode);
EN_TIMER_ERROR TIMER_setInitialValue(timerNumber timer, uint16_t initialValue);
EN_TIMER_ERROR TIMER_start(timerNumber timer, prescalerChoice thePrescaler);
EN_TIMER_ERROR TIMER_stop(timerNumber timer);
uint8_t TIMER_getOverflowTIMER_BREAK_FLAG(timerNumber timer);
EN_TIMER_ERROR TIMER_clearOverflowTIMER_BREAK_FLAG(timerNumber timer);
EN_TIMER_ERROR TIMER_delay(timerNumber timer, uint16_t milliseconds);
EN_TIMER_ERROR TIMER_setTimerForInterrupt(timerNumber timer, uint16_t milliseconds);

#endif /* TIMER_H_ */