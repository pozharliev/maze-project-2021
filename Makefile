CC = g++ -std=c++17
CFLAGS = -g -w -Wall
LIBS = -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static

all: main

main: map.o main.cpp
	$(CC) $(CFLAGS) -o main.exe main.cpp map.o $(LIBS)

map.o: src/frontend/map.cpp include/frontend/map.h libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h
	$(CC) $(CFLAGS) -c src/frontend/map.cpp $(LIBS)

maze.o: src/backend/maze.cpp include/backend/maze.h
	$(CC) $(CFLAGS) -o maze.exe src/backend/maze.cpp

clean:
	rm *.exe *.o