
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    elemXOR.reset(new XorGateGraphicsElement(nullptr));
    elem.reset(new GraphicsElement(nullptr));
    m_view.reset(new QGraphicsView(ui->workingSpaceTab));
    m_scene.reset(new Scene(QPen(Qt::black, 2), 16, ui->workingSpaceTab));
    m_scene->addItem(elemXOR.get());
    m_view->setScene(m_scene.get());
    m_view->setSceneRect(0, 0, ui->workingSpaceTab->width(), ui->workingSpaceTab->height());



}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_notButton_clicked()
{

}


void MainWindow::on_andButton_clicked()
{

}


void MainWindow::on_nandButton_clicked()
{

}


void MainWindow::on_orButton_clicked()
{

}


void MainWindow::on_xorButton_clicked()
{

}


void MainWindow::on_norButton_clicked()
{

}

