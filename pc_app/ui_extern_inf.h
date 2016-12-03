/********************************************************************************
** Form generated from reading UI file 'extern_inf.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTERN_INF_H
#define UI_EXTERN_INF_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>
#include "qwt_plot.h"
#include "qwwled.h"

QT_BEGIN_NAMESPACE

class Ui_IWExtern
{
public:
    QwtPlot *qwtPlotA;
    QTextEdit *_DisplayBox_Msg;
    QLineEdit *colorLabel;
    QLCDNumber *LCDDisplay_2;
    QwwLed *P1_led_y3;
    QwwLed *P1_led_x2;
    QwwLed *P1_led_x1;
    QwwLed *P1_led_y2;
    QwwLed *P1_led_x3;
    QwwLed *P1_led_y1;
    QwtPlot *qwtPlotB;
    QLCDNumber *LCDDisplay_1;

    void setupUi(QWidget *IWExtern)
    {
        if (IWExtern->objectName().isEmpty())
            IWExtern->setObjectName(QString::fromUtf8("IWExtern"));
        IWExtern->resize(961, 424);
        qwtPlotA = new QwtPlot(IWExtern);
        qwtPlotA->setObjectName(QString::fromUtf8("qwtPlotA"));
        qwtPlotA->setGeometry(QRect(0, 10, 461, 151));
        _DisplayBox_Msg = new QTextEdit(IWExtern);
        _DisplayBox_Msg->setObjectName(QString::fromUtf8("_DisplayBox_Msg"));
        _DisplayBox_Msg->setGeometry(QRect(0, 160, 761, 221));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(16);
        font.setStyleStrategy(QFont::PreferDefault);
        _DisplayBox_Msg->setFont(font);
        _DisplayBox_Msg->setReadOnly(true);
        colorLabel = new QLineEdit(IWExtern);
        colorLabel->setObjectName(QString::fromUtf8("colorLabel"));
        colorLabel->setGeometry(QRect(0, 380, 761, 41));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        colorLabel->setFont(font1);
        colorLabel->setReadOnly(true);
        LCDDisplay_2 = new QLCDNumber(IWExtern);
        LCDDisplay_2->setObjectName(QString::fromUtf8("LCDDisplay_2"));
        LCDDisplay_2->setGeometry(QRect(770, 340, 181, 41));
        LCDDisplay_2->setSmallDecimalPoint(true);
        LCDDisplay_2->setNumDigits(8);
        LCDDisplay_2->setMode(QLCDNumber::Dec);
        P1_led_y3 = new QwwLed(IWExtern);
        P1_led_y3->setObjectName(QString::fromUtf8("P1_led_y3"));
        P1_led_y3->setGeometry(QRect(880, 220, 41, 41));
        P1_led_x2 = new QwwLed(IWExtern);
        P1_led_x2->setObjectName(QString::fromUtf8("P1_led_x2"));
        P1_led_x2->setGeometry(QRect(830, 170, 41, 51));
        P1_led_x1 = new QwwLed(IWExtern);
        P1_led_x1->setObjectName(QString::fromUtf8("P1_led_x1"));
        P1_led_x1->setGeometry(QRect(780, 170, 41, 51));
        P1_led_y2 = new QwwLed(IWExtern);
        P1_led_y2->setObjectName(QString::fromUtf8("P1_led_y2"));
        P1_led_y2->setGeometry(QRect(830, 220, 41, 41));
        P1_led_x3 = new QwwLed(IWExtern);
        P1_led_x3->setObjectName(QString::fromUtf8("P1_led_x3"));
        P1_led_x3->setGeometry(QRect(880, 170, 41, 51));
        P1_led_y1 = new QwwLed(IWExtern);
        P1_led_y1->setObjectName(QString::fromUtf8("P1_led_y1"));
        P1_led_y1->setGeometry(QRect(780, 220, 41, 41));
        qwtPlotB = new QwtPlot(IWExtern);
        qwtPlotB->setObjectName(QString::fromUtf8("qwtPlotB"));
        qwtPlotB->setGeometry(QRect(470, 10, 481, 151));
        LCDDisplay_1 = new QLCDNumber(IWExtern);
        LCDDisplay_1->setObjectName(QString::fromUtf8("LCDDisplay_1"));
        LCDDisplay_1->setGeometry(QRect(770, 290, 181, 41));
        LCDDisplay_1->setSmallDecimalPoint(true);
        LCDDisplay_1->setNumDigits(8);
        LCDDisplay_1->setMode(QLCDNumber::Dec);

        retranslateUi(IWExtern);

        QMetaObject::connectSlotsByName(IWExtern);
    } // setupUi

    void retranslateUi(QWidget *IWExtern)
    {
        IWExtern->setWindowTitle(QApplication::translate("IWExtern", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IWExtern: public Ui_IWExtern {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTERN_INF_H
