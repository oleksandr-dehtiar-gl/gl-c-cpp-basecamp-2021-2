#ifndef ORGATE_H
#define ORGATE_H

#include "logicelement.h"

class OrGate : public LogicElement
{
public:
    OrGate(int input_amount);
    void updateLogic() override;
};

#endif // ORGATE_H
