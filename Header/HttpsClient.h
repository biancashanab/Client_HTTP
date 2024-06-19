#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include "HttpClient.h"
#include "SslConnection.h"

class HttpsClient : public HttpClient 
{
public:
    std::string send_request(const std::string& method, const std::string& host, const std::string& path,
                             const std::map<std::string, std::string>& headers = {},
                             const std::string& body = "") override;
};

#endif // HTTPSCLIENT_H

