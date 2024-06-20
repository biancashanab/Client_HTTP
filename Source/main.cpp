#include <iostream>
#include <fstream>
#include <map>

#include "HttpClient.h"
#include "HttpsClient.h"
#include "TimeoutManagement.h"
#include "CacheControl.h"
#include "CookieControl.h"

/*

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

void testHttpMethods(HttpClientBase& client, const std::string& host) 
{
    FILE* file;
    std::string path = "/";
    std::string response;

    std::map<std::string, std::string> headers = {
        {"User-Agent", "HttpClient/1.0"}
    };

    
    response = client.get(host, path, headers);
    file = fopen("Response/get_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "GET response:\n%s\n", response.c_str());
        fclose(file);
    }

    response = client.head(host, path, headers);
    file = fopen("Response/head_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "HEAD response:\n%s\n", response.c_str());
        fclose(file);
    }

    response = client.post(host, path, headers, "Body of POST request");
    file = fopen("Response/post_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "POST response:\n%s\n", response.c_str());
        fclose(file);
    }

    response = client.connect(host, path, headers);
    file = fopen("Response/connect_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "CONNECT response:\n%s\n", response.c_str());
        fclose(file);
    }

    response = client.put("localhost", path, headers, "PUT /new.html HTTP/1.1"
"Host: example.com"
"<p>New File</p>");
    file = fopen("Response/put_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "PUT response:\n%s\n", response.c_str());
        fclose(file);
    }

    response = client.trace("localhost", path, headers);
    file = fopen("Response/trace_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "TRACE response:\n%s\n", response.c_str());
        fclose(file);
    }


    response = client.del("localhost", path, headers);
    file = fopen("Response/delete_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "DELETE response:\n%s\n", response.c_str());
        fclose(file);
    }

    response = client.options(host, path, headers,"Origin: http://example.com");
    file = fopen("Response/options_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "OPTIONS response:\n%s\n", response.c_str());
        fclose(file);
    }

    std::cout<< client.send_request("OPTIONS", host, path, headers,"Cache-Control: max-age=0"
"Sec-Ch-Ua: \"Not-A.Brand\";v=\"99\", \"Chromium\";v=\"124\""
"Sec-Ch-Ua-Mobile: ?0"
"Sec-Ch-Ua-Platform: \"Linux\""
"Upgrade-Insecure-Requests: 1"
"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.6367.118 Safari/537.36"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,/;q=0.8,application/signed-exchange;v=b3;q=0.7"
"Sec-Fetch-Site: none"
"Sec-Fetch-Mode: navigate"
"Sec-Fetch-User: ?1"
"Sec-Fetch-Dest: document"
"Accept-Encoding: gzip, deflate, br"
"Accept-Language: en-US,en;q=0.9"
"Priority: u=0, i") << std::endl;
}
*/

void testHttpMethods(HttpClient& client, const std::string& host) 
{
    FILE* file;
    std::string path = "/";
    std::string response;

    std::map<std::string, std::string> headers = {
        {"User-Agent", "HttpClient/1.0"},
        {"Cache-Control", client.get_cache_control().getDirective("max-age")},
        {"Cookie", client.get_cookie_control().getCookieHeader()}
    };

    response = client.get(host, path, headers);
    file = fopen("Response/get_response.txt", "w");
    if (file != nullptr) {
            fprintf(file, "GET response:\n%s\n", response.c_str());
            fclose(file);
    }
    std::cout << "GET response" << std::endl;


    response = client.head(host, path, headers);
    file = fopen("Response/head_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "HEAD response:\n%s\n", response.c_str());
        fclose(file);
    }
    std::cout << "HEAD response" << std::endl;


    response = client.post(host, path, headers, "Body of POST request");
    file = fopen("Response/post_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "POST response:\n%s\n", response.c_str());
        fclose(file);
    }
    std::cout << "POST response" << std::endl;


    response = client.put("localhost", path, headers, "<p>New File</p>");
    file = fopen("Response/put_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "PUT response:\n%s\n", response.c_str());
        fclose(file);
    }
    std::cout << "PUT response" << std::endl;


    response = client.del("localhost", path, headers);
    file = fopen("Response/delete_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "DELETE response:\n%s\n", response.c_str());
        fclose(file);
    }
    std::cout << "DELETE response" << std::endl;


    response = client.connect(host, path, headers);
    file = fopen("Response/connect_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "CONNECT response:\n%s\n", response.c_str());
        fclose(file);
    }
    std::cout << "CONNECT response" << std::endl;


    response = client.options(host, path, headers, "Origin: http://example.com");
    file = fopen("Response/options_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "OPTIONS response:\n%s\n", response.c_str());
        fclose(file);
    }
    std::cout << "OPTIONS response" << std::endl;


    response = client.trace("localhost", path, headers);
    file = fopen("Response/trace_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "TRACE response:\n%s\n", response.c_str());
        fclose(file);
    }
    std::cout << "TRACE response" << std::endl;
}


int main() 
{
    std::string host = "example.com";

    std::cout << "Testing HttpClient\n";
    HttpClient httpClient;

    httpClient.get_cache_control().addDirective("max-age", "3600");
    httpClient.get_cookie_control().addCookie("sessionid", "abc123");

    testHttpMethods(httpClient, host);
    std::cout << "Testing finished\n";

    // std::cout << "\nTesting HttpsClient\n";
    // HttpsClient httpsClient;
    // testHttpMethods(httpsClient, host);
    // std::cout << "Testing finished\n";

    // std::cout << "\nTesting SocketConnection\n";
    // testSocketConnection();
    // std::cout << "Testing finished\n";

    return 0;
}
