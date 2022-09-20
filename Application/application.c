/*
 * application.c
 */ 

#include "application.h"

uint8_t TRAFFIC_STATE = 0;		// VARIABLE TO DETECT CURRENT TRAFFIC STATE
uint8_t PEDS_MODE = 0;			// VARIABLE TO SEE IF IT'S PEDESTRIAN MODE OR NOT
uint8_t TIMER_BREAK_FLAG = 0;	// FLAG TO BREAK TIMERS WHEN RETURNING FROM INTERRUPTS

// FUNCTION TO TURN OFF ALL LEDS
EN_APP_ERROR APP_turnOffLEDs()
{
	LED_setState(CARS_GREEN, OFF);
	LED_setState(CARS_YELLOW, OFF);
	LED_setState(CARS_RED, OFF);
	LED_setState(PEDESTRIANS_GREEN, OFF);
	LED_setState(PEDESTRIANS_YELLOW, OFF);
	LED_setState(PEDESTRIANS_RED, OFF);
	
	return APP_OK;
}

// FUNCTION FOR THE CARS TO PASS, TURNING ON THEIR GREEN LED
EN_APP_ERROR APP_carsPass()
{
	LED_setState(CARS_GREEN, ON);
	
	if (PEDS_MODE) // IF IT'S PEDESTRIAN MODE
		LED_setState(PEDESTRIANS_RED, ON);
		
	for (uint8_t i = 0; i < 50; i++)
	{
		if (TRAFFIC_STATE == CARS_PASSING)
			TIMER_delay(TIMER0, 100);
		else
			break;	// IF STATE CHANGED, BREAK THE TIMER
	}
	APP_turnOffLEDs();
	return APP_OK;
}

// FUNCTION TO IMPLEMENT READY STATE
EN_APP_ERROR APP_ready()
{
	if (PEDS_MODE) // IF IT'S PEDESTRIAN MODE, IT WILL BLINK 2 LEDS
		LED_blinkTwo(CARS_YELLOW, PEDESTRIANS_YELLOW, 5000, 500);
	else
		LED_blinkOne(CARS_YELLOW, 5000, 500, &PEDS_MODE); // BLINK ONE LED AND BREAK TIMER IF RETURNED FROM INTERRUPT

	APP_turnOffLEDs();
	return APP_OK;
}

// FUNCTION TO IMPLEMENT CARS STOPPING, TURNING THEIR RED LED ON
EN_APP_ERROR APP_carsStop()
{
	LED_setState(CARS_RED, ON);

	if (PEDS_MODE == 1)
		LED_setState(PEDESTRIANS_GREEN, ON);
		
	for (uint8_t i = 0; i < 50; i++)
	{
		// IF RETURNED FROM INTERRUPT, BREAK the loop...
		if (TIMER_BREAK_FLAG == 1)
		{
			TIMER_BREAK_FLAG = 0;
			break;
		}
		TIMER_delay(TIMER2, 100);
	}
	APP_turnOffLEDs();
	return APP_OK;
}

// SWITCH FUNCTION, MOVING FROM A STATE TO ANOTHER WHILE IMPLEMENTING THE ABOVE FUNCTIONS
EN_APP_ERROR APP_goToNextState()
{
	switch (TRAFFIC_STATE)
	{
		case BEGIN_STATE:
			TRAFFIC_STATE++;	// STATE = CARS PASSING
			APP_carsPass();
			break;
		case CARS_PASSING:
			TRAFFIC_STATE++;	// STATE = CARS READY TO STOP
			APP_ready();
			break;
		case CARS_READY_TO_STOP:
			TRAFFIC_STATE++;	// STATE = CARS STOP
			APP_carsStop();
			break;
		case CARS_STOP:
			TRAFFIC_STATE++;	// STATE = CARS READY TO PASS
			APP_ready();
			break;
		case CARS_READY_TO_PASS:
			TRAFFIC_STATE = CARS_PASSING;	// RETURN TO FIRST STATE
			PEDS_MODE = 0;	// IF PEDS MODE WAS EVER 1, GET IT BACK TO 0
			APP_carsPass();
			break;
	}
	return APP_OK;
}


// INTERRUPT SERVICE ROUTINE TO HANDLE BUTTON PRESSES
ISR(EXT_INT_0)
{
	TIMER_delay(TIMER1, 500); // WAIT FOR LONG PRESS
	
	if (BUTTON_getState(CROSSWALK_BUTTON) == RELEASED) // DETECT SHORT PRESS
	{
		if (TRAFFIC_STATE == CARS_PASSING) // SWITCH TO BLINKS
		{
			PEDS_MODE = 1;
			APP_turnOffLEDs();
			APP_goToNextState(); // MOVE TO THE READY STATE BUT PEDS_MODE = 1, BLINKING 2 LEDS
		}
		else if (TRAFFIC_STATE == CARS_READY_TO_STOP)
		{
			APP_turnOffLEDs();
			PEDS_MODE = 1;
			TRAFFIC_STATE--;	// STATE NOW = CARS PASSING..
			LED_setState(PEDESTRIANS_RED, ON);
			APP_goToNextState(); // RESET THE READY STATE BUT PEDS_MODE = 1, BLINKING 2 LEDS
		}
		else if (TRAFFIC_STATE == CARS_STOP) // IF CARS' RED LED IS ON
		{
			PEDS_MODE = 1;
			LED_setState(PEDESTRIANS_GREEN, ON);
			TIMER_delay(TIMER0, 5000);
			TIMER_BREAK_FLAG = 1;
		}
	}
}

// FUNCTION TO INITIALIZE THE APPLICATION
EN_APP_ERROR APP_initialize()
{
	BUTTON_initialize(CROSSWALK_BUTTON);

	LED_initialize(CARS_GREEN);
	LED_initialize(CARS_YELLOW);
	LED_initialize(CARS_RED);

	LED_initialize(PEDESTRIANS_GREEN);
	LED_initialize(PEDESTRIANS_YELLOW);
	LED_initialize(PEDESTRIANS_RED);
	
	INTERRUPT_initialize(EXT_0, RISING_EDGE);
	
	return APP_OK;
}

// FUNCTION TO START THE APPLICATION
EN_APP_ERROR APP_start()
{
	APP_goToNextState();
	return APP_OK;
}