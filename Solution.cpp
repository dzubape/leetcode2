#define LOGGER_NAME LOG
#include "Solution.hpp"

json getTestInput(const std::string& filepath) {

    ifstream ifs(filepath);
    auto data = json::parse(ifs);
    LOGV(data);
    return data;
}

void Solution::printDuration() {
    LOG << "duration: " << m_duration.value << m_duration.units;
}