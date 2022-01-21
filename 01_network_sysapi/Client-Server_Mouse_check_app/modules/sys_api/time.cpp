#ifdef linux
#include <unistd.h>

void sleep(int seconds)
{
    usleep(seconds * 1'000'000);
}

#endif
