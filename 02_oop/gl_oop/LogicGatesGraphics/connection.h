#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsPathItem>
#include <QPen>
class Port;
class InPort;
class OutPort;

class Connection :public QGraphicsPathItem
{
public:

    Connection(QGraphicsItem * parent = nullptr);
    void setStartPort(Port * startPort);
    void setEndPort(Port * endPort);
    void setStartPos(const QPointF& startPos);
    void setEndPos(const QPointF& endPos);
    void updateConnectionPosFromPorts();
    Port * getEndPort();
    Port * getStartPort();
    void updatePath();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    void swapPorts();
    void setState(const int8_t& state);
    void updateColor();
    InPort* otherPort(OutPort* outPort);
    OutPort* otherPort(InPort* inPort);
    Port * otherPort(Port * port);
private:

    Port * m_startPort = nullptr;
    Port * m_endPort = nullptr;
    QPointF m_startPos;
    QPointF m_endPos;
    QPen m_currentPen;
    int8_t m_state;


};

#endif // CONNECTION_H
