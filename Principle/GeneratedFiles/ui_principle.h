/********************************************************************************
** Form generated from reading UI file 'principle.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPLE_H
#define UI_PRINCIPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrincipleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PrincipleClass)
    {
        if (PrincipleClass->objectName().isEmpty())
            PrincipleClass->setObjectName(QStringLiteral("PrincipleClass"));
        PrincipleClass->resize(600, 400);
        menuBar = new QMenuBar(PrincipleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        PrincipleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PrincipleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PrincipleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PrincipleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PrincipleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PrincipleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PrincipleClass->setStatusBar(statusBar);

        retranslateUi(PrincipleClass);

        QMetaObject::connectSlotsByName(PrincipleClass);
    } // setupUi

    void retranslateUi(QMainWindow *PrincipleClass)
    {
        PrincipleClass->setWindowTitle(QApplication::translate("PrincipleClass", "Principle", 0));
    } // retranslateUi

};

namespace Ui {
    class PrincipleClass: public Ui_PrincipleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPLE_H
