#ifndef HEARTBEAT_COMM_H
#define HEARTBEAT_COMM_H

#include <QMainWindow>
#include <QByteArray>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <qcombobox.h>
#include <qwwled.h>

#include "highlighter.h"
#include "tftpc.h"
#include "textprogressbar.h"

#ifdef ZSERIAL
#include "serial_cs.h"
#else
#include "lrn_io.h"
#endif
#include "mem_rw.h"
#include "file_rw.h"
#include "rtc_pp.h"
#include "adc.h"
#include "scratch_pp.h"
#include "scratch_pad.h"
#include "sensor_pp.h"
#include "codeeditor.h"
#include "shared_struct.h"
#include "iwextern.h"
#include "ext_script.h"

QT_BEGIN_NAMESPACE
class QAction;
class QListWidget;
class QMenu;
class QTextEdit;
class QLineEdit;
class QwwLed;
class QListView;
class QTreeItem;
class QListWidgetItem;
class QTreeWidgetItem;
class QTreeWidget;
QT_END_NAMESPACE

class HeartBeat : public QMainWindow
{
    Q_OBJECT
private:

public:
    HeartBeat();
    ~HeartBeat();
    bool eventFilter(QObject *object, QEvent *e);
    bool reinit_done;
    unsigned char iMode;
    ioTxtGrpthExchStrct  iGuiUpdate;

#ifdef ZSERIAL
    SERIAL_cs  *p_lrn;
#else
    LRN_io  *p_lrn;
#endif
    MemRw_class  *mem_obj;
    FileRw_class *file_obj;
    RTC_pp       *rtc_obj;
    SENSOR_pp    *sensor_obj;
    SCRATCH_pp   *scratch_obj;
    CodeEditor   *editor;
    IWExtern     *iExtern;
    ADC_class    *adc_obj;

    ScratchPad   *s_pad1;
    ScratchPad   *s_pad2;
    ScratchPad   *s_pad3;
    ScratchPad   *s_rs485;
    ScratchPad   *s_uart2;
    ScratchPad   *s_uart3;
    ScratchPad   *s_uart23;

    unsigned char in_data[2048];
    char c_code_data[4095];
    unsigned char buff[2048];
    unsigned short len;
    int coap_client_read(unsigned char *ucbuff);
    unsigned short ubufflen;
    QString  addr_from_broadcast;
    QString fileName;
    QString fname;

signals:
    void responseRcvd();
    void uart1_Get();
    void uart1_Put();
    void msg_Pumped();
    void finished();

    void SIG_SCRATCH1(ioTxtGrpthExchStrct &);
    void SIG_SCRATCH2(ioTxtGrpthExchStrct &);
    void SIG_SCRATCH3(ioTxtGrpthExchStrct &);
    void SIG_RS485(ioTxtGrpthExchStrct &);
    void SIG_UART2(ioTxtGrpthExchStrct &);
    void SIG_UART3(ioTxtGrpthExchStrct &);
    void SIG_UART23(ioTxtGrpthExchStrct &);

private slots:

    void GUI_UPDATE(ioTxtGrpthExchStrct &);
    void timerExpired();
    void delayRAMCodeTimerrExpired();

    void newScriptSlot();
    void PushRTCTimeSlot();
    void autoExecScriptSlot();

    void slotEditAutoExecScriptC(bool);
    void FoundDataLoggerHWString(QString);
    void HeartBeatTimerSyncSlot();
    void post_coap(unsigned char *cbf,unsigned short len)
    {
        p_lrn->push_msg(cbf,len,1);
    }

    void slot_Edit_OR_PUSH_INI(bool x);
    void slot_Edit_OR_PUSH_C_Script(bool x);
    void slot_Run_Script_In_Hardware(bool x);
    void slot_script_load_and_run();
    void slot_script_run();
    void slot_FormatSDCard();
    void slot_Reboot();

private:
    QTimer      delayRAMCodeTimer;
    QToolBar    *tBar;
    ExternSig   *ext_msgPump;
    Oscope      *oscope;
    Osignal     *osignal;
    QTFTPWidget *tqftp;
    QTabWidget  *tabWidget;
    void commonMsgHandle();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void createTabWidget();

    Highlighter *highlighter;

    QTextEdit *scratch_pad1;
    QTextEdit *scratch_pad2;
    QTextEdit *scratch_pad3;

    QTextEdit *textEdit1;
    QTextEdit *textEdit2;
    QTextEdit *textEdit3;
    QListWidget *customerList;
    QListWidget *paragraphsList;
    QComboBox    *oscope_id;

    //QMenu *fileMenu;
    //QMenu *editMenu;
    //QMenu *viewMenu;
    //QMenu *helpMenu;
    QLineEdit  *lineEdit;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QAction *autoExecScript;
    //QAction *newScript;
    QAction *rtcClock;

    QAction *saveAct;
    //QAction *printAct;
    //QAction *undoAct;
    //QAction *aboutAct;
    //QAction *aboutQtAct;
    //QAction *quitAct;

    QAction *d_connect;
    QAction *d_format;
    QAction *d_reboot;

    QwwLed  *connLED;
    QwwLed  *commLED;
    //QwwLed  *runLED;
    //QwwLed  *_led3;
    QToolBar *formatDisk;

    QTimer  timer;

    QAction *d_ini_script;
    QAction *d_autoexec_script;
    QAction *d_run_script;
    QAction *d_ram_script;

    QTime downloadTime;
    QTimer *timerHeartBeat;
    TextProgressBar progressBar;
    QPushButton *sendButton;
    QPushButton *getButton;

protected:
    void closeEvent(QCloseEvent *event);
signals:
    void push_trigger(unsigned char *b,unsigned short len);
    void sig_pullFile(const QString &string);
    void sig_pushFile(const QString &string);
    void sig_script_load_and_run();
    void sig_script_run();
    void do_plot();


public slots:
    void route_pkt(scoap_packet_t &);
    void update_progress(qint64,qint64);
    void browse_and_send();
    void getFile();
    void update_code_buffer()
    {
        memcpy(c_code_data,editor->c_code_data,sizeof(c_code_data));
        delayRAMCodeTimer.setInterval(550);
        delayRAMCodeTimer.setSingleShot(true);
        delayRAMCodeTimer.start();
    }
    void comm_start();
    void comm_end();
    void msg_PumpedRcvd();
};

#endif
