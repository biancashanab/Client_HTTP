#include "CacheControl.h"

CacheControl::CacheControl() {}

void CacheControl::addDirective(const std::string& directive, const std::string& value) {
    cacheDirectives[directive] = value;
}

std::string CacheControl::getDirective(const std::string& directive) 
{
    if (cacheDirectives.find(directive) != cacheDirectives.end()) 
    {
        return cacheDirectives[directive];
    }
    return "";
}
