#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_moveToRep_clicked();

    void on_cloneNewRep_clicked();

    void on_commitChanges_clicked();

    void on_addNewChangesToIndex_clicked();

    void on_showBranchList_clicked();

    void on_checkoutToBranch_clicked();

    void on_ShowCommitList_clicked();

    void on_checkoutToCommit_clicked();

private:
    Ui::MainWindow *ui;
    QString repositoryPath;

    void printList(const QString&);
    void printCommitList(const QString&);
    QString getCommitHash(QString commitInfo);
    QString castPath(QString);
};
#endif // MAINWINDOW_H
