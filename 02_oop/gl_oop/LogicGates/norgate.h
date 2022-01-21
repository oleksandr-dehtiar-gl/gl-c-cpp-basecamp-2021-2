#ifndef NORGATE_H
#define NORGATE_H

#include "../logicelement.h"

class NorGate : public LogicElement
{
public:
    NorGate(int input_amount = 2);
    void updateLogic() override;
};

#endif // NORGATE_H
