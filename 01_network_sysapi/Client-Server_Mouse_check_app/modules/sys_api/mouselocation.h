#ifndef MOUSELOCATION_H
#define MOUSELOCATION_H


class MouseLocation
{
public:
    MouseLocation();
    MouseLocation(int x, int y);
private:
    int mouseX;
    int mouseY;
    friend bool operator==(const MouseLocation&, const MouseLocation&);
};

#endif // MOUSELOCATION_H
