#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#define LOGV(VALUE) LOGGER_NAME << # VALUE ": " << (VALUE)

class Logger;

class Logger {
    std::ostream *m_outputPtr;
    std::ostream *m_stdOutputPtr;

    class LogTrail {
        typedef int count_t;
    protected:
        Logger* m_loggerPtr;
        count_t* m_counterPtr;
        int m_value;
    public:
        LogTrail() = delete;
        LogTrail(Logger*);
        LogTrail(LogTrail&);
        LogTrail(LogTrail&&);
        ~LogTrail();

        template<typename T>
        LogTrail& operator<<(const T& value) {

            (*m_loggerPtr->m_outputPtr) << value;
            if(m_loggerPtr->m_stdOutputPtr)
                (*m_loggerPtr->m_stdOutputPtr) << value;
            return *this;
        }
    };
public:
    Logger();
    Logger(const std::string& filepath, std::ostream* = nullptr);

    ~Logger();

    template<typename T>
    LogTrail operator<<(const T& value) {

        (*m_outputPtr) << value;
        if(m_stdOutputPtr)
            (*m_stdOutputPtr) << value;
        return LogTrail(this);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& value) {

    os << '[';
    for(size_t i=0; i<value.size(); ++i) {

        auto& v = value[i];
        if(i > 0)
            os << ", ";
        os << v;
    }
    os << ']';

    return os;
}

#endif // LOGGER_HPP
