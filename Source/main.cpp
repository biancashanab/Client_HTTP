#include <iostream>
#include <map>
#include "HttpClient.h"

void testHttpClient() 
{
    HttpClient client;

    std::string method = "GET";
    std::string host = "www.Example.com";
    std::string path = "/";
    std::map<std::string, std::string> headers = {
        {"User-Agent", "HttpClient/1.0"}
    };

    std::string response = client.send_request(method, host, path, headers);
    std::cout << "HTTP Client Response:\n" << response << std::endl;
}

void testSocketConnection()
{
    SocketConnection connection;

    std::string host = "www.Example.com";
    int port = 80;

    connection.connect(host, port);
    std::cout << "Socket connected to " << host << ":" << port << std::endl;

    std::string request = "GET / HTTP/1.1\r\nHost: " + host + "\r\n";
    connection.send(request);

    std::string response = connection.receive();
    std::cout << "Socket Response:\n" << response << std::endl;

    connection.close();
    std::cout << "Socket closed" << std::endl;
}


int main() 
{
    std::cout << "Testing HttpClient:\n";
    testHttpClient();

    std::cout << "\nTesting SocketConnection:\n";
    testSocketConnection();

    return 0;
}

