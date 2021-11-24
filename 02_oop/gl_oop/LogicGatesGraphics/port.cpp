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


const std::vector<Connection *> & Port::getConnections() const
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

void Port::updateConnection()
{
    for(auto ind = 0; ind < m_connections.size(); ind++)
    {
        m_connections[ind]->updateConnectionPosFromPorts();
        m_connections[ind]->updatePath();
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
    if(con)
    {
        Port * start_port = con->getStartPort();
        Port * end_port = con->getEndPort();
        if(!start_port)
        {
            con->setStartPort(this);
            m_connections.push_back(con);
            return true;
        }
        else if(!end_port && start_port->isInput() && (start_port->parentItem() != this->parentItem()))
        {
            con->setEndPort(this);
            m_connections.push_back(con);
            return true;
        }


    }
    return false;
}

void OutPort::disconnect()
{

        if(m_connections.back()->getEndPort() == this)
        {
            m_connections.back()->setEndPort(nullptr);
        }
        else
        {
            m_connections.back()->setStartPort(nullptr);
        }
        m_connections.pop_back();

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
            m_connections.push_back(con);
            return true;
        }
        else if(!end_port && !start_port->isInput() && (start_port->parentItem() != this->parentItem()))
        {
            con->setEndPort(this);
            m_connections.push_back(con);
            return true;
        }

    }
    return false;
}

void InPort::disconnect()
{

        if(m_connections[0]->getEndPort() == this)
        {
            m_connections[0]->setEndPort(nullptr);
        }
        else
        {
            m_connections[0]->setStartPort(nullptr);
        }
        m_connections.pop_back();

}
