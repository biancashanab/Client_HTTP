#ifndef HTTPCLIENTBASE_H
#define HTTPCLIENTBASE_H

#include <string>
#include <map>

class HttpClientBase 
{
public:
    virtual ~HttpClientBase() = default;
    virtual std::string send_request(const std::string& method, const std::string& host, const std::string& path,
                                     const std::map<std::string, std::string>& headers = {},
                                     const std::string& body = "") = 0;
};

#endif // HTTPCLIENTBASE_H

