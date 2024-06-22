#include "CacheControl.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

CacheControl::CacheControl(const std::string& cacheDirectory) : cacheDirectory(cacheDirectory), useCache(false) 
{
    if (!std::filesystem::exists(cacheDirectory)) {
        std::filesystem::create_directory(cacheDirectory);
    }
}

CacheControl::~CacheControl() { }

void CacheControl::setUseCache(bool useCache) 
{
    this->useCache = useCache;
}

bool CacheControl::isUsingCache() const 
{
    return useCache;
}

bool CacheControl::checkCacheExists(const std::string& host) 
{
    return std::filesystem::exists(getCacheFilename(host));
}


void CacheControl::saveCache(const std::string& host, const std::string& response) 
{
    if (!useCache) {
        return;
    }

    std::ofstream outfile(getCacheFilename(host), std::ios::app);
    if (!outfile) {
        std::cerr << "Error opening cache file for server: " << host << std::endl;
        return;
    }
    outfile << response;
    outfile.close();
}

std::string CacheControl::getCacheFilename(const std::string& host) const 
{
    return cacheDirectory + "/" + host + ".html";
}

std::string CacheControl::loadCache(const std::string& host) 
{
    std::ifstream infile(getCacheFilename(host));
    if (!infile) {
        return "";
    }

    std::ostringstream buffer;
    buffer << infile.rdbuf();
    return buffer.str();
}