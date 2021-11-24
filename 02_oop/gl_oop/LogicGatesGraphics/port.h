#ifndef PORT_H
#define PORT_H
#include <QGraphicsPathItem>
#include "connection.h"





class Port : public QGraphicsPathItem
{


public:
    Port(QGraphicsItem * parent = nullptr, bool inputFlag = false);
    void hoverEnter();
    void hoverLeave();
    void updateConnection();
    virtual bool connect(Connection * con) = 0;
    virtual void disconnect() = 0;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    const bool isInput() const;
    const std::vector<Connection *> & getConnections() const;
protected:
    std::vector<Connection*> m_connections;
    const bool m_inputFLag;

};


class InPort : public Port
{
public:

    bool connect(Connection * con) override;
    void disconnect() override;
    InPort(QGraphicsItem * parent = nullptr);

};

class OutPort : public Port
{
public:
    bool connect(Connection * con) override;
    void disconnect() override;
    OutPort(QGraphicsItem * parent = nullptr);
};


#endif // PORT_H
