#include "norgate.h"

NorGate::NorGate(int input_amount) : LogicElement(input_amount)
{}

void NorGate::updateLogic()
{
   updateLogicHelper(m_inputs[0], ElementType::NOR);
}
