#include "socket.h"

Socket::Socket()
{
    socket_descriptor = -1;
}

Socket::Socket(int domain, int type, int protocol)
{
    socket_descriptor = socket(domain, type, protocol);
}

int Socket::bind(const struct sockaddr *address, const int address_length) const
{
    return ::bind(socket_descriptor, address, address_length);
}

int Socket::listen(const int backlog) const
{
    return ::listen(socket_descriptor, backlog);
}

int Socket::accept(void *client_address, socklen_t *address_length) const
{
    return ::accept(socket_descriptor, (struct sockaddr*)client_address, address_length);
}

int Socket::connect(const struct sockaddr *server_address, const int address_length) const
{
    return ::connect(socket_descriptor, server_address, address_length);
}

int Socket::send(const void *message, const int length, const int flags) const
{
    return ::send(socket_descriptor, message, length, flags);
}

int Socket::send_all(char *message, const int length, const int flags) const
{
    int totalSentBytesNumber = 0;
    int lastSentBytesNumber;

    while(totalSentBytesNumber < length)
    {
        lastSentBytesNumber = send(message + totalSentBytesNumber, length - totalSentBytesNumber, flags);
        if(lastSentBytesNumber == -1)
            break;
        totalSentBytesNumber += lastSentBytesNumber;
    }

    return (lastSentBytesNumber == -1 ? -1 : totalSentBytesNumber);
}

int Socket::receive(void *buffer, const int length, const int flags) const
{
    return ::recv(socket_descriptor, buffer, length, flags);
}

int Socket::receive_all(void *buffer, const int length, const int flags) const
{
    int bytesReceived = 0;
    while(bytesReceived < length)
    {
        bytesReceived = receive(buffer, length, flags);
        if(bytesReceived == 0)
            break;
    }
    return bytesReceived;
}

int Socket::close() const
{
    return ::close(socket_descriptor);
}

int Socket::shutdown(const int how) const
{
    return ::shutdown(socket_descriptor, how);
}

int Socket::get_socket_descriptor() const
{
    return socket_descriptor;
}

void Socket::set_socket_descriptor(const int new_descriptor)
{
    socket_descriptor = new_descriptor;
}


