#pragma once
#include <string>
#include <functional>
#include <map>
#include "Any.hpp"
#include "function_traits.hpp"
#include "NonCopyable.hpp"

class MessageBus: NonCopyable
{
public:
    // 注册主题, lambda
	template<typename F>
	void Attach(F&& f, const std::string& strTopic="")
	{
		auto func = to_function(std::forward<F>(f));
		Add(strTopic, std::move(func));
	}

    // non-const member function 
    template<typename R, class... Args, class C, class... DArgs, class P>
    void Attach(R(C::*f)(DArgs...), P && p, std::string strKey)
    {
        std::function<R(Args...)> fn = [&, f](Args... args){return (*p.*f)(std::forward<Args>(args)...); };
        Add(strKey, std::move(fn));
    }

    // const member function
    template<typename R, class... Args, class C, class... DArgs, class P>
    void Attach(R(C::*f)(DArgs...) const, P && p, std::string strKey)
    {
        std::function<R(Args...)> fn = [&, f](Args... args){return (*p.*f)(std::forward<Args>(args)...); };
        Add(strKey, std::move(fn));
    }

//     template<typename R, class... Args, class F, class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
//     void Attach(F && f, std::string strKey)
//     {
//         std::function<R(Args...)> fn = [&](Args... args){return f(std::forward<Args>(args)...); };
//         Add(strKey, std::move(fn));
//     }

    
    // 发送消息
	template<typename R>
	void SendReq(const std::string& strTopic = "")
	{
		using function_type = std::function<R()>;
		std::string strMsgType =strTopic+ typeid(function_type).name();
		auto range = m_map.equal_range(strMsgType);
		for (Iterater it = range.first; it != range.second; ++it)
		{
			auto f = it->second.AnyCast < function_type >();
			f();
		}
	}
	template<typename R, typename... Args>
	void SendReq(Args&&... args, const std::string& strTopic = "")
	{
		using function_type = std::function<R(Args...)>;
		std::string strMsgType =strTopic+ typeid(function_type).name();
		auto range = m_map.equal_range(strMsgType);
		for (Iterater it = range.first; it != range.second; ++it)
		{
			auto f = it->second.AnyCast < function_type >();
			f(std::forward<Args>(args)...);
		}
	}

	//移除某个主题, 需要主题和消息类型
	template<typename R, typename... Args>
	void Remove(const std::string& strTopic = "")
	{
		using function_type = std::function<R(Args...)>;

		string strMsgType =strTopic +typeid(function_type).name();
		int count = m_map.count(strMsgType);
		auto range = m_map.equal_range(strMsgType);
		m_map.erase(range.first, range.second);
	}

private:
	template<typename F>
	void Add(const std::string& strTopic, F&& f)
	{
		std::string strMsgType = strTopic + typeid(F).name();
		m_map.emplace(std::move(strMsgType), std::forward<F>(f));
	}

private:
	std::multimap<std::string, Any> m_map;
	typedef std::multimap<std::string, Any>::iterator Iterater;
};
