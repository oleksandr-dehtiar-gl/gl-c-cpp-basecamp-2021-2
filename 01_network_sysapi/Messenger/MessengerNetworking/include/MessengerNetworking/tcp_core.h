#pragma once
#ifdef _WIN32 
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501  /* Windows XP. */
  #endif
  #include <winsock2.h>
  #include <ws2tcpip.h>
#else
  /* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */
#endif
//additional libraries add here
#include <string>
#include <iostream>
#include <exception>
namespace TCPCORE{
class tcpCore{
  protected:
    WSADATA wsData;
    WORD ver;
    int conPort = 7300;
    int wsOk;
    SOCKET sock;
    sockaddr_in hint;

    virtual void bind() = 0;
    int initializeWinsock();
    decltype(INVALID_SOCKET) createSocket();
    virtual void connect() = 0;
};
}