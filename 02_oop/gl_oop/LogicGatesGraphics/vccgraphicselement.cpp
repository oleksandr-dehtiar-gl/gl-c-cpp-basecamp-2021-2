#include "vccgraphicselement.h"

VCCGraphicsElement::VCCGraphicsElement(QGraphicsItem * parent) : GraphicsElement(parent)
{
    setType(ElementType::VCC);
    addOutput(true);

}
