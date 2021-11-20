#include "cnew.h"
#include "csave.h"
#include "invoker.h"
#include "savechanges.h"
cNew::cNew(bool &edited_, Ui::MainWindow *ui_, MainWindow *th):edited(&edited_), ui(ui_), form(th){}
void cNew::exec()const{
    int temp=0;
    if(*edited)
    {
        temp = saveChanges();
        if(temp == QMessageBox::Save){
            Invoker invoker;
            invoker.exec(new cSave(ui, form));
        }
    }
    if(!(temp == QMessageBox::Cancel)){
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



