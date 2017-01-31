MY_CPP = /usr/bin/g++

# makefile for compiling weight_enumerator.c into weight_enumerator.out


weight_enumerator.out:  weight_enumerator.o;
	$(MY_CPP)  weight_enumerator.o  -o $@


weight_enumerator.o: weight_enumerator.c; $(MY_CPP) -c weight_enumerator.c -o $@

