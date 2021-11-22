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






class WorkSpace : public QObject
{
    Q_OBJECT
public:
    WorkSpace(QTabWidget * tabWidget, QObject* parent = nullptr);
    ~WorkSpace();
    bool eventFilter(QObject *target, QEvent *event) override;
    void AddElement(ElementType type);
private:
    std::unique_ptr<QGraphicsView> m_view;
    std::unique_ptr<Scene> m_scene;
    std::vector<Port*> m_selected_items;

};

#endif // WORKSPACE_H
