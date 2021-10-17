CC = g++ -std=c++17
CFLAGS = -g -w -Wall

maze.o: src/backend/maze.cpp include/backend/maze.h
	$(CC) $(CFLAGS) -o maze.exe src/backend/maze.cpp include/backend/maze.h

clean:
	rm *.exe *.o
