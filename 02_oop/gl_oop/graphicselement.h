#ifndef GRAPHICSELEMENT_H
#define GRAPHICSELEMENT_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <memory>
#include "elementtype.h"
#include "LogicGatesGraphics/port.h"

class GraphicsElement : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsElement(QGraphicsItem* parent);
    virtual ~GraphicsElement();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    ElementType getType() const;
    void setType(ElementType type);


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void addInputs(int inputAmount = 2);
    void addOutput();
    std::unique_ptr<QPixmap> m_pixmap;
    ElementType m_type;

    std::vector<Port*> m_inputs;
    Port * m_output = nullptr;



private:
    std::vector<std::string> m_type_strs = {"Default", "AND", "NAND", "NOR", "NOT", "OR", "XOR"};


};

#endif // GRAPHICSELEMENT_H
