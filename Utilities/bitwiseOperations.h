/*
 * bitwiseOperations.h
 */ 

#ifndef BITWISEOPERATIONS_H_
#define BITWISEOPERATIONS_H_

#define setBitState(REGISTER, BITNUM, BITSTATE) (BITSTATE == 1) ? (REGISTER |= (1<<BITNUM)) : (REGISTER &= ~(1<<BITNUM))
#define getBit(REGISTER, BITNUM) (REGISTER&(1<<BITNUM))>>BITNUM
#define toggleBit(REGISTER, BITNUM) REGISTER ^= (1<<BITNUM)

#endif /* BITWISEOPERATIONS_H_ */