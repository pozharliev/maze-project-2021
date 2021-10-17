CC = g++ -std=c++17
CFLAGS = -g -w -Wall

<<<<<<< HEAD
maze.o: src/backend/maze.cpp include/backend/maze.h
	$(CC) $(CFLAGS) -o maze.exe src/backend/maze.cpp include/backend/maze.h
=======
all: player.o run

run: player.o
	./player

player.o: main.cpp src/frontend/player.cpp include/frontend/player.h libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h
	$(CC) -o player.exe main.cpp src/frontend/player.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static
>>>>>>> player-movement

clean:
	rm *.exe *.o
