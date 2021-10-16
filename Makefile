CC = g++ -std=c++17
CFLAGS = -g -w -Wall
LIBS = -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static

all: player.o run

run: player.o
	./player

player.o: main.cpp src/frontend/player.cpp include/frontend/player.h libs/olcPixelGameEngine.h
	$(CC) -o player.exe main.cpp src/frontend/player.cpp include/frontend/player.h $(LIBS)

maze.o: src/backend/maze.cpp include/backend/maze.h
	$(CC) $(CFLAGS) -o maze.exe src/backend/maze.cpp include/backend/maze.h

clean:
	rm *.exe *.o
