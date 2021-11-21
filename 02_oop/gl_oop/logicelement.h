#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H
#include <vector>
#include "elementtype.h"
class LogicElement
{
public:

    LogicElement(int input_amount);
    virtual ~LogicElement();
    virtual void updateLogic() = 0;
    virtual bool getOutput() const;



protected:
    bool m_output;
    std::vector<bool> m_inputs;
    void updateLogicHelper(bool inp, ElementType type, int offset = 1);

};

#endif // LOGICELEMENT_H
