#include <vector>
#include <random>

#include "maze.h"

class CheckedMaze
{
    public:
        CheckedMaze(int width, int height);
        char* checkedMaze;
        char* mazeWithPath; // Checked maze but with an optimal path in it

    public:
        void printCheckedMazeWithPath();
        void printCheckedMaze();
        void checkMaze();
        int getWidth() const;
        int getHeight() const;

    private:
        Maze* maze = NULL;

        int m_mWidth;
        int m_mHeight;

        int m_possibleWays ;

        int m_x;
        int m_y;

        int m_nVisitedCells;

        std::vector<std::pair<int, int>> m_visitedCells;

        std::vector<std::pair<int, int>> m_stack;

    private:
        bool isInBound(const int& x, const int& y) const;
        std::vector<std::pair<int, int>> getNeighbours(const int& x, const int& y) const;
        bool searchForAlreadyVisitedCells(const int& x, const int& y) const;
        int toIndex(const int& x, const int& y) const;
        void fixMaze();
        void initMazeWithPath();
};