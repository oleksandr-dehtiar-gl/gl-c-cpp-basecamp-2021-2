#include "port.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
Port::Port(QGraphicsItem * parent,  PortType port_type) : QGraphicsPathItem(parent), m_type(port_type)
{

    QPainterPath p;
    p.addPolygon(QRectF(QPointF(-8, 0), QPointF(0, 8)));
    setPath(p);

    setPen(QPen(Qt::darkRed));
    setBrush(Qt::red);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setState(-1);

}

void Port::setState(const uint8_t &state)
{
    m_state = state;
}

const uint8_t Port::getIndex() const
{
    return m_indexInElement;
}

void Port::setIndex(const uint8_t & index)
{
    m_indexInElement = index;
}



void Port::hoverEnter()
{
    setBrush(Qt::yellow);
    update();
}
void Port::hoverLeave()
{
    setBrush(Qt::red);
    update();
}

bool Port::connect(Connection *con)
{

   Port * start_port = con->getStartPort();
   if(!start_port)
   {
       con->setStartPort(this);
       m_connections.insert(con);
       return true;
   }
   if(start_port->m_type != this->m_type && (start_port->parentItem() != this->parentItem()))
   {
       con->setEndPort(this);
       m_connections.insert(con);
       return true;

   }
   return false;

}

const std::set<Connection *> & Port::getConnections() const
{
    return m_connections;
}

QVariant Port::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemScenePositionHasChanged) {
        updateConnection();
    }
    return value;
}

void Port::disconnect(Connection *con)
{
    if(!m_connections.empty())
    {
            Port * startPort = con->getStartPort();
            if(startPort == this)
            {
                con->setStartPort(nullptr);
            }
            else
            {
                con->setEndPort(nullptr);
            }
            m_connections.erase(con);
    }
}

const PortType Port::getPortType() const
{
    return m_type;
}

void Port::updateConnection()
{
    for(auto it = m_connections.begin(); it != m_connections.end(); it++)
    {
        (*it)->updateConnectionPosFromPorts();
        (*it)->updatePath();
    }
}

OutPort::OutPort(QGraphicsItem * parent) : Port(parent, PortType::output)
{}

bool OutPort::connect(Connection *con)
{
    if(con)
    {
        return Port::connect(con);
    }
    return false;
}


InPort::InPort(QGraphicsItem * parent) : Port(parent, PortType::input)
{}

bool InPort::connect(Connection *con)
{
    if(con && m_connections.empty())
    {
        return Port::connect(con);
    }
    return false;
}



