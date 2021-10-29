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

main: menu lobby uncheckedMaze mazeChecker room player $(MAIN)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(MAIN) mainMenu.o lobby.o maze.o checkedMaze.o room.o player.o $(LIBS)
	./$(EXECUTABLE)

menu: $(SRC)/$(FE)/mainMenu.cpp $(INCLUDE)/$(FE)/mainMenu.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/$(FE)/mainMenu.cpp

lobby: $(SRC)/$(FE)/lobby.cpp $(INCLUDE)/$(FE)/lobby.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/$(FE)/lobby.cpp

room: $(SRC)/$(FE)/room.cpp $(INCLUDE)/$(FE)/room.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/$(FE)/room.cpp

player: $(SRC)/$(FE)/player.cpp $(INCLUDE)/$(FE)/player.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/$(FE)/player.cpp

maze: uncheckedMaze mazeChecker
	$(CXX) $(CXXFLAGS) -o maze.exe maze.o checkedMaze.o

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