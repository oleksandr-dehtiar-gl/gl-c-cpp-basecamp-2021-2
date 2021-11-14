#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtXml>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <algorithm>
#include "passwordwindow.h"
#include "encdec.h"
#include <fstream>

struct Password;
std::ifstream& operator>>(std::ifstream& is, Password& st)
{
    is >> st.name  >> st.password;
    return is;
}
std::ofstream& operator<<(std::ofstream& os, Password& st)
{
    os << st.name << " " << st.password << std::endl;
    return os;
}

void MainWindow::addPassword(Password ps)
{
    std::ofstream oFile("passwords.txt", std::ios::app);

    oFile << ps;
    oFile.close();
}

std::vector<Password> MainWindow::getPasswords()
    {
        std::ifstream iFile("passwords.txt");
        Password pass;
        std::vector<Password> passwords;
        while (iFile >> pass)
        {
            passwords.push_back(pass);
        }
        return passwords;
    }

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

void MainWindow::on_pushButton_2_clicked() //New Storage
{
    PasswordWindow pw;
    pw.setModal(true);
    pw.exec();
    int password = pw.getPassword();

    QString newXmlFile = QFileDialog::getSaveFileName(this, "Create Storage", "C://", "XML (*.xml)");
    QFile oFile(newXmlFile);
    oFile.open(QIODevice::ReadWrite);
    oFile.close();

    Password passwordInfo(fileName(newXmlFile).toStdString(), password);
    if(std::ifstream("passwords.txt").is_open() == false)
    {
        encdec enc("passwords.txt");
        addPassword(passwordInfo);
        enc.encrypt(1234);
    }
    else
    {
        encdec enc("passwords.txt");
        enc.decrypt(1234);
        addPassword(passwordInfo);
        enc.encrypt(1234);
    }
}

void MainWindow::on_pushButton_clicked() // Open Storage
{
    encdec enc("passwords.txt");
    enc.decrypt(1234);
    if(storagePath != "")
    {
        encdec oldFile(storagePath);
        for (auto i : getPasswords())
        {
            if(i.name == fileName(storagePath).toStdString())
            {
                oldFile.encrypt(i.password);
            }
        }
    }

    bool correctPassword = false;
    while(correctPassword == false)
    {
        PasswordWindow pw;
        pw.setModal(true);
        pw.exec();
        int pass = pw.getPassword();
        QString tempStoragePath = QFileDialog::getOpenFileName(this, "Open Storage", "C://", "XML (*.xml)");
        for (auto i: getPasswords())
        {
            if(i.name == fileName(tempStoragePath).toStdString() && i.password == pass)
            {
                correctPassword = true;
                storagePath = tempStoragePath;
                encdec xmlEnc(storagePath);
                xmlEnc.decrypt(pass);
            }
        }

        if (correctPassword == false)
        {
            QMessageBox::critical(this, "Error", "Wrong password");
        }
    }




    enc.encrypt(1234);

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

void MainWindow::on_pushButton_3_clicked() //Add new object
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


void MainWindow::on_pushButton_GetObject_clicked() //Get Object
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
