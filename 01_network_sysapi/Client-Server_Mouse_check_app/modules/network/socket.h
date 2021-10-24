#ifndef SOCKET_H
#define SOCKET_H

#ifdef linux

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

class Socket
{
public:
    Socket();
    Socket(const int domain, const int type, const int protocol);
    int bind(const struct sockaddr *address, const int address_length) const;
    int listen(const int backlog) const;
    int accept(void *client_address, socklen_t *address_length) const;
    int connect(const struct sockaddr *server_address, const int address_length) const;
    int send(const void *message, const int length, const int flags) const;
    int send_all(char *message, const int length, const int flags) const;
    int receive(void *buf, const int length, const int flags) const;
    int receive_all(void *buf, const int length, const int flags) const;
    int close() const;
    int shutdown(const int how) const;
    int get_socket_descriptor() const;
    void set_socket_descriptor(const int new_descriptor);
private:
    int socket_descriptor;
};

#endif // SOCKET_H
