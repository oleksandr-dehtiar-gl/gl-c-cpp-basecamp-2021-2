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
#include "LogicGates/andgate.h"
#include "LogicGates/nandgate.h"
#include "LogicGates/norgate.h"
#include "LogicGates/orgate.h"
#include "LogicGates/xorgate.h"
#include "LogicGates/notgate.h"

#include <QGraphicsSceneMouseEvent>





class WorkSpace : public QObject
{
    Q_OBJECT
public:
    WorkSpace(QTabWidget * tabWidget, QObject* parent = nullptr);
    ~WorkSpace();
    bool eventFilter(QObject *target, QEvent *event) override;
    void AddElement(ElementType type);


private:
    bool mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    bool mousePressEvent(QGraphicsSceneMouseEvent * event);
    void StartNewConnection(const QPointF& m_mousePos);
    void AttachConnection();
    void DetachConnection(const QPointF& m_mousePos);
    void MapElement(GraphicsElement * graphElem, LogicElement * logElem);
    GraphicsElement* BuildGraphicElement(ElementType type);
    LogicElement* BuildLogicElement(ElementType type);


private:

    std::unique_ptr<QGraphicsView> m_view;
    std::unique_ptr<Scene> m_scene;
    Port* m_hoverPort = nullptr;
    Connection* m_editedConn = nullptr;
    std::map<GraphicsElement *, LogicElement *> m_elementAsoc;

};

#endif // WORKSPACE_H
