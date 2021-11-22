#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workspace.h"

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
    std::unique_ptr<WorkSpace> m_workspace;
};
#endif // MAINWINDOW_H
