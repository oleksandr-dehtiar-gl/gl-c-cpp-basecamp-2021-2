#include "port.h"
#include <QPainter>
Port::Port(QGraphicsItem * parent, bool inputFlag) : QGraphicsPathItem(parent), m_inputFLag(inputFlag)
{
    QPainterPath p;
    p.addPolygon(QRectF(QPointF(-8, 0), QPointF(0, 8)));
    setPath(p);

    setPen(QPen(Qt::darkRed));
    setBrush(Qt::red);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

const bool Port::isInput() const
{
    return m_inputFLag;
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
        if(m_connections.find(con) != m_connections.end())
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
}

void Port::updateConnection()
{
    for(auto it = m_connections.begin(); it != m_connections.end(); it++)
    {
        (*it)->updateConnectionPosFromPorts();
        (*it)->updatePath();
    }
}

OutPort::OutPort(QGraphicsItem * parent) : Port(parent, false)
{

}


InPort::InPort(QGraphicsItem * parent) : Port(parent, true)
{
}


bool OutPort::connect(Connection *con)
{
    if(con && m_connections.find(con) == m_connections.end())
    {
        Port * start_port = con->getStartPort();
        Port * end_port = con->getEndPort();
        if(!start_port)
        {
            con->setStartPort(this);
            m_connections.insert(con);
            return true;
        }
        else if(!end_port && start_port->isInput() && (start_port->parentItem() != this->parentItem()))
        {
            con->setEndPort(this);
            m_connections.insert(con);
            return true;
        }
    }
    return false;
}



bool InPort::connect(Connection *con)
{
    if(con && m_connections.empty())
    {
        Port * start_port = con->getStartPort();
        Port * end_port = con->getEndPort();
        if(!start_port)
        {
            con->setStartPort(this);
            m_connections.insert(con);
            return true;
        }
        else if(!end_port && !start_port->isInput() && (start_port->parentItem() != this->parentItem()))
        {
            con->setEndPort(this);
            m_connections.insert(con);
            return true;
        }

    }
    return false;
}


