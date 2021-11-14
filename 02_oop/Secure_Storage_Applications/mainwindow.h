#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <vector>
#include <QtXml>
#include <map>

struct Password;
std::ifstream& operator>>(std::ifstream& is, Password& st);
std::ofstream& operator<<(std::ofstream& os, Password& st);

struct Password
{
    Password() = default;
    Password(std::string name, int password) : name(name), password(password){}
    std::string name;
    int password;
};

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
    void addPassword(Password);
    std::vector<Password> getPasswords();
    void printFiles();
    void closeEvent(QCloseEvent *event);

};
#endif // MAINWINDOW_H
