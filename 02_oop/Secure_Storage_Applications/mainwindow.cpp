#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtXml>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QCloseEvent>
#include <fstream>
#include <algorithm>
#include "passwordwindow.h"
#include "encdec.h"

const int PasswordsFileKey = 1234;

//=================Read/Write from/in file operators==========================
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
//===========================================

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


QString MainWindow::fileName(QString filePath) //Return fileName from path to file
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
    //Create password window
    PasswordWindow pw;
    pw.setModal(true);
    pw.exec();

    //Save password from window in variable
    int password = pw.getPassword();

    //Choosing the place where we want to save storage(XML file)
    QString newXmlFile = QFileDialog::getSaveFileName(this, "Create Storage", "C://", "XML (*.xml)");
    //Create storage(XML file)
    QFile oFile(newXmlFile);
    oFile.open(QIODevice::ReadWrite);
    oFile.close();

    //We write the file name and password to it in the file
    Password passwordInfo(fileName(newXmlFile).toStdString(), password);
    if(std::ifstream("passwords.txt").is_open() == false)
    {
        //If the file does not exist, then we create it, write information into it and encrypt
        encdec enc("passwords.txt");
        addPassword(passwordInfo);
        enc.encrypt(PasswordsFileKey);
    }
    else
    {
        //If the file exists, then we decrypt it, write the information and encrypt
        encdec enc("passwords.txt");
        enc.decrypt(PasswordsFileKey);
        addPassword(passwordInfo);
        enc.encrypt(PasswordsFileKey);
    }
}

void MainWindow::on_pushButton_clicked() // Open Storage
{
    //Decrypting the password file
    encdec enc("passwords.txt");
    enc.decrypt(PasswordsFileKey);

    //If some storage is already open and we want to open a new one, then we encrypt the open one
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

    //Password check
    bool correctPassword = false;
    while(correctPassword == false)
    {
        //Create password window
        PasswordWindow pw;
        pw.setModal(true);
        pw.exec();
        //Save password from window in variable
        int pass = pw.getPassword();
        //Select the storage we want to open
        QString tempStoragePath = QFileDialog::getOpenFileName(this, "Open Storage", "C://", "XML (*.xml)");
        for (auto i: getPasswords())
        {
            //If the password is correct, then we decrypt the storage and open
            if(i.name == fileName(tempStoragePath).toStdString() && i.password == pass)
            {
                correctPassword = true;
                storagePath = tempStoragePath;
                encdec xmlEnc(storagePath);
                xmlEnc.decrypt(pass);
            }
        }

        //Displaying a password error
        if (correctPassword == false)
        {
            QMessageBox::critical(this, "Error", "Wrong password");
        }
    }

    //Displaying files that are stored in the repository
    ui->listWidget->clear();
    printFiles();

    //Encrypting a password file
    enc.encrypt(PasswordsFileKey);
}

//Fills the map with the names of the files that are in the storage and the data that are stored in the files
std::map<QString, QString> MainWindow::readStorage()
{
    QFile xmlFile(storagePath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        qDebug()<<"Error to open file";
    }

    //We create an object with which to read from a file
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&xmlFile);
    xmlReader.readNext();   //Goes to the first item in the file
    QString fileName;
    QString fileContent;
    std::map<QString, QString> xmlContent;

    //Cycle around until we reach the end of the document
    while(!xmlReader.atEnd())
    {
        //Checking if an element is the start of a tag
        if(xmlReader.isStartElement())
        {       
            if(xmlReader.name() == "File")
            {
                //We take all the attributes of the tag and iterate over them for writing to fileName
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    fileName = attr.value().toString();
                }
                //we take the text from the body of the tag and write it to fileContent
                fileContent = xmlReader.readElementText();
                //Add pair to map
                xmlContent.emplace(fileName, fileContent);
            }
        }
        //Move on to the next file element
        xmlReader.readNext();
    }
    xmlFile.close();
    return xmlContent;
}

void MainWindow::printFiles()
{
    QFile xmlFile(storagePath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        qDebug()<<"Error to open file";
    }

    //We create an object with which to read from a file
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&xmlFile);
    xmlReader.readNext();   // Goes to the first item in the file

    //Cycle around until we reach the end of the document
    while(!xmlReader.atEnd())
    {
        //Checking if an element is the start of a tag
        if(xmlReader.isStartElement())
        {
            //Checks if the tag name is equal to the File
            if(xmlReader.name() == "File")
            {
                //We take all the attributes of the tag and iterate over them for adding to list
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    ui->listWidget->addItem(attr.value().toString());
                }
            }

        }
        //Move on to the next file element
        xmlReader.readNext();
    }
    xmlFile.close();
}

void MainWindow::on_pushButton_3_clicked() //Add new object
{
    std::map<QString, QString> xmlContent; //Create a map to store the file name and its contents
    xmlContent = readStorage();//Fill the map
    //Select the file we want to add to storage
    QString newFilePath = QFileDialog::getOpenFileName(this, "Add file", "C://", "All (*.*)");
    QString newFileName = fileName(newFilePath);
    QFile newFile(newFilePath);
    if(!newFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Already opened or there is another issue";
        newFile.close();
    }

    //Reading information from a file into a variable
    QTextStream newFileContent(&newFile);
    newFileContent.setCodec("UTF-8");
    QString tempString = newFileContent.readAll();

    //Open xmlFile
    QFile xmlFile(storagePath);
    xmlFile.open(QIODevice::WriteOnly);

    //We create an object with which to write to a file
    QXmlStreamWriter xmlWriter(&xmlFile);
    xmlWriter.setAutoFormatting(true);  // Install text auto-formatting
    xmlWriter.writeStartDocument();     // We start writing to the document
    xmlWriter.writeStartElement("Files");   // We write the first element with its name

    //We write the data that was already in the storage
    for (const auto& i : xmlContent)
    {
        xmlWriter.writeStartElement("File");//We write a tag with a name
        xmlWriter.writeAttribute("name",i.first);//Write attribute with file name
        xmlWriter.writeCharacters(i.second);//Write file content
        xmlWriter.writeEndElement();//Close tag
    }

    xmlWriter.writeStartElement("File");  // We write a tag with a name
    xmlWriter.writeAttribute("name", newFileName);//Write attribute with new file name

    xmlWriter.writeCharacters(tempString);//Write file content
    xmlWriter.writeEndElement();        // Close tag
    // Close "Files" tag
    xmlWriter.writeEndElement();
    // Finishing writing to the document
    xmlWriter.writeEndDocument();
    newFile.close();
    xmlFile.close();

    //Displaying files that are stored in the repository
    ui->listWidget->clear();
    printFiles();
}

void MainWindow::on_pushButton_GetObject_clicked() //Get Object
{
    QFile xmlFile(storagePath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        qDebug()<<"Error to open file";
    }

    //We create an object with which to read from a file
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&xmlFile);
    xmlReader.readNext();   // Goes to the first item in the file

    QString tempString;
    //Cycle around until we reach the end of the document
    while(!xmlReader.atEnd())
    {
        //Checking if an element is the start of a tag
        if(xmlReader.isStartElement())
        {
            //Checks if the tag name is equal to the file
            if(xmlReader.name() == "File")
            {
                //We take all the attributes of the tag and iterate over them to validate the file selected by the user
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    //If the attribute of the tag and the name of the file selected by the user coincide, then we write to the variable
                    if(ui->listWidget->currentItem()->text() == attr.value().toString())
                    {
                        tempString = xmlReader.readElementText();
                        break;
                    }
                }
            }

        }
        //Move on to the next file element
        xmlReader.readNext();
    }

    //Choose where we want to save the file
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "C://", "txt (*.txt)");
    QFile oFile(fileName);
    oFile.open(QIODevice::ReadWrite);

    //We write information to a file
    oFile.write(tempString.toUtf8());

    oFile.close();
}

void MainWindow::on_DeleteObject_clicked()
{
    std::map<QString, QString> xmlContent;
    xmlContent = readStorage();

    QFile xmlFile(storagePath);
    xmlFile.open(QIODevice::WriteOnly);

    //We create an object with which to read from a file
    QXmlStreamWriter xmlWriter(&xmlFile);
    xmlWriter.setAutoFormatting(true);  // Install text auto-formatting
    xmlWriter.writeStartDocument();     // We start writing to the document
    xmlWriter.writeStartElement("Files");   // We write the first element with its name
    //We write the data that was already in the storage
    for (const auto& i : xmlContent)
    {
        //If the filename is equal to the filename of the file we want to delete, skip it
        if(ui->listWidget->currentItem()->text() == i.first) continue;
        xmlWriter.writeStartElement("File");
        xmlWriter.writeAttribute("name",i.first);
        xmlWriter.writeCharacters(i.second);
        xmlWriter.writeEndElement();
    }

    //Close the "Files" tag
    xmlWriter.writeEndElement();
    //Finishing writing to the document
    xmlWriter.writeEndDocument();
    xmlFile.close();

    //Displaying files that are stored in the repository
    ui->listWidget->clear();
    printFiles();
}

//application close handler
void MainWindow::closeEvent(QCloseEvent *event)
{
    //If a file is open
    if(storagePath != "")
    {
        //Decrypt the password file
        encdec oldFile(storagePath);
        encdec passFile("passwords.txt");
        passFile.decrypt(PasswordsFileKey);

        //Looping through file names and passwords
        for (auto i : getPasswords())
        {
            //When we find the name of the open file Encrypt it
            if(i.name == fileName(storagePath).toStdString())
            {
                oldFile.encrypt(i.password);
                passFile.encrypt(PasswordsFileKey);
            }
        }
    }
    event->accept();
}
