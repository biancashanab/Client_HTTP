#include "HttpClient.h"
#include <iostream>

HttpClient::HttpClient()
{
    cache = CacheControl();
    cookie = CookieControl();
}

CacheControl &HttpClient::get_cache_control()
{
    return cache;
}

CookieControl &HttpClient::get_cookie_control()
{
    return cookie;
}

std::string HttpClient::send_request(const std::string &method, const std::string &host, const std::string &path,
                                     const std::map<std::string, std::string> &headers, const std::string &body)
{
    const int timeout_duration = 10;

    try {
        if (cache.checkUseCache()) {
            std::string cachedResponse = cache.getFromCache(method, host, path);
            if (!cachedResponse.empty()) {
                return cachedResponse;
            }
        }

        SocketConnection connection;
        connection.setTimeout(timeout_duration);
        connection.connect(host, 80);
        
        HttpRequest request(method, host, path, headers, body);
        connection.send(request.to_string());

        std::string response_str = connection.receive();
        HttpResponse response(response_str);

        if (cache.checkUseCache()) {
            cache.saveToCache(method, host, path, response_str);
        }

        std::map<std::string, std::string> responseHeaders = response.get_headers();
        auto it = responseHeaders.find("Set-Cookie");
        if (it != responseHeaders.end()) {
            cookie.addCookie(it->second, host);
        }

        if (method == "HEAD") {
            std::ostringstream header_info;
            header_info << "Status: " << response.get_status_code() << " " << response.get_status_message() << "\n";
            for (const auto& header : response.get_headers()) {
                header_info << header.first << ": " << header.second << "\n";
            }
            return header_info.str();
        }

        return response.get_body();

    } catch (const std::exception& e) {
       
        std::cerr << "HTTP request error: " << e.what() << std::endl;
        return "";
    }
}

std::string HttpClient::get(const std::string& host, const std::string& path,
                            const std::map<std::string, std::string>& headers) {
    return send_request("GET", host, path, headers);
}

std::string HttpClient::head(const std::string& host, const std::string& path,
                             const std::map<std::string, std::string>& headers) {
    return send_request("HEAD", host, path, headers);
}

std::string HttpClient::post(const std::string& host, const std::string& path,
                             const std::map<std::string, std::string>& headers, const std::string& body) {
    return send_request("POST", host, path, headers, body);
}

std::string HttpClient::put(const std::string& host, const std::string& path,
                            const std::map<std::string, std::string>& headers, const std::string& body) {
    return send_request("PUT", host, path, headers, body);
}

std::string HttpClient::del(const std::string& host, const std::string& path,
                            const std::map<std::string, std::string>& headers) {
    return send_request("DELETE", host, path, headers);
}

std::string HttpClient::connect(const std::string& host, const std::string& path,
                                const std::map<std::string, std::string>& headers) {
    return send_request("CONNECT", host, path, headers);
}

std::string HttpClient::trace(const std::string& host, const std::string& path,
                              const std::map<std::string, std::string>& headers) {
    return send_request("TRACE", host, path, headers);
}