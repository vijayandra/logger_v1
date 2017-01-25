#ifndef __CMD_CONSOLE_H
#define __CMD_CONSOLE_H

#include "options.h"
#include <QFile>
#include <QObject>
#include <QQueue>
#include <QTime>
#include <QTimer>
#include <QUrl>
#include "textprogressbar.h"

#ifdef ZSERIAL
#include "serial_cs.h"
#else
#include "lrn_io.h"
#endif

#include "lrn_tcp_c.h"
#include "lrn_tcp_s.h"

#include "mem_rw.h"
#include "file_nw.h"
#include "rtc_pp.h"
#include "sensor_pp.h"

class Console: public QObject
{
    Q_OBJECT
public:
    void append(const QStringList &s);

    Console(QObject *parent = 0);
    ~Console();
#ifdef ZSERIAL
    SERIAL_cs  *p_lrn;
#else
    LRN_io  *p_lrn;
#endif
    //LrnTcpClient *lrn_tcp_c;
    //LrnTcpServer *lrn_tcp_s;

    MemRw_class  *mem_obj;
    FileNw_class *file_obj;
    RTC_pp       *rtc_obj;
    SENSOR_pp    *sensor_obj;
    QStringList  cmdlinearg;
    QString      fileName;
    bool         isRebootReq;

    unsigned short lTimer;

    unsigned char buff[2048];

    int test();

signals:
    void finished();
    void kick_start_signal();

public slots:
    void route_pkt(scoap_packet_t &);
    void heartbeat_pulse();
    void kick_start_slot();

private slots:

    void showProgress(qint64 bytesReceived, qint64 bytesTotal);
    void HeartBeatTimerSyncSlot();
    void FoundDataLoggerHW();
    void post_coap(unsigned char *cbf,unsigned short len);
    void GUI_UPDATE(ioTxtGrpthExchStrct &);

private:
    QTime downloadTime;
    //QTimer *timer = new QTimer(this);
    QTimer *timerHeartBeat;
    TextProgressBar progressBar;
};

#endif
