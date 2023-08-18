#include <iostream>

using namespace std;

#include "logger.hpp"
Logger LOG("leetcode.log", &std::cerr);

class Solution {
public:
    int divide(int dividend, int divisor) {
        return 0;
    }
};

class Prop {
    int m_v;
public:
    Prop(int v=777) : m_v(v) {LOG << '[' << this << "] " << "Prop(" << m_v << ")";}
    ~Prop() {LOG << '[' << this << "] " << "~Prop(" << m_v << ")";}
};

class Base {
public:
    Prop m_prop2;
    Prop m_prop1;
    Base() : m_prop1(1), m_prop2(2) {LOG << '[' << this << "] " << "Base()";}
    ~Base() {LOG << '[' << this << "] " << "~Base()";}
};

struct A {
    virtual void test() {LOG << "A::test";}
};

struct B : public A {
    virtual void test() {LOG << "B::test";}
};

struct C1 {
    operator std::string() {
        return "Hello, I'm C1!";
    }
};
struct C2 {
    int m_x;
    long m_z;
    operator std::string() {
        return "Hello, I'm C2!";
    }
};

int operator"" _RU(unsigned long long x) {
    return x / 1000;
}

int main()
{
//    Base b;

    char c('x');

    LOG << "char: " << c;
    LOG << "static_cast<int>: " << static_cast<int>(c);
    int x = 121;
    LOG << "reinterpret_cast<char *>: " << *reinterpret_cast<char *>(&x);
    LOG << "reinterpret_cast<int *>: " << *reinterpret_cast<int *>(&c);

    C1 c1;
    LOG << "reinterpret_cast<C2 *>(C1): " << std::string(*reinterpret_cast<C2 *>(&c1));

    B b;
    A &ra = b;
    dynamic_cast<B&>(ra).test();

    LOG << "+++++";
    A a;
    B &rb = static_cast<B&>(a);
    rb.test();

    LOG << "+++++";
    B().test();

    LOG << "+++++";
    LOG << 14500_RU;

    return 0;
}
