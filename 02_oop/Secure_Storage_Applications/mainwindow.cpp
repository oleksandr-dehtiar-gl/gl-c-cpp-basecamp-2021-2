#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtXml>
#include <QTextStream>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Create Storage", "C://", "XML (*.xml)");
    QFile oFile(fileName);
    oFile.open(QIODevice::ReadWrite);
    oFile.close();
}

void MainWindow::on_pushButton_clicked()
{
    this->storagePath = QFileDialog::getOpenFileName(this, "Open Storage", "C://", "XML (*.xml)");
}

void MainWindow::on_pushButton_3_clicked()
{
    QString newFilePath = QFileDialog::getOpenFileName(this, "Add file", "C://", "All (*.*)");
    QFile newFile(newFilePath);
    if(!newFile.open(QFile::ReadOnly))
    {
        qDebug() << "Already opened or there is another issue";
        newFile.close();
    }
    QTextStream newFileContent(&newFile);



    QFile xmlFile(storagePath);
    if (!xmlFile.open(QFile::WriteOnly | QFile::Text ))
    {
       qDebug() << "Already opened or there is another issue";
       xmlFile.close();
    }

    QTextStream xmlContent(&xmlFile);

    QDomDocument document;

    QDomElement root = document.createElement("Files");
    document.appendChild(root);

    QDomElement student = document.createElement("File");
    student.setAttribute("Number", "1");

    student.appendChild(document.createTextNode(newFileContent.readAll()));
    root.appendChild(student);

    xmlContent << document.toString();
    xmlFile.close();

}


void MainWindow::on_pushButton_GetObject_clicked()
{
    //QString tempPath = QFileDialog::getOpenFileName(this, "Open Storage", "C://", "XML (*.xml)");
    QFile xmlFile(storagePath);
    if (!xmlFile.open(QFile::ReadOnly | QFile::Text ))
    {
        // Error while loading file
    }

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&xmlFile);
    xmlReader.readNext();   // Переходит к первому элементу в файле

    QString tempString;
    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name() == "File")
            {
                tempString = xmlReader.readElementText();
            }
        }


        xmlReader.readNext();
    }



    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "C://", "txt (*.txt)");
    QFile oFile(fileName);
    oFile.open(QIODevice::ReadWrite);

    oFile.write(tempString.toUtf8());

    oFile.close();
}
