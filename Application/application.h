/*
 * application.h
 */ 


#ifndef HEADER_H_
#define HEADER_H_

#include "../ECUAL/LED/LED.h"
#include "../ECUAL/Button/Button.h"
#include "../MCAL/Timer/timer.h"
#include "../MCAL/Interrupt/interrupt.h"
#include "../Utilities/PINconfigurations.h"

#define BEGIN_STATE			0
#define CARS_PASSING		1
#define CARS_READY_TO_STOP	2
#define CARS_STOP			3
#define CARS_READY_TO_PASS	4

typedef enum {
	APP_OK, APP_FAILED
}EN_APP_ERROR;

uint8_t TRAFFIC_STATE;
uint8_t PEDS_MODE;
uint8_t TIMER_BREAK_FLAG; // FLAG TO BREAK TIMER

EN_APP_ERROR APP_turnOffLEDs();
EN_APP_ERROR APP_carsPass();
EN_APP_ERROR APP_ready();
EN_APP_ERROR APP_carsStop();
EN_APP_ERROR APP_goToNextState();

EN_APP_ERROR APP_initialize();
EN_APP_ERROR APP_start();

#endif /* HEADER_H_ */