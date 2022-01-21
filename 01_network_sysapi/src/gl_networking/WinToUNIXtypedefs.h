
#ifndef _WIN32
#include <unistd.h>
#include <cstdint>
static const int INVALID_SOCKET = ~0;
static const int FALSE = 0;
static const int TRUE = 1; 
typedef int BOOL;
typedef uint32_t ULONG;
static const int SOCKET_ERROR = -1;
#ifndef WSAGetLastError
        #define WSAGetLastError() errno
#endif
#ifndef closesocket
        #define closesocket(fd) close(fd)
#endif

#endif
