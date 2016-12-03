#include <qmainwindow.h>
#include <qapplication.h>
#include <qwt_counter.h>
#include <qwt_slider.h>
#include <qtoolbar.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qmainwindow.h>
#include <qwt_slider.h>
#include <qcombobox.h>
#include <qwt_analog_clock.h>
#include <qwt_plot.h>
#include <qevent.h>
#if QT_VERSION < 0x040000
#include <qwhatsthis.h>
#endif
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_scale_widget.h>
#include <qwt_wheel.h>
#include <qwt_plot.h>
#include <qwt_interval.h>
#include <qwt_system_clock.h>
#include <QtGui>

#include "iwextern.h"
#include "shared_struct.h"
//#include "../common/iw_interface.h"
#include "ext_script.h"

IWExtern::IWExtern(QWidget *parent)
    : QWidget(parent)
{
    unsigned short j;

    ui.setupUi(this);

#if 0
    for(j=0; j<USER_ARRAY_SIZE; j++)
    {
        xAxis_Array[j]     = j;
        y1_g1Axis_Array[j] = 0;
        y2_g1Axis_Array[j] = 0;
        y1_g2Axis_Array[j] = 0;
        y2_g2Axis_Array[j] = 0;
    }
    ui.qwtPlotA->setAxisTitle(QwtPlot::xBottom, "Plot A(X)");
    ui.qwtPlotA->setAxisTitle(QwtPlot::yLeft, "Y");
    ui.qwtPlotA->setTitle("A1 & A2");
    ui.qwtPlotB->setAxisTitle(QwtPlot::xBottom, "Plot B(X)");
    ui.qwtPlotB->setAxisTitle(QwtPlot::yLeft, "Y");
    ui.qwtPlotB->setTitle("B1 & B2");

    pl_A1 = new QwtPlotCurve("A1");
    pl_A2 = new QwtPlotCurve("A2");
    pl_A1->setRawSamples(xAxis_Array,y1_g1Axis_Array,USER_ARRAY_SIZE);
    pl_A2->setRawSamples(xAxis_Array,y2_g1Axis_Array,USER_ARRAY_SIZE);
    pl_A1->setPen(QPen(Qt::red,1));
    pl_A2->setPen(QPen(Qt::blue,1));
    pl_A1->attach(ui.qwtPlotA);
    pl_A2->attach(ui.qwtPlotA);

    pl_B1 = new QwtPlotCurve("B1");
    pl_B2 = new QwtPlotCurve("B2");
    pl_B1->setRawSamples(xAxis_Array,y1_g2Axis_Array,USER_ARRAY_SIZE);
    pl_B2->setRawSamples(xAxis_Array,y2_g2Axis_Array,USER_ARRAY_SIZE);
    pl_B1->setPen(QPen(Qt::red,1));
    pl_B2->setPen(QPen(Qt::blue,1));
    pl_B1->attach(ui.qwtPlotB);
    pl_B2->attach(ui.qwtPlotB);



    ui.P1_led_x1->setColor(Qt::white);
    ui.P1_led_x1->setChecked(true);
    ui.P1_led_x2->setColor(Qt::white);
    ui.P1_led_x2->setChecked(true);
    ui.P1_led_x3->setColor(Qt::white);
    ui.P1_led_x3->setChecked(true);
    ui.P1_led_y1->setColor(Qt::white);
    ui.P1_led_y1->setChecked(true);
    ui.P1_led_y2->setColor(Qt::white);
    ui.P1_led_y2->setChecked(true);
    ui.P1_led_y3->setColor(Qt::white);
    ui.P1_led_y3->setChecked(true);

    QPalette pal(Qt::black);
    pal.setColor(QPalette::WindowText, Qt::green);
    ui.LCDDisplay_1->setPalette(pal);
    ui.LCDDisplay_1->display(0);
    pal.setColor(QPalette::WindowText, Qt::red);
    ui.LCDDisplay_2->setPalette(pal);
    ui.LCDDisplay_2->display(0);
#endif

    //connect(ui.startCalButton_Ex1,SIGNAL(clicked()),SLOT(Ex1_Procedure()));
    connect(this, SIGNAL(banner_msg()),this,SLOT(banner_msg_rcvd()));
}


IWExtern::~IWExtern()
{
    delete pl_A1;
    delete pl_A2;
    delete pl_B1;
    delete pl_B2;
}

void IWExtern::Ex1_Procedure(void)
{
#ifdef FIXME_NOW
    StartCalibratio_Ex1();
#endif
}

void IWExtern::Ex2_Procedure(void)
{
#ifdef FIXME_NOW
    StartCalibratio_Ex2();
#endif
}

void IWExtern::BootMode(void)
{
    unsigned char bMode;

#ifdef FIXME_NOW
    bMode=vb_BootProcedure();
    if(bMode)
    {
        ui.colorLabel->setStyleSheet("QLineEdit{background: red;}");
        ui.colorLabel->setAutoFillBackground(true);
        ui.colorLabel->setText("Enterning Boot Mode");
    }
#endif
}
void IWExtern::SoftReset(void)
{
    unsigned char bMode;

#ifdef FIXME_NOW
    bMode=vb_SoftReset();
    if(bMode)
    {
        ui.colorLabel->setStyleSheet("QLineEdit{background: red;}");
        ui.colorLabel->setAutoFillBackground(true);
        ui.colorLabel->setText("SoftReset Mode");
    }
#endif
}

void IWExtern::Ex3_Procedure(void)
{
#ifdef FIXME_NOW
    StartCalibratio_Ex3();
#endif
}

QColor IWExtern::Translate(unsigned char xColor)
{
    if(xColor==IW_WHITE)            return Qt::white;
    else if(xColor==IW_BLACK)       return Qt::black;
    else if(xColor==IW_RED)         return Qt::red;
    else if(xColor==IW_DARKRED)     return Qt::darkRed;
    else if(xColor==IW_GREEN)       return Qt::green;
    else if(xColor==IW_DARKGREEN)   return Qt::darkGreen;
    else if(xColor==IW_BLUE)        return Qt::blue;
    else if(xColor==IW_DARKBLUE)    return Qt::darkBlue;
    else if(xColor==IW_CYAN)        return Qt::cyan;
    else if(xColor==IW_DARKCYAN)    return Qt::darkCyan;
    else if(xColor==IW_MAGENTA)     return Qt::magenta;
    else if(xColor==IW_DARKMAGENTA) return Qt::darkMagenta;
    else if(xColor==IW_YELLOW)      return Qt::yellow;
    else if(xColor==IW_DARKYELLOW)  return Qt::darkYellow;
    else if(xColor==IW_GRAY)        return Qt::gray;
    else if(xColor==IW_DARKGRAY)    return Qt::darkGray;
    else if(xColor==IW_LIGHTGRAY)   return Qt::lightGray;
    else if(xColor==IW_TRANSPARENT) return Qt::transparent;
    else  return Qt::transparent;
}

void IWExtern::LED_Action(int led_Num,int xColor)
{
    QColor sCol_led;

    switch(led_Num)
    {
    case 0:
        ui.P1_led_x1->setColor(Translate(xColor));
        break;
    case 1:
        ui.P1_led_x2->setColor(Translate(xColor));
        break;
    case 2:
        ui.P1_led_x3->setColor(Translate(xColor));

        break;
    case 3:
        ui.P1_led_y1->setColor(Translate(xColor));

        break;
    case 4:
        ui.P1_led_y2->setColor(Translate(xColor));
        break;
    case 5:
        ui.P1_led_y3->setColor(Translate(xColor));
        break;
    default:
        break;
    }

}

void IWExtern::Banner_Action(int type_Text)
{
    char banner_text[1023];
    unsigned char xcolor;

    if(type_Text==0xffff)
    {
        ui._DisplayBox_Msg->clear();
    }
    else if(type_Text==1)
    {
#ifdef FIXME_NOW
        vb_ReadText(banner_text,&xcolor);
#endif
        ui._DisplayBox_Msg->append(banner_text);
    }
    else
    {
#ifdef FIXME_NOW
        vb_ReadBanner(banner_text,&xcolor);
#endif
        ui.colorLabel->setText(banner_text);

        if(xcolor==IW_GREEN)
        {
            ui.colorLabel->setStyleSheet("QLineEdit{background: green;}");
            ui.colorLabel->setAutoFillBackground(true);
        }
        else if(xcolor==IW_RED)
        {
            ui.colorLabel->setStyleSheet("QLineEdit{background: red;}");
            ui.colorLabel->setAutoFillBackground(true);
        }
        else if(xcolor==IW_BLUE)
        {
            ui.colorLabel->setStyleSheet("QLineEdit{background: blue;}");
            ui.colorLabel->setAutoFillBackground(true);
        }
        else if(xcolor==IW_YELLOW)
        {
            ui.colorLabel->setStyleSheet("QLineEdit{background: yellow;}");
            ui.colorLabel->setAutoFillBackground(true);
        }
        else if(xcolor==IW_BLACK)
        {
            ui.colorLabel->setStyleSheet("QLineEdit{background: black;}");
            ui.colorLabel->setAutoFillBackground(true);
        }
        else
        {
            ui.colorLabel->setStyleSheet("QLineEdit{background: white;}");
            ui.colorLabel->setAutoFillBackground(true);
        }
    }


}

void IWExtern::Winlog_Action(void)
{
    ui.P1_led_y3->setColor(Qt::green);
}

void IWExtern::UserIn(void)
{
}

void IWExtern::banner_msg_rcvd()
{
#if 0
    printf("winMsg=%d\r\n",scrWinMsg.wm);
    printf("wPar=%d\r\n",scrWinMsg.wmlPar);
    printf("wPar=%d\r\n",scrWinMsg.wmwPar);
    printf("wPar=%f\r\n",scrWinMsg.wFltVal[0]);
    printf("wPar=%s\r\n",scrWinMsg.wmsg_cStr);
    fflush(stdout);
#endif
    switch(scrWinMsg.wm)
    {
    case WM_BANNER:
        ui._DisplayBox_Msg->append(scrWinMsg.wmsg_cStr);
        break;
    case WM_CLEAR_MSG:
        ui._DisplayBox_Msg->clear();
        break;
    case WM_APPEND_MSG:
        ui._DisplayBox_Msg->append(scrWinMsg.wmsg_cStr);
        break;
    case WM_LED:
        LED_Action(scrWinMsg.wmwPar,scrWinMsg.wmlPar);
        break;
    case WM_LCD_DEC:
        ui.LCDDisplay_1->setDecMode();
        ui.LCDDisplay_2->setDecMode();
        ui.LCDDisplay_1->display(scrWinMsg.wmwPar);
        ui.LCDDisplay_2->display(scrWinMsg.wmlPar);
        break;
    case WM_LCD_HEX:
        ui.LCDDisplay_1->setHexMode();
        ui.LCDDisplay_2->setHexMode();
        ui.LCDDisplay_1->display(scrWinMsg.wmwPar);
        ui.LCDDisplay_2->display(scrWinMsg.wmlPar);
        break;
    default:
        break;
    }
}
