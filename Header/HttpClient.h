#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "HttpClientBase.h"
#include "SocketConnection.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

class HttpClient : public HttpClientBase 
{
public:
    std::string send_request(const std::string& method, const std::string& host, const std::string& path,
                             const std::map<std::string, std::string>& headers = {},
                             const std::string& body = "") override;
};

#endif // HTTPCLIENT_H

