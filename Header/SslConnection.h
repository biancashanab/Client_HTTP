#ifndef SSLCONNECTION_H
#define SSLCONNECTION_H

#include "SocketConnection.h"
#include <openssl/ssl.h>
#include <openssl/err.h>

class SslConnection : public SocketConnection
{
public:
    SslConnection();
    virtual ~SslConnection();

    void connect(const std::string& host, int port) ;
    void send(const std::string& data) ;
    std::string receive() ;
    void close() ;

private:
    SSL_CTX* ctx;
    SSL* ssl;
};

#endif // SSLCONNECTION_H

