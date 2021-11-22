#include "port.h"
#include <QPainter>
Port::Port(QGraphicsItem * parent) : QGraphicsPathItem(parent)
{
    QPainterPath p;
    p.addPolygon(QRectF(QPointF(-8, 0), QPointF(0, 8)));
    setPath(p);

    setPen(QPen(Qt::darkRed));
    setBrush(Qt::red);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}
