#include "xorgategraphicselement.h"

XorGateGraphicsElement::XorGateGraphicsElement(QGraphicsItem* parent) : GraphicsElement(parent)
{
    setType(ElementType::XOR);
}
