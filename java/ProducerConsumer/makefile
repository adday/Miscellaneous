#Makefile for CS370:P3
#Alexander Day
JCC = javac
JFLAGS = -g

all: BoundedBuffer.class Producer.class Consumer.class Main.class

BoundedBuffer.class: BoundedBuffer.java
	$(JCC) $(JFLAGS) BoundedBuffer.java

Producer.class: Producer.java
	$(JCC) $(JFLAGS) Producer.java

Consumer.class: Consumer.java
	$(JCC) $(JFLAGS) Consumer.java

Main.class: Main.java BoundedBuffer.class Producer.class Consumer.class
	$(JCC) $(JFLAGS) Main.java

clean: 
	$(RM) *.class
