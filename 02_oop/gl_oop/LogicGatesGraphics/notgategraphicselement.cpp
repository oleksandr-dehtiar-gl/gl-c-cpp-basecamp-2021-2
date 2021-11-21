#include "notgategraphicselement.h"

NotGateGraphicsElement::NotGateGraphicsElement(QGraphicsItem * parent) : GraphicsElement(parent)
{
    setType(ElementType::NOT);
}
