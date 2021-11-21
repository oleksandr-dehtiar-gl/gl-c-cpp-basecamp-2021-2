#include "xorgate.h"

XorGate::XorGate(int input_amount) : LogicElement(input_amount)
{}


void XorGate::updateLogic()
{
    updateLogicHelper(m_inputs[0], ElementType::XOR);
}
