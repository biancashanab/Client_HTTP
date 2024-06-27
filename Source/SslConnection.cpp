#include "SslConnection.h"
#include <stdexcept>
#include <iostream>

SslConnection::SslConnection() : ssl(nullptr) 
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    const SSL_METHOD* method = SSLv23_client_method();
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        throw std::runtime_error("Unable to create SSL context");
    }
}

SslConnection::~SslConnection() {
    SSL_CTX_free(ctx);
}

void SslConnection::connect(const std::string& host, int port) 
{
    SocketConnection::connect(host, port); // Connect using TCP socket

    ssl = SSL_new(ctx);
    if (!ssl) {
        throw std::runtime_error("SSL object creation failed");
    }

    if (!SSL_set_fd(ssl, sock)) {
        throw std::runtime_error("SSL set fd failed");
    }

    if (SSL_connect(ssl) <= 0) {
        throw std::runtime_error("SSL connection failed");
    }
}

void SslConnection::send(const std::string& data) {
    SSL_write(ssl, data.c_str(), data.size());
}

std::string SslConnection::receive() 
{
    /*
    char buffer[4096];
    int bytes_received = SSL_read(ssl, buffer, sizeof(buffer));
    if (bytes_received > 0) {
        return std::string(buffer, bytes_received);
    } else {
        throw std::runtime_error("SSL read failed");
    }*/

    char buffer[4096];
    int bytes_received = SSL_read(ssl, buffer, sizeof(buffer));
    if (bytes_received > 0) {
        std::string response(buffer, bytes_received);
       std::cout << "Received: " << response << std::endl; // Apentru debug
        return response;
    } else {
        throw std::runtime_error("SSL read failed");
    }
}

void SslConnection::close() 
{
    if (ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        ssl = nullptr;
    }
    SocketConnection::close();
}

