//#include "../../include/backend/maze.h"
#include <vector>
#include <algorithm>
#include <random>

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



    public:
        Maze(int width, int height)
        {
           m_mWidth = width;
           m_mHeight = height;

           maze = new char[m_mWidth * m_mHeight];

           for(int i = 0; i < m_mWidth * m_mHeightl; i++)
           {
               maze[i] = '#';
           }

           m_x = 0;
           m_y = 0;
        }

        std::vector<std::pair<int, int>> getNeighbours(const int& x, const int& y) const
        {
            std::vector<std::pair<int, int>> availableNeighbours;
            
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
            int nVisitedCells = 1;

            visitedCells.push_back(std::make_pair(m_x, m_y));

            maze[toIndex(m_x, m_y)] = ' ';

            while(visitedCells < m_mWidth * m_mHeight)
            {
                auto rd = std::random_device {};
                auto rng = std::default_random_engine { rd ()};
                std::shuffle(std::begin(actions), std::end(actions), rng);

                int dx = 0;
                int dy = 0;

                int nextAction = actions[nextActionN];

                if(nextAction == SIDES::RIGHT and isInBound())


            }
        }

};