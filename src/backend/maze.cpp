#include "../../include/backend/maze.h"

/**
 * @file maze.cpp
 *
 * @brief Definition of the Maze class.
 */

Maze::Maze(int width, int height)
{
    m_mWidth = width;
    m_mHeight = height;

    maze = new char[m_mWidth  * m_mHeight];

    // Set the whole maze to just walls
    for (int i = 0; i < m_mWidth * m_mHeight; i++)
    {
        maze[i] = '#';
    }

    m_actions = { ACTIONS::UP, ACTIONS::RIGHT, ACTIONS::DOWN, ACTIONS::LEFT };

    m_possibleWays = 0;
    
    initMaze();
}

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

bool Maze::isInBound(const int& x, const int& y) const
{
    if (x < 0 or x > m_mWidth) return false;
    if (y < 0 or y > m_mHeight) return false;

    return true;
}

int Maze::toIndex(const int& x, const int& y) const
{
    return y * m_mWidth + x;
}

void Maze::Visit(int x, int y)
{
    // Mark the cell as a path
    maze[toIndex(x, y)] = ' ';

    m_possibleWays++;

    // Generate a random number
    auto rd = std::random_device {};

    // Generate a seed for the random number
    auto rng = std::default_random_engine{rd()};

    // Shuffle the actions vector based on the random numbers
    std::shuffle(m_actions.begin(), m_actions.end(), rng);


    // Iterate over every action
    for (int action : m_actions)
    {
        // Variables for offset
        int dx = 0;
        int dy = 0;

        // Generate offset based on the path
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

        // Generate the next visited cells based on the offset
        int x2 = x + (dx << 1);
        int y2 = y + (dy << 1);

        // If the next cells are in the maze
        if (isInBound(x2, y2))
        {
            // Recursively check them and mark them
            if (maze[toIndex(x2, y2)] == '#')
            {
                maze[toIndex(x2 - dx, y2 - dy)] = ' ';
                m_possibleWays++;

                Visit(x2, y2);
            }
        }
    }
}

void Maze::initMaze()
{
    Visit(1, 1);
}

Maze::~Maze()
{
    delete[] maze;
}

