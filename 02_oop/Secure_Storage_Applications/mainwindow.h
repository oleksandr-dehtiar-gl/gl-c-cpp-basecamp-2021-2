#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <vector>
#include <QtXml>
#include <map>

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
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_GetObject_clicked();

private:
    Ui::MainWindow *ui;
    QString storagePath = "";
    std::map<QString, QString> readStorage();
    QString fileName(QString filePath);
    int password;
};
#endif // MAINWINDOW_H
