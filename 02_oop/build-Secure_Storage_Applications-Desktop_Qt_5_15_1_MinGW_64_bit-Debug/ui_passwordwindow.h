/********************************************************************************
** Form generated from reading UI file 'passwordwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDWINDOW_H
#define UI_PASSWORDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PasswordWindow
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *passwordLabel;
    QPushButton *Enter;

    void setupUi(QDialog *PasswordWindow)
    {
        if (PasswordWindow->objectName().isEmpty())
            PasswordWindow->setObjectName(QString::fromUtf8("PasswordWindow"));
        PasswordWindow->resize(404, 113);
        widget = new QWidget(PasswordWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 20, 381, 70));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        passwordLabel = new QLineEdit(widget);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        verticalLayout->addWidget(passwordLabel);

        Enter = new QPushButton(widget);
        Enter->setObjectName(QString::fromUtf8("Enter"));

        verticalLayout->addWidget(Enter);


        retranslateUi(PasswordWindow);

        QMetaObject::connectSlotsByName(PasswordWindow);
    } // setupUi

    void retranslateUi(QDialog *PasswordWindow)
    {
        PasswordWindow->setWindowTitle(QCoreApplication::translate("PasswordWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("PasswordWindow", "Enter password:", nullptr));
        Enter->setText(QCoreApplication::translate("PasswordWindow", "Enter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswordWindow: public Ui_PasswordWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDWINDOW_H
