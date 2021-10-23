#include <vector>
#include <random>

#include "maze.h"

class Checker
{
    public:
        Checker(int width, int height);
        Maze* maze = NULL;

    public:
        void printMaze();
        void checkMaze();
        int getWidth() const;
        int getHeight() const;


    private:
        int m_mWidth;
        int m_mHeight;

        char* checkedMaze;

        int m_possibleWays ;

        int endpointX = m_mWidth;
        int endpointY = m_mHeight - 1;

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


};