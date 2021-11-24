#include "workspace.h"
#include "mainwindow.h"


WorkSpace::WorkSpace(QTabWidget * tabWidget, QObject * parent) : QObject(nullptr)
{


    m_view.reset(new QGraphicsView(tabWidget));
    m_scene.reset(new Scene(QPen(Qt::black, 2), 16, nullptr));
    m_view->setScene(m_scene.get());
    m_view->setSceneRect(0, 0, tabWidget->width(), tabWidget->height());
    m_view->setMouseTracking(true);
    m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    m_scene->installEventFilter(this);

}


bool WorkSpace::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    if(!event)
    {
        return false;
    }
    QPointF scenePos = event->scenePos();
    Port * port = dynamic_cast<Port *>(m_scene->itemAt(scenePos, QTransform()));
    if(port)
    {
        m_hoverPort = port;
        m_hoverPort->hoverEnter();
        if(m_editedConn)
        {
            m_scene->update();
            m_editedConn->setEndPos(event->scenePos());
            m_editedConn->updatePath();
            return true;
        }
        return true;
    }
    else
    {
        if(m_hoverPort)
        {
            m_hoverPort->hoverLeave();
            m_hoverPort = nullptr;
            return true;
        }
        if(m_editedConn)
        {
            m_scene->update();
            m_editedConn->setEndPos(event->scenePos());
            m_editedConn->updatePath();
            return true;
        }

    }
    return false;
}

void WorkSpace::DetachConnection(const QPointF& m_mousePos)
{

    m_editedConn = m_hoverPort->getConnections().back();
    if(m_editedConn->getEndPort() == m_hoverPort)
    {
        m_editedConn->getEndPort()->disconnect();

    }
    else
    {
        m_editedConn->getStartPort()->disconnect();
        m_editedConn->setStartPort(m_editedConn->getEndPort());
        m_editedConn->setEndPort(nullptr);

    }
    m_editedConn->setEndPos(m_mousePos);
    m_editedConn->updateConnectionPosFromPorts();



}

void WorkSpace::StartNewConnection(const QPointF& m_mousePos)
{
    if(m_hoverPort->connect(m_editedConn))
    {
        m_editedConn->setEndPos(m_mousePos);
        m_hoverPort->updateConnection();
        m_scene->addItem(m_editedConn);


    }
    else
    {
        delete m_editedConn;
        m_editedConn = nullptr;
    }

}

void WorkSpace::AttachConnection()
{
    if(m_hoverPort->connect(m_editedConn))
    {
        m_hoverPort->updateConnection();
    }
    else
    {

        m_editedConn->getStartPort()->disconnect();
        m_scene->removeItem(m_editedConn);
        delete m_editedConn;
    }
     m_editedConn = nullptr;
}


bool WorkSpace::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(!event)
    {
        return false;
    }

    if(m_hoverPort)
    {
        if(!m_editedConn)
        {
            if(!m_hoverPort->getConnections().empty() && m_hoverPort->isInput())
            {
                DetachConnection(event->scenePos());
                return true;
            }
            m_editedConn = new Connection();
            m_editedConn->setZValue(-1);
            StartNewConnection(event->scenePos());
            return true;
        }
        else
        {
            AttachConnection();
            return true;
        }
        return false;
    }
    else
    {
        if(m_editedConn)
        {

            if(m_editedConn->getStartPort())
            {
                m_editedConn->getStartPort()->disconnect();
            }
            else if(m_editedConn->getStartPort())
            {
                m_editedConn->getEndPort()->disconnect();
            }
            m_scene->removeItem(m_editedConn);
            delete m_editedConn;
            m_editedConn = nullptr;
            return true;
        }

    }
    return false;
}

void WorkSpace::AddElement(ElementType type)
{
    GraphicsElement * elem = nullptr;
    switch (type)
    {
    case ElementType::AND:

        elem = new AndGateGraphicsElement(nullptr);

        break;
    case ElementType::NAND:
        elem = new NandGateGraphicsElement(nullptr);
        break;
    case ElementType::NOR:
        elem = new NorGateGraphicsElement(nullptr);
        break;
    case ElementType::NOT:
        elem = new NotGateGraphicsElement(nullptr);
        break;
    case ElementType::OR:
        elem = new OrGateGraphicsElement(nullptr);
        break;
    case ElementType::XOR:
        elem = new XorGateGraphicsElement(nullptr);
        break;
    case ElementType::DEFAULT:
    default:
        return;
    }
    if(elem != nullptr)
    {
        Port * in1 = new InPort(elem);
        Port * in2 = new InPort(elem);
        Port * out1 = new OutPort(elem);
        elem->addInputs(in1);
        elem->addInputs(in2);
        elem->addOutputs(out1);
        m_scene->addItem(elem);
    }

}


bool WorkSpace::eventFilter(QObject* target, QEvent* event)
{
    auto obj = dynamic_cast<Scene*>(target);
    bool result = false;
    if(obj)
    {
        QGraphicsSceneMouseEvent* evt = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        switch(static_cast<int>(event->type()))
        {
        case QEvent::GraphicsSceneMousePress:

            result = mousePressEvent(evt);
            break;
        case QEvent::GraphicsSceneMouseMove:
            result = mouseMoveEvent(evt);
            break;
        default:
            return result;
        }
    }

    if(result)
    {
        return result;
    }

    return QObject::eventFilter(target, event);

}

WorkSpace::~WorkSpace()
{

    for(int ind = 0; ind < m_scene->items().size(); ind++)
    {
        delete m_scene->items()[ind];
    }
}
