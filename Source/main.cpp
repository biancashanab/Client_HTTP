#include <iostream>
#include <fstream>
#include <map>

#include "HttpClient.h"
#include "HttpsClient.h"
#include "CacheControl.h"
#include "CookieControl.h"



/*
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


    response = client.put(host, path, headers, "<p>New File</p>");
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


    response = client.trace(host, path, headers);
    file = fopen("Response/trace_response.txt", "w");
    if (file != nullptr) {
        fprintf(file, "TRACE response:\n%s\n", response.c_str());
        fclose(file);
    }
    std::cout << "TRACE response" << std::endl;
}


int main() 
{
    std::string host = "172.16.44.183";
    std::cout << "Testing HttpClient\n";
    HttpClient httpClient;

    httpClient.get_cache_control().setUseCache(true);
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


*/



int main(int argc, char* argv[]) 
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <request_type> <host>" << std::endl;
        return 1;
    }

    std::string request_type = argv[1];
    std::string host = argv[2];

    HttpClient client;

    client.get_cache_control().setUseCache(true);
    client.get_cache_control().addDirective("max-age", "3600");
    client.get_cookie_control().addCookie("sessionid", "abc123");

    std::string response;
    std::map<std::string, std::string> headers = {
        {"User-Agent", "HttpClient/1.0"},
        {"Cache-Control", client.get_cache_control().getDirective("max-age")},
        {"Cookie", client.get_cookie_control().getCookieHeader()}
    };

    if (request_type == "GET") {
        response = client.get(host, "/", headers);
    } else if (request_type == "POST") {
        response = client.post(host, "/", headers, "Body of POST request");
    } else if (request_type == "HEAD") {
        response = client.head(host, "/", headers);
    } else if (request_type == "PUT") {
        response = client.put(host, "/", headers, "<p>New File</p>");
    } else if (request_type == "DELETE") {
        response = client.del(host, "/", headers);
    } else if (request_type == "CONNECT") {
        response = client.connect(host, "/", headers);
    } else if (request_type == "TRACE") {
        response = client.trace(host, "/", headers);
    } else {
        std::cerr << "Unsupported request type: " << request_type << std::endl;
        return 1;
    }

    std::cout << response << std::endl;

    return 0;
}
