#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class Maze
{
    public:
        Maze(int width, int height);

        // Initializer for the maze
        void initMaze();

        // Getter for the width
        int getWidth() const;
        // Getter fpr the height
        int getHeight() const;
        // Getter for the possible paths in the maze
        int getPossibleWays() const;

    public:
        char* maze;

    private:
        // Every possible action for movement
        enum ACTIONS {
            UP = 1,
            RIGHT = 2,
            DOWN = 3,
            LEFT = 4,
        };

        std::vector<int> m_actions;

        int m_mHeight;
        int m_mWidth;

        // Every possible path in the maze
        int m_possibleWays;

    private:
        // Recursively checks every coordinate in the maze
        // Marks with
        // ' ' for available path
        // '#' for wall
        void Visit(int x, int y);

        // Checks if the point is in the maze
        bool isInBound(const int& x, const int& y) const;

        // Converts coordinates from (x, y) to coordinates in a 1D array
        int toIndex(const int& x, const int& y) const;

        // Fixes some errors in the maze that may have occurred in the process
        void fixMaze();

};