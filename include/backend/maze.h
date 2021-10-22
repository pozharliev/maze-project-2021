#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class Maze
{
private:
    enum ACTIONS {
        UP = 1,
        RIGHT = 2,
        DOWN = 3,
        LEFT = 4,
    };

    int m_mHeight;
    int m_mWidth;

    std::vector<int> actions;

private:
    bool isInBound(const int& x, const int& y) const;
    int toIndex(const int& x, const int& y) const;
    void Visit(int x, int y);
    void printGrid() const;
    void checkMaze();

public:
    Maze(int width, int height);
    void initMaze();

public:
    char* maze;
};