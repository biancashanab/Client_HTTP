#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include <iostream>
#include "HttpClient.h"
#include "SslConnection.h"

class HttpsClient : public HttpClient
{
public:
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

    void addCookie(const std::string &cookie, const std::string &host);
};

#endif // HTTPSCLIENT_H
