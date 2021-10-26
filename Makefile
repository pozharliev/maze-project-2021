CXX = g++ -std=c++17
CXXFLAGS = -g -w -Wall

LIBS = -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static
LIBPATH = libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h

EXECUTABLE = main.exe
MAIN = main.cpp

SRC = src
INCLUDE = include
FE = frontend
BE = backend

all: main

main: lobby player $(MAIN)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(MAIN) lobby.o player.o $(LIBS)
	./$(EXECUTABLE)

lobby: $(SRC)/$(FE)/Lobby.cpp $(INCLUDE)/$(FE)/Lobby.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/$(FE)/Lobby.cpp

player: $(SRC)/$(FE)/Player.cpp $(INCLUDE)/$(FE)/Player.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/$(FE)/Player.cpp

maze: uncheckedMaze mazeChecker
	$(CXX) $(CXXFLAGS) -o maze.exe maze.o checkedMaze.o
	./maze

mazeChecker: $(SRC)/$(BE)/checkedMaze.cpp $(INCLUDE)/$(BE)/checkedMaze.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/$(BE)/checkedMaze.cpp

uncheckedMaze: $(SRC)/$(BE)/maze.cpp $(INCLUDE)/$(BE)/maze.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/$(BE)/maze.cpp

logger: src/logger/logger.cpp include/logger/logger.h
	$(CXX) $(CXXFLAGS) -o logger.exe src/logger/logger.cpp

clean:
	rm *.exe *.o

# map.o: src/frontend/map.cpp include/frontend/game.h libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h
# 	$(CXX) $(CXXFLAGS) -c src/frontend/map.cpp $(LIBS)

# gameManager.o: map.o src/backend/gameManager.cpp include/backend/gameManager.h libs/olcPixelGameEngine.h libs/olcPGEX_TransformedView.h
# 	$(CXX) $(CXXFLAGS) -c src/backend/gameManager.cpp map.o $(LIBS)

# gameManager: libs lobby player src/frontend/gameManager.cpp include/frontend/gameManager.h
# 	$(CXX) $(CXXFLAGS) -c src/frontend/gameManager.cpp

# game.o: src/frontend/game.cpp include/frontend/game.h $(LIBPATH)
# 	$(CXX) $(CXXFLAGS) -c src/frontend/game.cpp $(LIBS)
