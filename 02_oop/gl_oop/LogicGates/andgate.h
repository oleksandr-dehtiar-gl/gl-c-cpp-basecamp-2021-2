#ifndef ANDGATE_H
#define ANDGATE_H


#include "../logicelement.h"

class AndGate : public LogicElement
{
public:
    AndGate(int inputAmount = 2);
    void updateLogic() override;

};

#endif // ANDGATE_H
