#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsPathItem>
class Port;

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
private:
    Port * m_startPort = nullptr;
    Port * m_endPort = nullptr;
    QPointF m_startPos;
    QPointF m_endPos;


};

#endif // CONNECTION_H
