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
    }
    else
    {

//        QString gitCommand = "git clone " + ui->pathToCloneLine->text();
//        ui->commitedChangesLabel->setText(gitCommand);

          //system("cd /d C:/Users && dir > pingresult.txt");
          //system("cd /d " + ui->commitedChangesLabel->text().toUtf8() + " && git --version > tempFile.txt");
         // std::ifstream in(ui->commitedChangesLabel->text().toUtf8() + "/tempFile.txt");

          //system("dir > pingresult.txt");

        std::vector<std::string> results;
        int i = system("cd /d " + ui->commitedChangesLabel->text().toUtf8() + " && git clone " + ui->pathToCloneLine->text().toUtf8());

        if (i != 0)
        {
            QMessageBox::warning(this,"Error", "Something went wrong!");
        }
//        std::ifstream in("tempFile.txt");
//        std::string line;
//            while(getline(in, line))
//            results.push_back(line);

//        for (auto i: results)
//        {
//            ui->commitedChangesLabel->setText(ui->commitedChangesLabel->text() + QString::fromStdString(i));
//        }
    }
}
