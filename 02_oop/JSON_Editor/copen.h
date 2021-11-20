#ifndef COPEN_H
#define COPEN_H

#include "command.h"
#include "mainwindow.h"

class cOpen : public Command
{
private:
    bool *edited;
    Ui::MainWindow *ui;
    MainWindow *form;
public:
    cOpen(bool &edited,Ui::MainWindow *ui_, MainWindow *th);
    void exec()const override;
};

#endif // COPEN_H
