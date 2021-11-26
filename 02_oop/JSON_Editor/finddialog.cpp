#include "finddialog.h"
#include "ui_finddialog.h"

findDialog::findDialog(Ui::MainWindow *ui_, QWidget *parent) :
    QDialog(parent),
    uiFinder(new Ui::findDialog), uiMain(ui_)
{
    uiFinder->setupUi(this);
}

findDialog::~findDialog()
{
    delete uiFinder;
}

void findDialog::on_findButton_clicked()
{
    uiMain->textEdit->find(uiFinder->lineEdit->text());
}

