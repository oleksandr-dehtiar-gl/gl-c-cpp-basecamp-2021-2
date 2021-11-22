#include "workspace.h"
#include "mainwindow.h"
#include <QGraphicsSceneMouseEvent>

WorkSpace::WorkSpace(QTabWidget * tabWidget, QObject * parent) : QObject(nullptr)
{


    //MainWindow * mainWindow = dynamic_cast<MainWindow*>(parent);
    m_view.reset(new QGraphicsView(tabWidget));
    m_scene.reset(new Scene(QPen(Qt::black, 2), 16, nullptr));
    m_view->setScene(m_scene.get());
    m_view->setSceneRect(0, 0, tabWidget->width(), tabWidget->height());
    m_scene->installEventFilter(this);

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
        Port * in1 = new Port(elem);
        Port * in2 = new Port(elem);
        elem->addInputs(in1);
        elem->addInputs(in2);
        m_scene->addItem(elem);
    }

}


bool WorkSpace::eventFilter(QObject *target, QEvent *event)
{
    auto obj = dynamic_cast<Scene*>(target);
    if(target)
    {
        auto evt = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        if(evt && event->type() == QEvent::GraphicsSceneMousePress)
        {
            QPointF pos = evt->scenePos();
            QGraphicsItem* item = m_scene->itemAt(pos, QTransform());
            Port* port = dynamic_cast<Port*>(item);
            if(port)
            {
                m_selected_items.push_back(port);
                port->setBrush(Qt::yellow);
                return true;
            }
            else
            {
                for(auto it = m_selected_items.begin(); it != m_selected_items.end(); it++)
                {
                    Port * p = dynamic_cast<Port*>(*it);
                    if(p)
                    {
                        p->setBrush(Qt::red);

                    }
                }
                m_selected_items.clear();
                return QObject::eventFilter(target, event);

            }
        }

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
