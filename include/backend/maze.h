#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#define MAZE_HEIGHT 10
#define MAZE_WIDTH 10

class Maze
{
    private:
        char* maze;

        enum ACTIONS {
            UP = 1,
            RIGHT = 2,
            DOWN = 3,
            LEFT = 4,
        };

        int m_mHeight;
        int m_mWidth;

        std::vector<int> actions;

    private:
        bool isInBound(const int& x, const int& y) const;
        int toIndex(const int& x, const int& y) const;
        void Visit(int x, int y);
        void printGrid() const;

    public:
        Maze();
        void initMaze();
};