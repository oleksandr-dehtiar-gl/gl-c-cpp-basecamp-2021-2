/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action1;
    QAction *action2;
    QAction *action3;
    QAction *actiondef;
    QAction *actionExport_files;
    QWidget *centralwidget;
    QPushButton *add_file_1;
    QPushButton *compare_files;
    QPushButton *add_file_2;
    QTableWidget *tableWidget_1;
    QTableWidget *tableWidget_2;
    QPushButton *del_row;
    QPushButton *add_row;
    QPushButton *del_row_2;
    QPushButton *add_row_2;
    QMenuBar *menubar;
    QMenu *menufile;
    QMenu *menuTheme;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(833, 547);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../photo_new_wind/cute-panda-head-kawaii_no_davn.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        action1 = new QAction(MainWindow);
        action1->setObjectName(QString::fromUtf8("action1"));
        action2 = new QAction(MainWindow);
        action2->setObjectName(QString::fromUtf8("action2"));
        action3 = new QAction(MainWindow);
        action3->setObjectName(QString::fromUtf8("action3"));
        actiondef = new QAction(MainWindow);
        actiondef->setObjectName(QString::fromUtf8("actiondef"));
        actionExport_files = new QAction(MainWindow);
        actionExport_files->setObjectName(QString::fromUtf8("actionExport_files"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        add_file_1 = new QPushButton(centralwidget);
        add_file_1->setObjectName(QString::fromUtf8("add_file_1"));
        add_file_1->setGeometry(QRect(10, 10, 101, 31));
        add_file_1->setCursor(QCursor(Qt::PointingHandCursor));
        compare_files = new QPushButton(centralwidget);
        compare_files->setObjectName(QString::fromUtf8("compare_files"));
        compare_files->setGeometry(QRect(350, 10, 131, 31));
        compare_files->setCursor(QCursor(Qt::PointingHandCursor));
        add_file_2 = new QPushButton(centralwidget);
        add_file_2->setObjectName(QString::fromUtf8("add_file_2"));
        add_file_2->setGeometry(QRect(720, 10, 101, 31));
        add_file_2->setCursor(QCursor(Qt::PointingHandCursor));
        tableWidget_1 = new QTableWidget(centralwidget);
        tableWidget_1->setObjectName(QString::fromUtf8("tableWidget_1"));
        tableWidget_1->setGeometry(QRect(10, 50, 401, 451));
        tableWidget_2 = new QTableWidget(centralwidget);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(420, 50, 401, 451));
        del_row = new QPushButton(centralwidget);
        del_row->setObjectName(QString::fromUtf8("del_row"));
        del_row->setGeometry(QRect(120, 20, 51, 21));
        add_row = new QPushButton(centralwidget);
        add_row->setObjectName(QString::fromUtf8("add_row"));
        add_row->setGeometry(QRect(170, 20, 51, 21));
        del_row_2 = new QPushButton(centralwidget);
        del_row_2->setObjectName(QString::fromUtf8("del_row_2"));
        del_row_2->setGeometry(QRect(610, 20, 51, 21));
        add_row_2 = new QPushButton(centralwidget);
        add_row_2->setObjectName(QString::fromUtf8("add_row_2"));
        add_row_2->setGeometry(QRect(660, 20, 51, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 833, 20));
        menufile = new QMenu(menubar);
        menufile->setObjectName(QString::fromUtf8("menufile"));
        menuTheme = new QMenu(menufile);
        menuTheme->setObjectName(QString::fromUtf8("menuTheme"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menufile->addAction(menuTheme->menuAction());
        menufile->addSeparator();
        menufile->addAction(actionExport_files);
        menuTheme->addAction(action1);
        menuTheme->addAction(action2);
        menuTheme->addAction(action3);
        menuTheme->addAction(actiondef);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "GL_TASK_1", nullptr));
        action1->setText(QCoreApplication::translate("MainWindow", "Ocean Blue", nullptr));
        action2->setText(QCoreApplication::translate("MainWindow", "Valera", nullptr));
        action3->setText(QCoreApplication::translate("MainWindow", "Tea with milk", nullptr));
        actiondef->setText(QCoreApplication::translate("MainWindow", "def", nullptr));
        actionExport_files->setText(QCoreApplication::translate("MainWindow", "Export files", nullptr));
        add_file_1->setText(QCoreApplication::translate("MainWindow", "Add file 1", nullptr));
        compare_files->setText(QCoreApplication::translate("MainWindow", "Compare files", nullptr));
        add_file_2->setText(QCoreApplication::translate("MainWindow", "Add file 2", nullptr));
        del_row->setText(QCoreApplication::translate("MainWindow", "Del row", nullptr));
        add_row->setText(QCoreApplication::translate("MainWindow", "Add row", nullptr));
        del_row_2->setText(QCoreApplication::translate("MainWindow", "Del row", nullptr));
        add_row_2->setText(QCoreApplication::translate("MainWindow", "Add row", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuTheme->setTitle(QCoreApplication::translate("MainWindow", "Theme", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
