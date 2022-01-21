#ifdef linux
#include <X11/Xlib.h>
#include <unistd.h>
#include <stdint.h>
#endif

#include "mousetracker.h"

MouseTracker::MouseTracker()
{
    previousLocation = new MouseLocation(0, 0);
}

MouseTracker::~MouseTracker()
{
    delete previousLocation;
}

bool MouseTracker::checkMouseActivity()
{
    MouseLocation currentLocation = getMouseLocation();
    if(currentLocation == *previousLocation)
    {
        return 0;
    }

    *previousLocation = currentLocation;
    return 1;
}

#ifdef linux
MouseLocation MouseTracker::getMouseLocation() const
{
    static Display *display = XOpenDisplay(0);

    static Window root = XDefaultRootWindow(display);
    Window root_return;
    Window child_return;
    int root_x_return;
    int root_y_return;
    int win_x_return;
    int win_y_return;
    uint32_t mask_return;

    while (true)
    {
        if (::XQueryPointer(display, root, &root_return, &child_return, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return))
        {
            return MouseLocation(root_x_return, root_y_return);
        }
    }
    return MouseLocation(-1, -1);
}
#endif
