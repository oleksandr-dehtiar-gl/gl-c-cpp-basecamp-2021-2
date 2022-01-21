#ifndef NOTGATE_H
#define NOTGATE_H

#include "../logicelement.h"

class NotGate : public LogicElement
{
public:
    NotGate(int input_amount = 1);
    void updateLogic() override;
};

#endif // NOTGATE_H
