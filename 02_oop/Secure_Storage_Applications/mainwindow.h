#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <vector>
#include <map>

struct Password;
//Operators used to read/write passwords from/in file
std::ifstream& operator>>(std::ifstream& is, Password& st);
std::ofstream& operator<<(std::ofstream& os, Password& st);

struct Password //struct to store information about the file and password to it
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
    void on_pushButton_2_clicked(); //Create new Storage
    void on_pushButton_clicked(); //Open storage
    void on_pushButton_3_clicked(); //Add file to storage
    void on_pushButton_GetObject_clicked(); //Get file from storage
    void on_DeleteObject_clicked(); //Delete file from storage

private:
    Ui::MainWindow *ui;
    QString storagePath = "";

    QString fileName(QString filePath);
    void addPassword(Password);
    void printFiles();
    void closeEvent(QCloseEvent *event);
    std::map<QString, QString> readStorage();
    std::vector<Password> getPasswords();
};
#endif // MAINWINDOW_H
