#include "logger.hpp"

#include <iostream>



Logger::Logger() {

    m_outputPtr = &std::cout;
}

Logger::Logger(const std::string &filepath) {

    m_outputPtr = new std::ofstream(filepath, std::ofstream::app);
}

Logger::~Logger() {

    if(m_outputPtr != &std::cout) {


        delete m_outputPtr;
    }
}

Logger::LogTrail::LogTrail(Logger *logger)
    : m_loggerPtr(logger)
    , m_counterPtr(new count_t(1))
{
//    std::cout << "LogTrail(Logger *) counter: " << *m_counterPtr << std::endl;
}

Logger::LogTrail::LogTrail(LogTrail &other)
    : m_loggerPtr(other.m_loggerPtr)
    , m_counterPtr(other.m_counterPtr)
{
    ++*m_counterPtr;
//    std::cout << "LogTrail(LogTrail &) counter: " << *m_counterPtr << std::endl;
}


Logger::LogTrail::LogTrail(LogTrail &&other)
    : m_loggerPtr(other.m_loggerPtr)
    , m_counterPtr(other.m_counterPtr)
{
//    ++*m_counterPtr;
//    std::cout << "LogTrail(LogTrail &) counter: " << *m_counterPtr << std::endl;
}

Logger::LogTrail::~LogTrail() {

    --*m_counterPtr;
//    std::cout << "~LogTrail() counter: " << *m_counterPtr << std::endl;

    if(!*m_counterPtr) {

        delete m_counterPtr;
        (*m_loggerPtr->m_outputPtr) << "\n";
    }

}
