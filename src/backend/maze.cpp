//#include "../../include/backend/maze.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
class Maze{
    private:
        char* maze;

        int m_mWidth;
        int m_mHeight;

        enum SIDES {
            RIGHT = 1,
            DOWN = 2,
            LEFT = 3,
            UP = 4,
        };

        int m_x;
        int m_y;

        std::vector<std::pair<int, int>> visitedCells;

        std::vector<int> actions = {SIDES::RIGHT, SIDES::DOWN, SIDES::LEFT, SIDES::UP};

        int nextActionN = 0;

        std::vector<std::pair<int, int>> neighbours;

        int nVisitedCells = 0;

        std::vector<std::pair<int ,int>> stack;



    public:
        Maze(int width, int height)
        {
           m_mWidth = width;
           m_mHeight = height;

           maze = new char[m_mWidth * m_mHeight];

           for(int i = 0; i < m_mWidth * m_mHeight; i++)
           {
               maze[i] = '#';
           }

           m_x = 1;
           m_y = 1;
        }

        bool searchForAlreadyVisitedCells(const int& x, const int& y) const
        {
            for (auto pair: visitedCells)
            {
                if (pair.first == x and pair.second == y) return true;
            }
            return false;
        }

        // Wild India Starts Here
        std::vector<std::pair<int, int>> getNeighbours(const int& x, const int& y) const
        {
            std::vector<std::pair<int, int>> availableNeighbours;

            if(isInBound(x + 1, y) and !searchForAlreadyVisitedCells(x + 1, y))
            {
                availableNeighbours.push_back(std::make_pair(x + 1, y));
            }

            if(isInBound(x - 1, y) and !searchForAlreadyVisitedCells(x - 1, y))
            {
                availableNeighbours.push_back(std::make_pair(x - 1, y));
            }

            if(isInBound(x, y + 1) and !searchForAlreadyVisitedCells(x, y + 1))
            {
                availableNeighbours.push_back(std::make_pair(x, y + 1));
            }

            if(isInBound(x, y - 1) and !searchForAlreadyVisitedCells(x ,y - 1))
            {
                availableNeighbours.push_back(std::make_pair(x, y - 1));
            }

            return availableNeighbours;
            
        }


        int toIndex(const int& x,const int& y) const
        {
            return y * m_mWidth + x;
        }

        bool isInBound(const int& x,const int& y) const
        {
            if (!( x > 0 and x < m_mWidth))  return false;
            if (!( y > 0 and y < m_mHeight)) return false;

            return true;
        }

        void initMaze()
        {
            nVisitedCells = 1;

            visitedCells.push_back(std::make_pair(m_x, m_y));
            stack.push_back(std::make_pair(m_x, m_y));

            maze[toIndex(m_x, m_y)] = ' ';

            while(nVisitedCells <= m_mWidth * m_mHeight or ((m_x == m_mWidth) and (m_y == m_mHeight)))
            {
                for(int y = 0; y < m_mHeight; y++)
                {
                    for(int x = 0; x < m_mWidth; x++)
                    {
                        std::cout<<maze[toIndex(x, y)];
                    }
                    std::cout<<std::endl;
                }
                std::cout<<std::endl;

                std::vector<std::pair<int,int>> neighbours = getNeighbours(stack[stack.size() - 1].first, stack[stack.size() - 1].second);

                if(!(neighbours.empty()))
                {
                    std::random_device rd; // obtain a random number from hardware
                    std::mt19937 gen(rd()); // seed the generator
                    std::uniform_int_distribution<> distr(0, neighbours.size() - 1); // define the range

                    auto nextCell = distr(gen);
                    m_x = neighbours[nextCell].first;
                    m_y = neighbours[nextCell].second;

                    maze[toIndex(m_x, m_y)] = ' ';

                    //TODO Make the algorithm go in a straight line until it cannot or until a certain range is 

                    visitedCells.push_back(std::make_pair(m_x, m_y));
                    stack.push_back(std::make_pair(m_x, m_y));

                    nVisitedCells++;
                }
                else
                {
                    stack.pop_back();
                }
            }
        }
    void printMaze()
    {
        for(int y = 0; y < m_mHeight; y++)
        {
            for(int x = 0; x < m_mWidth; x++)
            {
                std::cout<<maze[toIndex(x, y)];
            }
            std::cout<<std::endl;
        }


    }
};

int main()
{
    Maze maze(10, 10);
    maze.initMaze();
    maze.printMaze();
}

