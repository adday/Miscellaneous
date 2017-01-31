P3: Producer/Consumer Problem using Bounded Circular Buffer:

Build executable command:	make all
Run executable command:	java Main arg1 arg2 arg3

							where: 	arg1 is the size of the BoundedBuffer, BI
									arg2 is the number of items to produce, NI
									arg3 is the max wait time, MW

This program utilizes a circular bounded buffer into which a producer can insert items and 
a consumer can remove them. It satisfies the specifications of P3 for CS370 Operating Systems.

NOTE: If the buffer size entered is 0, then the number of items to produce must also be 0.

Let's start our explanation in Main.java:

	In Main.java we do a number of things. The first is to parse all command line arguments
	for later use into the appropriate variables and ensure their validity. On invalid input program 
	terminates after displaying a usage message.For input checking and thread
	exception handling some code is placed in try-catch blocks. 

	After this a producer is created and given exclusive access to the buffer in order to produce items.
	In order to ensure that the producer does not go into a deadlocked(infinite waiting) state waiting for a 
	consumer when the bounded buffer becomes full the parallel boolean flag passed in is false. 
	This causes the producer to only print successful insertions for the number of items it is able to produce,
	which is the number of items the buffer can hold, BI. It prints one unsuccessful insertion message and then terminates.
	
	After the producer has exclusive access, a consumer is created. With it, the same method as above, but consuming, 
	is performed by the consumer. Similarly, it will only successfully consume up to the number of items in the buffer and 
	will then print the unsuccessful removal message only once .

	Next is the parallel section, here there are two producers and one consumer created. The producers 
	want to produce the amount of items to produce passed in by the command line. The consumer seeks 
	to consume 2 times this many items, thus consuming all items produced by the two producers. These
	processes will run concurrently. The BoundedBuffer satisfies the needed amount of items even, NI, even if
	NI > BI, the size of the buffer. This is done as the consumer will consume items allowing a producer to add 
	another item. After all items, NI, have been produced and consumed, main terminates. 

Now let's look at the classes individually in more detail:

	BoundedBuffer.java: The BoundedBuffer class holds insert() and remove() methods designed for a circular buffer. 
						The isEmpty() and isFull() methods are used by the producer and consumer and use a 
						length variable in order to assess  buffer availability. 
						Pointer in/out positions are updated using a modulus operation.

	Producer.java:	The Producer class uses a synchronized produce() method to insert items into the buffer. The items 
				     	inserted are random doubles, generated on the fly. Mutual exclusion of buffer access for the
				 	producer is provided by a call to wait() and notify(). The producer produces only NI items.
					The use of the flag variable to terminate execution when not running in parallel with a consumer 
					can be seen in the produce() method. When an item is produced, a statement prints telling where it 
					was inserted in the buffer and at what time. When an item fails to be inserted into the buffer, a
					statement prints telling where it was to be inserted and at what time.

	Consumer.java:	The Consumer class uses a synchronized consume() method to remove items from the buffer. While 
					items are not  technically "removed", removal is achieved through use of the out pointer held in the
					BoundedBuffer class. Essentially, the consumer's call to BoundedBuffer.remove() will manipulate the 
					pointer so as to indicate a new open position. Mutual exclusion of  buffer access by the consumer is
					provided by a call to wait() and notify(). The consumer consumes the number of items passed into 
					the constructor, either NI or 2*NI depending on which section in Main.java. The use of the flag 
					variable to terminate execution when not running in parallel with a producer can be seen in the 
					consume() method. When an item is consumed, a statement prints telling where it was removed
					from the buffer and at what time. When an item fails to be removed from the buffer, a statement 
					prints telling where it was to be removed and at what time.
			
	

