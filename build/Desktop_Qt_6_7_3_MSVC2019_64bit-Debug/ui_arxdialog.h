/********************************************************************************
** Form generated from reading UI file 'arxdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARXDIALOG_H
#define UI_ARXDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QSpinBox *spinBox;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(354, 273);
        horizontalLayout = new QHBoxLayout(Dialog);
        horizontalLayout->setObjectName("horizontalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(Dialog);
        label->setObjectName("label");

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(6, QFormLayout::LabelRole, label_3);

        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName("pushButton");

        formLayout->setWidget(8, QFormLayout::LabelRole, pushButton);

        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName("pushButton_2");

        formLayout->setWidget(10, QFormLayout::LabelRole, pushButton_2);

        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit);

        lineEdit_2 = new QLineEdit(Dialog);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_2);

        spinBox = new QSpinBox(Dialog);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(1);

        formLayout->setWidget(6, QFormLayout::FieldRole, spinBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(8, QFormLayout::FieldRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(10, QFormLayout::FieldRole, verticalSpacer_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(9, QFormLayout::LabelRole, verticalSpacer_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(7, QFormLayout::LabelRole, verticalSpacer_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(5, QFormLayout::LabelRole, verticalSpacer_5);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer_6);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(11, QFormLayout::LabelRole, verticalSpacer_7);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(0, QFormLayout::LabelRole, verticalSpacer_8);

        label_4 = new QLabel(Dialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(0, QFormLayout::FieldRole, label_4);

        label_5 = new QLabel(Dialog);
        label_5->setObjectName("label_5");

        formLayout->setWidget(1, QFormLayout::FieldRole, label_5);


        horizontalLayout->addLayout(formLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "A", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "B", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "k", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "OK", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "Cancel", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p>Enter numbers with a decimal point, separated </p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "by a semicolon (;). Example: 3.14; 2.71; 1.618", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARXDIALOG_H
