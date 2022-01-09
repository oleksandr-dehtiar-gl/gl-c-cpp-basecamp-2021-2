#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->commitedChangesLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_moveToRep_clicked()
{
    repositoryPath = QFileDialog::getExistingDirectory(this, "Please enter path");
    ui->commitedChangesLabel->setText(repositoryPath);
}

void MainWindow::on_cloneNewRep_clicked()
{
    if(ui->pathToCloneLine->text().isEmpty())
    {
        ui->commitedChangesLabel->setText("Enter the path to rep");
        QMessageBox::warning(this,"Error", "Enter the link to the repository you want to copy");
    }
    else if(repositoryPath.isEmpty())
    {
        QMessageBox::warning(this,"Error", "Select a repository");
    }
    else
    {

//        QString gitCommand = "git clone " + ui->pathToCloneLine->text();
//        ui->commitedChangesLabel->setText(gitCommand);

          //system("cd /d C:/Users && dir > pingresult.txt");
          //system("cd /d " + ui->commitedChangesLabel->text().toUtf8() + " && git --version > tempFile.txt");
         // std::ifstream in(ui->commitedChangesLabel->text().toUtf8() + "/tempFile.txt");

          //system("dir > pingresult.txt");
        int i = system("cd /d " + repositoryPath.toUtf8() + " && git clone " + ui->pathToCloneLine->text().toUtf8());

        if (i != 0)
        {
            QMessageBox::warning(this,"Error", "Something went wrong!");
        }
        else
        {
            ui->pathToCloneLine->setText("");
        }
    }
}

void MainWindow::on_commitChanges_clicked()
{
    if(ui->commitNameLine->text().isEmpty())
    {
        //ui->commitedChangesLabel->setText("Enter the path to rep");
        QMessageBox::warning(this,"Error", "Enter the commit name");
    }
    else if(repositoryPath.isEmpty())
    {
        QMessageBox::warning(this,"Error", "Select a repository");
    }
    else
    {
        int i = system("cd /d " + repositoryPath.toUtf8() + " && git commit -m " + ui->commitNameLine->text().toUtf8());
        if (i != 0)
        {
            QMessageBox::warning(this,"Error", "Something went wrong!");
        }
        else
        {
            ui->commitNameLine->setText(" ");
        }
    }
}

void MainWindow::on_addNewChangesToIndex_clicked()
{
    int i = system("cd /d " + repositoryPath.toUtf8() + " && git add .");
    if (i != 0)
    {
        QMessageBox::warning(this,"Error", "Something went wrong!");
    }
    else
    {
        QMessageBox::information(this,"Info", "Files added to index!");
    }
}
