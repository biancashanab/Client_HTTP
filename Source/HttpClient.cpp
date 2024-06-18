#include "HttpClient.h"

std::string HttpClient::send_request(const std::string& method, const std::string& host, const std::string& path,
                                     const std::map<std::string, std::string>& headers, const std::string& body) {
    SocketConnection connection;
    connection.connect(host, 80);

    HttpRequest request(method, host, path, headers, body);
    connection.send(request.to_string());

    std::string response_str = connection.receive();
    HttpResponse response(response_str);
    return response.get_body();
}

