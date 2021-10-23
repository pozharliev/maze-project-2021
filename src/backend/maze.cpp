#include "../../include/backend/maze.h"


Maze::Maze(int width, int height)
{
    m_mWidth = width;
    m_mHeight = height;

    maze = new char[(m_mWidth + 1) * m_mHeight];

    
    // Set the whole maze to just walls
    for (int i = 0; i < m_mWidth * m_mHeight; i++)
    {
        maze[i] = '#';
    }

    m_actions = { ACTIONS::UP, ACTIONS::RIGHT, ACTIONS::DOWN, ACTIONS::LEFT };

    // Variable for every empty space in the maze
    m_possibleWays = 0;
    
    initMaze();
}

// Getters for encapsulation

int Maze::getWidth() const
{
    return m_mWidth;
}

int Maze::getHeight() const
{
    return m_mHeight;
}

int Maze::getPossibleWays() const
{
    return m_possibleWays;
}
// End of getters

// Check if the point is in the maze
bool Maze::isInBound(const int& x, const int& y) const
{
    if (x < 0 or x > m_mWidth) return false;
    if (y < 0 or y > m_mHeight) return false;

    return true;
}

// Convert coordinates from (x, y) to coordinates in a 1D array
int Maze::toIndex(const int& x, const int& y) const
{
    return y * m_mWidth + x;
}

// Recursively check every coordinate in the maze
void Maze::Visit(int x, int y)
{
    maze[toIndex(x, y)] = ' ';

    m_possibleWays++;

    auto rd = std::random_device {};
    auto rng = std::default_random_engine{rd()};
    std::shuffle(std::begin(m_actions), std::end(m_actions), rng);

    for (int action : m_actions)
    {
        int dx = 0;
        int dy = 0;

        switch (action)
        {
            case ACTIONS::UP: dy = -1;
                break;
            case ACTIONS::DOWN: dy = 1;
                break;
            case ACTIONS::RIGHT: dx = 1;
                break;
            case ACTIONS::LEFT: dx = -1;
                break;
        }

        int x2 = x + (dx << 1);
        int y2 = y + (dy << 1);

        if (isInBound(x2, y2))
        {
            if (maze[toIndex(x2, y2)] == '#')
            {
                maze[toIndex(x2 - dx, y2 - dy)] = ' ';
                m_possibleWays++;

                Visit(x2, y2);
            }
        }
    }
}

void Maze::fixMaze() {
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

void Maze::initMaze()
{
    Visit(1, 1);
    fixMaze();
}

