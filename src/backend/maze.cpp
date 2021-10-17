#include "../../include/backend/maze.h"


Maze::Maze()
{
    m_mWidth = MAZE_WIDTH;
    m_mHeight = MAZE_HEIGHT;

    maze = new char[(m_mWidth + 1) * m_mHeight];

    for(int i = 0;i < m_mWidth * m_mHeight; i++)
    {
        maze[i] = '#';
    }

    actions = {ACTIONS::UP, ACTIONS::RIGHT, ACTIONS::DOWN, ACTIONS::LEFT};
}

bool Maze::isInBound(const int& x, const int& y) const
{
    if( x < 0 or x > m_mWidth) return false;
    if( y < 0 or y > m_mHeight) return false;

    return true;
}

int Maze::toIndex(const int& x, const int& y) const
{
    return y * m_mWidth + x;
}

void Maze::Visit(int x, int y)
{
    maze[toIndex(x, y)] = ' ';

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(actions), std::end(actions), rng);

    for(int action: actions)
    {
        int dx = 0;
        int dy = 0;

        switch(action)
        {
            case ACTIONS::UP : dy = -1;
                break;
            case ACTIONS::DOWN : dy = 1;
                break;
            case ACTIONS::RIGHT : dx = 1;
                break;
            case ACTIONS::LEFT : dx = -1;
                break;
        }

        int x2 = x + (dx << 1);
        int y2 = y + (dy<<1);

        if(isInBound(x2,y2))
        {
            if(maze[toIndex(x2,y2)] == '#')
            {
                maze[toIndex(x2 - dx, y2 - dy)] = ' ';

                Visit(x2,y2);
            }
        }
    }
}

void Maze::checkMaze() {
    for (int y = 0; y < m_mHeight + 1; y++)
    {
        for (int x = 0; x < m_mWidth + 1; x++)
        {
            maze[toIndex(x, y)] = maze[toIndex(x, y)];
        }
        for (int i = 0; i < m_mWidth; i++)
        {
            maze[toIndex(i, (m_mHeight))] = '#';
        }
    }
    maze[toIndex(m_mWidth, m_mHeight)] = '#';
}



void Maze::printGrid() const
{
    for(int y = 0; y < m_mHeight + 1; y++)
    {
        for(int x = 0; x < m_mWidth + 1; x++)
        {
            if(x == 1 and y == 1)
            {
                std::cout<<'s';
                continue;
            }

            if((x == (m_mWidth )) and  (y == (m_mHeight - 1)))
            {
                std::cout<<'e';
                break;
            }
            std::cout<<maze[toIndex(x,y)];
        }
        std::cout<<std::endl;
    }
}

void Maze::initMaze()
{
    Visit(1, 1);
    checkMaze();
    printGrid();
}
