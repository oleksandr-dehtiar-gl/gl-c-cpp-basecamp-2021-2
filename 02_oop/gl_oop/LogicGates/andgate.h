#ifndef ANDGATE_H
#define ANDGATE_H

#include <assert.h>
#include "../logicelement.h"

class AndGate : public LogicElement
{
public:
    AndGate(int inputAmount);
    void updateLogic() override;

};

#endif // ANDGATE_H
