#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <memory>
#include "scene.h"
#include "graphicselement.h"
#include "LogicGatesGraphics/xorgategraphicselement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_notButton_clicked();

    void on_andButton_clicked();

    void on_nandButton_clicked();

    void on_orButton_clicked();

    void on_xorButton_clicked();

    void on_norButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QGraphicsView> m_view;
    std::unique_ptr<Scene> m_scene;
    std::unique_ptr<GraphicsElement> elemXOR;
    std::unique_ptr<GraphicsElement> elem;




};
#endif // MAINWINDOW_H
