#ifndef LOGICINPUT_H
#define LOGICINPUT_H
#include "../logicelement.h"

class LogicInput : public LogicElement
{
public:
    LogicInput(bool isVCC = false);
    void updateLogic() override;

};

#endif // LOGICINPUT_H
