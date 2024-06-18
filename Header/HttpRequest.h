#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <map>
#include <sstream>

class HttpRequest 
{
public:
    HttpRequest(const std::string& method, const std::string& host, const std::string& path,
                const std::map<std::string, std::string>& headers, const std::string& body);

    std::string to_string() const;

private:
    std::string method;
    std::string host;
    std::string path;
    std::map<std::string, std::string> headers;
    std::string body;
};

#endif // HTTPREQUEST_H

