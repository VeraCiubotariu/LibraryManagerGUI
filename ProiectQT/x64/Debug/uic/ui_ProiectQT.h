/********************************************************************************
** Form generated from reading UI file 'ProiectQT.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROIECTQT_H
#define UI_PROIECTQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProiectQTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProiectQTClass)
    {
        if (ProiectQTClass->objectName().isEmpty())
            ProiectQTClass->setObjectName(QString::fromUtf8("ProiectQTClass"));
        ProiectQTClass->resize(600, 400);
        menuBar = new QMenuBar(ProiectQTClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ProiectQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProiectQTClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ProiectQTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ProiectQTClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ProiectQTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ProiectQTClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ProiectQTClass->setStatusBar(statusBar);

        retranslateUi(ProiectQTClass);

        QMetaObject::connectSlotsByName(ProiectQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProiectQTClass)
    {
        ProiectQTClass->setWindowTitle(QCoreApplication::translate("ProiectQTClass", "ProiectQT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProiectQTClass: public Ui_ProiectQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROIECTQT_H
