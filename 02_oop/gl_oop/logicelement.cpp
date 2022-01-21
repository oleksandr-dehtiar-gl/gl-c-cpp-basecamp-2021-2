#include "logicelement.h"
#include <assert.h>
#include <algorithm>
LogicElement::LogicElement(int input_amount)
{
    m_inputs.resize(input_amount);
    std::fill(m_inputs.begin(), m_inputs.end(), false);
}

LogicElement::~LogicElement()
{}


int8_t LogicElement::getOutput() const
{
    if(isValid())
    {
        return static_cast<int8_t>(m_output);
    }
    return -1;

}





void LogicElement::removePredecessor(uint8_t portNum)
{
    auto predecessorIt = m_predecessors.find(portNum);
    if(predecessorIt != m_predecessors.end())
    {

        auto successorIt = predecessorIt->second->m_successors.find(this);
        if((--successorIt->second) == 0)
        {
            predecessorIt->second->removeSuccessor(this);
        }
        m_predecessors.erase(portNum);

    }

}

void LogicElement::removeSuccessor(LogicElement *elm)
{
    m_successors.erase(elm);
}
void LogicElement::setSuccessor(LogicElement *elm)
{
    m_successors[elm]++;
}
void LogicElement::connectPredeccessor(LogicElement *elm, uint8_t portNum)
{
    m_predecessors[portNum] = elm;
    elm->setSuccessor(this);
}

int LogicElement::calculatePriority()
{
    if(m_beingVisited)
    {
        return 0;
    }
    if(m_priority != -1)
    {
        return m_priority;
    }
    m_beingVisited = true;
    int current_p = 0;
    for(auto it = m_successors.begin(); it != m_successors.end(); it++)
    {
        current_p = std::max(it->first->calculatePriority(), current_p);
    }
    m_priority = current_p + 1;
    m_beingVisited = false;
    return m_priority;
}
void LogicElement::resetPriority()
{
    m_priority = -1;
}
const int LogicElement::getPriority() const
{
    return m_priority;
}

bool LogicElement::isValid() const
{
    if(m_inputs.size() == m_predecessors.size())
    {
        for(auto predecessorsIt = m_predecessors.begin(); predecessorsIt != m_predecessors.end(); predecessorsIt++)
        {
            if(!predecessorsIt->second->isValid())
            {
                return false;
            }
        }
        return true;
    }
    return false;
}



void LogicElement::setInputValues()
{
    for(auto it = m_predecessors.begin(); it != m_predecessors.end(); it++)
    {
        m_inputs[it->first] = it->second->getOutput();
    }
}

void LogicElement::updateLogicHelper(bool inp, ElementType type, int offset)
{
    if(offset >= m_inputs.size() || !isValid())
    {
        return;
    }
    switch (type)
    {
    case ElementType::AND:
        m_output = inp && m_inputs[offset];

        if(!m_output)
        {
            return;
        }
        updateLogicHelper(m_output, ElementType::AND, offset + 1);
        break;

    case ElementType::NAND:

        updateLogicHelper(inp, ElementType::AND, offset);
        m_output = !m_output;
        break;

    case ElementType::NOR:
        updateLogicHelper(inp, ElementType::OR, offset);
        m_output = !m_output;
        break;

    case ElementType::NOT:
        m_output = !inp;
        break;
    case ElementType::OR:


        m_output = inp || m_inputs[offset];

        if(m_output)
        {
            return;
        }
        updateLogicHelper(m_output, ElementType::OR, offset + 1);
        break;

    case ElementType::XOR:

        m_output = !(inp == m_inputs[offset]);
        updateLogicHelper(m_output, ElementType::XOR, offset + 1);
        break;

    case ElementType::DEFAULT:
    default:
        m_output = false;
        break;
    }
}
