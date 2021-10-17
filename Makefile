CC = g++ -std=c++17
CFLAGS = -g -w -Wall

all: player.o run

run: player.o
	./player

player.o: main.cpp src/frontend/player.cpp include/frontend/player.h libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h
	$(CC) -o player.exe main.cpp src/frontend/player.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static

clean:
	rm *.exe *.o