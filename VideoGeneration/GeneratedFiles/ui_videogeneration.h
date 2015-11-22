/********************************************************************************
** Form generated from reading UI file 'videogeneration.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOGENERATION_H
#define UI_VIDEOGENERATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoGenerationClass
{
public:
    QWidget *centralWidget;
    QLineEdit *profileName_lineEdit;
    QLabel *label;
    QPushButton *generateVideoPushButton;
    QLabel *lblOutput;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VideoGenerationClass)
    {
        if (VideoGenerationClass->objectName().isEmpty())
            VideoGenerationClass->setObjectName(QStringLiteral("VideoGenerationClass"));
        VideoGenerationClass->resize(903, 783);
        centralWidget = new QWidget(VideoGenerationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        profileName_lineEdit = new QLineEdit(centralWidget);
        profileName_lineEdit->setObjectName(QStringLiteral("profileName_lineEdit"));
        profileName_lineEdit->setGeometry(QRect(230, 90, 271, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 90, 89, 25));
        generateVideoPushButton = new QPushButton(centralWidget);
        generateVideoPushButton->setObjectName(QStringLiteral("generateVideoPushButton"));
        generateVideoPushButton->setGeometry(QRect(550, 80, 231, 46));
        lblOutput = new QLabel(centralWidget);
        lblOutput->setObjectName(QStringLiteral("lblOutput"));
        lblOutput->setGeometry(QRect(70, 170, 741, 471));
        lblOutput->setAutoFillBackground(true);
        VideoGenerationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VideoGenerationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 903, 38));
        VideoGenerationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VideoGenerationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VideoGenerationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VideoGenerationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VideoGenerationClass->setStatusBar(statusBar);

        retranslateUi(VideoGenerationClass);

        QMetaObject::connectSlotsByName(VideoGenerationClass);
    } // setupUi

    void retranslateUi(QMainWindow *VideoGenerationClass)
    {
        VideoGenerationClass->setWindowTitle(QApplication::translate("VideoGenerationClass", "VideoGeneration", 0));
        label->setText(QApplication::translate("VideoGenerationClass", "ProfileId", 0));
        generateVideoPushButton->setText(QApplication::translate("VideoGenerationClass", "Generate Video", 0));
        lblOutput->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VideoGenerationClass: public Ui_VideoGenerationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOGENERATION_H
