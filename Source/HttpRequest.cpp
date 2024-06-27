#include "HttpRequest.h"

HttpRequest::HttpRequest(const std::string& method, const std::string& host, const std::string& path,
                         const std::map<std::string, std::string>& headers, const std::string& body)
    : method(method), host(host), path(path), headers(headers), body(body) {}


std::string HttpRequest::to_string() const 
{
    std::ostringstream request;
    request << method << " " << path << " HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";

    for (const auto& header : headers) {
        request << header.first << ": " << header.second << "\r\n";
    }
    if (!body.empty()) {
        request << "Content-Length: " << body.size() << "\r\n";
    }
    request << "Connection: close\r\n\r\n";
    if (!body.empty()) {
        request << body;
    }
    return request.str();
}
