#define LOGGER_NAME LOG
#include "Solution.hpp"

json getTestInput(const std::string& filepath) {

    ifstream ifs(filepath);
    LOG << "is open: " << ifs.is_open();
    auto data = json::parse(ifs);
    // LOGV(data);
    return data;
}

void Solution::printDuration() {

    auto value = m_duration.value;
    std::string units = m_duration.units;

    if(m_duration.value * 1e-3 > 10) {

        if(m_duration.value * 1e-6 > 10) {

            value *= 1e-6;
            units = "sec";
        }
        else {

            value *= 1e-3;
            units = "msec";
        }
    }
    LOG << "duration: " << value << units;
}