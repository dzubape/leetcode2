#define LOGGER_NAME LOG
#include "Solution.hpp"

#include <sys/stat.h>
#include <unistd.h>
bool fileExists(const std::string& filepath) {
    char cwd[256];
    getcwd(cwd, 256);
    LOGV(cwd);

    struct stat st;
    if(stat(filepath.data(), &st)) {
        LOG << "stat for " << filepath << " failed";
    }
    else {
        LOGV(st.st_size);
    }
    return true;
}

json getTestInput(const std::string& filepath) {
    // fileExists(filepath);
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
    ADD_SWITCH_CASE("longest-valid-parentheses", longestValidParentheses);
    ADD_SWITCH_CASE("find-first-and-last-position-of-element-in-sorted-array", findFirstAndLastPositionOfElementInSortedArray);
    //<< ADD_SWITCH_CASE
    else
        throw new exception;
}