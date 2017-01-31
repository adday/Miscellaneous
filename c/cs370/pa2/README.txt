CS370 PA2
Author: Alexander Day CSU#:830 523 317

FILE DESCRIPTIONS:
expox.c: 
	 This file compiles to "expox" using Makefile.
	 It expects two input arguments: 1. floating point x s.t. 0 < x < 1
					 2. integer n s.t. n > 0
 	 It passes these arguments to a child process that it forks called
	 "expoxch". If the fork() fails then it returns 1. Upon return from 
	 the child process, it prints the child exit code. This process 
	 also prints its PID. It then returns 0.

expoxch.c: 
	 This file compiles to "expoxch" using Makefile.
	 It expects two input arguments: 1. floating point x s.t. 0 < x < 1
					 2. integer n s.t. n > 0
		NOTE: These arguments will be represented as char*
		      for passing and are parsed to appropriate type.
 	 It then approximates the exponential function to the power x. This is
	 done using the series expansion. The built in C implementation of pow()
	 is used in calculating the series as well as the iterative factorial 
	 function defined in this file. The program prints out the result of
	 calculating e^x using built in function.The program will print out message
         stating the parameters used in calculation and the estimated value as 
	 well as the PID of this process. If the series calculation differs from 
 	 built in C function exp() by more than 1 than it prints an error message 
	 that the approximation is off and returns 1. If the approximation is
	 correct it returns 0. 

Makefile:
	 Compiles two executables "expox" and "expoxch" from the .c files expox.c 
	 and expoxch.c

