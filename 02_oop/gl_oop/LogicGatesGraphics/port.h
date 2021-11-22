#ifndef PORT_H
#define PORT_H
#include <QGraphicsPathItem>



class Port : public QGraphicsPathItem
{
public:
    Port(QGraphicsItem * parent = nullptr);
protected:
};


class InPort : public Port
{

};


class OutPort: public Port
{

};

#endif // PORT_H
