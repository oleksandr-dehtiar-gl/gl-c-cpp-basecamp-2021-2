#include "nandgategraphicselement.h"

NandGateGraphicsElement::NandGateGraphicsElement(QGraphicsItem * parent) : GraphicsElement(parent)
{
    setType(ElementType::NAND);
    addInputs();
    addOutput();
}
