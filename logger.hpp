#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

class LogTrail;

class Logger {
protected:
public:
    std::ostream *m_outputPtr;

public:
    Logger();
    Logger(const std::string& filepath);

    ~Logger();

    template<typename T>
    Logger& operator<<(const T& value) {

        (*m_outputPtr) << value;
        return *this;
    }
};

#if 0
template<typename T>
Logger& operator<<(Logger& log, const T& value) {

    (*log.m_outputPtr) << value;
    return log;
}
#endif

#endif // LOGGER_HPP
