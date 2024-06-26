#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <filesystem>
#include <sstream>

#include "HttpsClient.h"
#include "CacheControl.h"
#include "CookieControl.h"

namespace fs = std::filesystem;

void printFilesContentInDirectory()
{
    std::ifstream file("files.txt", std::ios::in);
    if (!file)
    {
        std::cerr << "Failed to open files.txt" << std::endl;
        return;
    }
    std::string filename;
    while (file >> filename)
    {
        std::string my_path = "Cache/" + filename;
        std::ifstream file2(my_path, std::ios::in);
        if (file2)
        {
            std::string buffer;
            while (std::getline(file2, buffer))
            {
                std::cout << buffer << std::endl;
            }
            file2.close();
        }
    }
    file.close();
}

std::vector<std::string> readFiles(const std::string &filename)
{
    std::vector<std::string> files;
    std::ifstream infile(filename);
    if (!infile)
    {
        std::cerr << "Failed to open " << filename << std::endl;
        return files;
    }

    std::string file;
    while (std::getline(infile, file))
    {
        files.push_back(file);
        std::cout << file;
    }

    return files;
}

bool request_http(std::string request_type, std::string host, bool use_cache, std::string subdomain, std::string body)
{
    HttpClient client;
    if (use_cache)
    {
        client.get_cache_control().setUseCache(true);
    }

    client.get_cookie_control().addCookie("sessionid", "abc123");

    std::string response;
    std::map<std::string, std::string> headers = {
        {"User-Agent", "HttpClient/1.0"},
        {"Cache-Control", client.get_cache_control().isUsingCache() ? "max-age=3600" : "no-cache"},
        {"Cookie", client.get_cookie_control().getCookieHeader()}};
    if (request_type == "GET")
    {
        std::vector<std::string> files = readFiles("files.txt");
        for (const std::string &file : files)
        {
            std::string filename = "Cache/" + file;
            std::ofstream outfile(filename);
            std::string url = "http://" + host + "/" + file;
            response = client.get(host, url, headers);
            if (strstr(response.c_str(), "404") == NULL && strstr(response.c_str(), "Not Found") == NULL)
            {
                outfile << response;
                if (file == "index.html")
                    std::cout << response << std::endl;
            }
            outfile.close();
        }
    }
    else if (request_type == "POST")
    {
        headers["Content-Type"] = "application/x-www-form-urlencoded";
        if (subdomain == "wordlist")
        {
            std::ifstream infile("subdomains.txt");
            if (!infile)
            {
                std::cerr << "Failed to open subdomains.txt" << std::endl;
                return 1;
            }

            std::string subdomain;
            while (std::getline(infile, subdomain))
            {
                if (body.find("wordlist") != std::string::npos)
                {
                    std::ifstream infile2("passwords.txt");
                    if (!infile2)
                    {
                        std::cerr << "Failed to open passwords.txt" << std::endl;
                        return 1;
                    }
                    std::string password;
                    while (std::getline(infile2, password))
                    {
                        std::string modified_body = body;
                        std::size_t pos = modified_body.find("password=wordlist");
                        if (pos != std::string::npos)
                        {
                            modified_body.replace(pos, std::string("password=wordlist").length(), "password=" + password);
                        }
                        subdomain = "/" + subdomain;
                        std::string response = client.post(host, subdomain, headers, modified_body);
                        if (response.find("successful") != std::string::npos)
                        {
                            std::cout << "Response from " << host << " with the subdomain: " << subdomain << " and password: " << password << ":\n"
                                      << response << std::endl;
                            return 0;
                        }
                    }
                }
                else
                {
                    subdomain = "/" + subdomain;
                    std::string response = client.post(host, subdomain, headers, body);
                    if (response.find("successful") != std::string::npos)
                    {
                        std::cout << "Response from " << host << " with the subdomain: " << subdomain << ":\n"
                                  << response << std::endl;
                        return 0;
                    }
                }
            }
        }
        else
        {
            if (body.find("wordlist") != std::string::npos)
            {
                std::ifstream infile2("passwords.txt");
                if (!infile2)
                {
                    std::cerr << "Failed to open passwords.txt" << std::endl;
                    return 1;
                }
                std::string password;
                while (std::getline(infile2, password))
                {
                    std::string modified_body = body;
                    std::size_t pos = modified_body.find("password=wordlist");
                    if (pos != std::string::npos)
                    {
                        modified_body.replace(pos, std::string("password=wordlist").length(), "password=" + password);
                    }
                    std::string response = client.post(host, subdomain, headers, modified_body);
                    if (response.find("successful") != std::string::npos)
                    {
                        std::cout << "Response from " << host << " with the subdomain: " << subdomain << " and password: " << password << ":\n"
                                  << response << std::endl;
                        return 0;
                    }
                }
            }
            else
            {
                std::string response = client.post(host, subdomain, headers, body);
                if (response.find("successful") != std::string::npos)
                {
                    std::cout << "Response from " << host << " with the subdomain: " << subdomain << ":\n"
                              << response << std::endl;
                    return 0;
                }
            }
        }
    }
    else if (request_type == "HEAD")
    {
        response = client.head(host, "/", headers);
    }
    else if (request_type == "PUT")
    {
        response = client.put(host, "/", headers, "<p>New File</p>");
    }
    else if (request_type == "DELETE")
    {
        response = client.del(host, "/", headers);
    }
    else if (request_type == "CONNECT")
    {
        response = client.connect(host, "/", headers);
    }
    else if (request_type == "TRACE")
    {
        response = client.trace(host, "/", headers);
    }
    else
    {
        std::cerr << "Unsupported request type: " << request_type << std::endl;
        return 1;
    }
    std::cout << response << std::endl;
    return 0;
}

bool request_https(std::string request_type, std::string host, bool use_cache, std::string subdomain, std::string body)
{
    HttpsClient client;
    if (use_cache)
    {
        client.get_cache_control().setUseCache(true);
    }

    client.addCookie("sessionid", "abc123");

    std::string response;
    std::map<std::string, std::string> headers = {
        {"User-Agent", "HttpClient/1.0"},
        {"Cache-Control", client.get_cache_control().isUsingCache() ? "max-age=3600" : "no-cache"},
        {"Cookie", client.get_cookie_control().getCookieHeader()}};

    if (request_type == "GET")
    {
        std::vector<std::string> files = readFiles("files.txt");
        for (const std::string &file : files)
        {
            std::string filename = "Cache/" + file;
            std::ofstream outfile(filename);
            std::string url = "https://" + host + "/" + file;
            response = client.get(host, url, headers);
            if (strstr(response.c_str(), "404") == NULL && strstr(response.c_str(), "Not Found") == NULL)
            {
                outfile << response;
                if (file == "index.html")
                    std::cout << response << std::endl;
            }
            outfile.close();
        }
    }
    else if (request_type == "POST")
    {
        headers["Content-Type"] = "application/x-www-form-urlencoded";
        if (subdomain == "wordlist")
        {
            std::ifstream infile("subdomains.txt");
            if (!infile)
            {
                std::cerr << "Failed to open subdomains.txt" << std::endl;
                return 1;
            }

            std::string subdomain;
            while (std::getline(infile, subdomain))
            {
                if (body.find("wordlist") != std::string::npos)
                {
                    std::ifstream infile2("passwords.txt");
                    if (!infile2)
                    {
                        std::cerr << "Failed to open passwords.txt" << std::endl;
                        return 1;
                    }
                    std::string password;
                    while (std::getline(infile2, password))
                    {
                        std::string modified_body = body;
                        std::size_t pos = modified_body.find("password=wordlist");
                        if (pos != std::string::npos)
                        {
                            modified_body.replace(pos, std::string("password=wordlist").length(), "password=" + password);
                        }
                        subdomain = "/" + subdomain;
                        std::string response = client.post(host, subdomain, headers, modified_body);
                        if (response.find("successful") != std::string::npos)
                        {
                            std::cout << "Response from " << host << " with the subdomain: " << subdomain << " and password: " << password << ":\n"
                                      << response << std::endl;
                            return 0;
                        }
                    }
                }
                else
                {
                    subdomain = "/" + subdomain;
                    std::string response = client.post(host, subdomain, headers, body);
                    if (response.find("successful") != std::string::npos)
                    {
                        std::cout << "Response from " << host << " with the subdomain: " << subdomain << ":\n"
                                  << response << std::endl;
                        return 0;
                    }
                }
            }
        }
        else
        {
            if (body.find("wordlist") != std::string::npos)
            {
                std::ifstream infile2("passwords.txt");
                if (!infile2)
                {
                    std::cerr << "Failed to open passwords.txt" << std::endl;
                    return 1;
                }
                std::string password;
                while (std::getline(infile2, password))
                {
                    std::string modified_body = body;
                    std::size_t pos = modified_body.find("password=wordlist");
                    if (pos != std::string::npos)
                    {
                        modified_body.replace(pos, std::string("password=wordlist").length(), "password=" + password);
                    }
                    std::string response = client.post(host, subdomain, headers, modified_body);
                    if (response.find("successful") != std::string::npos)
                    {
                        std::cout << "Response from " << host << " with the subdomain: " << subdomain << " and password: " << password << ":\n"
                                  << response << std::endl;
                        return 0;
                    }
                }
            }
            else
            {
                std::string response = client.post(host, subdomain, headers, body);
                if (response.find("successful") != std::string::npos)
                {
                    std::cout << "Response from " << host << " with the subdomain: " << subdomain << ":\n"
                              << response << std::endl;
                    return 0;
                }
            }
        }
    }
    else if (request_type == "HEAD")
    {
        response = client.head(host, "/", headers);
    }
    else if (request_type == "PUT")
    {
        response = client.put(host, "/", headers, "<p>New File</p>");
    }
    else if (request_type == "DELETE")
    {
        response = client.del(host, "/", headers);
    }
    else if (request_type == "CONNECT")
    {
        response = client.connect(host, "/", headers);
    }
    else if (request_type == "TRACE")
    {
        response = client.trace(host, "/", headers);
    }
    else
    {
        std::cerr << "Unsupported request type: " << request_type << std::endl;
        return 1;
    }
    std::cout << response << std::endl;
    return 0;
}



int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        std::cerr << "Usage: " << argv[0] << " <request_type> <host> <use_cache>\n";
        return 1;
    }
    std::string protocol = argv[1];

    if (protocol == "http")
    {
        request_http(argv[2], argv[3], std::stoi(argv[4]), argv[5], argv[6]);
    }
    else if (protocol == "https")
    {
        request_https(argv[2], argv[3], std::stoi(argv[4]), argv[5], argv[6]);
    }
    else
    {
        std::cerr << "Unsupported protocol: " << protocol << std::endl;
        return 1;
    }

    return 0;
}
