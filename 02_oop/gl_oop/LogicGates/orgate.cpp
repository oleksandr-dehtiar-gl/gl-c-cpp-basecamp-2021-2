#include "orgate.h"


OrGate::OrGate(int input_amount) : LogicElement(input_amount)
{}

void OrGate::updateLogic()
{
    updateLogicHelper(m_inputs[0], ElementType::OR);
}


