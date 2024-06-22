#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cctype>   

#include "HttpClient.h"
#include "HttpsClient.h"
#include "CacheControl.h"
#include "CookieControl.h"


int main(int argc, char* argv[]) 
{
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <REQUEST_TYPE> <HOST> <USE_CACHE>" << std::endl;
        return 1;
    }

    std::string request_type = argv[1];
    std::string host = argv[2];
    bool use_cache = std::stoi(argv[3]);

    HttpClient client;

    if(use_cache) {
        client.get_cache_control().setUseCache(true);
    //    client.get_cache_control().addDirective("max-age", "3600");
    }

    client.get_cookie_control().addCookie("sessionid", "abc123");

    std::string response;
    std::map<std::string, std::string> headers = {
        {"User-Agent", "HttpClient/1.0"},
        {"Cache-Control", client.get_cache_control().isUsingCache() ? "max-age=3600" : "no-cache"},
        {"Cookie", client.get_cookie_control().getCookieHeader()}
    };

     std::transform(request_type.begin(), request_type.end(), request_type.begin(),
                   [](unsigned char c){ return std::toupper(c); });


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
