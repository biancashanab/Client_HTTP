#ifndef HTTPCLIENTBASE_H
#define HTTPCLIENTBASE_H

#include <string>
#include <map>
#include "TimeoutManagement.h"
#include "CacheControl.h"
#include "CookieControl.h"

class HttpClientBase 
{
public:
    HttpClientBase() = default; 
    virtual ~HttpClientBase() = default;
    
    virtual std::string send_request(const std::string& method, const std::string& host, const std::string& path,
                                     const std::map<std::string, std::string>& headers = {},
                                     const std::string& body = "") = 0;

    virtual std::string get(const std::string& host, const std::string& path,
                    const std::map<std::string, std::string>& headers = {}) = 0;

    virtual std::string head(const std::string& host, const std::string& path,
                     const std::map<std::string, std::string>& headers = {}) = 0;

    virtual std::string post(const std::string& host, const std::string& path,
                     const std::map<std::string, std::string>& headers, const std::string& body) = 0;

    virtual std::string put(const std::string& host, const std::string& path,
                    const std::map<std::string, std::string>& headers, const std::string& body) = 0;

    virtual std::string del(const std::string& host, const std::string& path,
                    const std::map<std::string, std::string>& headers = {}) = 0;

    virtual std::string connect(const std::string& host, const std::string& path,
                        const std::map<std::string, std::string>& headers = {}) = 0;  

    virtual std::string options(const std::string& host, const std::string& path,
                        const std::map<std::string, std::string>& headers,  const std::string& body) = 0;

    virtual std::string trace(const std::string& host, const std::string& path,
                      const std::map<std::string, std::string>& headers = {}) = 0;

};

#endif // HTTPCLIENTBASE_H

