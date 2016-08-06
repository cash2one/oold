
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

    std::cout << typeid(void).name();

	return 0;
}

