#pragma once
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

    std::vector<int> m_actions;

    int m_possibleWays;

private:
    bool isInBound(const int& x, const int& y) const;
    int toIndex(const int& x, const int& y) const;
    void Visit(int x, int y);
    void fixMaze();

public:
    Maze(int width, int height);
    void initMaze();
    int getWidth() const;
    int getHeight() const;
    int getPossibleWays() const;

public:
    char* maze;

};