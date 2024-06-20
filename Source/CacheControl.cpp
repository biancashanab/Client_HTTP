#include "CacheControl.h"


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

bool CacheControl::getUseCache() const
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