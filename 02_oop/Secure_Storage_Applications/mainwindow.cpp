#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtXml>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <algorithm>
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

QString MainWindow::fileName(QString filePath)
{
    QString fileName;

    for (int i = filePath.size() - 1; ; i--)
    {
        if(filePath[i] != '/')
        {
            fileName.append(filePath[i]);
        }
        else if(filePath[i] == '/')
        {
            break;
        }
    }
    std::reverse(fileName.begin(), fileName.end());
    return fileName;
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

std::map<QString, QString> MainWindow::readStorage()
{
    QFile xmlFile(storagePath);
    if (!xmlFile.open(QFile::ReadOnly | QFile::Text ))
    {
        // Error while loading file
    }

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&xmlFile);
    xmlReader.readNext();   // Переходит к первому элементу в файле

    QString tempString;
    QString fileName;
    QString fileContent;
    std::map<QString, QString> xmlContent;
    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name() == "File")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    fileName = attr.value().toString();
                }
                fileContent = xmlReader.readElementText();
                xmlContent.emplace(fileName, fileContent);
            }

        }


        xmlReader.readNext();
    }
    xmlFile.close();
    return xmlContent;
}

void MainWindow::on_pushButton_3_clicked()
{
    std::map<QString, QString> xmlContent;
    xmlContent = readStorage();
    QString newFilePath = QFileDialog::getOpenFileName(this, "Add file", "C://", "All (*.*)");
    QString newFileName = fileName(newFilePath);
    QFile newFile(newFilePath);
    if(!newFile.open(QFile::ReadOnly))
    {
        qDebug() << "Already opened or there is another issue";
        newFile.close();
    }

    QTextStream newFileContent(&newFile);
    newFileContent.setCodec("UTF-8");
    QString tempString = newFileContent.readAll();

    QFile xmlFile(storagePath);
    xmlFile.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&xmlFile);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("Files");   // Записываем первый элемент с его именем
    for (const auto& i : xmlContent)
    {
        xmlWriter.writeStartElement("File");
        xmlWriter.writeAttribute("name",i.first);
        xmlWriter.writeCharacters(i.second);
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeStartElement("File");  // Записываем тег с именем для первого чекбокса
    xmlWriter.writeAttribute("name", newFileName);

    xmlWriter.writeCharacters(tempString);
    xmlWriter.writeEndElement();        // Закрываем тег
    /* Закрываем тег "Files"
     * */
    xmlWriter.writeEndElement();
    /* Завершаем запись в документ
     * */
    xmlWriter.writeEndDocument();
    newFile.close();
    xmlFile.close();   // Закрываем файл
}


void MainWindow::on_pushButton_GetObject_clicked()
{
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
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if(ui->FileName->text() == attr.value().toString())
                    {
                        tempString = xmlReader.readElementText();
                        break;
                    }
                }
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
