/********************************************************************************
** Form generated from reading UI file 'qttesting.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTESTING_H
#define UI_QTTESTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtTestingClass
{
public:
    QWidget *centralWidget;
    QLabel *lblCamera1;
    QLabel *lblCamera2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtTestingClass)
    {
        if (QtTestingClass->objectName().isEmpty())
            QtTestingClass->setObjectName(QStringLiteral("QtTestingClass"));
        QtTestingClass->resize(1366, 600);
        centralWidget = new QWidget(QtTestingClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblCamera1 = new QLabel(centralWidget);
        lblCamera1->setObjectName(QStringLiteral("lblCamera1"));
        lblCamera1->setGeometry(QRect(0, 0, 751, 541));
        lblCamera1->setAutoFillBackground(true);
        lblCamera2 = new QLabel(centralWidget);
        lblCamera2->setObjectName(QStringLiteral("lblCamera2"));
        lblCamera2->setGeometry(QRect(770, 0, 591, 551));
        lblCamera2->setAutoFillBackground(true);
        QtTestingClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtTestingClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1366, 21));
        QtTestingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtTestingClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtTestingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtTestingClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtTestingClass->setStatusBar(statusBar);

        retranslateUi(QtTestingClass);

        QMetaObject::connectSlotsByName(QtTestingClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtTestingClass)
    {
        QtTestingClass->setWindowTitle(QApplication::translate("QtTestingClass", "QtTesting", 0));
        lblCamera1->setText(QString());
        lblCamera2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtTestingClass: public Ui_QtTestingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTESTING_H
