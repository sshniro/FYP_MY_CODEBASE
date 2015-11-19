/********************************************************************************
** Form generated from reading UI file 'generatevideo.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEVIDEO_H
#define UI_GENERATEVIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateVideo
{
public:
    QLabel *label;
    QLineEdit *profileId_lineEdit;
    QPushButton *generatePushButton;

    void setupUi(QWidget *GenerateVideo)
    {
        if (GenerateVideo->objectName().isEmpty())
            GenerateVideo->setObjectName(QStringLiteral("GenerateVideo"));
        GenerateVideo->resize(665, 191);
        label = new QLabel(GenerateVideo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 50, 89, 25));
        profileId_lineEdit = new QLineEdit(GenerateVideo);
        profileId_lineEdit->setObjectName(QStringLiteral("profileId_lineEdit"));
        profileId_lineEdit->setGeometry(QRect(210, 50, 351, 31));
        generatePushButton = new QPushButton(GenerateVideo);
        generatePushButton->setObjectName(QStringLiteral("generatePushButton"));
        generatePushButton->setGeometry(QRect(250, 100, 150, 46));

        retranslateUi(GenerateVideo);

        QMetaObject::connectSlotsByName(GenerateVideo);
    } // setupUi

    void retranslateUi(QWidget *GenerateVideo)
    {
        GenerateVideo->setWindowTitle(QApplication::translate("GenerateVideo", "GenerateVideo", 0));
        label->setText(QApplication::translate("GenerateVideo", "Profile ID", 0));
        generatePushButton->setText(QApplication::translate("GenerateVideo", "Generate", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateVideo: public Ui_GenerateVideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEVIDEO_H
