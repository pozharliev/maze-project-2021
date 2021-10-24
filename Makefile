CC = g++ -std=c++17
CXXFLAGS = -g -w -Wall
LIBS = -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static
LIBPATH = libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h

all: main run

run: main
	./main

main: game.o main.cpp
	$(CC) $(CXXFLAGS) -o main.exe main.cpp game.o $(LIBS)

game.o: src/frontend/game.cpp include/frontend/game.h $(LIBPATH)
	$(CC) $(CXXFLAGS) -c src/frontend/game.cpp $(LIBS)

maze: uncheckedMaze.o mazeChecker.o
	$(CC) $(CXXFLAGS) -o maze.exe maze.o checkedMaze.o

mazeChecker.o: src/backend/checkedMaze.cpp
	$(CC) $(CXXFLAGS) -c src/backend/checkedMaze.cpp

uncheckedMaze.o: src/backend/maze.cpp include/backend/maze.h
	$(CC) $(CXXFLAGS) -c src/backend/maze.cpp

clean:
	rm *.exe *.o

# map.o: src/frontend/map.cpp include/frontend/game.h libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h
# 	$(CC) $(CXXFLAGS) -c src/frontend/map.cpp $(LIBS)

# gameManager.o: map.o src/backend/gameManager.cpp include/backend/gameManager.h libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h
# 	$(CC) $(CXXFLAGS) -c src/backend/gameManager.cpp map.o $(LIBS)

