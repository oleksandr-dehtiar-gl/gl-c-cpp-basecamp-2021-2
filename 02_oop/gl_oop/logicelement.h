#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H
#include <vector>
#include <unordered_map>
#include "elementtype.h"




class LogicElement
{
public:

    LogicElement(int input_amount);
    virtual ~LogicElement();
    virtual void updateLogic() = 0;
    int8_t getOutput() const;
    int calculatePriority();
    const int getPriority() const;
    void connectPredeccessor(LogicElement * elm, uint8_t portNum);
    void removePredecessor(uint8_t portNum);
    void removeSuccessor(LogicElement * elm);
    void setSuccessor(LogicElement * elm);
    void setInputValues();
    void resetPriority();


protected:

    void updateLogicHelper(bool inp, ElementType type, int offset = 1);
    bool isValid() const;

protected:

    bool m_output;
    std::vector<bool> m_inputs;
    std::unordered_map<uint8_t, LogicElement*> m_predecessors;
    std::unordered_map<LogicElement*, uint8_t> m_successors;
    int m_priority = -1;
    bool m_beingVisited = false;

};

#endif // LOGICELEMENT_H
