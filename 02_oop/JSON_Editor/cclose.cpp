#include "cclose.h"
#include "csave.h"
#include "invoker.h"
#include "savechanges.h"
cClose::cClose(bool &edited_, Ui::MainWindow *ui_, MainWindow *th):edited(&edited_), ui(ui_), form(th){}
void cClose::exec()const{
    int temp=0;
    if(*edited)
    {
        temp = saveChanges();
        if(temp == QMessageBox::Save){
            Invoker invoker;
            invoker.exec(new cSave(ui, form, *edited));
        }
        *edited = false;
    }
    if(!(temp == QMessageBox::Cancel)){
        ui->textEdit->setEnabled(false);
        *edited = false;
        ui->textEdit->clear();
    }
}
cClose::~cClose(){
//    delete ui;
//    delete form;
//    delete edited;
}
