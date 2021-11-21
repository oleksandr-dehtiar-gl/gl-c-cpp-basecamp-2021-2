#ifndef GRAPHICSELEMENT_H
#define GRAPHICSELEMENT_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <memory>
#include "elementtype.h"




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
    std::unique_ptr<QPixmap> m_pixmap;
    ElementType m_type;
private:
    std::vector<std::string> m_type_strs = {"Default", "AND", "NAND", "NOR", "NOR", "OR", "XOR"};
};

#endif // GRAPHICSELEMENT_H
