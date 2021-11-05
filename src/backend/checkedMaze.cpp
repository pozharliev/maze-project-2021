#include "../../include/backend/maze.h"
#include "../../include/backend/checkedMaze.h"

CheckedMaze::CheckedMaze(int width, int height)
{
    maze = new Maze(width, height);

    m_mWidth = maze->getWidth();
    m_mHeight = maze->getHeight();
    m_possibleWays = maze->getPossibleWays();

    checkedMaze = maze->maze;

    mazeWithPath = new char[m_mWidth * m_mHeight];

    reversedMaze = new char[m_mWidth * m_mHeight];

    m_x = 1;
    m_y = 1;

    m_nVisitedCells = 1;
}

void CheckedMaze::fillChanceGenerator(std::vector<bool>& pathVector,
                                      std::vector<bool>& speedVector,
                                      std::vector<bool>& dashVector
)
{
    for(int i = 0; i < PATH_SCROLL_CHANCE / 10; i++)
    {
        pathVector.push_back(true);
    }

    for(int i = PATH_SCROLL_CHANCE / 10; i < 10; i++)
    {
        pathVector.push_back(false);
    }

    for(int i = 0; i < SPEED_SCROLL_CHANCE / 10; i++)
    {
        speedVector.push_back(true);
    }

    for(int i = SPEED_SCROLL_CHANCE / 10; i < 10; i++)
    {
        speedVector.push_back(false);
    }

    for(int i = 0; i < DASH_SCROLL_CHANCE / 10; i++)
    {
        dashVector.push_back(true);
    }

    for(int i = DASH_SCROLL_CHANCE / 10; i < 10; i++)
    {
        dashVector.push_back(false);
    }

}

void CheckedMaze::shuffleGenerators(std::vector<bool>& pathVector,
                                    std::vector<bool>& speedVector,
                                    std::vector<bool>& dashVector
)
{
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(pathVector.begin(), pathVector.end(), rng);
    std::shuffle(speedVector.begin(), speedVector.end(), rng);
    std::shuffle(dashVector.begin(), dashVector.end(), rng);
}

void CheckedMaze::enrichMaze(char *maze, int width, int height) {
    fillChanceGenerator(pathScrollChance, speedScrollChance, dashScrollChance);
    shuffleGenerators(pathScrollChance, speedScrollChance, dashScrollChance);

    std::random_device rd;

    // Generate a seed for the rng
    std::mt19937 gen(rd());

    // Define a range for the random number
    std::uniform_int_distribution<> mazeY(0, height - 1);
    std::uniform_int_distribution<> mazeX(0, width - 1);

    auto cellX = mazeX(gen);
    auto cellY = mazeY(gen);

    if(pathScrollChance[0])
    {
        if (maze[cellX * width + cellY] != '#' and
            maze[cellX * width + cellY] != 'S' and
            maze[cellX * width + cellY] != 'D')
        {
            maze[cellX * width + cellY] = 'P';
        }
        else
        {
            enrichMaze(maze, width, height);
        }
    }

    cellX = mazeX(gen);
    cellY = mazeY(gen);

    if(speedScrollChance[0])
    {
        if (maze[cellX * width + cellY] != '#' and
            maze[cellX * width + cellY] != 'P' and
            maze[cellX * width + cellY] != 'D')
        {
            maze[cellX * width + cellY] = 'S';
        }
        else
        {
            enrichMaze(maze, width, height);
        }
    }

    cellX = mazeX(gen);
    cellY = mazeY(gen);

    if(dashScrollChance[0])
    {
        if (maze[cellX * width + cellY] != '#' and
            maze[cellX * width + cellY] != 'P' and
            maze[cellX * width + cellY] != 'S')
        {
            maze[cellX * width + cellY] = 'D';
        }
        else
        {
            enrichMaze(maze, width, height);
        }
    }
}


bool CheckedMaze::isInBound(const int& x, const int& y) const
{
    if (!(x > 0 and x < m_mWidth))  return false;
    if (!(y > 0 and y < m_mHeight)) return false;

    return true;
}

std::vector<std::pair<int, int>> CheckedMaze::getNeighbours(const int& x, const int& y) const
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

bool CheckedMaze::searchForAlreadyVisitedCells(const int& x, const int& y) const
{
    for (auto pair : m_visitedCells)
    {
        if (pair.first == x and pair.second == y) return true;
    }
    return false;
}

int CheckedMaze::toIndex(const int& x, const int& y) const
{
    return y * m_mWidth + x;
}

void CheckedMaze::fixMaze()
{
    for (int y = 0; y < m_mHeight; y++)
    {
        for (int x = 0; x < m_mWidth; x++)
        {
            if(checkedMaze[toIndex(x, y)] == '0')
            {
                checkedMaze[toIndex(x, y)] = ' ';
            }
        }
    }
}

void CheckedMaze::initMazeWithPath()
{
    for (int y = 0; y < m_mHeight; y++)
    {
        for (int x = 0; x < m_mWidth; x++)
        {
            mazeWithPath[toIndex(x, y)] = maze->maze[toIndex(x, y)];
        }
    }
}

void CheckedMaze::initReversedMaze()
{
    for (int y = 0; y < m_mHeight; y++)
    {
        for (int x = 0; x < m_mWidth; x++)
        {
            reversedMaze[toIndex(x, y)] = maze->maze[toIndex(x, y)];
        }
    }

    std::reverse(reversedMaze, reversedMaze + ((getHeight()) * ((getWidth())) - getHeight()));

}

void CheckedMaze::checkMaze()
{
    m_visitedCells.push_back(std::make_pair(m_x, m_y));
    m_stack.push_back(std::make_pair(m_x, m_y));

    // Mark the path
    maze->maze[toIndex(m_x, m_y)] = '0';

    while (true)
    {
        // Get all available unchecked neighbours for the current cell
        std::vector<std::pair<int, int >> neighbours = getNeighbours(m_stack[m_stack.size() - 1].first, m_stack[m_stack.size() - 1].second);

        // If there are any unchecked neighbours
        if (!neighbours.empty())
        {
            // Random number generator
            std::random_device rd;

            // Generate a seed for the rng
            std::mt19937 gen(rd());

            // Define a range for the random number
            std::uniform_int_distribution<> distr(0, neighbours.size() - 1);

            // Get a random cell from the available neighbours
            auto nextCell = distr(gen);

            // Set the current coordinates to the random cell's
            m_x = neighbours[nextCell].first;
            m_y = neighbours[nextCell].second;

            // Mark the cell as a part of the solution
            maze->maze[toIndex(m_x, m_y)] = '0';

            m_visitedCells.push_back(std::make_pair(m_x, m_y));
            m_stack.push_back(std::make_pair(m_x, m_y));

            m_nVisitedCells++;

            // The path arrives at the end of the maze
            if((m_x == m_mWidth - 1 and m_y == m_mHeight - 1))
            {
                initMazeWithPath();
                fixMaze();
                initReversedMaze();
                enrichMaze(maze->maze, m_mWidth, m_mHeight);
                printCheckedMaze();
                printCheckedMazeWithPath();
                printReversedMaze();
                break;
            }

            // There is no solution to the maze
            if(m_nVisitedCells == m_possibleWays)
            {
                // Generate another maze and repeat the process until there is a solvable maze
                CheckedMaze anotherMaze(m_mWidth, m_mHeight);
                anotherMaze.checkMaze();
                break;
            }
        }

        else
        {
            // Unmark the cell
            maze->maze[toIndex(m_stack[m_stack.size() - 1].first, m_stack[m_stack.size() - 1].second)] = ' ';

            // Backtrack for a previous cell that has unchecked neighbours
            m_stack.pop_back();
        }
    }
}

int CheckedMaze::getWidth() const
{
    return m_mWidth;
}

int CheckedMaze::getHeight() const
{
    return m_mHeight;
}


// Used for debugging
void CheckedMaze::printCheckedMaze()
{
    for (int y = 0; y < m_mHeight; y++)
    {
        for (int x = 0; x < m_mWidth; x++)
        {
            std::cout << maze->maze[toIndex(x, y)];
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

void CheckedMaze::printCheckedMazeWithPath()
{
    for (int y = 0; y < m_mHeight; y++)
    {
        for (int x = 0; x < m_mWidth; x++)
        {
            std::cout << mazeWithPath[toIndex(x, y)];
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

void CheckedMaze::printReversedMaze()
{
    for (int y = 0; y <m_mHeight; y++)
    {
        for (int x = 0; x < m_mWidth; x++)
        {
            std::cout << reversedMaze[toIndex(x, y)];
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

CheckedMaze::~CheckedMaze()
{
    delete maze;
    delete[] mazeWithPath;
    delete[] reversedMaze;
}
//int main()
//{
//    CheckedMaze m(20, 20);
//    m.checkMaze();
//}