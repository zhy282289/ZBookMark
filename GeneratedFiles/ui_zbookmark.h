/********************************************************************************
** Form generated from reading UI file 'zbookmark.ui'
**
** Created: Sat Oct 12 11:16:40 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZBOOKMARK_H
#define UI_ZBOOKMARK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZBookMarkClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ZBookMarkClass)
    {
        if (ZBookMarkClass->objectName().isEmpty())
            ZBookMarkClass->setObjectName(QString::fromUtf8("ZBookMarkClass"));
        ZBookMarkClass->resize(600, 400);
        menuBar = new QMenuBar(ZBookMarkClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ZBookMarkClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ZBookMarkClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ZBookMarkClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ZBookMarkClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ZBookMarkClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ZBookMarkClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ZBookMarkClass->setStatusBar(statusBar);

        retranslateUi(ZBookMarkClass);

        QMetaObject::connectSlotsByName(ZBookMarkClass);
    } // setupUi

    void retranslateUi(QMainWindow *ZBookMarkClass)
    {
        ZBookMarkClass->setWindowTitle(QApplication::translate("ZBookMarkClass", "ZBookMark", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ZBookMarkClass: public Ui_ZBookMarkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZBOOKMARK_H
