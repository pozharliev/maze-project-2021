#include "../../include/logger/logger.h"

Logger::Logger()
{
    initLogFile();

    initTime();
};

void Logger::initLogFile()
{
    m_log.open("logs/logs.log", std::ios::out);

    if(m_log.is_open())
    {
        std::cout<<"Opened the log file"<<std::endl;
    }

    else
    {
        std::cout<<"Couldn't open the log file"<<std::endl;
    }
}

void Logger::initTime()
{
    std::time_t t = std::time(0);

    m_time = std::localtime(&t);
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

void Logger::Info(const std::string& info) const
{
    std::cout<<"Info";
}

void Logger::Warning(const std::string& warning) const
{
    std::cout<<"Warning";
}

void Logger::Error(const std::string& error) const
{
    std::cout<<"Error";
}
