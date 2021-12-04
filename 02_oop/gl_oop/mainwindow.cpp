
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    m_workspace.reset(new WorkSpace(ui->workingSpaceTab));
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_notButton_clicked()
{
    m_workspace->addElement(ElementType::NOT);
}


void MainWindow::on_andButton_clicked()
{
    m_workspace->addElement(ElementType::AND);
}

void MainWindow::on_nandButton_clicked()
{
    m_workspace->addElement(ElementType::NAND);
}


void MainWindow::on_orButton_clicked()
{
    m_workspace->addElement(ElementType::OR);
}


void MainWindow::on_xorButton_clicked()
{
    m_workspace->addElement(ElementType::XOR);
}


void MainWindow::on_norButton_clicked()
{
    m_workspace->addElement(ElementType::NOR);
}


void MainWindow::on_vccButton_clicked()
{
    m_workspace->addElement(ElementType::VCC);
}



void MainWindow::on_gndButton_clicked()
{
    m_workspace->addElement(ElementType::GND);
}

