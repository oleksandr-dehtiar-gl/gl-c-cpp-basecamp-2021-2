#ifndef MouseTracker_H
#define MouseTracker_H

#include "mouselocation.h"

class MouseTracker
{
public:
    MouseTracker();
    ~MouseTracker();
    MouseLocation getMouseLocation() const;
    bool checkMouseActivity();
private:
    MouseLocation* previousLocation;
};

#endif // MouseTracker_H
