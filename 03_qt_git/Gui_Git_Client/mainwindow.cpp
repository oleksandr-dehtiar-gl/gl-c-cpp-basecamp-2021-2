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

void MainWindow::printList(const QString& path)
{
    std::vector<std::string> results;
    std::ifstream in(path.toUtf8() + "/temp.txt");
    if(!in.is_open())
    {
        QMessageBox::warning(this,"Error", "Error open temp file!");
    }
    else
    {
        std::string line;
        while(getline(in, line))
        {
            if (line.empty())
            {
                continue;
            }
            results.push_back(line);
        }
    }
    ui->listWidget->clear();
    for (auto i : results)
    {
        ui->listWidget->addItem(QString::fromStdString(i));
    }
}

void MainWindow::printCommitList(const QString& path)
{
    std::vector<std::string> results;
    std::ifstream in(path.toUtf8() + "/temp.txt");
    if(!in.is_open())
    {
        QMessageBox::warning(this,"Error", "Error open temp file!");
    }
    else
    {
        std::string line, commitInfo;
        int counter = 0;
        while(getline(in, line))
        {
            if (line.empty())
            {
                continue;
            }

            if(counter == 3)
            {
                commitInfo += line;
                results.push_back(commitInfo);
                commitInfo = "";
                counter = -1;
            }
            else
            {
                line+='\n';
                commitInfo += line;
            }
               counter++;
        }

    }
    ui->listWidget->clear();
    for (auto i : results)
    {
        ui->listWidget->addItem(QString::fromStdString(i));
    }
}

QString MainWindow::castPath(QString path)
{
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == '/')
        {
            path[i] = '\\';
            path.insert(i, '\\');
        }
    }
    return path;
}

QString MainWindow::getCommitHash(QString commitInfo)
{
    QString commitHash = "";

    for (auto i : commitInfo)
    {
        if(i == '\n') break;
        commitHash += i;
    }
    commitHash.remove(0,7);

    return commitHash;
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
    else if(repositoryPath.isEmpty())
    {
        QMessageBox::warning(this,"Error", "Select a repository");
    }
    else
    {
        QMessageBox::information(this,"Info", "Files added to index!");
    }
}

void MainWindow::on_showBranchList_clicked()
{
    if(repositoryPath.isEmpty())
    {
        QMessageBox::warning(this,"Error", "Select a repository");
    }
    else
    {
        int i = system("cd /d " + repositoryPath.toUtf8() + " && git branch > temp.txt");
        if (i != 0)
        {
            QMessageBox::warning(this,"Error", "Something went wrong!");
        }
        else
        {
            QString repositoryPathCopy = castPath(repositoryPath);
            ui->commitedChangesLabel->setText(repositoryPathCopy);
            printList(repositoryPath);
        }
    }
   //Enter code to delete temp file
}

void MainWindow::on_checkoutToBranch_clicked()
{
    if(repositoryPath.isEmpty())
    {
        QMessageBox::warning(this,"Error", "Select a repository");
    }
    else
    {
        if(ui->listWidget->selectedItems().isEmpty())
        {
            QMessageBox::warning(this,"Error", "Select the branch!");
            return;
        }

        QString selectedBranch = ui->listWidget->currentItem()->text();
        int i = system("cd /d " + repositoryPath.toUtf8() + " && git checkout " + selectedBranch.toUtf8());

        if (i != 0)
        {
            QMessageBox::warning(this,"Error", "Something went wrong!");
        }
        else
        {
            on_showBranchList_clicked();
        }
    }
    //Enter code to delete tempfile
}

void MainWindow::on_ShowCommitList_clicked()
{
    if(repositoryPath.isEmpty())
    {
        QMessageBox::warning(this,"Error", "Select a repository");
    }
    else
    {
        int i = system("cd /d " + repositoryPath.toUtf8() + " && git log > temp.txt");
        if (i != 0)
        {
            QMessageBox::warning(this,"Error", "Something went wrong!");
        }
        else
        {
            QString repositoryPathCopy = castPath(repositoryPath);
            printCommitList(repositoryPathCopy);
        }
    }
   //Enter code to delete temp file
}

void MainWindow::on_checkoutToCommit_clicked()
{
    if(repositoryPath.isEmpty())
    {
        QMessageBox::warning(this,"Error", "Select a repository");
    }
    else
    {
        if(ui->listWidget->selectedItems().isEmpty())
        {
            QMessageBox::warning(this,"Error", "Select the branch!");
            return;
        }

        QString selectedCommit = getCommitHash(ui->listWidget->currentItem()->text());

        int i = system("cd /d " + repositoryPath.toUtf8() + " && git checkout " + selectedCommit.toUtf8());

        if (i != 0)
        {
            QMessageBox::warning(this,"Error", "Something went wrong!");
        }
        else
        {
            on_ShowCommitList_clicked();
        }
    }
}


