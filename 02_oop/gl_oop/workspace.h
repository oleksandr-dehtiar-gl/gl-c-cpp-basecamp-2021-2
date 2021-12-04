#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QObject>
#include <QGraphicsView>
#include <QTabWidget>
#include <memory>
#include "scene.h"
#include "LogicGatesGraphics/andgategraphicselement.h"
#include "LogicGatesGraphics/nandgategraphicselement.h"
#include "LogicGatesGraphics/norgategraphicselement.h"
#include "LogicGatesGraphics/orgategraphicselement.h"
#include "LogicGatesGraphics/xorgategraphicselement.h"
#include "LogicGatesGraphics/notgategraphicselement.h"
#include "LogicGatesGraphics/gndgraphicselement.h"
#include "LogicGatesGraphics/vccgraphicselement.h"
#include "LogicGates/andgate.h"
#include "LogicGates/nandgate.h"
#include "LogicGates/norgate.h"
#include "LogicGates/orgate.h"
#include "LogicGates/xorgate.h"
#include "LogicGates/notgate.h"
#include "LogicGates/logicinput.h"


#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>





class WorkSpace : public QObject
{
    Q_OBJECT
public:

    WorkSpace(QTabWidget * tabWidget, QObject* parent = nullptr);
    ~WorkSpace();
    bool eventFilter(QObject *target, QEvent *event) override;
    void addElement(ElementType type);


private:

    bool mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    bool mousePressEvent(QGraphicsSceneMouseEvent * event);
    bool keyPressEvent(QKeyEvent* event);
    void startNewConnection(const QPointF& m_mousePos);
    void attachConnection(InPort * inPort);
    void attachConnection(OutPort * outPort);
    void detachConnection(const QPointF& m_mousePos);
    void cancelConnection();
    void mapElement(GraphicsElement * graphElem, LogicElement * logElem);
    void applyConnection(GraphicsElement * elem, InPort * port);
    void sortElements();
    void updateElements();
    void calculateSignals();
    void redrawView();
    void deleteElement(GraphicsElement * element);
    GraphicsElement* buildGraphicElement(ElementType type);
    LogicElement* buildLogicElement(ElementType type);



private:

    std::unique_ptr<QGraphicsView> m_view;
    std::unique_ptr<Scene> m_scene;
    Port* m_hoverPort = nullptr;
    Connection* m_editedConn = nullptr;
    std::map<GraphicsElement *, LogicElement *> m_elementAsoc;
    std::vector<LogicElement *> m_logicElements;

};

#endif // WORKSPACE_H
