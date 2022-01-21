#include "orgategraphicselement.h"

OrGateGraphicsElement::OrGateGraphicsElement(QGraphicsItem * parent) : GraphicsElement(parent)
{
    setType(ElementType::OR);
    addInputs();
    addOutput();
}
