#pragma once

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

    public:
        std::map<std::string, std::string> InfoLog
        {
            {"MAZE_INITIALIZED", "Initializing a new maze."},
            {"MAZE_UNSOLVABLE",  "The maze was unsolvable."},
            {"MAZE_SOLVING",     "Trying to solve the new maze."},
        };
        std::map<std::string, std::string> WarningLog;
        std::map<std::string, std::string> ErrorLog;


    private:
        std::ofstream m_log;
        std::tm* m_time;


    private:
        void initLogFile();
        std::string getTime() const;
};