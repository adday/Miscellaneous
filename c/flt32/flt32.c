#include "field.h"
#include "flt32.h"

/** @file flt32.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in flt32.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Alexander Day  830-523-317</b>
 */
int abs(int x);
/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_sign (flt32 x) {
  return getBit(x,31);
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_exp (flt32 x) {
  return (getField(x, 30, 23, 0) - 127); 
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_val (flt32 x) {
  return setBit(getField(x, 22, 0, 0),23);
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
void flt32_get_sve(flt32 x, int* sign, int* val, int* exp) {
	*sign = (flt32_get_sign (x));
	*val = (flt32_get_val(x));
	*exp = (flt32_get_exp(x));
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_leftmost_1 (int value) {
	int i;
	for(i = 31; i >= 0; i--){
		int bitMask = 1 << i;
		int x = value & bitMask;
		if(x)
			return i;}
	return -1;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_abs (flt32 x) {
	return clearBit(x,31);
	}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_negate (flt32 x) {	
	if(!x)//Prevent negation of zero
		return 0;
	if(getBit(x,31))
		return clearBit(x, 31);
	return setBit(x,31);
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_add (flt32 x, flt32 y) {
	if((flt32_abs(y) == flt32_abs(x)) && (flt32_get_sign(x) != flt32_get_sign(y)))
		return 0;
	if(flt32_abs(y) > flt32_abs(x)){//Make X hold highest absolute value
		int temp = y;
		y = x;
		x = temp;}
	//Account for cases where x or y = 0	
	if(!x)
		return y;
	if(!y)
		return x;
	//Seperate flt32 into sign, exponent, mantissa
	int signX = flt32_get_sign(x);
	int expX = flt32_get_exp(x) + 127;
	int valX = flt32_get_val(x);
	int signY = flt32_get_sign(y);
	int expY = flt32_get_exp(y) + 127;	
	int valY = flt32_get_val(y);
	while(expX > expY){	
		expY++;//Increment exponent
		valY = valY >> 1;}//Shift mantissa for each increment
	while(expY > expX){
		expX++;//Increment exponent
		valX = valX >> 1;}//Shift mantissa for each increment
	int valResult;
	int signResult = 0;
	int expResult = expY;//expX = expY	
	bool sameSigns = false;
	if(!signX & !signY){ //Both operands (+)
		sameSigns = true;
		valResult = valX + valY;}
	if(signX & signY){//Both operands (-)
		sameSigns = true;
		valResult = (~valY + 1) + (~valX + 1);//Add using 2s complement
		valResult = ~valResult + 1;//Convert from 2s complement
		signResult = 1;} 
	if(sameSigns)
		while(flt32_leftmost_1(valResult) > 23){//Adjust mantissa (sX=sY)
			valResult = valResult >> 1;
			expResult++;} 
	if(signX != signY){//Signs not the same
		valResult = valX + (~valY + 1);//Convert to 2's complement 
		if(signX)//Negative sign on larger #- MAKE RESULT (-)
			signResult = 1;
		while(flt32_leftmost_1(valResult) < 23){//Adjust mantissa (sX!=sY)
			valResult = valResult << 1;
			expResult--;} }
	if(valResult == 0){
		signResult = 0;
		return 0;}
	valResult = clearBit(valResult, 23);//Normalize (remove implicit 1)
	flt32 result = 0;
	result = result | (signResult << 31);
	result = result | (expResult << 23);
	result = result | valResult; 
	return result;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_sub (flt32 x, flt32 y) {	
 	return flt32_add(x, flt32_negate(y));
}

