#include "HttpsClient.h"


void HttpsClient::addCookie(const std::string &cookie, const std::string &host)
{
    get_cookie_control().addCookie(cookie, host);
}

std::string HttpsClient::send_request(const std::string &method, const std::string &host, const std::string &path, const std::map<std::string, std::string> &headers, const std::string &body)
{
    try
    {
        SslConnection connection;
        connection.connect(host, 443);

        HttpRequest request(method, host, path, headers, body);
        connection.send(request.to_string());

        std::string response_str = connection.receive();
        HttpResponse response(response_str);

        std::map<std::string, std::string> responseHeaders = response.get_headers();
        auto it = responseHeaders.find("Set-Cookie");
        if (it != responseHeaders.end())
        {
            addCookie(it->second, host);
        }
        
        if (method == "HEAD")
        {
            std::ostringstream header_info;
            header_info << "Status: " << response.get_status_code() << " " << response.get_status_message() << "\n";
            for (const auto &header : response.get_headers())
            {
                header_info << header.first << ": " << header.second << "\n";
            }
            return header_info.str();
        }

        return response.get_body();
    }
    catch (const std::exception &e)
    {
        std::cerr << "HTTP request error: " << e.what() << std::endl;
        return "";
    }
}

std::string HttpsClient::get(const std::string &host, const std::string &path, const std::map<std::string, std::string> &headers)
{
    if (cache.isUsingCache() && cache.checkCacheExists(host))
    {
        return cache.loadCache(host);
    }

    std::string response = send_request("GET", host, path, headers);
    cache.saveCache(host, response);
    return response;
}

std::string HttpsClient::head(const std::string &host, const std::string &path, const std::map<std::string, std::string> &headers)
{
    return send_request("HEAD", host, path, headers);
}

std::string HttpsClient::post(const std::string &host, const std::string &path, const std::map<std::string, std::string> &headers, const std::string &body)
{
    return send_request("POST", host, path, headers, body);
}

std::string HttpsClient::put(const std::string &host, const std::string &path, const std::map<std::string, std::string> &headers, const std::string &body)
{
    return send_request("PUT", host, path, headers, body);
}

std::string HttpsClient::del(const std::string &host, const std::string &path, const std::map<std::string, std::string> &headers)
{
    return send_request("DELETE", host, path, headers);
}

std::string HttpsClient::connect(const std::string &host, const std::string &path, const std::map<std::string, std::string> &headers)
{
    return send_request("CONNECT", host, path, headers);
}

std::string HttpsClient::trace(const std::string &host, const std::string &path, const std::map<std::string, std::string> &headers)
{
    return send_request("TRACE",host,path,headers);
}