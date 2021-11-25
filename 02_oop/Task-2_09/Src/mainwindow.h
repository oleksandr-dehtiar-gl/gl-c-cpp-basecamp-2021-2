#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QKeyEvent>
#include <QDialog>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    virtual void keyPressEvent(QKeyEvent* event);

private:
    Ui::MainWindow* ui;
    void Generate();
    void Up();
    void Down();
    void Right();
    void Left();
    void Turn();
    void Color(int x, int y); // Change cell color

    int score;

    QWidget* centralWidget;
    QPushButton* Reset;
    QLabel* scoreText;
    QGridLayout* map;
    QLabel* cell[4][4];

private slots:
    void ResetGame();
};
#endif // MAINWINDOW_H
