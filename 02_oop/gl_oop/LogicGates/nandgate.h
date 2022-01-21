#ifndef NANDGATE_H
#define NANDGATE_H

#include "../logicelement.h"

class NandGate: public LogicElement
{
public:
    NandGate(int input_amount = 2);
    void updateLogic() override;
};

#endif // NANDGATE_H
