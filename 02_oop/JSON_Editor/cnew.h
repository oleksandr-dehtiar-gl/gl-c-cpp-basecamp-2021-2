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
    QString *mainFileName;
public:
    cNew(bool &edited_, Ui::MainWindow* ui_, MainWindow* th, QString &fileName_);
    void exec()const override;
    ~cNew();
};

#endif // CNEW_H
