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

void WorkSpace::sortElements()
{
    for(auto it = m_logicElements.begin(); it != m_logicElements.end(); it++)
    {
        (*it)->calculatePriority();
    }

    auto comparer = [](LogicElement * el1, LogicElement * el2){ return el1->getPriority() > el2->getPriority();};
    std::sort(m_logicElements.begin(), m_logicElements.end(), comparer);
}

void WorkSpace::updateElements()
{
    for(auto it = m_logicElements.begin(); it != m_logicElements.end(); it++)
    {
        (*it)->setInputValues();
        (*it)->updateLogic();
    }
    for(auto it = m_elementAsoc.begin(); it != m_elementAsoc.end(); it++)
    {
        OutPort * outport = it->first->getOutputPort();
        outport->setValue(it->second->getOutput());
    }
}


void WorkSpace::calculateSignals()
{
    for(auto element_it = m_elementAsoc.begin(); element_it != m_elementAsoc.end(); element_it++)
    {
        element_it->second->resetPriority();
    }
    sortElements();
    updateElements();


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
        if(!m_hoverPort)
        {
            m_hoverPort = port;
            m_hoverPort->hoverEnter();
        }
        else if(m_hoverPort != port)
        {
            m_hoverPort->hoverLeave();
            m_hoverPort = nullptr;
        }

    }
    else if(m_hoverPort)
    {
        m_hoverPort->hoverLeave();
        m_hoverPort = nullptr;


    }
    if(m_editedConn)
    {
        m_scene->update();
        m_editedConn->setEndPos(event->scenePos());
        m_editedConn->updatePath();
        return true;
    }
    return false;
}

void WorkSpace::detachConnection(const QPointF& m_mousePos)
{
    m_editedConn = *m_hoverPort->getConnections().begin();
    m_hoverPort->setState(-1);
    m_hoverPort->disconnect(m_editedConn);
    applyConnection(m_hoverPort->getParentElement(), dynamic_cast<InPort*>(m_hoverPort));
    m_editedConn->setEndPos(m_mousePos);
    m_editedConn->updatePath();
}

void WorkSpace::startNewConnection(const QPointF& m_mousePos)
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
void WorkSpace::cancelConnection()
{
    Port * editedConnStartPort = m_editedConn->getStartPort();
    editedConnStartPort->disconnect(m_editedConn);
    m_scene->removeItem(m_editedConn);
    delete m_editedConn;
    m_editedConn = nullptr;
}


void WorkSpace::attachConnection(InPort* inPort)
{
    if(inPort->connect(m_editedConn))
    {
       inPort->updateConnection();
       applyConnection(m_hoverPort->getParentElement(), inPort);
    }
    else
    {
        m_editedConn->getStartPort()->disconnect(m_editedConn);
        m_scene->removeItem(m_editedConn);
        delete m_editedConn;
    }

}

void WorkSpace::attachConnection(OutPort* outPort)
{
    if(outPort->connect(m_editedConn))
    {
        if(outPort != m_editedConn->getStartPort())
        {
            m_editedConn->swapPorts();
        }
        applyConnection(m_editedConn->otherPort(outPort)->getParentElement(), m_editedConn->otherPort(outPort));
        outPort->updateConnection();
    }
    else
    {
        m_editedConn->getStartPort()->disconnect(m_editedConn);
        m_scene->removeItem(m_editedConn);
        delete m_editedConn;
    }

}

void WorkSpace::redrawView()
{
    m_view->viewport()->repaint(m_scene->sceneRect().x(), m_scene->sceneRect().y(), m_scene->sceneRect().width(), m_scene->sceneRect().height());
}


bool WorkSpace::keyPressEvent(QKeyEvent* event)
{
    if(!event)
    {
        return false;
    }
    if(!m_scene->selectedItems().empty())
    {
        deleteElement(dynamic_cast<GraphicsElement*>(m_scene->selectedItems().at(0)));
        calculateSignals();
        return true;
    }
    return false;
}

bool WorkSpace::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(!event)
    {
        return false;
    }
    if(m_hoverPort)
    {
        if(!m_scene->selectedItems().empty())
        {
            m_scene->selectedItems().at(0)->setSelected(false);
        }
        if(!m_editedConn)
        {
            if(!m_hoverPort->getConnections().empty() && m_hoverPort->getPortType() == PortType::input)
            {
                detachConnection(event->scenePos());
                calculateSignals();
                redrawView();
                return true;
            }
            m_editedConn = new Connection();
            startNewConnection(event->scenePos());
            return true;
        }
        else
        {

            if(m_hoverPort->getPortType() == PortType::input)
            {
                attachConnection(dynamic_cast<InPort*>(m_hoverPort));

            }
            else
            {
                attachConnection(dynamic_cast<OutPort*>(m_hoverPort));

            }

            m_editedConn = nullptr;
            calculateSignals();
            redrawView();
            return true;
        }
        return false;
    }
    else if(m_editedConn)
    {
        cancelConnection();
        return true;
    }
    return false;
}

void WorkSpace::deleteElement(GraphicsElement * element)
{
    LogicElement * logEl = m_elementAsoc[element];

    //detach predecessor logic elements
    for(auto inputIt = element->getInputs().begin(); inputIt != element->getInputs().end(); inputIt++)
    {
        InPort* inPort = *inputIt;
        Connection * conn = *inPort->getConnections().begin();
        if(!conn)
        {
            continue;
        }
        OutPort * otherPort = conn->otherPort(inPort);
        GraphicsElement * predecessorsGraphElem = otherPort->getParentElement();
        LogicElement * predecessorsLogElem = m_elementAsoc[predecessorsGraphElem];
        predecessorsLogElem->removeSuccessor(logEl);
        otherPort->disconnect(conn);
        m_scene->removeItem(conn);
        delete conn;
    }

    //detach successor logic elements;
    OutPort * outPort = element->getOutputPort();
    for(auto connectionIt = outPort->getConnections().begin(); connectionIt != outPort->getConnections().end(); connectionIt++)
    {
        Connection * conn = *connectionIt;
        if(!conn)
        {
            continue;
        }
        InPort* inPort = conn->otherPort(outPort);
        inPort->setValue(-1);
        GraphicsElement * successorGraphElem = inPort->getParentElement();
        LogicElement * successorLogicElem = m_elementAsoc[successorGraphElem];
        successorLogicElem->removePredecessor(inPort->getIndex());
        inPort->disconnect(conn);
        m_scene->removeItem(conn);
        delete conn;
    }
    m_scene->removeItem(element);
    m_elementAsoc.erase(element);
    auto elementIt = std::find(m_logicElements.begin(), m_logicElements.end(), logEl);
    m_logicElements.erase(elementIt);
    delete logEl;
    delete element;

}

LogicElement * WorkSpace::buildLogicElement(ElementType type)
{
    LogicElement * elem = nullptr;
    switch (type)
    {
    case ElementType::AND:
        elem = new AndGate();
        break;
    case ElementType::NAND:
        elem = new NandGate();
        break;
    case ElementType::NOR:
        elem = new NorGate();
        break;
    case ElementType::NOT:
        elem = new NotGate();
        break;
    case ElementType::OR:
        elem = new OrGate();
        break;
    case ElementType::XOR:
        elem = new XorGate();
        break;
    case ElementType::GND:
        elem = new LogicInput(false);
        break;
    case ElementType::VCC:
        elem = new LogicInput(true);
        break;
    case ElementType::DEFAULT:
    default:
        return nullptr;
    }
    return elem;
}

GraphicsElement * WorkSpace::buildGraphicElement(ElementType type)
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
    case ElementType::GND:
        elem = new GNDGRaphicsElement(nullptr);
        break;
    case ElementType::VCC:
        elem = new VCCGraphicsElement(nullptr);
        break;
    case ElementType::DEFAULT:
    default:
        return nullptr;
    }
    return elem;
}

void WorkSpace::mapElement(GraphicsElement *graphElem, LogicElement *logElem)
{
    m_elementAsoc[graphElem] = logElem;
}

void WorkSpace::applyConnection(GraphicsElement * elem, InPort * port)
{
    LogicElement * log_elem = m_elementAsoc[elem];
    Connection * predecessorsConnection = port->getConnections().empty() ? nullptr : *(port->getConnections().begin());
    if(!predecessorsConnection)
    {
        log_elem->removePredecessor(port->getIndex());
        return;
    }
    Port * predecessorsConnectedPort = predecessorsConnection->otherPort(port);
    GraphicsElement * predecessorsGraphicsElement = predecessorsConnectedPort->getParentElement();
    LogicElement * predecessorLogicElement = m_elementAsoc[predecessorsGraphicsElement];
    log_elem->connectPredeccessor(predecessorLogicElement, port->getIndex());
}

void WorkSpace::addElement(ElementType type)
{
   GraphicsElement * graphElem = buildGraphicElement(type);
   if(!graphElem)
   {
       return;
   }
   LogicElement * logicElem = buildLogicElement(type);
   if(!logicElem)
   {
       delete graphElem;
       return;
   }
   mapElement(graphElem, logicElem);
   m_scene->addItem(graphElem);
   m_logicElements.push_back(logicElem);

}


bool WorkSpace::eventFilter(QObject* target, QEvent* event)
{
    auto obj = dynamic_cast<Scene*>(target);
    bool result = false;
    if(obj)
    {
        QGraphicsSceneMouseEvent* mouse_evt = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        QKeyEvent * key_evt = dynamic_cast<QKeyEvent*>(event);
        switch(static_cast<int>(event->type()))
        {
        case QEvent::GraphicsSceneMousePress:
            result = mousePressEvent(mouse_evt);
            break;
        case QEvent::GraphicsSceneMouseMove:
            result = mouseMoveEvent(mouse_evt);
            break;
        case QEvent::KeyPress:
            if(key_evt->key() == Qt::Key_Delete)
            {
                result = keyPressEvent(key_evt);
            }
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
    for(auto it = m_elementAsoc.begin(); it != m_elementAsoc.end(); it++)
    {
        delete it->second;
    }
    m_elementAsoc.clear();
    for(int ind = 0; ind < m_scene->items().size(); ind++)
    {
        delete m_scene->items()[ind];
    }
    m_logicElements.clear();
}
