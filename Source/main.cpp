#include <iostream>
#include <map>

#include "HttpClient.h"
#include "HttpsClient.h"
#include "TimeoutManagement.h"
#include "CacheControl.h"

void testHttpClient() 
{
    HttpClient client;
    TimeoutManagement timeout(5.0); // 5 seconds timeout
    CacheControl cache;
    cache.addDirective("max-age", "3600");

    std::string method = "GET";
    std::string host = "www.example.com";
    std::string path = "/";
    std::map<std::string, std::string> headers = {
        {"User-Agent", "HttpClient/1.0"},
        {"Cache-Control", cache.getDirective("max-age")}
    };

    timeout.start();
    try {
        while (!timeout.isTimeout()) {
            std::string response = client.send_request(method, host, path, headers);
            std::cout << "HTTP Client Response:\n" << response << std::endl;
            break;
        }
        if (timeout.isTimeout()) {
            std::cout << "HTTP request timed out." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "HTTP request error: " << e.what() << std::endl;
    }
}

void testHttpsClient() 
{
    HttpsClient client;
    TimeoutManagement timeout(5.0); 
    CacheControl cache;
    cache.addDirective("max-age", "3600");
    std::string method = "GET";
    std::string host = "www.google.com";
    std::string path = "/";
    std::map<std::string, std::string> headers = {
        {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"},
        {"Cache-Control", cache.getDirective("max-age")}
    };

    timeout.start();
    try {
        while (!timeout.isTimeout()) {

            std::string response = client.send_request(method, host, path, headers);
            std::cout << "HTTPS Client Response:\n" << response << std::endl;
            break;
        }
        if (timeout.isTimeout()) {
            std::cout << "HTTPS request timed out." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "HTTPS request error: " << e.what() << std::endl;
    }
}

void testSocketConnection()
{
    SocketConnection connection;

    std::string host = "www.Example.com";
    int port = 80;

       try {
        connection.connect(host, port);
        std::cout << "Socket connected to " << host << ":" << port << std::endl;

        std::string request = "GET / HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
        connection.send(request);

        std::string response = connection.receive();
        std::cout << "Socket Response:\n" << response << std::endl;

        connection.close();
        std::cout << "Socket closed" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Socket connection error: " << e.what() << std::endl;
    }
}

int main() 
{
    std::cout << "Testing HttpClient:\n";
    testHttpClient();

    std::cout << "\nTesting HttpsClient:\n";
    testHttpsClient();

   std::cout << "\nTesting SocketConnection:\n";
   testSocketConnection();

    return 0;
}



