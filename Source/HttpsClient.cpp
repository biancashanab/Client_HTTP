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
