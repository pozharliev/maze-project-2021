#pragma once

#define MAZE_INITIALIZED "Initializing a new maze."
#define MAZE_UNSOLVABLE  "The maze was unsolvable."
#define MAZE_SOLVING     "Trying to solve the new maze."

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <map>

class Logger
{
    public:
        Logger();
        void Info(const std::string& info) const;
        void Warning(const std::string& warning) const;
        void Error(const std::string& error) const;

    private:
        std::ofstream m_log;
        std::tm* m_time;

    private:
        void initLogFile();
        std::string getTime() const;
};