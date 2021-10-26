#pragma once

#include <fstream>
#include <iostream>
#include <ctime>

class Logger
{
    public:
        Logger();
        void Info(const std::string& info) const;
        void Warning(const std::string& warning) const;
        void Error(const std::string& error) const;

    public:
        enum Info{};
        enum Warning{};
        enum Error{};


    private:
        std::ofstream m_log;
        std::tm* m_time;


    private:
        void initLogFile();
        void initTime();
        std::string getTime() const;
};