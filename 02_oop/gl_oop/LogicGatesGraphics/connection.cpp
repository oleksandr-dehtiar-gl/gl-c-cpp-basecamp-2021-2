#include "connection.h"
#include "port.h"
#include <QPainter>
Connection::Connection(QGraphicsItem * parent) : QGraphicsPathItem(parent)
{
    setBrush(Qt::NoBrush);
    setFlag(QGraphicsItem::ItemIsSelectable);
    m_startPort = nullptr;
    m_endPort = nullptr;
    setZValue(-1);
}


void Connection::updateColor()
{
    QColor color;
    switch(m_state)
    {
    case -1:
        color.setRgb(0,0,0);
        break;
    case 0:
        color.setRgb(255,0,0);
        break;
    case 1:
        color.setRgb(0,255,0);
        break;
    default:
        break;
    }

    m_currentPen.setColor(color);
    m_currentPen.setWidth(4);
}


void Connection::setStartPort(Port *startPort)
{
    m_startPort = startPort;
}

void Connection::setEndPort(Port *endPort)
{
    m_endPort = endPort;
}

OutPort* Connection::otherPort(InPort *inPort)
{
    return dynamic_cast<OutPort*>(m_startPort);
}

InPort* Connection::otherPort(OutPort *outPort)
{
    return dynamic_cast<InPort*>(m_endPort);
}

Port * Connection::otherPort(Port * port)
{
    if(dynamic_cast<InPort*>(port))
    {
        return m_startPort;
    }
    return m_endPort;
}
void Connection::swapPorts()
{
    std::swap(m_startPort, m_endPort);
}
void Connection::setStartPos(const QPointF &startPos)
{
    m_startPos = startPos;
}

void Connection::setEndPos(const QPointF &endPos)
{
    m_endPos = endPos;
}


void Connection::updateConnectionPosFromPorts()
{
    if(m_startPort)
    {
        m_startPos = m_startPort->scenePos();
        m_startPos.rx() -= 4;
        m_startPos.ry() += 4;

    }
    if(m_endPort)
    {
        m_endPos = m_endPort->scenePos();
        m_endPos.rx() -= 4;
        m_endPos.ry() += 4;
    }

}

void Connection::setState(const int8_t &state)
{
    m_state = state;

    updateColor();
}

Port* Connection::getStartPort()
{
    return m_startPort;
}

Port* Connection::getEndPort()
{
    return m_endPort;
}

void Connection::updatePath()
{
    QPainterPath path;
    qreal topHalfX = (m_endPos.x() - m_startPos.x()) * 0.5;
    qreal botHalfX =  topHalfX;
    path.moveTo(m_startPos);
    path.lineTo(m_startPos.x() + topHalfX, m_startPos.y());
    path.lineTo(m_startPos.x() + botHalfX, m_endPos.y());
    path.lineTo(m_endPos);
    setPath(path);

}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget)
{
    painter->setPen(m_currentPen);
    painter->drawPath(path());
}


