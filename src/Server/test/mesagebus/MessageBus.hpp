#pragma once
#include <string>
#include <functional>
#include <map>
#include "Any.hpp"
#include "function_traits.hpp"
#include "NonCopyable.hpp"


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


/*

*/

template<typename R = int>
class MessageBus
    : NonCopyable
{
public:
    // 注册主题, lambda
	template<typename F>
	void attach(const std::string strTopic, F&& f)
	{
		auto func = to_function(std::forward<F>(f));
		add(strTopic, std::move(func));
	}

    // non-const member function 
    template<class... Args, class C, class... DArgs, class P>
    void attach(const std::string strTopic, R(C::*f)(DArgs...), P && p)
    {
        std::function<R(Args...)> fn = [&, f](Args... args){return (*p.*f)(std::forward<Args>(args)...); };
        add(strTopic, std::move(fn));
    }

    // const member function
    template<class... Args, class C, class... DArgs, class P>
    void attach(const std::string strTopic, R(C::*f)(DArgs...) const, P && p)
    {
        std::function<R(Args...)> fn = [&, f](Args... args) {return (*p.*f)(std::forward<Args>(args)...); };
        add(strTopic, std::move(fn));
    }

	void notify(const std::string strTopic = "")
	{
		using func_type = std::function<R()>;
		std::string strMsgType = strTopic+ typeid(func_type).name();
		auto range = m_map.equal_range(strMsgType);
		for (auto it = range.first; it != range.second; ++it)
		{
            try
            {
                auto f = it->second.AnyCast < func_type >();
                f();
            }
            catch (std::logic_error& err)
            {
                std::cout << err.what() << "\n";
            }
		}
	}


    template<typename... Args>
    void notify(const std::string strTopic, Args&&... args)
    {
        using func_type = std::function < R(Args...) > ;
        std::string strMsgType = strTopic + typeid(func_type).name();
        auto range = m_map.equal_range(strMsgType);
        for (auto it = range.first; it != range.second; ++it)
        {
            try
            {
                auto f = it->second.AnyCast < func_type >();
                f(std::forward<Args>(args)...);
            }
            catch (std::logic_error& err)
            {
                std::cout << err.what() << "\n";
            }
        }
    }

	template<typename... Args>
	R request(const std::string strTopic, Args&&... args)
	{
		using func_type = std::function<R(Args...)>;
		std::string strMsgType = strTopic + typeid(func_type).name();
		auto range = m_map.equal_range(strMsgType);
		for (auto it = range.first; it != range.second; ++it)
		{
			
            try
            {
                auto f = it->second.AnyCast < func_type >();
                return f(std::forward<Args>(args)...);
            }
            catch(std::logic_error& err)
            {
                std::cout << err.what() << "\n";
            }
			
		}

        return false;
	}

	//移除某个主题, 需要主题和消息类型
	template<typename... Args>
	void remove(const std::string strTopic = "")
	{
		using func_type = std::function<R(Args...)>;

		string strMsgType =strTopic +typeid(func_type).name();
		int count = m_map.count(strMsgType);
		auto range = m_map.equal_range(strMsgType);
		m_map.erase(range.first, range.second);
	}

private:
	template<typename F>
	void add(const std::string& strTopic, F&& f)
	{
		std::string strMsgType = strTopic + typeid(F).name();
		m_map.emplace(std::move(strMsgType), std::forward<F>(f));
	}
private:
	std::multimap<std::string, Any> m_map;
};
