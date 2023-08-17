#include <iostream>

using namespace std;

#include "logger.hpp"

class Solution {
public:
    int divide(int dividend, int divisor) {
        return 0;
    }
};

class Prop {
public:
    Prop() {

    }
};

Logger LOG("leetcode.log");

int main()
{
//        Logger log("leetcode.log");
    LOG << " {one}" << " {two}" << " {three}";
    LOG << " {four}" << " {five}" << " {six}";
    const int &rx = 12;
    LOG << "rx: " << &rx;
    return 0;
}
