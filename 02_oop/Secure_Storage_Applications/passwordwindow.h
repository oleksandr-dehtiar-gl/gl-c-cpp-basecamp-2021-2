#ifndef PASSWORDWINDOW_H
#define PASSWORDWINDOW_H

#include <QDialog>

//Password entry window
namespace Ui {
class PasswordWindow;
}

class PasswordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordWindow(QWidget *parent = nullptr);
    int getPassword() {return password;}
    ~PasswordWindow();

private slots:
    void on_Enter_clicked();

private:
    Ui::PasswordWindow *ui;
    int password;
};

#endif // PASSWORDWINDOW_H
