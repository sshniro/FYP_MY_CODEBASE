/********************************************************************************
** Form generated from reading UI file 'videopanel.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPANEL_H
#define UI_VIDEOPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoPanel
{
public:
    QLabel *label;

    void setupUi(QWidget *VideoPanel)
    {
        if (VideoPanel->objectName().isEmpty())
            VideoPanel->setObjectName(QStringLiteral("VideoPanel"));
        VideoPanel->resize(873, 690);
        label = new QLabel(VideoPanel);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 310, 721, 341));
        label->setAutoFillBackground(true);

        retranslateUi(VideoPanel);

        QMetaObject::connectSlotsByName(VideoPanel);
    } // setupUi

    void retranslateUi(QWidget *VideoPanel)
    {
        VideoPanel->setWindowTitle(QApplication::translate("VideoPanel", "VideoPanel", 0));
        label->setText(QApplication::translate("VideoPanel", "VIDEO", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoPanel: public Ui_VideoPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPANEL_H
