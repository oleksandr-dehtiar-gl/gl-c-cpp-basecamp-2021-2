#ifndef PORT_H
#define PORT_H
#include <QGraphicsPathItem>
#include <set>
#include "connection.h"





class Port : public QGraphicsPathItem
{


public:
    Port(QGraphicsItem * parent = nullptr, bool inputFlag = false);
    void hoverEnter();
    void hoverLeave();
    void updateConnection();
    virtual bool connect(Connection * con) = 0;
    void disconnect(Connection * con);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    const bool isInput() const;
    const std::set<Connection *> & getConnections() const;
protected:
    std::set<Connection*> m_connections;
    const bool m_inputFLag;

};


class InPort : public Port
{
public:

    bool connect(Connection * con) override;

    InPort(QGraphicsItem * parent = nullptr);

};

class OutPort : public Port
{
public:
    bool connect(Connection * con) override;

    OutPort(QGraphicsItem * parent = nullptr);
};


#endif // PORT_H
