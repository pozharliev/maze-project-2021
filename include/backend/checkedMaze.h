#pragma once

#include <vector>
#include <random>


#define PATH_SCROLL_CHANCE 20
#define SPEED_SCROLL_CHANCE 40
#define DASH_SCROLL_CHANCE 70

#include "../logger.hpp"
#include "maze.h"

/**
 * @file checkedMaze.h
 *
 * @brief Declaration of the CheckedMaze class.
 */

/**
 * @brief The CheckedMaze is responsible for checking if the generated maze is correct, formatting the maze, and enriching it with runes.
 */

class CheckedMaze
{
public:
    CheckedMaze(int width, int height);

    ~CheckedMaze();

    // Solvable checked maze returned by the program
    char* checkedMaze;

    // Checked maze but with an optimal path in it
    char* mazeWithPath;

    char* reversedMaze;

public:
     /**
     * @brief Recursively checks if the maze is solvable, and if it is not, generates a new one.
     *
     * The function recursively checks a coordinate, that is not a wall,
     * then chooses a random neighbour that has not been visited yet,
     * and repeats the process until it gets to the end of the maze. \n
     * If there isn't a neighbour that is unchecked,
     * backtracks to a coordinate that has any unvisited neighbour(s) left. \n
     * Else if there aren't any unchecked cells it generates a new maze
     * and repeats the process, until there is a solvable maze.
     *
     * @param[in] maze
     *
     * @param[out] checkedMaze,
     *             mazeWithPath,
      *            reversedMaze
     *
     * @return void
     **/
    void checkMaze();

    // Used for debugging purposes
    void printCheckedMazeWithPath();
    // Used for debugging purposes
    void printCheckedMaze();
    // Used for debugging purposes
    void printReversedMaze();

     /**
     * @brief Returns the width of the maze.
     *
     * @return int
     **/
    int getWidth() const;

    /**
    * @brief Returns the height of the maze.
    *
    * @return int
    **/
    int getHeight() const;


private:
    Maze* maze = NULL; //!< @brief Maze class-variable, used for providing a generated maze.

    Logger logger;

    int m_mWidth; //!< @brief Width of the Maze.
    int m_mHeight; //!< @brief Height of the Maze.

    int m_possibleWays; //!< @brief Every cell that is not a wall.

    // Current coordinates
    int m_x; 
    int m_y; 

    // Number of already visited cells
    int m_nVisitedCells;

    std::vector<std::pair<int, int>> m_visitedCells; //!< @brief Stores every already-visited cell.

    std::vector<std::pair<int, int>> m_stack; //!< @brief Vector used like a std::stack variable, used for backtracking.

    std::vector<bool> pathScrollChance;
    std::vector<bool> speedScrollChance;
    std::vector<bool> dashScrollChance;

private:
     /**
     * @brief Checks if a coordinate is in or outside the maze.
     *
     * @param x The x axis
     * @param y The y axis
     *
     * @return bool
     * */
    bool isInBound(const int& x, const int& y) const;

    /**
    * @brief Checks every unvisited, in-bound neighbour and returns a vector of all of the neighbour(s).
    *
    * @param x The x axis of the coordinate.
    * @param y The y axis of the coordinate.
    *
    * @return std::vector<std::pair<int, int>> neighbours
    *
    **/
    std::vector<std::pair<int, int>> getNeighbours(const int& x, const int& y) const;

    /**
    * @brief Checks if a cell has been visited or not.
    *
    * @param x The x axis of the coordinate.
    * @param y The y axis of the coordinate.
    *
    * @return bool
    *
    **/
    bool searchForAlreadyVisitedCells(const int& x, const int& y) const;

    /**
    * @brief Converts 2D to 1D coordinates
    *
    * @note Takes coordinates in (x,y) format and returns (z) format.
    *
    * @param x The x axis of the coordinate.
    * @param y The y axis of the coordinate.
    *
    * @return int
    *
    **/
    int toIndex(const int& x, const int& y) const;

    // Removes the markings in the maze and replaces them with '0'
    void fixMaze();

    // Copies the initial maze with its path into a new public variable
    void initMazeWithPath();

    // Copies the checked maze and reverses it
    void initReversedMaze();

    void fillChanceGenerator(std::vector<bool>& pathVector,
                             std::vector<bool>& speedVector,
                             std::vector<bool>& dashVector);

    void shuffleGenerators(std::vector<bool>& pathVector,
                           std::vector<bool>& speedVector,
                           std::vector<bool>& dashVector);

    void enrichMaze();
};