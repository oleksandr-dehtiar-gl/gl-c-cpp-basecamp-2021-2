#ifndef PORT_H
#define PORT_H
#include <QGraphicsPathItem>
#include "connection.h"
#include <set>
#include <QPen>
#include <QBrush>



enum PortType
{
    input,
    output,
    undefined
};

class GraphicsElement;


class Port : public QGraphicsPathItem
{

public:
    Port(GraphicsElement * parent = nullptr, PortType port_type = PortType::undefined, const int8_t& initial_state = -1);
    void hoverEnter();
    void hoverLeave();
    void updateConnection();
    bool connect(Connection* con);
    void disconnect(Connection* con);
    const std::set<Connection*> & getConnections() const;
    void setIndex(const uint8_t& index);
    void setState(const int8_t& state);
    const uint8_t getIndex() const;
    const PortType getPortType() const;
    void updateColor();
    GraphicsElement * getParentElement() const;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

protected:

    friend void Connection::setEndPort(Port * end_port);
    friend void Connection::setStartPort(Port * start_port);
    friend void Connection::swapPorts();
    QPen m_currentPen;
    QBrush m_currentBrush;
    std::set<Connection*> m_connections;
    const PortType m_type;
    uint8_t m_indexInElement;
    int8_t m_state;
    GraphicsElement * m_parentElement;
};


class InPort : public Port
{
public:

    InPort(GraphicsElement * parent = nullptr);
    bool connect(Connection * con);
    void setValue(const int8_t & value);

};

class OutPort : public Port
{
public:

    OutPort(GraphicsElement * parent = nullptr, const int8_t& initital_state = -1);
    bool connect(Connection * con);
    void setValue(const int8_t & value);
};


#endif // PORT_H
