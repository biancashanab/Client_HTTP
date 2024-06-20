#include "CookieControl.h"

void CookieControl::addCookie(const std::string& name, const std::string& value) 
{
    cookies[name] = value;
}

std::string CookieControl::getCookie(const std::string& name) const 
{
    auto it = cookies.find(name);
    if (it != cookies.end()) 
    {
        return it->second;
    }
    return "";
}

std::string CookieControl::getCookieHeader() const 
{
    std::string cookieHeader;
    for (const auto& cookie : cookies) {
        if (!cookieHeader.empty()) {
            cookieHeader += "; ";
        }
        cookieHeader += cookie.first + "=" + cookie.second;
    }
    return cookieHeader;
}

void CookieControl::removeCookie(const std::string& name) 
{
    cookies.erase(name);
}
