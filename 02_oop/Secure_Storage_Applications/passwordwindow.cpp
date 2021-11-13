#include "passwordwindow.h"
#include "ui_passwordwindow.h"

PasswordWindow::PasswordWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordWindow)
{
    ui->setupUi(this);
}

PasswordWindow::~PasswordWindow()
{
    delete ui;
}

void PasswordWindow::on_Enter_clicked()
{
    this->password = ui->passwordLabel->text().toInt();
}
