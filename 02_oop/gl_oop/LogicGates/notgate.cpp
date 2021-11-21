#include "notgate.h"

NotGate::NotGate() : LogicElement(1)
{}

void NotGate::updateLogic()
{
    m_output = (m_inputs & 1);
}
