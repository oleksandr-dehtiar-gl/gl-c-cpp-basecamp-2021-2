#include "andgate.h"

AndGate::AndGate(int inputAmount) : LogicElement(inputAmount)
{
    assert(inputAmount > 0 && inputAmount <= sizeof(char));
}

void AndGate::updateLogic()
{

    int accumulation = 0;
    for(int i = 0; i < m_input_amount; i++)
    {
        accumulation += (m_inputs >> i) & 1;
    }
    m_output = accumulation == m_input_amount;
}

bool AndGate::getOutput() const
{
    return true;
}
