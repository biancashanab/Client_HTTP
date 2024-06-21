#pragma once
#include <string>

class CacheControl {
public:
    CacheControl(const std::string& filename) : useCache(false), maxAgeInSeconds(3600), cacheFilename(filename) {}
    ~CacheControl();

    void setUseCache(bool use);
    void addDirective(const std::string& directive, const std::string& value);
    std::string getDirective(const std::string& directive) const;
    std::string getCacheDirective() const;
    bool checkUseCache() const;
    std::string getFromCache(const std::string& method, const std::string& host, const std::string& path) const;
    void saveToCache(const std::string& method, const std::string& host, const std::string& path, const std::string& response);

private:
    bool useCache;
    int maxAgeInSeconds;
    std::map<std::string, std::string> cacheDirectives;
    std::string cacheFilename;
    std::string generateKey(const std::string& method, const std::string& host, const std::string& path) const;
};
