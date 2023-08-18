#include "logger.hpp"

#include <iostream>

class DeadLog {
public:
    template<typename T>
    DeadLog& operator<<(const T&) {return *this;}
};

DeadLog deadLog;
#define _LOG() deadLog
#define ENDL "\n"

#define LOG() globalLog

#define DEFAULT_OUTPUT std::cerr
Logger::Logger() {

    m_outputPtr = &DEFAULT_OUTPUT;
}

Logger::Logger(const std::string &filepath, std::ostream *stdOutput)
    : m_outputPtr(new std::ofstream(filepath, std::ofstream::app)),
      m_stdOutputPtr(stdOutput)
{}

Logger::~Logger() {

    if(m_outputPtr != &DEFAULT_OUTPUT) {

        delete m_outputPtr;
    }
}

Logger::LogTrail::LogTrail(Logger *logger)
    : m_loggerPtr(logger)
    , m_counterPtr(new count_t(1))
{
    _LOG() << "LogTrail(Logger *) counter: " << *m_counterPtr << ENDL;
}

Logger::LogTrail::LogTrail(LogTrail &other)
    : m_loggerPtr(other.m_loggerPtr)
    , m_counterPtr(other.m_counterPtr)
{
    ++*m_counterPtr;
    _LOG() << "LogTrail(LogTrail &) counter: " << *m_counterPtr << ENDL;
}

Logger::LogTrail::LogTrail(LogTrail &&other)
    : m_loggerPtr(other.m_loggerPtr)
    , m_counterPtr(other.m_counterPtr)
{
//    ++*m_counterPtr;
    _LOG() << "LogTrail(LogTrail &&) counter: " << *m_counterPtr << ENDL;
}

Logger::LogTrail::~LogTrail() {

    --*m_counterPtr;
    _LOG() << "~LogTrail() counter: " << *m_counterPtr << ENDL;

    if(!*m_counterPtr) {

        delete m_counterPtr;
        (*m_loggerPtr->m_outputPtr) << "\n";
        if(m_loggerPtr->m_stdOutputPtr)
            (*m_loggerPtr->m_stdOutputPtr) << "\n";
    }
}
