/** @file       logic.c
 *  @brief      Functions simulating digital logic
 *  @details    This file contains functions to test the following digital logic:
 *              NOT, OR, AND, XOR, D LATCH, RS LATCH, ADDER, MULTIPLEXER, DECODER.
 *              
 *
 *  @author     Alexander Day
 *  @date       25FEB2015
 */

//Include files
#include "logic.h"

//Logic Gates


/**
 * Simulates NOT logic gate.
 *
 *  @param A    input to the NOT gate
 *  @return     NOT gate output, returns NOT A
 *
 * Truth table
 <pre>
        A   return
        0   1
        1   0
 </pre>
 */
BIT not_gate(BIT A)
{
    if (A==FALSE) {
        return TRUE;
    } else {
        return FALSE;
    }
}


/**
 * Simulates OR logic gate.
 *
 *  @param A    first input to the OR gate
 *  @param B    second input to the OR gate
 *  @return     returns A OR B
 *
 * Truth table
 <pre>
        A B  return
        0 0    0    
        0 1    1    
        1 0    1    
        1 1    1    
 </pre>
 */
BIT or_gate(BIT A, BIT B)
{
    if (A==FALSE && B==FALSE) {
        return FALSE;
    } else {
        return TRUE;
    }
}


/**
 * Simulates AND logic gate.
 *
 * @param A first input to the AND gate
 * @param B second input to the AND gate
 * @return return A AND B
 *
 * Truth Table
 <pre>
        A B  return
	0 0    0
	0 1    0
	1 0    0
	1 1    1
 </pre>
 */
BIT and_gate(BIT A, BIT B){
    if (A==TRUE && B==TRUE)
	return TRUE;
    else
	return FALSE; 	
}
	

/**
 * Simulates XOR logic gate.
 *
 * @param A first input to the XOR gate
 * @param B second input to the XOR gate
 * @return return A XOR B
 *
 * Truth Table
 <pre>
        A B  return
	0 0    0
	0 1    1
	1 0    1
	1 1    0
 </pre>
 */
BIT xor_gate(BIT A, BIT B){
   if ((A==FALSE && B==TRUE) | (A==TRUE && B==FALSE))
	return TRUE;
   else
	return FALSE; 
}


//Sequential Circuits


/**
 * Simulates RS latch circuit.
 * Asserts if S = R = 0.
 *
 *  @param S    set input line
 *  @param R    reset input line
 *  @return     returns RS latch output
 *
 * Truth table
 <pre>
        S R  return
        0 0   assert
        0 1   1 
        1 0   0 
        1 1   previous output 
 </pre>
 */
BIT rs_latch(BIT S, BIT R)
{
    static BIT saved_bit = FALSE;
    
    // if both bits are zero then behavior of R-S latch
    // is undefined so we will have the simulation assert
    assert(!(S==FALSE && R==FALSE));
    
    // implements the truth table
    if (S==FALSE) {
        saved_bit = TRUE; // Set
    } else if (R==FALSE) {
        saved_bit = FALSE; // Reset
    } else {
        saved_bit = saved_bit; // Unchanged
    }

    return saved_bit;
}


/**
 * Simulates a gated D latch.
 *  
 *  @param D    value to set in RS latch
 *  @param WE   allows manipulation of RS latch when TRUE
 *  @return     returns RS latch output
 *
 * Truth table
 <pre>
        D WE  return
        0 0   previous output
        0 1   0 
        1 0   previous output
        1 1   1 
 </pre>
 */
BIT d_latch(BIT D, BIT WE){
	static BIT saved_bit = FALSE;
	
	//Implements the truth table
	if(WE == TRUE)
		saved_bit = D;
	return saved_bit;
}


//Combinational Circuits


/**
 * Simulates a 4-bit adder
 *  
 *  @param O1         first operand (4 bits)
 *  @param O2	      second operand (4 bits)
 *  @param carryIn    third input to multiplexer (1 bit)
 *  @param carryOut   pointer to carryOut bit (set when sum has 5 bits)
 *  @return           the sum of the operands (4 bits)
 *
 * Truth table (given from documentation)
 <pre>
         01      02   carryIn   carryOut   return
        0101    0101     0         0        1010
        0101    0101     1         0        1011
        0001    0111     1         0        1001
        0111    0111     0         0        1110
        1101    1101     1         1       11011
 </pre>
 */
int adder(int O1, int O2,  BIT carryIn, BIT *carryOut){
	int sum;
	if(carryIn == TRUE)
		sum = O1 + O2 + 1;
	else
		sum = O1 + O2;	
	if(sum > 15)//value exceeds 4 bits
		*carryOut = TRUE;
	return (sum & 0xf);//mask only 4 bits
}


/**
 * Simulates a 4-input multiplexer
 *  
 *  @param A    first input to multiplexer
 *  @param B    second input to multiplexer
 *  @param C    third input to multiplexer
 *  @param D    fourth input to multiplexer
 *  @param S1   first select line
 *  @param S0   second select line
 *  @return     returns multiplexer output
 *
 * Truth table (given from documentation)
 <pre>
        A  B  C  D  S1  S0  return
        0  0  0  0  0   0   0 (A)
        1  1  1  1  1   1   1 (D)
	1  0  1  0  1   0   1 (C)
        0  1  0  1  0   1   1 (B)
 </pre>
 */
BIT multiplexer(BIT A, BIT B, BIT C, BIT D, BIT S1, BIT S0){
	if((S1 == FALSE) && (S0 == FALSE))
		return A;
	else if((S1 == FALSE) && (S0 == TRUE))
		return B;
	else if((S1 == TRUE) && (S0 == FALSE))
		return C;
	else if((S1 == TRUE) && (S0 == TRUE))
		return D;
	else
		return FALSE;
}


/**
 * Simulates a 2-input decoder
 *  
 *  @param A    first input to multiplexer
 *  @param B    second input to multiplexer
 *  @param C    third input to multiplexer
 *  @param D    fourth input to multiplexer
 *  @param S1   first select line
 *  @param S0   second select line
 *  @return     returns multiplexer output
 *
 * Truth table (given from documentation)
 <pre>
        A  B   O0  O1  O2  O3  
        0  0   1   0   0   0
  	0  1   0   1   0   0
 	1  0   0   0   1   0
	1  1   0   0   0   1 
 </pre>
 */
void decoder(BIT A, BIT B, BIT *O0, BIT *O1, BIT *O2, BIT *O3){
	if((A == FALSE) && (B == FALSE))
		*O0 = TRUE;
	else if(A == FALSE)
		*O1 = TRUE;
	else if((A == TRUE) && (B == FALSE))
		*O2 = TRUE;
  	else if(B == TRUE)
		*O3 = TRUE;
}

