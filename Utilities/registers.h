/*
 * registers.h
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "typeDefs.h"


//************ AVR REGISTERS *************

#define	SREG	*((volatile uint8_t*)0x5F)



//************ DIO REGISTERS *************

///////// PORTA /////////

#define	PORTA	*((volatile uint8_t*)0x3B)
#define	DDRA	*((volatile uint8_t*)0x3A)
#define	PINA	*((volatile uint8_t*)0x39)

///////// PORTB /////////

#define	PORTB	*((volatile uint8_t*)0x38)
#define	DDRB	*((volatile uint8_t*)0x37)
#define	PINB	*((volatile uint8_t*)0x36)

///////// PORTC /////////

#define	PORTC	*((volatile uint8_t*)0x35)
#define	DDRC	*((volatile uint8_t*)0x34)
#define	PINC	*((volatile uint8_t*)0x33)

///////// PORTD /////////

#define	PORTD	*((volatile uint8_t*)0x32)
#define	DDRD	*((volatile uint8_t*)0x31)
#define	PIND	*((volatile uint8_t*)0x30)



//************ TIMERS REGISTERS *************

///////// GENERAL REGISTERS /////////

#define TIMSK	*((volatile uint8_t*)0x59)
#define	TIFR	*((volatile uint8_t*)0x58)

///////// TIMER0 /////////

#define	TCCR0	*((volatile uint8_t*)0x53)
#define	TCNT0	*((volatile uint8_t*)0x52)

///////// TIMER1 /////////

#define TCCR1A	*((volatile uint8_t*)0x4F)
#define TCCR1B	*((volatile uint8_t*)0x4E)

#define TCNT1H	*((volatile uint8_t*)0x4D)
#define TCNT1L	*((volatile uint8_t*)0x4C)

///////// TIMER2 /////////

#define	TCCR2	*((volatile uint8_t*)0x45)
#define	TCNT2	*((volatile uint8_t*)0x44)



//************ INTERRUPTS REGISTERS *************

#define	GICR	*((volatile uint8_t*)0x5B)
#define	GIFR	*((volatile uint8_t*)0x5A)

#define	MCUCR	*((volatile uint8_t*)0x55)
#define	MCUCSR	*((volatile uint8_t*)0x54)

#endif /* REGISTERS_H_ */