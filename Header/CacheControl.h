#ifndef CACHECONTROL_H
#define CACHECONTROL_H

#include <string>


class CacheControl {
public:
    CacheControl(const std::string& cacheDirectory);
    ~CacheControl();

    
    bool isUsingCache() const;
    bool checkCacheExists(const std::string& host);
    void setUseCache(bool useCache);
    void saveCache(const std::string& host, const std::string& response);
    std::string loadCache(const std::string& host);
    std::string getCacheFilename(const std::string& host) const;

private:

    std::string cacheDirectory;
    bool useCache;
};

#endif // CACHECONTROL_H

