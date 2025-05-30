#ifndef TOKEN_HH
#define TOKEN_HH

#include    <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <boost/json.hpp>

using namespace   std;

class Token 
{
private:
    string    _key;
    string    _user;
    string    _token;

    string  createJwt();
public:
    Token(boost::json::object item);
    Token(const string key, const string user);
    virtual ~Token();
    string  getToken();
    string  getUser();
    string  base64UrlDecode(const string &str);
    string  base64UrlEncode(const string &str);
    boost::json::object         generate(int id);
};

#endif