all: measure sender

measure: measure.o
	gcc measure.o -o measure

measure.o: measure.c
	gcc -c measure.c

sender: sender.o
	gcc sender.o -o sender

sender.o: sender.c
	gcc -c sender.c

clear: 
	rm -f *.o measure sender