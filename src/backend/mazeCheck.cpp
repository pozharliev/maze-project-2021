#include "../../include/backend/maze.h"
#include <vector>
#include <random>

class Checker
{
public:
    Checker()
    {
        maze = new Maze(10, 10);
        m_mWidth = maze->getWidth();
        m_mHeight = maze->getHeight();
        possibleWays = maze->getPossibleWays();
        std::cout << std::endl;
        std::cout << m_mHeight << " " << m_mHeight;
        std::cout << std::endl;
    }

private:
    Maze* maze = NULL;

    int m_mWidth;
    int m_mHeight;

    int possibleWays ;

    int endpointX = m_mWidth;
    int endpointY = m_mHeight - 1;


    int m_x;
    int m_y;

    int m_nVisitedCells;

    std::vector<std::pair<int, int>> m_visitedCells;

    std::vector<std::pair<int, int>> m_stack;

private:
    bool isInBound(const int& x, const int& y) const
    {
        if (!(x > 0 and x < m_mWidth))  return false;
        if (!(y > 0 and y < m_mHeight)) return false;

        return true;
    }

    std::vector<std::pair<int, int>> getNeighbours(const int& x, const int& y) const
    {
        std::vector<std::pair<int, int>> availableNeighbours;

        if (isInBound(x + 1, y) and !searchForAlreadyVisitedCells(x + 1, y) and maze->maze[toIndex(x + 1, y)] == ' ')
        {
            availableNeighbours.push_back(std::make_pair(x + 1, y));
        }
        if (isInBound(x - 1, y) and !searchForAlreadyVisitedCells(x - 1, y) and maze->maze[toIndex(x - 1, y)] == ' ')
        {
            availableNeighbours.push_back(std::make_pair(x - 1, y));
        }

        if (isInBound(x, y + 1) and !searchForAlreadyVisitedCells(x, y + 1) and maze->maze[toIndex(x, y + 1)] == ' ')
        {
            availableNeighbours.push_back(std::make_pair(x, y + 1));
        }

        if (isInBound(x, y - 1) and !searchForAlreadyVisitedCells(x, y - 1) and maze->maze[toIndex(x, y - 1)] == ' ')
        {
            availableNeighbours.push_back(std::make_pair(x, y - 1));
        }

        return availableNeighbours;
    }

    bool searchForAlreadyVisitedCells(const int& x, const int& y) const
    {
        for (auto pair : m_visitedCells)
        {
            if (pair.first == x and pair.second == y) return true;
        }
        return false;
    }

    int toIndex(const int& x, const int& y) const
    {
        return y * m_mWidth + x;
    }

public:
    void printMaze()
    {
        for (int y = 0; y <= m_mHeight; y++)
        {
            for (int x = 0; x <= m_mWidth; x++)
            {
                std::cout << maze->maze[toIndex(x, y)];
            }
            std::cout << std::endl;
        }
        std::cout<<std::endl;
    }


    void checkMaze()
    {

        m_x = 1;
        m_y = 1;

        m_nVisitedCells = 1;

        m_visitedCells.push_back(std::make_pair(m_x, m_y));
        m_stack.push_back(std::make_pair(m_x, m_y));

        maze->maze[toIndex(m_x, m_y)] = '0';

        while (true)
        {
            printMaze();

            std::vector<std::pair<int, int >> neighbours = getNeighbours(m_stack[m_stack.size() - 1].first, m_stack[m_stack.size() - 1].second);

            if (!neighbours.empty())
            {
                std::random_device rd; // obtain a random number from hardware
                std::mt19937 gen(rd()); // seed the generator
                std::uniform_int_distribution<> distr(0, neighbours.size() - 1); // define the range

                auto nextCell = distr(gen);
                m_x = neighbours[nextCell].first;
                m_y = neighbours[nextCell].second;

                maze->maze[toIndex(m_x, m_y)] = '0';

                m_visitedCells.push_back(std::make_pair(m_x, m_y));
                m_stack.push_back(std::make_pair(m_x, m_y));
                m_nVisitedCells++;
                std::cout << std::endl << m_x << " " << m_y << " " << m_mWidth - 1<< " " << m_mHeight - 1 << std::endl;

                if((m_x == m_mWidth - 1 and m_y == m_mHeight - 1))
                {
                    break;
                }
                if(m_nVisitedCells == possibleWays)
                {
                    std::cout<<std::endl<<"doesnt work kekw";
                    break;
                }
            }
            else
            {
                maze->maze[toIndex(m_x, m_y)] = '0';
                m_stack.pop_back();
            }

        }
    }
};

int main()
{
    Checker checker;

    checker.checkMaze();
    checker.printMaze();



}