#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

class Logger;

class Logger {
    std::ostream *m_outputPtr;
    class LogTrail {
        typedef int count_t;
    protected:
        Logger* m_loggerPtr;
        count_t* m_counterPtr;
    public:
        LogTrail(Logger*);
        LogTrail(LogTrail&);
        LogTrail(LogTrail&&);
        ~LogTrail();

        template<typename T>
        LogTrail& operator<<(const T& value) {

            (*m_loggerPtr->m_outputPtr) << value;
            return *this;
        }
    };
public:
    Logger();
    Logger(const std::string& filepath);

    ~Logger();

    template<typename T>
    LogTrail operator<<(const T& value) {

        (*m_outputPtr) << value;
        LogTrail logTrail(this);
        return logTrail;
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
