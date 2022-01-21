#include "port.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include "../graphicselement.h"

Port::Port(GraphicsElement * parent,  PortType port_type, const int8_t & initial_state) : QGraphicsPathItem(parent), m_type(port_type), m_parentElement(parent)
{

    QPainterPath p;
    p.addPolygon(QRectF(QPointF(-8, 0), QPointF(0, 8)));
    setPath(p);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    m_currentBrush.setStyle(Qt::SolidPattern);
    setState(initial_state);
    setPen(m_currentPen);
    setBrush(m_currentBrush);
}


GraphicsElement * Port::getParentElement() const
{
    return m_parentElement;
}
void Port::setState(const int8_t &state)
{
    m_state = state;
    updateColor();

}

const uint8_t Port::getIndex() const
{
    return m_indexInElement;
}

void Port::setIndex(const uint8_t & index)
{
    m_indexInElement = index;
}

void Port::updateColor()
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
    m_currentBrush.setColor(color);
    m_currentPen.setColor(color);
}

void Port::hoverEnter()
{
    setBrush(Qt::yellow);
    setPen(m_currentPen);
    update();

}
void Port::hoverLeave()
{
    setBrush(m_currentBrush);
    setPen(m_currentPen);
    update();
}

bool Port::connect(Connection *con)
{

   Port * start_port = con->getStartPort();
   if(!start_port)
   {
       con->setStartPort(this);
       con->setState(m_state);
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

OutPort::OutPort(GraphicsElement * parent, const int8_t& initital_state) : Port(parent, PortType::output, initital_state)
{}

bool OutPort::connect(Connection *con)
{
    if(con)
    {
        return Port::connect(con);
    }
    return false;
}



void OutPort::setValue(const int8_t &value)
{
    setState(value);
    for(auto it = m_connections.begin(); it != m_connections.end(); it++)
    {
        (*it)->setState(m_state);
        InPort* otherPort = dynamic_cast<InPort*>((*it)->otherPort(this));
        if(otherPort)
        {
            otherPort->setValue(value);
        }
    }
}


InPort::InPort(GraphicsElement * parent) : Port(parent, PortType::input)
{}

void InPort::setValue(const int8_t &value)
{
    setState(value);
}

bool InPort::connect(Connection *con)
{
    if(con && m_connections.empty())
    {
        return Port::connect(con);
    }
    return false;
}


