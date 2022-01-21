#include "notgate.h"

NotGate::NotGate(int input_amount) : LogicElement(input_amount)
{}

void NotGate::updateLogic()
{
    updateLogicHelper(m_inputs[0], ElementType::NOT, 0);
}
