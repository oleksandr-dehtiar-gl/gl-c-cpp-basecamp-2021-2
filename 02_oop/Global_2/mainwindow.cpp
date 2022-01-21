#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

// for add file to table
void addFile(QString fileName, QTableWidget *table);

// for export edit files
void saveToFile(QTableWidget *table, int count);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    // save theme -------------
    /*
    QDir dir("/GL_TASK_2/Sources");
    //QString s;

    //s = dir.relativeFilePath("/home/mary/file.txt");
    QString filN = dir.relativeFilePath("../Other files/settingsSave.txt");
    QFile  nFile(filN);

    if (!nFile.open(QFile::ReadWrite  | QFile::Text))
    {
      qDebug() << "could not open the file";
      return;
    }

    QTextStream str(&nFile);
    qDebug() << str.readLine();

    nFile.close();
    */

    on_actiondef_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ADD FILES --- --- --- --- --- ---
void MainWindow::on_add_file_1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open A File", "C:\\" );
    QTableWidget *table = ui->tableWidget_1;
    addFile(fileName, table);

}

void MainWindow::on_add_file_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open A File", "C:\\" );
    QTableWidget *table2 = ui->tableWidget_2;
    addFile(fileName, table2);

}

void addFile(QString fileName, QTableWidget *table){

    if (fileName != "")
    {
        QFile file(QFileInfo(fileName).absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        QTextStream out(&file);
        QList< QStringList > lists;
        QString line;
        do {
            line = out.readLine();
            lists << line.split("\t");
        } while (!line.isNull());

        // Set the table size (assuming the rows are all the same length).

        table->setRowCount( lists.size() );
        table->setColumnCount( lists[0].size() );

        for ( int row = 0; row < lists.size(); ++row ) {
            for ( int column = 0; column < lists[row].size(); ++column ) {
                table->setItem(row, column, new QTableWidgetItem(lists[row][column]));
                table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                table->setHorizontalHeaderLabels(QStringList() << fileName.split('/')[(fileName.split('/')).length()-1]);
            }
        }
     }

}

// COMPARE FILES --- --- --- --- --- ---
void MainWindow::on_compare_files_clicked()
{
    qDebug() << ui->tableWidget_1->model()->index(2 , 0);
    int table1Count = ui->tableWidget_1->rowCount();
    int table2Count = ui->tableWidget_2->rowCount();

    int countForLoopMax = (table1Count > table2Count) ? table1Count : table2Count;
    int countForLoopMin = (table1Count < table2Count) ? table1Count : table2Count;
    qDebug() << "max = "+QString::number(countForLoopMax) << "min = "+QString::number(countForLoopMin);

    for(int i = 0 ; i < countForLoopMax; i++){
        ui->tableWidget_1->model()->setData(ui->tableWidget_1->model()->index(i, 0), QColor(Qt::white), Qt::BackgroundRole);
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i, 0), QColor(Qt::white), Qt::BackgroundRole);

        if(i != countForLoopMin){
            if(ui->tableWidget_1->model()->index(i , 0).data() !=
                    ui->tableWidget_2->model()->index(i , 0).data()){
                ui->tableWidget_1->model()->setData(ui->tableWidget_1->model()->index(i, 0), QColor(255,134,40), Qt::BackgroundRole);
                ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i, 0), QColor(255,134,40), Qt::BackgroundRole);
            }
            else{
                ui->tableWidget_1->model()->setData(ui->tableWidget_1->model()->index(i, 0), QColor(100,255,40), Qt::BackgroundRole);
                ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i, 0), QColor(100,255,40), Qt::BackgroundRole);

            }
        }
    }
}

// THEMES --- --- --- --- --- ---
// Theme Ocean Blue
void MainWindow::on_action1_triggered()
{
    //BACK
    MainWindow::setStyleSheet("background-color: #71C9CE;");

    // BUTTON
    QString style= "border: 1px solid black; background-color: #A6E3E9;";
    ui->add_file_1->setStyleSheet(style);
    ui->add_file_2->setStyleSheet(style);
    ui->compare_files->setStyleSheet(style);
    ui->del_row->setStyleSheet(style);
    ui->del_row_2->setStyleSheet(style);
    ui->add_row->setStyleSheet(style);
    ui->add_row_2->setStyleSheet(style);

    //TOOL BAR
    ui->menubar->setStyleSheet("background-color: #CBF1F5;");

    //TABLE
    ui->tableWidget_1->setStyleSheet("background-color: #E3FDFD;");
    ui->tableWidget_2->setStyleSheet("background-color: #E3FDFD;");
}

// Theme Valera
void MainWindow::on_action2_triggered()
{
    //BACK
    MainWindow::setStyleSheet("background-color: #AA4A30;");

    // BUTTON
    QString style= "border: 1px solid black; background-color: #E89F71;";
    ui->add_file_1->setStyleSheet(style);
    ui->add_file_2->setStyleSheet(style);
    ui->compare_files->setStyleSheet(style);
    ui->del_row->setStyleSheet(style);
    ui->del_row_2->setStyleSheet(style);
    ui->add_row->setStyleSheet(style);
    ui->add_row_2->setStyleSheet(style);

    //TOOL BAR
    ui->menubar->setStyleSheet("background-color: #D57149;");

    //TABLE
    ui->tableWidget_1->setStyleSheet("background-color: #EDCFA9;");
    ui->tableWidget_2->setStyleSheet("background-color: #EDCFA9;");
}

// Theme Tea with milk
void MainWindow::on_action3_triggered()
{
    //BACK
    MainWindow::setStyleSheet("background-color: #596E79;");

    // BUTTON
    QString style= "border: 1px solid black; background-color: #DFD3C3;";
    ui->add_file_1->setStyleSheet(style);
    ui->add_file_2->setStyleSheet(style);
    ui->compare_files->setStyleSheet(style);
    ui->del_row->setStyleSheet(style);
    ui->del_row_2->setStyleSheet(style);
    ui->add_row->setStyleSheet(style);
    ui->add_row_2->setStyleSheet(style);

    //TOOL BAR
    ui->menubar->setStyleSheet("background-color: #C7B198;");

    //TABLE
    ui->tableWidget_1->setStyleSheet("background-color: #F0ECE3;");
    ui->tableWidget_2->setStyleSheet("background-color: #F0ECE3;");
}

// Theme def.
void MainWindow::on_actiondef_triggered()
{
    //BACK
    MainWindow::setStyleSheet("background-color: #f0f0f0;");

    // BUTTON
    QString style= "border: 1px solid #c0c0c0; background-color: #e1e1e1;";
    ui->add_file_1->setStyleSheet(style);
    ui->add_file_2->setStyleSheet(style);
    ui->compare_files->setStyleSheet(style);
    ui->del_row->setStyleSheet(style);
    ui->del_row_2->setStyleSheet(style);
    ui->add_row->setStyleSheet(style);
    ui->add_row_2->setStyleSheet(style);

    //TOOL BAR
    ui->menubar->setStyleSheet("background-color: #ffffff;");

    //TABLE
    ui->tableWidget_1->setStyleSheet("background-color: #ffffff;");
    ui->tableWidget_2->setStyleSheet("background-color: #ffffff;");
}

// EXPORT FILES --- --- --- --- --- ---
void MainWindow::on_actionExport_files_triggered()
{
    int table1Count = ui->tableWidget_1->rowCount();
    int table2Count = ui->tableWidget_2->rowCount();


    QTableWidget *table = ui->tableWidget_1;
    QTableWidget *table2 = ui->tableWidget_2;
    saveToFile(table, table1Count);
    saveToFile(table2, table2Count);

}

void saveToFile(QTableWidget *table, int count){
    QString tableText;
    for(int i = 0; i < count;i++){
        tableText += table->model()->index(i , 0).data().toString();
        tableText += "\n";
    }

    QString fname = QFileDialog::getSaveFileName(nullptr, tableText, ".", "Text files (*.txt);" );
    qDebug() << "name is : " << fname;
    QFile f(fname);
    f.open( QIODevice::WriteOnly );
    f.write(tableText.toUtf8());
    f.close();
}

//DELETE ROW FOR FILES 1-2 --- --- --- --- --- ---
void MainWindow::on_del_row_clicked()
{
    QModelIndexList indexes = ui->tableWidget_1->selectionModel()->selectedRows();
    while (!indexes.isEmpty()) {
        ui->tableWidget_1->model()->removeRows(indexes.last().row(), 1);
        indexes.removeLast();
    }
}
void MainWindow::on_del_row_2_clicked()
{
    QModelIndexList indexes = ui->tableWidget_2->selectionModel()->selectedRows();
    while (!indexes.isEmpty()) {
        ui->tableWidget_2->model()->removeRows(indexes.last().row(), 1);
        indexes.removeLast();
    }

}

// ADD ROW FOR FILES 1-2 --- --- --- --- --- ---
void MainWindow::on_add_row_clicked()
{
    ui->tableWidget_1->insertRow( ui->tableWidget_1->rowCount() );
}

void MainWindow::on_add_row_2_clicked()
{
    ui->tableWidget_2->insertRow( ui->tableWidget_2->rowCount() );
}

//--- --- --- --- --- --- --- ---- --- ---
//                             ==>FOR LIST<==
//    QString fileName = QFileDialog::getOpenFileName(this, "Open A File", "C:\\" );
//    if (fileName != "")
//    {
//        QFile file(QFileInfo(fileName).absoluteFilePath());
//        file.open(QIODevice::ReadOnly);
//        QTextStream out(&file);
//        //QTextStream stream(&file);
//        QString line;
//        do {
//            line = out.readLine(); //stream

//            /* do something with the line */
//            ui->listW_file_2->addItem(line);

//        } while (!line.isNull());
//        file.close();
//     }
//--- --- --- --- --- --- --- ---- --- ---




