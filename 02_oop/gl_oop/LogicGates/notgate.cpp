#include "notgate.h"

NotGate::NotGate() : LogicElement(1)
{}

void NotGate::updateLogic()
{
    updateLogicHelper(m_inputs[0], ElementType::NOT);
}
