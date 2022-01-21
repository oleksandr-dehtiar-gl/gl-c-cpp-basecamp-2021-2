#ifdef _WIN32

#define UNICODE
#define _CRT_SECURE_NO_WARNING
#include <TlHelp32.h>

#else
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#endif

#ifdef _WIN32
    typedef HANDLE ProcessHandle;
#else   
    typedef pid_t ProcessHandle;
#endif
