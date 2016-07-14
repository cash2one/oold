#include <iostream>
#include <vector>
#include <boost/any.hpp>
#include <map>
#include <functional>
using namespace std;


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

template <typename R = void>
class MessageBus
{
public:
    //注册消息
    template< class... Args, class F, class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
    void Attach(string strKey, F && f)
    {
        std::function<R(Args...)> fn = [&](Args... args){return f(std::forward<Args>(args)...); };
        m_map.insert(std::make_pair(strKey + type_name < Args...>(), std::move(fn)));
    }

    // non-const member function 
    template<class... Args, class C, class... DArgs, class P>
    void Attach(string strKey, R(C::*f)(DArgs...), P && p)
    {
        std::function<R(Args...)> fn = [&, f](Args... args){return (*p.*f)(std::forward<Args>(args)...); };
        m_map.insert(std::make_pair(strKey + type_name < Args...>(), std::move(fn)));
    }

    template<class... Args, class C, class... DArgs, class P>
    void Attach(string strKey, R(C::*f)(DArgs...) const, P && p)
    {
        std::function<R(Args...)> fn = [&, f](Args... args){return (*p.*f)(std::forward<Args>(args)...); };
        m_map.insert(std::make_pair(strKey + type_name < Args...>(), std::move(fn)));
    }

    //广播消息，主题和参数可以确定一个消息, 所有的消息接收者都将收到并处理该消息
    template<typename... Args>
    void SendReq(string strTopic, Args... args)
    {
        auto range = m_map.equal_range(strTopic + type_name < Args...>());
        for (auto it = range.first; it != range.second; it++)
        {
            std::function<R(Args...)> f = boost::any_cast<std::function<R(Args...)>>(it->second);
            f(args...);
        }
    }

    //移除消息
    template<typename... Args>
    void Remove(string strTopic)
    {
        string strMsgType = GetNameofMsgType<Args...>();
        auto range = m_map.equal_range(strTopic + strMsgType);
        m_map.erase(range.first, range.second);
    }

private:
    std::multimap<string, boost::any> m_map;
};

struct A
{
    void Test(int x){ cout << x << endl; }
    void GTest()
    {
        cout << "it is a test" << endl;
    }
    void HTest(int x) const
    {
        cout << "it is a HTest" << endl;
    }
};

void GG(int x)
{
    cout << "it is a gg" << endl;
}

class X
{
public:
  X() { cout << "X()" << endl;}
  ~X() { cout << "~X()" << endl;}
};

void GG1()
{
    cout << "it is a GG" << endl;
}

void GG2(X* obj, int x1, int x2)
{
    cout << obj << " " << x1  << " " << x2 << endl;
}



void TestMessageBus()
{
    A a;
    MessageBus<> bus;
    bus.Attach<int>("aa", &A::Test, &a);
    int x = 3;
    bus.SendReq("aa", 3);

    bus.Attach<int>("hh", &A::HTest, &a);
    bus.SendReq("hh", x);
    bus.Attach("bb", &A::GTest, &a);
    bus.SendReq("bb");

    bus.Attach<int>("gg", GG);
    bus.SendReq("gg", 3);

    bus.Attach("gg", GG1);
    bus.SendReq("gg");

    bus.Attach<X*, int, int>("test", GG2);
    X obj;
    bus.SendReq("test", &obj, 1, 2);
}


int main(void)
{
    TestMessageBus();
    system("pause");
	return 0;
}