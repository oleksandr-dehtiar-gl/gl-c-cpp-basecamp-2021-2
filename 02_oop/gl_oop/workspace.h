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
#include "LogicGatesGraphics/orgategraphicselement.h"
#include "LogicGatesGraphics/notgategraphicselement.h"
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
    //bool mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
private:
    std::unique_ptr<QGraphicsView> m_view;
    std::unique_ptr<Scene> m_scene;
    Port* m_hoverPort = nullptr;
    Connection* m_editedConn = nullptr;

};

#endif // WORKSPACE_H
