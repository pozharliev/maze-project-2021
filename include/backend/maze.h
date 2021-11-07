#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

/**
 * @file maze.h
 *
 * @brief Declaration of the Maze class.
 */

/**
 * @brief The Maze class is responsible for generating a maze.
 */
class Maze
{
    public:
        Maze(int width, int height);

        ~Maze();

        /**
        * @brief Initializer for the maze.
        *
        * @note Acts as a wrapper for the Maze::Visit function.
        *
        * @return void
        * */
        void initMaze();

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

        /**
        * @brief Returns all cells that are not walls.
        *
        * @return int
        **/
        int getPossibleWays() const;

    public:
        char* maze; //!< @brief The generated maze.
                    //!< @note Dynamic array.
                    //!< @note Is walls-only by default.

    private:
        /**
        * @brief Contains every possible action the algorithm take.
        * */
        enum ACTIONS {
            UP = 1, //!< @brief Add 1 to the y axis
            RIGHT = 2, //!< @brief Add 1 to the x axis
            DOWN = 3, //!< @brief Subtract 1 from the y axis
            LEFT = 4, //!< @brief Subtract 1 from the x axis
        };

        std::vector<int> m_actions; //!< @brief A std::vector used for getting random actions.
                                    //!< @note Acts as a wrapper for the #ACTIONS enum.

        int m_mWidth;  //!< @brief Width of the Maze.
        int m_mHeight; //!< @brief Height of the Maze.

        int m_possibleWays; //!< @brief Every cell that is not a wall.

    private:
        /**
        * @brief Recursively generates a maze, based on random decisions.
        *
        * The function starts on the (1,1) coordinate. \n
        * Converts the current coordinate to a path from a wall,
        * then picks a random neighbour from the unchecked-already neighbours,
        * making the offset from the current cell 2 (two) cells ahead. \n
        * If the generated offset is not outside of the maze,
        * it recursively visits the offset coordinates and repeats. \n
        * Else it chooses a different offset and repeats.
        *
        * @param x The x axis of the starting coordinate.
        * @param y The y axis of the starting coordinate.
        *
        * @param[in] maze
        *
        * @param[out] maze,
        *             m_possibleWays
        *
        * @return void
        **/
        void Visit(int x, int y);

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
        * @brief Converts 2D to 1D coordinates
        *
        * @note Takes coordinates in (int, int) format and returns (int) format.
        *
        * @param x The x axis of the coordinate.
        * @param y The y axis of the coordinate.
        *
        * @return int
        *
        **/
        int toIndex(const int& x, const int& y) const;

};