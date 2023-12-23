#include <iostream>

using namespace std;

#include "Solution.hpp"

#include "logger.hpp"
#define LOGGER_NAME LOG
Logger LOG("leetcode.log", &std::cerr);

void printHelp() {
    LOG << "./leetcode2 'task-name' ['custom-test-input.json']";
}

int main(int argc, char *argv[])
{
    if(argc < 2) {
        LOG << "Error: no argument passed";
        printHelp();
        exit(1);
    }
    auto taskName = argv[1];
    
    LOG << "Task name: " << taskName;
    ~LOG;
    Solution solution;
    solution.setTestInputFor(taskName);
    return solution.runTest(taskName);
}
