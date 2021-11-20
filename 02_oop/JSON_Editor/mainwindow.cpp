#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cquit.h"
#include "cabout.h"
#include "csave.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    invoker = new Invoker();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete invoker;
}


void MainWindow::on_actionQuit_triggered()
{
    invoker->exec(new cQuit());
}


void MainWindow::on_actionNew_triggered()
{

}


void MainWindow::on_actionAbout_triggered()
{
    invoker->exec(new cAbout());
}


void MainWindow::on_actionSave_triggered()
{
    invoker->exec(new cSave(ui, this));
}

