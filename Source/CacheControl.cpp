#include "CacheControl.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio> 


 /*
void CacheControl::setUseCache(bool use)
{
    useCache = use;
}

void CacheControl::addDirective(const std::string& directive, const std::string& value)
{
    cacheDirectives[directive] = value;
}

std::string CacheControl::getDirective(const std::string& directive) const
{
    auto it = cacheDirectives.find(directive);
    if (it != cacheDirectives.end()) {
        return it->second;
    }
    return "";
}

std::string CacheControl::getCacheDirective() const
{
    if (useCache) {
        return "max-age=" + std::to_string(maxAgeInSeconds);
    } else {
        return "no-cache";
    }
}

bool CacheControl::checkUseCache() const
{
    return useCache;
}

std::string CacheControl::getFromCache(const std::string& method, const std::string& host, const std::string& path) const
{
    std::string key = method + "_" + host + "_" + path;
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }
    return "";
}

void CacheControl::saveToCache(const std::string& method, const std::string& host, const std::string& path, const std::string& response)
{
    std::string key = method + "_" + host + "_" + path;
    cache[key] = response;
}

*/


CacheControl::~CacheControl() 
{
    std::remove(cacheFilename.c_str());
}

void CacheControl::setUseCache(bool use)
{
    useCache = use;
}

void CacheControl::addDirective(const std::string& directive, const std::string& value) 
{
    cacheDirectives[directive] = value;
}

std::string CacheControl::getDirective(const std::string& directive) const 
{
    auto it = cacheDirectives.find(directive);
    if (it != cacheDirectives.end()) {
        return it->second;
    }
    return "";
}

std::string CacheControl::getCacheDirective() const 
{
    if (useCache) {
        return "max-age=" + std::to_string(maxAgeInSeconds);
    } else {
        return "no-cache";
    }
}

bool CacheControl::checkUseCache() const 
{
    return useCache;
}

std::string CacheControl::generateKey(const std::string& method, const std::string& host, const std::string& path) const 
{
    return method + "_" + host + "_" + path;
}

std::string CacheControl::getFromCache(const std::string& method, const std::string& host, const std::string& path) const 
{
    if (!useCache) {
        return "";
    }

    std::ifstream infile(cacheFilename);
    if (!infile) {
        std::cerr << "Error opening cache file: " << cacheFilename << std::endl;
        return "";
    }

    std::string key = generateKey(method, host, path);
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string fileKey, value;
        if (std::getline(iss, fileKey, '=') && std::getline(iss, value)) {
            if (fileKey == key) {
                return value;
            }
        }
    }

    return "";
}

void CacheControl::saveToCache(const std::string& method, const std::string& host, const std::string& path, const std::string& response) 
{
    if (!useCache) {
        return;
    }

    std::ofstream outfile(cacheFilename, std::ios_base::app); // Deschide fișierul în modul append
    if (!outfile) {
        std::cerr << "Error opening cache file: " << cacheFilename << std::endl;
        return;
    }

    std::string key = generateKey(method, host, path);
    outfile << key << "=" << response << std::endl;
}





