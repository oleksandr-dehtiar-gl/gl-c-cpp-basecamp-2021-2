#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "invoker.h"
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Invoker *invoker;
    bool edited = false;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSelect_All_triggered();

    void on_actionFind_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionQuit_triggered();

    void on_actionNew_triggered();

    void on_actionAbout_triggered();

    void on_actionSave_triggered();

    void on_textEdit_textChanged();

    void on_actionClose_triggered();

    void on_actionOpen_triggered();

    void on_actionCopy_triggered();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
