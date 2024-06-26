#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include <iostream>
#include "HttpClient.h"
#include "SslConnection.h"

class HttpsClient : public HttpClient 
{
public:
    std::string send_request(const std::string& method, const std::string& host, const std::string& path,
                             const std::map<std::string, std::string>& headers = {},
                             const std::string& body = "") override;

    void addCookie(const std::string &cookie, const std::string &host);
};

#endif // HTTPSCLIENT_H

