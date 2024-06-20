#include "HttpResponse.h"
#include <sstream>

HttpResponse::HttpResponse(const std::string& raw_response) 
{
    parse(raw_response);
}

void HttpResponse::parse(const std::string& raw_response) 
{
    std::istringstream response_stream(raw_response);
    std::string line;

        // citesc status line
    std::getline(response_stream, line);
    std::istringstream status_line(line);
    std::string http_version;
    status_line >> http_version >> status_code;
    std::getline(status_line, status_message);
    status_message = status_message.substr(1);

        // citesc headers
    while (std::getline(response_stream, line) && line != "\r") 
    {
        auto colon_pos = line.find(':');
        if (colon_pos != std::string::npos) 
        {
            std::string header_name = line.substr(0, colon_pos);
            std::string header_value = line.substr(colon_pos + 2, line.length() - colon_pos - 3); // Remove "\r"
            headers[header_name] = header_value;
        }
    }

        // citesc body
    std::ostringstream body_stream;
    while (std::getline(response_stream, line)) {
        body_stream << line << "\n";
    }
    body = body_stream.str();
}

int HttpResponse::get_status_code() const 
{ 
    return status_code;
}

std::string HttpResponse::get_status_message() const 
{ 
    return status_message; 
}

std::map<std::string, std::string> HttpResponse::get_headers() const 
{
    return headers; 
}

std::string HttpResponse::get_body() const 
{ 
    return body; 
}

std::string HttpResponse::get_header_value(const std::string& header_name) const 
{
        auto it = headers.find(header_name);
        if (it != headers.end()) {
            return it->second;
        }
        return "";
    }

