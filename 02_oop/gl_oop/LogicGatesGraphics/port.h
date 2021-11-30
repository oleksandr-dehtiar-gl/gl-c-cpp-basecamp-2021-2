#ifndef PORT_H
#define PORT_H
#include <QGraphicsPathItem>
#include <set>
#include "connection.h"
#include <QPen>
#include <QBrush>



enum PortType
{
    input,
    output,
    undefined
};

class Port : public QGraphicsPathItem
{


public:
    Port(QGraphicsItem * parent = nullptr, PortType port_type = PortType::undefined);
    void hoverEnter();
    void hoverLeave();
    void updateConnection();
    bool connect(Connection * con);
    void disconnect(Connection * con);    
    const std::set<Connection *> & getConnections() const;
    void setIndex(const uint8_t & index);
    void setState(const uint8_t& state);
    const uint8_t getIndex() const;
    const PortType getPortType() const;

    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
protected:
    QPen m_currentPen;
    QBrush m_currentBrush;
    std::set<Connection*> m_connections;
    const PortType m_type;
    uint8_t m_indexInElement;
    uint8_t m_state;


};


class InPort : public Port
{
public:

    InPort(QGraphicsItem * parent = nullptr);
    bool connect(Connection * con);

};

class OutPort : public Port
{
public:

    OutPort(QGraphicsItem * parent = nullptr);
    bool connect(Connection * con);
};


#endif // PORT_H
