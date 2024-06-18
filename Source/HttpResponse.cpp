#include "HttpResponse.h"
#include <sstream>

HttpResponse::HttpResponse(const std::string& raw_response) {
    parse(raw_response);
}

void HttpResponse::parse(const std::string& raw_response) {
    std::istringstream response_stream(raw_response);
    std::string line;

    while (std::getline(response_stream, line) && line != "\r") {
        if (line.find(":") != std::string::npos) {
            std::string header_name = line.substr(0, line.find(":"));
            std::string header_value = line.substr(line.find(":") + 2);
            headers[header_name] = header_value;
        }
    }

    std::ostringstream body_stream;
    while (std::getline(response_stream, line)) {
        body_stream << line << "\n";
    }
    body = body_stream.str();
}

std::string HttpResponse::get_body() const {
    return body;
}

std::string HttpResponse::get_header(const std::string& name) const {
    auto it = headers.find(name);
    if (it != headers.end()) {
        return it->second;
    }
    return "";
}

