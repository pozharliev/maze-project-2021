#pragma once

#include <stack>

#define MAZE_WIDTH 50
#define MAZE_HEIGHT 25
#define MAZE_PATH_WIDTH 3
#define START_Y 0
#define START_X 0

class Maze
{
    public:
        Maze();
        void mazeInit();
        void printMaze();

    private:
        int offset(const int& x, const int& y) const;

        int m_MazeWidth;
        int m_MazeHeight;
        int* m_maze;

        enum
        {
            NORTH = 0x01,
            EAST = 0x02,
            SOUTH = 0x04,
            WEST = 0x08,
            VISITED = 0x10,
        };

        std::stack<std::pair<int, int>> m_Stack;

        int m_VisitedCells;
        int m_PathWidth;

};