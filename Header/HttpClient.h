#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "HttpClientBase.h"
#include "SocketConnection.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

class HttpClient : public HttpClientBase
{
public:
    HttpClient();
    ~HttpClient() = default;

    CacheControl &get_cache_control();
    CookieControl &get_cookie_control();

    std::string send_request(const std::string &method, const std::string &host, const std::string &path,
                             const std::map<std::string, std::string> &headers = {},
                             const std::string &body = "") override;

    std::string get(const std::string &host, const std::string &path,
                    const std::map<std::string, std::string> &headers = {}) override;

    std::string head(const std::string &host, const std::string &path,
                     const std::map<std::string, std::string> &headers = {}) override;

    std::string post(const std::string &host, const std::string &path,
                     const std::map<std::string, std::string> &headers, const std::string &body) override;

    std::string put(const std::string &host, const std::string &path,
                    const std::map<std::string, std::string> &headers, const std::string &body) override;

    std::string del(const std::string &host, const std::string &path,
                    const std::map<std::string, std::string> &headers = {}) override;

    std::string connect(const std::string &host, const std::string &path,
                        const std::map<std::string, std::string> &headers = {}) override;

    std::string trace(const std::string &host, const std::string &path,
                      const std::map<std::string, std::string> &headers = {}) override;

protected:
    CacheControl cache;
    CookieControl cookie;
};

#endif // HTTPCLIENT_H
