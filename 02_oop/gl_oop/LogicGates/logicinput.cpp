#include "logicinput.h"

LogicInput::LogicInput(bool isVCC): LogicElement(0)
{
    m_output = isVCC;
}

void LogicInput::updateLogic()
{

}
