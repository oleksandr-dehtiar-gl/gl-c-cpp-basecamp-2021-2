#include "norgategraphicselement.h"

NorGateGraphicsElement::NorGateGraphicsElement(QGraphicsItem * parent) : GraphicsElement(parent)
{
    setType(ElementType::NOR);
    addInputs();
    addOutput();
}
