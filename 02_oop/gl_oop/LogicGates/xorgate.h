#ifndef XORGATE_H
#define XORGATE_H

#include "../logicelement.h"
class XorGate : public LogicElement
{
public:
    XorGate(int input_amount);
    void updateLogic() override;
};

#endif // XORGATE_H
