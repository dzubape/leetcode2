#define LOGGER_NAME LOG
#include "Solution.hpp"

json getTestInput(const std::string& filepath) {
    ifstream ifs(filepath);
    auto data = json::parse(ifs);
    return data;
}

Solution::Solution(
    const std::string &testInputFilepath
)
    : m_testInputFilepath(testInputFilepath)
{}

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

void Solution::setTestInputFile(const std::string &filepath) {
    m_testInputFilepath = filepath;
}

void Solution::setTestInputFor(const std::string &caseName) {
    setTestInputFile(std::string("test-input") + '/' + caseName + ".json");
}

int Solution::runTest(const std::string &taskName, const std::string testInputFilepath) {
    if(testInputFilepath.empty());
    else
        setTestInputFile(testInputFilepath);

    LOG << "test_input: " << m_testInputFilepath;
    m_testInputData = getTestInput(m_testInputFilepath);

    if(false);
#define ADD_SWITCH_CASE(TASK_NAME, TASK_METHOD) else if(taskName == TASK_NAME) return test_ ## TASK_METHOD()
    ADD_SWITCH_CASE("next-permutation", nextPermutation);
    ADD_SWITCH_CASE("division-wo-division", divisionWoDivision);
    ADD_SWITCH_CASE("buy-sell-max-profit", buySellMaxProfit);
    else
        throw new exception;
}