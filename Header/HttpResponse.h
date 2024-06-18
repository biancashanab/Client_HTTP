#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <map>

class HttpResponse
{
public:
    HttpResponse(const std::string& raw_response);

    std::string get_body() const;
    std::string get_header(const std::string& name) const;

private:
    std::string body;
    std::map<std::string, std::string> headers;

    void parse(const std::string& raw_response);
};

#endif // HTTPRESPONSE_H
