/** @mainpage CS270 Spring 2015
 *  \htmlinclude "PA5.html"
 */

/** @file: main.c
 *  @brief Driver to test functions of number_detective.c (do not modify)
 *
 * @details This is a driver program for the functions in logic.c. It tests
 * 	    each function to ensure that its output correctly matches that of
 * 	    the truth table given.
 * <p>
 * @author Alexander Day
 * @date   25FEB2015
 * */

// Include files
#include "logic.h"

/** Entry point of the program
 * @param   argc count of arguments, will always be at least 1
 * @param   argv array of parameters to program argv[0] is the name of
 *          the program, so additional parameters will begin at index 1
 * @details If one of the test cases fail then the program will assert.
 * @return  0 the Linux convention for success.
 */
int main(int argc, char *argv[])
{
    // check NOT gate truth table
    // A   NOT(A)
    // 0     1
    // 1     0
    printf("===== Testing not_gate =====\n");
    assert(not_gate(FALSE) == TRUE); 
    assert(not_gate(TRUE) == FALSE); 


    // check OR gate truth table
    // A B (A OR B)
    // 0 0   0
    // 0 1   1
    // 1 0   1
    // 1 1   1
    printf("===== Testing or_gate =====\n");
    assert(or_gate(FALSE,FALSE) == FALSE); 
    assert(or_gate(FALSE,TRUE) == TRUE); 
    assert(or_gate(TRUE,FALSE) == TRUE); 
    assert(or_gate(TRUE,TRUE) == TRUE); 


    // check AND gate truth table
    // A B (A AND B)
    // 0 0   0
    // 0 1   0
    // 1 0   0
    // 1 1   1
    printf("===== Testing and_gate =====\n");
    assert(and_gate(FALSE,FALSE) == FALSE); 
    assert(and_gate(FALSE,TRUE) == FALSE); 
    assert(and_gate(TRUE,FALSE) == FALSE); 
    assert(and_gate(TRUE,TRUE) == TRUE); 

   

    // check XOR gate truth table
    // A B (A XOR B)
    // 0 0   0
    // 0 1   1
    // 1 0   1
    // 1 1   0
    printf("===== Testing xor_gate =====\n");
    assert(xor_gate(FALSE,FALSE) == FALSE); 
    assert(xor_gate(FALSE,TRUE) == TRUE); 
    assert(xor_gate(TRUE,FALSE) == TRUE); 
    assert(xor_gate(TRUE,TRUE) == FALSE); 

    
    // check RS latch truth table
    // the order matters so that the saved_bit will be true when expected
    //  S	R	saved_bit   rs_latch(S,R)
    //  FALSE	FALSE	FALSE	    will assert in rs_latch
    //  FALSE	FALSE	TRUE	    will assert in rs_latch
    //  TRUE	FALSE	FALSE	    FALSE
    //	TRUE	TRUE	FALSE	    FALSE
    //  FALSE	TRUE	FALSE	    TRUE
    //  FALSE	TRUE	TRUE	    TRUE
    //	TRUE	TRUE	TRUE	    TRUE
    //  TRUE	FALSE	TRUE	    FALSE
    printf("===== Testing rs_latch =====\n");
    assert( rs_latch( TRUE, FALSE )==FALSE );
    assert( rs_latch( TRUE, TRUE )==FALSE );
    assert( rs_latch( FALSE, TRUE )==TRUE );
    assert( rs_latch( FALSE, TRUE )==TRUE );
    assert( rs_latch( TRUE, TRUE )==TRUE );
    assert( rs_latch( TRUE, FALSE )==FALSE );

	
    // check gated D latch truth table
    // the order matters so that the saved_bit will be true when expected
    // D WE saved_bit   d_latch(D,WE)
    // 0 0  	0	     0
    // 0 1 	0	     0
    // 1 0   	0	     0	
    // 1 1   	0	     1
    // 0 0  	1	     1
    // 0 1 	1	     0
    // 1 0   	1	     1	
    // 1 1   	1	     1
    printf("===== Testing d_latch =====\n");
    assert( d_latch( FALSE, FALSE )==FALSE );
    assert( d_latch( FALSE, TRUE )==FALSE );
    assert( d_latch( TRUE, FALSE )==FALSE );
    assert( d_latch( TRUE, TRUE )==TRUE );
    assert( d_latch( FALSE, FALSE )==TRUE );
    assert( d_latch( TRUE, FALSE )==TRUE );
    assert( d_latch( TRUE, TRUE )==TRUE );
    assert( d_latch( FALSE, TRUE )==FALSE );


    // check adder truth table
    // the carryOut bit must be set appropriately
    //   O1      O2   carryIn   carryOut  adder(O1, O2, carryIn, *carryOut)
    //  0101    0101     0         0        1010
    //  0101    0101     1         0        1011
    //  0001    0111     1         0        1001
    //  0111    0111     0         0        1110
    //  1101    1101     1         1       11011
    BIT carryOut;
    printf("===== Testing adder =====\n");
    assert(adder(5, 5, FALSE, &carryOut)== 10 && carryOut == FALSE);
    assert(adder(15, 15, FALSE, &carryOut)==14  && carryOut == TRUE);
    carryOut = FALSE;//clear carryOut bit for next function call
    assert(adder(7, 5,FALSE, &carryOut) == 12 && carryOut == FALSE);
    assert(adder(7, 5, 1, &carryOut) == 13 && carryOut == FALSE);
    assert(adder(5, 5, TRUE, &carryOut) == 11 && carryOut == FALSE);
    assert(adder(1, 7, TRUE, &carryOut) == 9 && carryOut == FALSE);
    assert(adder(7, 7, FALSE, &carryOut) == 14 && carryOut == FALSE);
    assert(adder(13, 13, TRUE, &carryOut) == 11 && carryOut == TRUE);
 

    // check multiplexer truth table
    // A  B  C  D  S1  S0  multiplexer(A,B,C,D,S1,S0)
    // 0  0  0  0  0   0     0 (A)
    // 1  1  1  1  1   1     1 (D)
    // 1  0  1  0  1   0     1 (C)
    // 0  1  0  1  0   1     1 (B)  
    printf("===== Testing multiplexer =====\n");
    assert(multiplexer(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE)==FALSE );
    assert(multiplexer(TRUE, TRUE, TRUE ,TRUE, TRUE, TRUE)==TRUE );
    assert( multiplexer(TRUE, FALSE, TRUE, FALSE, TRUE, FALSE)== TRUE );
    assert( multiplexer(FALSE, TRUE, FALSE, TRUE, FALSE, TRUE)==TRUE );



    // check decoder truth table 
    // bits must be cleared before each function call
    // A  B   O0  O1  O2  O3  
    // 0  0   1   0   0   0
    // 0  1   0   1   0   0
    // 1  0   0   0   1   0
    // 1  1   0   0   0   1 
    BIT O0 = FALSE;
    BIT O1 = FALSE;
    BIT O2 = FALSE;
    BIT O3 = FALSE;
    printf("===== Testing decoder =====\n");
    decoder(FALSE, FALSE, &O0, &O1, &O2, &O3);
    assert((O0 == TRUE) && (O1 == FALSE) && (O2 == FALSE) && (O3 == FALSE));
    O0 = FALSE;//clear bit for next function call
    decoder(FALSE, TRUE, &O0, &O1, &O2, &O3);
    assert((O0 == FALSE) && (O1 == TRUE) && (O2 == FALSE) && (O3 == FALSE));
    O1 = FALSE;//clear bit for next function call
    decoder(TRUE, FALSE, &O0, &O1, &O2, &O3);
    assert((O0 == FALSE) && (O1 == FALSE) && (O2 == TRUE) && (O3 == FALSE));
    O2 = FALSE;//clear bit for next function call
    decoder(TRUE, TRUE, &O0, &O1, &O2, &O3);
    assert((O0 == FALSE) && (O1 == FALSE) && (O2 == FALSE) && (O3 == TRUE));
    

    return 0;
}


