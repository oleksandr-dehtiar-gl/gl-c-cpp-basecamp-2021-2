#include "andgate.h"

AndGate::AndGate(int input_amount) : LogicElement(input_amount)
{}

void AndGate::updateLogic()
{
    updateLogicHelper(m_inputs[0], ElementType::AND);
}

