#include "../../include/backend/maze.h"

#include <iostream>

#include <random>
#include <stack>
#include <vector>

 Maze::Maze()
{
    m_MazeWidth = MAZE_WIDTH;
    m_MazeHeight = MAZE_HEIGHT;

    m_maze = new int[m_MazeWidth * m_MazeHeight];

    // Iterates through the array and sets all values to 0
    for (int i = 0; i < m_MazeWidth * m_MazeHeight; i++)
    {
        m_maze[i] = 0;
    }

    // There are 3 starting paths - Left, Right and Down-Right
    m_PathWidth = MAZE_PATH_WIDTH;

    // Choose which point to start from
    int x = START_X;
    int y = START_Y;

    // Push the starting point (0,0)
    m_Stack.push(std::make_pair(x, y));

    // In the coordinate system, you can use
    // y * height + x to determine
    // where the point is
    // based on its x and y coordinates
    m_maze[y * m_MazeWidth + x] = VISITED;

    m_VisitedCells = 1;

}

int Maze::offset(const int &x, const int &y) const
{
    return (m_Stack.top().second + y) * m_MazeWidth + (m_Stack.top().first + x);
}

void Maze::mazeInit()
{
    if (m_VisitedCells < m_MazeWidth * m_MazeHeight)
    {
        // Create a set of unvisited neighbours
        std::vector<int> neighbours;

        // North neighbour
        if (m_Stack.top().second > 0 && (m_maze[offset(0, -1)] & VISITED) == 0)
            neighbours.push_back(0);
        // East neighbour
        if (m_Stack.top().first < m_MazeWidth - 1 && (m_maze[offset(1, 0)] & VISITED) == 0)
            neighbours.push_back(1);
        // South neighbour
        if (m_Stack.top().second < m_MazeHeight - 1 && (m_maze[offset(0, 1)] & VISITED) == 0)
            neighbours.push_back(2);
        // West neighbour
        if (m_Stack.top().first > 0 && (m_maze[offset(-1, 0)] & VISITED) == 0)
            neighbours.push_back(3);

        // Are there any neighbours available?
        if (!neighbours.empty())
        {
            // Choose one available neighbour at random
            int next_dir = neighbours[std::rand() % neighbours.size()];

            // Create a path between the neighbour and the current cell
            switch (next_dir)
            {
                case 0: // North
                    m_maze[offset(0, -1)] |= VISITED | SOUTH;
                    m_maze[offset(0,  0)] |= NORTH;
                    m_Stack.push(std::make_pair((m_Stack.top().first + 0), (m_Stack.top().second - 1)));
                    break;

                case 1: // East
                    m_maze[offset(+1, 0)] |= VISITED | WEST;
                    m_maze[offset( 0, 0)] |= EAST;
                    m_Stack.push(std::make_pair((m_Stack.top().first + 1), (m_Stack.top().second + 0)));
                    break;

                case 2: // South
                    m_maze[offset(0, +1)] |= VISITED | NORTH;
                    m_maze[offset(0,  0)] |= SOUTH;
                    m_Stack.push(std::make_pair((m_Stack.top().first + 0), (m_Stack.top().second + 1)));
                    break;

                case 3: // West
                    m_maze[offset(-1, 0)] |= VISITED | EAST;
                    m_maze[offset( 0, 0)] |= WEST;
                    m_Stack.push(std::make_pair((m_Stack.top().first - 1), (m_Stack.top().second + 0)));
                    break;

            }

            m_VisitedCells++;
        }
        else
        {
            // No available neighbours so backtrack!
            m_Stack.pop();
        }
    }

}

void Maze::printMaze()
{
    for(int i = 0; i < m_MazeWidth * m_MazeHeight; i++)
    {
        std::cout<<m_maze[i];
        if(i % m_MazeHeight == 0)
        {
            std::cout<<std::endl;
        }

    }

}

int main()
{
    Maze maze;
    maze.mazeInit();
    maze.printMaze();
}

