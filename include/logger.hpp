#pragma once

#define MAZE_INITIALIZED "Initializing a new maze."
#define MAZE_UNSOLVABLE  "The maze was unsolvable."
#define MAZE_SOLVING     "Trying to solve the new maze."
#define MAZE_SOLVABLE    "The maze was solvable"

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <map>

class Logger
{
    public:
        inline Logger();

        void initLogFile();

        inline void Info(const std::string& info);
        inline void Warning(const std::string& warning);
        inline void Error(const std::string& error);

    private:
        std::ofstream m_log;
        std::tm* m_time;

    private:
        inline std::string getTime() const;
        inline std::string getLogs(const std::string& type, const std::string& message) const;
};

inline Logger::Logger()
{
    std::time_t t = std::time(0);

    m_time = std::localtime(&t);
};

inline void Logger::initLogFile()
{
    std::string filename = "logs/logs.log";
    m_log.open(filename.c_str(), std::fstream::out | std::fstream::app);

    if(m_log.is_open())
    {
        std::cout<<"Opened the log file"<<std::endl;
    }

    else
    {
        std::cout<<"Couldn't open the log file"<<std::endl;
    }
}

inline std::string Logger::getLogs(const std::string& type, const std::string& message) const
{
    return getTime() + " " + "[" + type + "]" + " " + message + "\n";
}

inline std::string Logger::getTime() const
{
    using namespace std;

    return "[" +
           to_string(m_time->tm_mday) + "-" +
           to_string((m_time->tm_mon) + 1) + "-" +
           to_string((m_time->tm_year) + 1900) + " " +
           to_string(m_time->tm_hour) + ":" +
           to_string(m_time->tm_min) + ":" +
           to_string(m_time->tm_sec)
           + "]";
}

inline void Logger::Info(const std::string& info)
{
    m_log << getLogs("Info", info);
}

inline void Logger::Warning(const std::string& warning)
{
    m_log << getLogs("Warning", warning);
}

inline void Logger::Error(const std::string& error)
{
    m_log << getLogs("Error", error);
}
