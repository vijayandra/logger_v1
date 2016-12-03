#ifndef __PYTHON_INTERFACE_H
#define __PYTHON_INTERFACE_H

#include <qwt_plot.h>
#include <qwt_interval.h>
#include <qwt_system_clock.h>
#include "ext_script.h"
//! [0]
#include "ui_extern_inf.h"

QT_BEGIN_NAMESPACE
class Plot;
class QwtPlotCurve;
class Knob;
class WheelBox;
class QLineEdit;
class  QtColorPicker;
class QGroupBox;
class QGridLayout;
class QGroupBox;
QT_END_NAMESPACE
//! [0]

//! [1]
class IWExtern : public QWidget
{
private:
    Q_OBJECT

public:
    IWExtern(QWidget *parent = 0);
    ~IWExtern();
    QwtPlotCurve *pl_Channel_B2;
    ScriptWinMsg scrWinMsg;

private:
    Ui::IWExtern ui;
    char general_buffer[1024];
    QColor Translate(unsigned char xColor);

private:
    //Ui::Ui_MainWindow ui;
public slots:
    void Ex1_Procedure(void);
    void Ex2_Procedure(void);
    void Ex3_Procedure(void);
    void BootMode(void);
    void SoftReset(void);

    void Banner_Action(int);
    void LED_Action(int,int);
    void Winlog_Action(void);
    void UserIn(void);
    void banner_msg_rcvd();
private:
    QwtPlotCurve *pl_A1;
    QwtPlotCurve *pl_A2;
    QwtPlotCurve *pl_B1;
    QwtPlotCurve *pl_B2;
Q_SIGNALS:
    void banner_msg();
};
//! [1]

#endif
