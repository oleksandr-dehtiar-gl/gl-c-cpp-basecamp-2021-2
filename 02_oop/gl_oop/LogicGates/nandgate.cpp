#include "nandgate.h"

NandGate::NandGate(int input_amount) : LogicElement(input_amount)
{}

void NandGate::updateLogic()
{
    updateLogicHelper(m_inputs[0], ElementType::NAND);
}
