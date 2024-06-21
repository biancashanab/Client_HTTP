#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include <string>

class SocketConnection 
{
public:
    SocketConnection();
    virtual ~SocketConnection();

    void setTimeout(int seconds);
    void connect(const std::string& host, int port);
    void send(const std::string& data);
    std::string receive();
    void close();

protected:
    int sock;
};

#endif // SOCKETCONNECTION_H

