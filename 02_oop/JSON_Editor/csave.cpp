#include "csave.h"
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include "./ui_mainwindow.h"
cSave::cSave(Ui::MainWindow *ui_, MainWindow *th):ui(ui_), form(th){}
cSave::~cSave(){
    delete ui;
    delete form;
}
void cSave::exec() const
{
    QString fileName = QFileDialog::getSaveFileName(form, QString::fromUtf8("Save the File"), "",
                                                    QString::fromUtf8("Text file (*.txt);;JSON file (*.json)"));
    if (fileName.isEmpty())
            return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(form, QObject::tr("Unable to open file"),
                file.errorString());
            return;
        }
        QTextStream out(&file);
                out << ui->textEdit->toPlainText();
    }
}
