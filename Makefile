CC = gcc
CFLAGS = -g -Wall -std=c99

myavl: *.o
	$(CC) *.o -o myavl 

*.o: *.c
	$(CC) $(CFLAGS) -c *.c

clean:
	rm -rf *.o vgcore* teste?.out

purge: clean
	rm -rf myavl
