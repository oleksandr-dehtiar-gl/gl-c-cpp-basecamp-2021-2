#include "andgategraphicselement.h"

AndGateGraphicsElement::AndGateGraphicsElement(QGraphicsItem* parent) : GraphicsElement(parent)
{
    setType(ElementType::AND);
    addInputs();
    addOutput();
}
