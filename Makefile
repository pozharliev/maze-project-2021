CC = g++ -std=c++17
CFLAGS = -g -w -Wall

all: player.o run

run: player.o
	./player

maze.o: src/backend/maze.cpp include/backend/maze.h
	$(CC) $(CFLAGS) -o maze.exe src/backend/maze.cpp include/backend/maze.h

player.o: main.cpp src/frontend/map.cpp include/frontend/map.h libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h
	$(CC) -o player.exe main.cpp src/frontend/map.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static

clean:
	rm *.exe *.o