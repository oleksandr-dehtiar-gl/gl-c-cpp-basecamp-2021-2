#include "mouselocation.h"

MouseLocation::MouseLocation()
{

}

MouseLocation::MouseLocation(int x, int y)
{
    mouseX = x;
    mouseY = y;
}

bool operator==(const MouseLocation& left, const MouseLocation& right)
{
    return left.mouseX == right.mouseX &&
            left.mouseY == right.mouseY;
}
