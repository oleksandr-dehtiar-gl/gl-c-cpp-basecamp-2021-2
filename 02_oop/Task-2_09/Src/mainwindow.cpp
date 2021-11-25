#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    map = new QGridLayout(centralWidget);

    Reset = new QPushButton();
    Reset->setText("New / Reset");
    QObject::connect(Reset, SIGNAL(clicked()), this, SLOT(ResetGame()));
    map->addWidget(Reset, 0, 0);

    scoreText = 0;
    scoreText = new QLabel("Score: \n 0", this);
    scoreText->setAlignment(Qt::AlignCenter);
    scoreText->setStyleSheet("QLabel { background-color: #bbae9e; color: white; font:15pt; "
                             "font-weight:200; border-radius: 5px; }");
    map->addWidget(scoreText, 0, 3);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            cell[i][j] = new QLabel("", this);
            map->addWidget(cell[i][j], i + 1, j);
            cell[i][j]->setAlignment(Qt::AlignCenter);
            Color(i, j);
        }
    cell[1][0]->setFocus();
    setWindowTitle("The Game 2048");
    setFixedSize(500, 500);
    Generate();
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            delete cell[i][j];
}

void MainWindow::ResetGame()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            cell[i][j]->setText("");
            Color(i, j);
        }
    score = 0;
    scoreText = 0;
    scoreText = new QLabel("Score: \n 0", this);
    scoreText->setAlignment(Qt::AlignCenter);
    scoreText->setStyleSheet("QLabel { background-color: #bbae9e; color: white; font:15pt; "
                             "font-weight:200; border-radius: 5px; }");
    map->addWidget(scoreText, 0, 3);
    Reset->clearFocus();
    Generate();
}

void MainWindow::Generate()
{
    bool hasPlace = false;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            if (cell[i][j]->text() == "" || cell[i][j]->text() == "2")
            {
                hasPlace = true;
                break;
            }
        }
    if (!hasPlace)
    {
        QDialog* endDialog = new QDialog();
        endDialog->setMinimumWidth(200);
        endDialog->show();
    }
    int row = 0, column = 0;
    do
    {
        row = rand() % 4;
        column = rand() % 4;
    } while (cell[row][column]->text() != "" && cell[row][column]->text() != "2");
    cell[row][column]->setText(QString::number(cell[row][column]->text().toInt() + 2));
    Color(row, column);
}

void MainWindow::Color(int i, int j)
{
    switch (cell[i][j]->text().toInt())
    {
        case 0:
            cell[i][j]->setStyleSheet("QLabel { background-color: #cdc1b5; color: black; "
                                      "font:26pt; font-weight:350; border-radius: 5px;}");
            break;
        case 2:
            cell[i][j]->setStyleSheet("QLabel { background-color: #eee4da; color: black; "
                                      "font:26pt; font-weight:350; border-radius: 5px;}");
            break;
        case 4:
            cell[i][j]->setStyleSheet("QLabel { background-color: #eddfc4; color: black; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
        case 8:
            cell[i][j]->setStyleSheet("QLabel { background-color: #f4b17a; color: white; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
        case 16:
            cell[i][j]->setStyleSheet("QLabel { background-color: #f79663; color: white; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
        case 32:
            cell[i][j]->setStyleSheet("QLabel { background-color: #f67d62; color: white; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
        case 64:
            cell[i][j]->setStyleSheet("QLabel { background-color: #f65e39; color: white; "
                                      "font:26pt; font-weight:350; border-radius: 5px;}");
            break;
        case 128:
            cell[i][j]->setStyleSheet("QLabel { background-color: #edce73; color: white; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
        case 256:
            cell[i][j]->setStyleSheet("QLabel { background-color: #e9cf58; color: white; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
        case 512:
            cell[i][j]->setStyleSheet("QLabel { background-color: #edc651; color: white; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
        case 1024:
            cell[i][j]->setStyleSheet("QLabel { background-color: #eec744; color: white; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
        case 2048:
            cell[i][j]->setStyleSheet("QLabel { background-color: #edca64; color: white; "
                                      "font:26pt; font-weight:350;border-radius: 5px;}");
            break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Up:
            Up();
            break;
        case Qt::Key_Down:
            Down();
            break;
        case Qt::Key_Left:
            Right();
            break;
        case Qt::Key_Right:
            Left();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::Down()
{
    QString* a[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            a[i][j] = new QString(cell[i][j]->text());
    {
        for (int j = 0; j < 4; ++j)
        for (int i = 3; i >= 0; --i)
            if (cell[i][j]->text() == "")
                for (int k = i - 1; k >= 0; --k)
                    if (cell[k][j]->text() != "")
                    {
                        cell[i][j]->setText(cell[k][j]->text());
                        Color(i, j);
                        cell[k][j]->setText("");
                        Color(k, j);
                        break;
                    }
    int k;
    for (int j = 0; j < 4; ++j)
    {
        for (int i = 2; i >= 0; i--)
        {
            if (cell[i][j]->text() == cell[i + 1][j]->text() && cell[i][j]->text() != "")
            {
                cell[i + 1][j]->setText(QString::number(cell[i + 1][j]->text().toInt() * 2));
                score += cell[i + 1][j]->text().toInt();
                scoreText->setText("Score: \n" + QString::number(score));
                Color(i + 1, j);

                k = i;
                while (k > 0)
                {
                    k--;
                    cell[k + 1][j]->setText(cell[k][j]->text());
                    Color(k + 1, j);
                }
                if (k == 0)
                {
                    cell[0][j]->setText("");
                    Color(0, j);
                }
            }
        }
    }
    }
    bool flag = false;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (a[i][j] != cell[i][j]->text())
                flag = true;
    if (flag)
        Generate();
}

void MainWindow::Up()
{
    Turn();
    Turn();
    Down();
    Turn();
    Turn();
}

void MainWindow::Right()
{
    Turn();
    Down();
    Turn();
    Turn();
    Turn();
}

void MainWindow::Left()
{
    Turn();
    Turn();
    Turn();
    Down();
    Turn();
}

void MainWindow::Turn()
{
    int a[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            a[4 - j - 1][i] = cell[i][j]->text().toInt();
        }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            if (a[i][j] == 0)
            {
                cell[i][j]->setText("");
            }
            else
            {
                cell[i][j]->setText(QString::number(a[i][j]));
            }
            Color(i, j);
        }
}
/*
MainWindow::~MainWindow()
{
    delete ui;
}
*/
