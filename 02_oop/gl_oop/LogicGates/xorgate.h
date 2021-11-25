#ifndef XORGATE_H
#define XORGATE_H

#include "../logicelement.h"
class XorGate : public LogicElement
{
public:
    XorGate(int input_amount = 2);
    void updateLogic() override;
};

#endif // XORGATE_H
