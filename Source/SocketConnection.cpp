#include "SocketConnection.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <netdb.h>

SocketConnection::SocketConnection() : sock(-1) 
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        throw std::runtime_error("Socket creation failed");
    }
}

SocketConnection::~SocketConnection() {
    close();
}

void SocketConnection::connect(const std::string& host, int port) 
{
    struct sockaddr_in server_addr;
    struct hostent* server;

    server = gethostbyname(host.c_str());
    if (server == NULL) {
        throw std::runtime_error("Host not found");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    server_addr.sin_port = htons(port);

    if (::connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("Connection failed");
    }
}

void SocketConnection::send(const std::string& data) 
{
    if (::send(sock, data.c_str(), data.size(), 0) < 0) {
        throw std::runtime_error("Send failed");
    }
}

std::string SocketConnection::receive()
{
    char buffer[4096];
    int bytes_received = ::recv(sock, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        return std::string(buffer, bytes_received);
    } else if (bytes_received == 0) {
        throw std::runtime_error("Connection closed by peer");
    } else {
        throw std::runtime_error("Receive failed");
    }
}

void SocketConnection::close() 
{
    if (sock != -1) {
        ::close(sock);
        sock = -1;
    }
}

void SocketConnection::setTimeout(int seconds) 
{
    struct timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;
    
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv)) < 0) {
        throw std::runtime_error("Set receive timeout failed");
    }

    if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof(tv)) < 0) {
        throw std::runtime_error("Set send timeout failed");
    }
}