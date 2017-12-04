/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Dec 3 13:04:04 2017
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessUI
{
public:
    QLabel *label_origin;
    QLabel *label_process;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_open;
    QPushButton *pushButton_save;
    QSlider *horizontalSliderSoftSkin;
    QSlider *horizontalSliderWhite;
    QSlider *horizontalSliderSharp;
    QLabel *labelSoftSkin;
    QLabel *labelWhite;
    QLabel *labelSharp;
    QSlider *horizontalSliderThin;
    QLabel *labelThin;

    void setupUi(QWidget *ImageProcessUI)
    {
        if (ImageProcessUI->objectName().isEmpty())
            ImageProcessUI->setObjectName(QString::fromUtf8("ImageProcessUI"));
        ImageProcessUI->resize(1300, 800);
        label_origin = new QLabel(ImageProcessUI);
        label_origin->setObjectName(QString::fromUtf8("label_origin"));
        label_origin->setGeometry(QRect(280, 10, 500, 752));
        label_process = new QLabel(ImageProcessUI);
        label_process->setObjectName(QString::fromUtf8("label_process"));
        label_process->setGeometry(QRect(790, 10, 500, 752));
        layoutWidget = new QWidget(ImageProcessUI);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 20, 158, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_open = new QPushButton(layoutWidget);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));

        horizontalLayout->addWidget(pushButton_open);

        pushButton_save = new QPushButton(layoutWidget);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));

        horizontalLayout->addWidget(pushButton_save);

        horizontalSliderSoftSkin = new QSlider(ImageProcessUI);
        horizontalSliderSoftSkin->setObjectName(QString::fromUtf8("horizontalSliderSoftSkin"));
        horizontalSliderSoftSkin->setGeometry(QRect(0, 90, 160, 19));
        horizontalSliderSoftSkin->setMaximum(149);
        horizontalSliderSoftSkin->setValue(35);
        horizontalSliderSoftSkin->setOrientation(Qt::Horizontal);
        horizontalSliderWhite = new QSlider(ImageProcessUI);
        horizontalSliderWhite->setObjectName(QString::fromUtf8("horizontalSliderWhite"));
        horizontalSliderWhite->setGeometry(QRect(0, 140, 160, 19));
        horizontalSliderWhite->setValue(15);
        horizontalSliderWhite->setOrientation(Qt::Horizontal);
        horizontalSliderSharp = new QSlider(ImageProcessUI);
        horizontalSliderSharp->setObjectName(QString::fromUtf8("horizontalSliderSharp"));
        horizontalSliderSharp->setGeometry(QRect(0, 190, 160, 19));
        horizontalSliderSharp->setMaximum(149);
        horizontalSliderSharp->setValue(50);
        horizontalSliderSharp->setOrientation(Qt::Horizontal);
        labelSoftSkin = new QLabel(ImageProcessUI);
        labelSoftSkin->setObjectName(QString::fromUtf8("labelSoftSkin"));
        labelSoftSkin->setGeometry(QRect(0, 70, 54, 12));
        labelWhite = new QLabel(ImageProcessUI);
        labelWhite->setObjectName(QString::fromUtf8("labelWhite"));
        labelWhite->setGeometry(QRect(0, 120, 54, 12));
        labelSharp = new QLabel(ImageProcessUI);
        labelSharp->setObjectName(QString::fromUtf8("labelSharp"));
        labelSharp->setGeometry(QRect(0, 170, 54, 12));
        horizontalSliderThin = new QSlider(ImageProcessUI);
        horizontalSliderThin->setObjectName(QString::fromUtf8("horizontalSliderThin"));
        horizontalSliderThin->setGeometry(QRect(0, 240, 160, 19));
        horizontalSliderThin->setMinimum(-25);
        horizontalSliderThin->setMaximum(25);
        horizontalSliderThin->setValue(-5);
        horizontalSliderThin->setOrientation(Qt::Horizontal);
        labelThin = new QLabel(ImageProcessUI);
        labelThin->setObjectName(QString::fromUtf8("labelThin"));
        labelThin->setGeometry(QRect(0, 220, 54, 12));
        QWidget::setTabOrder(pushButton_open, pushButton_save);

        retranslateUi(ImageProcessUI);

        QMetaObject::connectSlotsByName(ImageProcessUI);
    } // setupUi

    void retranslateUi(QWidget *ImageProcessUI)
    {
        ImageProcessUI->setWindowTitle(QApplication::translate("ImageProcessUI", "\345\233\276\345\203\217\345\244\204\347\220\206", 0, QApplication::UnicodeUTF8));
        label_origin->setText(QApplication::translate("ImageProcessUI", "orignal Image", 0, QApplication::UnicodeUTF8));
        label_process->setText(QApplication::translate("ImageProcessUI", "process Image", 0, QApplication::UnicodeUTF8));
        pushButton_open->setText(QApplication::translate("ImageProcessUI", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        pushButton_save->setText(QApplication::translate("ImageProcessUI", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        labelSoftSkin->setText(QApplication::translate("ImageProcessUI", "\347\243\250\347\232\256", 0, QApplication::UnicodeUTF8));
        labelWhite->setText(QApplication::translate("ImageProcessUI", "\347\276\216\347\231\275", 0, QApplication::UnicodeUTF8));
        labelSharp->setText(QApplication::translate("ImageProcessUI", "\346\270\205\346\231\260", 0, QApplication::UnicodeUTF8));
        labelThin->setText(QApplication::translate("ImageProcessUI", "\347\230\246\350\204\270", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessUI: public Ui_ImageProcessUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
