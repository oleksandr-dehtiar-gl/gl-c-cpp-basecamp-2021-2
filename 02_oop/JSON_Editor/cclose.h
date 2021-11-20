#ifndef CCLOSE_H
#define CCLOSE_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "command.h"

class cClose : public Command
{
private:
    Ui::MainWindow *ui;
    MainWindow *form;
    bool *edited;
public:
    cClose(bool &edited_, Ui::MainWindow* ui_, MainWindow* th);
    void exec()const override;
    ~cClose();

};

#endif // CCLOSE_H
