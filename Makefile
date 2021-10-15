CC = g++
CFLAGS = -g -w -Wall

all: main run clean

run: main
	./main
main:

clean:
	rm bin/*.exe *.o
