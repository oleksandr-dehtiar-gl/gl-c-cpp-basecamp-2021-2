#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class findDialog; }
QT_END_NAMESPACE

class findDialog : public QDialog
{
    Q_OBJECT

public:
    explicit findDialog(Ui::MainWindow *ui_, QWidget *parent = nullptr);
    ~findDialog();

private slots:
    void on_findButton_clicked();

private:
    Ui::findDialog *uiFinder;
    Ui::MainWindow *uiMain;
};

#endif // FINDDIALOG_H
