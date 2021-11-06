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
        Logger();

        void initLogFile();

        void Info(const std::string& info);
        void Warning(const std::string& warning);
        void Error(const std::string& error);

    private:
        std::ofstream m_log;
        std::tm* m_time;

    private:
        std::string getTime() const;
        std::string getLogs(const std::string& type, const std::string& message) const;
};

Logger::Logger()
{
    std::time_t t = std::time(0);

    m_time = std::localtime(&t);
};

void Logger::initLogFile()
{
    m_log.open("logs/logs.log", std::ios::out | std::ios::trunc);

    if(m_log.is_open())
    {
        std::cout<<"Opened the log file"<<std::endl;
    }

    else
    {
        std::cout<<"Couldn't open the log file"<<std::endl;
    }
}

std::string Logger::getLogs(const std::string& type, const std::string& message) const
{
    return getTime() + " " + "[" + type + "]" + " " + message + "\n";
}

std::string Logger::getTime() const
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

void Logger::Info(const std::string& info)
{
    std::cout << "vlizam";
    m_log << getLogs("Info", info);
    std::cout<< "izlizam";
}

void Logger::Warning(const std::string& warning)
{
    m_log << getLogs("Warning", warning);
}

void Logger::Error(const std::string& error)
{
    m_log << getLogs("Error", error);
}
