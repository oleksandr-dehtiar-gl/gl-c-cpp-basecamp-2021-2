#ifndef CNEW_H
#define CNEW_H

#include "command.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
class cNew : public Command
{
private:
    Ui::MainWindow *ui;
    MainWindow *form;
    bool *edited;
public:
    cNew(bool &edited_, Ui::MainWindow* ui_, MainWindow* th);
    void exec()const override;
    ~cNew();
};

#endif // CNEW_H
