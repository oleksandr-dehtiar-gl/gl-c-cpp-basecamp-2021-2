#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QtCore/QCoreApplication>

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

    void on_add_file_1_clicked();

    void on_add_file_2_clicked();

    void on_compare_files_clicked();


    void on_action1_triggered();

    void on_action2_triggered();

    void on_action3_triggered();

    void on_actiondef_triggered();

    void on_actionExport_files_triggered();

    void on_del_row_clicked();

    void on_del_row_2_clicked();

    void on_add_row_clicked();

    void on_add_row_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
