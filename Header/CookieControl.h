#ifndef COOKIECONTROL_H
#define COOKIECONTROL_H

#include <string>
#include <map>

class CookieControl 
{
public:
    CookieControl() = default;
    ~CookieControl() = default;

    void addCookie(const std::string& name, const std::string& value);
    void removeCookie(const std::string& name);

    std::string getCookie(const std::string& name) const;
    std::string getCookieHeader() const;

private:
    std::map<std::string, std::string> cookies;
};

#endif // COOKIECONTROL_H
