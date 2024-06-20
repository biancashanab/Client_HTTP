#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <map>

class HttpResponse
{
public:
    HttpResponse(const std::string& raw_response);

    int get_status_code() const;
    std::string get_status_message() const ;
    std::map<std::string, std::string> get_headers() const ;
    std::string get_body() const;
    std::string get_header_value(const std::string& header_name) const;

private:
    int status_code;
    std::string status_message;
    std::map<std::string, std::string> headers;
    std::string body;

    void parse(const std::string& raw_response);
};

#endif // HTTPRESPONSE_H
