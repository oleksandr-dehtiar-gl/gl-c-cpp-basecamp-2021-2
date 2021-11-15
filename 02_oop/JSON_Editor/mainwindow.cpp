#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionNew_triggered()
{

}


void MainWindow::on_actionAbout_triggered()
{
    aboutDialog about;
    about.exec();
}

