#include "logicelement.h"
#include <assert.h>
LogicElement::LogicElement(int input_amount)
{
    assert(input_amount > 0 && input_amount <= 8);
    m_inputs.resize(input_amount);
    std::fill(m_inputs.begin(), m_inputs.end(), false);

}

LogicElement::~LogicElement()
{}


bool LogicElement::getOutput() const
{
    return m_output;
}


void LogicElement::updateLogicHelper(bool inp, ElementType type, int offset)
{
    if(offset >= m_inputs.size())
    {
        return;
    }
    switch (type)
    {
    case ElementType::AND:

        if(!m_output)
        {
            return;
        }
        m_output = inp && m_inputs[offset];
        updateLogicHelper(m_output, ElementType::AND, offset + 1);
        break;

    case ElementType::NAND:

        updateLogicHelper(inp, ElementType::AND, offset);
        m_output = !m_output;
        break;

    case ElementType::NOR:
        updateLogicHelper(inp, ElementType::AND, offset);
        m_output = !m_output;
        break;

    case ElementType::NOT:
        m_output = !inp;
        break;
    case ElementType::OR:

        if(m_output)
        {
            return;
        }
        m_output = inp || m_inputs[offset];
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
