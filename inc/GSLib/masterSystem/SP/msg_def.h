
#ifndef _IDL_DEF_I_
#define _IDL_DEF_I_

#include <json/inc/config.h>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
using namespace std;

#include <json/inc/rapidjson/document.h>     // rapidjson's DOM-style API
#include <json/inc/rapidjson/prettywriter.h> // for stringify JSON
#include <json/inc/rapidjson/filestream.h>   // wrapper of C stream for prettywriter as output
#include <json/inc/json_instream.h>
#include <json/inc/json_outstream.h>
#include <json/inc/rapidjson/stringbuffer.h>
#include <json/inc/smart_ptr/shared_ptr.h>
//! using namespace rapidjson;

typedef runtime_error        msg_exception_t;
typedef rapidjson::Document  json_dom_t;
typedef rapidjson::Value     json_value_t;

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

struct msg_t
{
    virtual ~msg_t(){}
    virtual string encode_json() const = 0;
};
typedef shared_ptr_t<msg_t> msg_ptr_t;

struct mail_req_t : public msg_t {
    string sender;
    vector<string> roles;
    string title;
    vector<uint32> itemids;
    string content;
    vector<uint32> itemnums;
    string zone;
    uint32 type;
    int parse(const json_value_t& jval_) {

            json_instream_t in("mail_req_t");
            in.decode("sender", jval_["sender"], sender).decode("roles", jval_["roles"], roles).decode("title", jval_["title"], title).decode("itemids", jval_["itemids"], itemids).decode("content", jval_["content"], content).decode("itemnums", jval_["itemnums"], itemnums).decode("zone", jval_["zone"], zone).decode("type", jval_["type"], type);
        return 0;
    }

    string encode_json() const
    {
        rapidjson::Document::AllocatorType allocator;
        rapidjson::StringBuffer            str_buff;
        json_value_t                       ibj_json(rapidjson::kObjectType);
        json_value_t                       ret_json(rapidjson::kObjectType);

        this->encode_json_val(ibj_json, allocator);
        ret_json.AddMember("mail_req_t", ibj_json, allocator);

        rapidjson::Writer<rapidjson::StringBuffer> writer(str_buff, &allocator);
        ret_json.Accept(writer);
        string output(str_buff.GetString(), str_buff.GetSize());
        return output;
    }
        
    int encode_json_val(json_value_t& dest, rapidjson::Document::AllocatorType& allocator) const{

        json_outstream_t out(allocator);
		out.encode("sender", dest, sender).encode("roles", dest, roles).encode("title", dest, title).encode("itemids", dest, itemids).encode("content", dest, content).encode("itemnums", dest, itemnums).encode("zone", dest, zone).encode("type", dest, type);
        return 0;
    }

};
struct accountpwd_req_t : public msg_t {
    string pwd;
    string zone;
    string accountname;
    int parse(const json_value_t& jval_) {

            json_instream_t in("accountpwd_req_t");
            in.decode("pwd", jval_["pwd"], pwd).decode("zone", jval_["zone"], zone).decode("accountname", jval_["accountname"], accountname);
        return 0;
    }

    string encode_json() const
    {
        rapidjson::Document::AllocatorType allocator;
        rapidjson::StringBuffer            str_buff;
        json_value_t                       ibj_json(rapidjson::kObjectType);
        json_value_t                       ret_json(rapidjson::kObjectType);

        this->encode_json_val(ibj_json, allocator);
        ret_json.AddMember("accountpwd_req_t", ibj_json, allocator);

        rapidjson::Writer<rapidjson::StringBuffer> writer(str_buff, &allocator);
        ret_json.Accept(writer);
        string output(str_buff.GetString(), str_buff.GetSize());
        return output;
    }
        
    int encode_json_val(json_value_t& dest, rapidjson::Document::AllocatorType& allocator) const{

        json_outstream_t out(allocator);
		out.encode("pwd", dest, pwd).encode("zone", dest, zone).encode("accountname", dest, accountname);
        return 0;
    }

};
struct accountforbid_req_t : public msg_t {
    uint32 setstate;
    string zone;
    string accountname;
    int parse(const json_value_t& jval_) {

            json_instream_t in("accountforbid_req_t");
            in.decode("setstate", jval_["setstate"], setstate).decode("zone", jval_["zone"], zone).decode("accountname", jval_["accountname"], accountname);
        return 0;
    }

    string encode_json() const
    {
        rapidjson::Document::AllocatorType allocator;
        rapidjson::StringBuffer            str_buff;
        json_value_t                       ibj_json(rapidjson::kObjectType);
        json_value_t                       ret_json(rapidjson::kObjectType);

        this->encode_json_val(ibj_json, allocator);
        ret_json.AddMember("accountforbid_req_t", ibj_json, allocator);

        rapidjson::Writer<rapidjson::StringBuffer> writer(str_buff, &allocator);
        ret_json.Accept(writer);
        string output(str_buff.GetString(), str_buff.GetSize());
        return output;
    }
        
    int encode_json_val(json_value_t& dest, rapidjson::Document::AllocatorType& allocator) const{

        json_outstream_t out(allocator);
		out.encode("setstate", dest, setstate).encode("zone", dest, zone).encode("accountname", dest, accountname);
        return 0;
    }

};
struct itemdeduct_req_t : public msg_t {
    uint32 itemid;
    uint32 itemnum;
    string name;
    string zone;
    int parse(const json_value_t& jval_) {

            json_instream_t in("itemdeduct_req_t");
            in.decode("itemid", jval_["itemid"], itemid).decode("itemnum", jval_["itemnum"], itemnum).decode("name", jval_["name"], name).decode("zone", jval_["zone"], zone);
        return 0;
    }

    string encode_json() const
    {
        rapidjson::Document::AllocatorType allocator;
        rapidjson::StringBuffer            str_buff;
        json_value_t                       ibj_json(rapidjson::kObjectType);
        json_value_t                       ret_json(rapidjson::kObjectType);

        this->encode_json_val(ibj_json, allocator);
        ret_json.AddMember("itemdeduct_req_t", ibj_json, allocator);

        rapidjson::Writer<rapidjson::StringBuffer> writer(str_buff, &allocator);
        ret_json.Accept(writer);
        string output(str_buff.GetString(), str_buff.GetSize());
        return output;
    }
        
    int encode_json_val(json_value_t& dest, rapidjson::Document::AllocatorType& allocator) const{

        json_outstream_t out(allocator);
		out.encode("itemid", dest, itemid).encode("itemnum", dest, itemnum).encode("name", dest, name).encode("zone", dest, zone);
        return 0;
    }

};
struct command_ret_t : public msg_t {
    string info;
    uint32 result;
    int parse(const json_value_t& jval_) {

            json_instream_t in("command_ret_t");
            in.decode("info", jval_["info"], info).decode("result", jval_["result"], result);
        return 0;
    }

    string encode_json() const
    {
        rapidjson::Document::AllocatorType allocator;
        rapidjson::StringBuffer            str_buff;
        json_value_t                       ibj_json(rapidjson::kObjectType);
        json_value_t                       ret_json(rapidjson::kObjectType);

        this->encode_json_val(ibj_json, allocator);
        ret_json.AddMember("command_ret_t", ibj_json, allocator);

        rapidjson::Writer<rapidjson::StringBuffer> writer(str_buff, &allocator);
        ret_json.Accept(writer);
        string output(str_buff.GetString(), str_buff.GetSize());
        return output;
    }
        
    int encode_json_val(json_value_t& dest, rapidjson::Document::AllocatorType& allocator) const{

        json_outstream_t out(allocator);
		out.encode("info", dest, info).encode("result", dest, result);
        return 0;
    }

};
struct broadcast_req_t : public msg_t {
    string content;
    string zone;
    int parse(const json_value_t& jval_) {

            json_instream_t in("broadcast_req_t");
            in.decode("content", jval_["content"], content).decode("zone", jval_["zone"], zone);
        return 0;
    }

    string encode_json() const
    {
        rapidjson::Document::AllocatorType allocator;
        rapidjson::StringBuffer            str_buff;
        json_value_t                       ibj_json(rapidjson::kObjectType);
        json_value_t                       ret_json(rapidjson::kObjectType);

        this->encode_json_val(ibj_json, allocator);
        ret_json.AddMember("broadcast_req_t", ibj_json, allocator);

        rapidjson::Writer<rapidjson::StringBuffer> writer(str_buff, &allocator);
        ret_json.Accept(writer);
        string output(str_buff.GetString(), str_buff.GetSize());
        return output;
    }
        
    int encode_json_val(json_value_t& dest, rapidjson::Document::AllocatorType& allocator) const{

        json_outstream_t out(allocator);
		out.encode("content", dest, content).encode("zone", dest, zone);
        return 0;
    }

};


template<typename T, typename R>
class msg_dispather_t
{
    typedef R                    socket_ptr_t;
    typedef int (msg_dispather_t<T, R>::*reg_func_t)(const json_value_t&, socket_ptr_t);
public:
    msg_dispather_t(T& msg_handler_):
        m_msg_handler(msg_handler_)
    {
        
        m_reg_func["mail_req_t"] = &msg_dispather_t<T, R>::mail_req_t_dispacher;
            
        m_reg_func["accountpwd_req_t"] = &msg_dispather_t<T, R>::accountpwd_req_t_dispacher;
            
        m_reg_func["accountforbid_req_t"] = &msg_dispather_t<T, R>::accountforbid_req_t_dispacher;
            
        m_reg_func["itemdeduct_req_t"] = &msg_dispather_t<T, R>::itemdeduct_req_t_dispacher;
            
        m_reg_func["broadcast_req_t"] = &msg_dispather_t<T, R>::broadcast_req_t_dispacher;
            
    }

    int dispath(const string& json_, socket_ptr_t sock_)
    {
        json_dom_t document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
        if (document.Parse<0>(json_.c_str()).HasParseError())
        {
            throw msg_exception_t("json format not right");
        }
        if (false == document.IsObject() && false == document.Empty())
        {
            throw msg_exception_t("json must has one field");
        }
    
        const json_value_t& val = document.MemberBegin()->name;
        const char* func_name   = val.GetString();
        typename map<string, reg_func_t>::const_iterator it = m_reg_func.find(func_name);
    
        if (it == m_reg_func.end())
        {
            char buff[512];
            snprintf(buff, sizeof(buff), "msg not supported<%s>", func_name);
            throw msg_exception_t(buff);
            return -1;
        }
        reg_func_t func = it->second;
    
        (this->*func)(document.MemberBegin()->value, sock_);
        return 0;
    }
        
    int mail_req_t_dispacher(const json_value_t& jval_, socket_ptr_t sock_)
    {
        shared_ptr_t<mail_req_t> ret_val(new mail_req_t());
        ret_val->parse(jval_);

        m_msg_handler.handle(ret_val, sock_);
        return 0;
    }
            
    int accountpwd_req_t_dispacher(const json_value_t& jval_, socket_ptr_t sock_)
    {
        shared_ptr_t<accountpwd_req_t> ret_val(new accountpwd_req_t());
        ret_val->parse(jval_);

        m_msg_handler.handle(ret_val, sock_);
        return 0;
    }
            
    int accountforbid_req_t_dispacher(const json_value_t& jval_, socket_ptr_t sock_)
    {
        shared_ptr_t<accountforbid_req_t> ret_val(new accountforbid_req_t());
        ret_val->parse(jval_);

        m_msg_handler.handle(ret_val, sock_);
        return 0;
    }
            
    int itemdeduct_req_t_dispacher(const json_value_t& jval_, socket_ptr_t sock_)
    {
        shared_ptr_t<itemdeduct_req_t> ret_val(new itemdeduct_req_t());
        ret_val->parse(jval_);

        m_msg_handler.handle(ret_val, sock_);
        return 0;
    }
            
    int broadcast_req_t_dispacher(const json_value_t& jval_, socket_ptr_t sock_)
    {
        shared_ptr_t<broadcast_req_t> ret_val(new broadcast_req_t());
        ret_val->parse(jval_);

        m_msg_handler.handle(ret_val, sock_);
        return 0;
    }
            
private:
    T&                      m_msg_handler;
    map<string, reg_func_t> m_reg_func;
};
        
#endif
