#include "cnew.h"
#include "csave.h"
#include "invoker.h"
#include "savechanges.h"
cNew::cNew(bool &edited_, Ui::MainWindow *ui_, MainWindow *th, QString &fileName):edited(&edited_), ui(ui_), form(th), mainFileName(&fileName){}
void cNew::exec()const{
    int temp=0;
    if(*edited)
    {
        temp = saveChanges();
        if(temp == QMessageBox::Save){
            Invoker invoker;
            invoker.exec(new cSave(ui, form, *edited, *mainFileName));
        }
    }
    if(!(temp == QMessageBox::Cancel)){
        *mainFileName = "Untitled";
        ui->textEdit->setEnabled(true);
        *edited = false;
        ui->textEdit->clear();
    }
}
cNew::~cNew(){
//    delete ui;
//    delete form;
//    delete edited;
}



