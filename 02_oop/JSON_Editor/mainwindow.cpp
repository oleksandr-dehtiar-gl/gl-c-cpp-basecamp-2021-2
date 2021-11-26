#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cquit.h"
#include "cabout.h"
#include "csave.h"
#include "cnew.h"
#include "cclose.h"
#include "copen.h"
#include "validator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    invoker = new Invoker();
    status_AmountOfCharacters = new QLabel();
    status_JSON_Validated = new QLabel();
    this->statusBar()->addWidget(status_AmountOfCharacters);
    this->statusBar()->addWidget(status_JSON_Validated);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete invoker;
    delete status_AmountOfCharacters;
    delete status_JSON_Validated;
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionFind_triggered()
{
    finder = new findDialog(ui, this);
    finder->show();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}
void MainWindow::on_actionQuit_triggered()
{
    invoker->exec(new cQuit());
}

void MainWindow::on_actionNew_triggered()
{
    invoker->exec(new cNew(edited, ui, this, fileName));
    this->setWindowTitle("JSON Editor - " + fileName);
}

void MainWindow::on_actionOpen_triggered()
{
    invoker->exec(new cOpen(edited, ui, this, fileName));
    this->setWindowTitle("JSON Editor - " + fileName);
}

void MainWindow::on_actionAbout_triggered()
{
    invoker->exec(new cAbout());
}

void MainWindow::on_actionClose_triggered()
{
    invoker->exec(new cClose(edited, ui, this, fileName));
    this->setWindowTitle("JSON Editor");
}

void MainWindow::on_actionSave_triggered()
{
    invoker->exec(new cSave(ui, this, edited, fileName));
    this->setWindowTitle("JSON Editor - " + fileName);
}

void MainWindow::on_textEdit_textChanged()
{
    edited = true;
    status_AmountOfCharacters->setText("Amount of characters: " + QString::number(ui->textEdit->toPlainText().size()));
    status_JSON_Validated->setText("JSON validator says the file is not validated");
}

void MainWindow::on_actionValidate_json_file_triggered()
{
    Validator validator;
    bool temp=validator.exec(ui->textEdit->toPlainText());
    status_JSON_Validated->setText("JSON validator says the file is " + QString(temp?"right":"wrong"));
}

