#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_grid.reset(new Grid(20));
    m_view.reset(new QGraphicsView(this));
    m_scene.reset(new QGraphicsScene(0,0, 1366, 768, this));

    m_view->setScene(m_scene.get());

    m_view->setSceneRect(0,0, 800, 800);
    m_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_view->setBackgroundBrush(m_grid->getDrawPattern());
    setCentralWidget(m_view.get());
    resize(800, 800);

}

MainWindow::~MainWindow()
{
    delete ui;
}
