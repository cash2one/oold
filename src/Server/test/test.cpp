
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

using namespace std;
struct AA
{
    int Test(int x, const std::string& a){ cout << x << " " << a << endl; return 0;}
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

    MessageBus<int> bus;
    bus.attach("test", [](int &a)->int{ std::cout << a++ << std::endl; return 0; });
    int i = 1;
    bus.request("test", i);
    bus.request("test",i);

    //std::cout << type_name<int , const A *>();

    AA a;
    bus.attach<int, const std::string&>("test1", &AA::Test, &a);
    const std::string str("a");
    bus.request("test1", 100, str);
	return 0;
}

