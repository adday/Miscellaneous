#include "field.h"
#include <stdio.h>

/** @file field.c
 *  @brief You will modify this file and implement six functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. For example, methods you write may need a mask value.
 *  You might write a method to compute a mask for you and use it wherever
 *  it is needed as opposed to just putting the code in line.
 *  These additional <b>static</b> functions are similar to Java’s private methods.
 * <p>
 * @author <b>Alexander Day 830 523 317</b> 
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
  int bitMask = 1 << position;
  int bit = (value & bitMask);
  if(bit == 0)
	  return 0;
  else
	  return 1;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
    	int bitMask = 1 << position;
	return (value | bitMask);
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
    	int bitMask = ~(1 << position);
	return (value & bitMask);
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
	if(hi < lo){//Reset hi and low to correct order
		int temp = hi;
		hi = lo;
		lo = temp;}
	int count, tempMask, newValue;
	int bitMask = 0;
	int diff = (hi - lo) + 1;
	for(count = 0; count < diff; count++){
        	tempMask = 1 << count;
		bitMask += tempMask;}
	bitMask = bitMask << lo;
	newValue = (bitMask & value) >> lo ;
	if(isSigned)
		if(getBit(newValue, diff-1) == 1){
			newValue = clearBit(newValue, diff-1);
			tempMask = ~0;
			int i;
			for(i = 0; i < diff-1; i++)
				tempMask = clearBit(tempMask, i);
			return (tempMask | newValue);}
   	return newValue;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setField (int oldValue, int hi, int lo, int newValue) {
	if(hi < lo){//Reset hi and low to correct order
		int temp = hi;
		hi = lo;
		lo = temp;}
	int count;
	newValue = newValue << lo;
	for(count = lo; count < hi+1; count++){
		if(getBit(newValue, count) == 0)
			oldValue = clearBit(oldValue, count);
		else
			oldValue = setBit(oldValue, count);
	}
	return oldValue;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int fieldFits (int value, int width, bool isSigned) {
	if(value < 0){
		value *= -1;
		width += 1;}
	if(isSigned)
		width -= 1;
	int i;
	value = value >> width;
	for(i = 0; i < 32 - width; i++)
		if(getBit(value,i) == 1)
			return 0;
	return 1;
}


