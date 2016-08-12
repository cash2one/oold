
#include "stdafx.h"
#include "./mesagebus/MessageBus.hpp"
#include <iostream>

struct A
{
    A()
    {
       std::cout << "A::A"<< std::endl;
    }
    ~A()
    {
        std::cout << "A::~A" << std::endl;
    }
};
A& GetA()
{   
    A temp; 
    std::cout << "XXXX" << std::endl;
    return temp;
}


template <typename... Args>
struct Impl;

template <typename First, typename... Args>
struct Impl < First, Args... >
{
    static std::string name()
    {
        return std::string(typeid(First).name()) + " " + Impl<Args...>::name();
    }
};

template <>
struct Impl < >
{
    static std::string name()
    {
        return "";
    }
};

template <typename... Args>
std::string type_name()
{
    return Impl<Args...>::name();
}

using namespace std;
struct AA
{
    void Test(int x) const { cout << x << endl; }
    void GTest()
    {
        cout << "it is a test" << endl;
    }
    void HTest(int x) const
    {
        cout << "it is a HTest" << endl;
    }
};

void test()
{
    cout << "I m in test";
}

int _tmain(int argc, _TCHAR* argv[])
{   
    //A&& a = std::move(GetA());
    //A& b = GetA();
    //A c = GetA();
    //std::cout << "===>" << std::endl;

    MessageBus bus;
    bus.Attach([](int &a) { std::cout << a++ << std::endl;}, "test");
    int i = 1;
    bus.SendReq<void, int&>(i, "test");
    bus.SendReq<void, int&>(i, "test");

    //std::cout << type_name<int , const A *>();

    AA a;
    bus.Attach<void, int>(&AA::Test, &a, "test1");
    bus.SendReq<void, int>(100, "test1");
	return 0;
}

