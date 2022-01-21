#include "gndgraphicselement.h"

GNDGRaphicsElement::GNDGRaphicsElement(QGraphicsItem * parent) : GraphicsElement(parent)
{
    setType(ElementType::GND);
    addOutput(false);

}
