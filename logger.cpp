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
