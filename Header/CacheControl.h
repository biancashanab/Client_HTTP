#pragma once
#include <map>
#include <string>

class CacheControl 
{
public:
    CacheControl();
    void addDirective(const std::string& directive, const std::string& value);
    std::string getDirective(const std::string& directive);

private:
    std::map<std::string, std::string> cacheDirectives;

};
