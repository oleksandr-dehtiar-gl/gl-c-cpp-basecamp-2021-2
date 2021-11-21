#include "graphicselement.h"
#include "scene.h"
#include <QApplication>
#include <QtMath>
GraphicsElement::GraphicsElement(QGraphicsItem* parent) : QGraphicsObject(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
    m_pixmap.reset(new QPixmap(64, 64));

}
GraphicsElement::~GraphicsElement()
{}

QVariant GraphicsElement::itemChange(GraphicsItemChange change,
const QVariant &value)
{

    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
                qobject_cast<Scene*> (scene()) && isSelected()){
            Scene* customScene = qobject_cast<Scene*> (scene());
            int gridSize = customScene->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;
            return QPointF(xV, yV);
        }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}

QRectF GraphicsElement::boundingRect() const
{
    return m_pixmap->rect();
}

ElementType GraphicsElement::getType() const
{
    return m_type;
}

void GraphicsElement::setType(ElementType type)
{
    m_type = type;
}




void GraphicsElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    painter->begin(m_pixmap.get());
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::darkRed);
    painter->drawRect(0, 0, 64,64);
    painter->drawText(QRect(0, 0, 64, 64), Qt::AlignCenter, QString(m_type_strs[static_cast<int>(m_type)].c_str()));

}
