#ifndef __RTC_RW_H
#define __RTC_RW_H

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
#include "shared_struct.h"


class RTC_pp: public QObject
{
    Q_OBJECT
public:
    explicit RTC_pp(QObject *parent);
    unsigned char buff[1288];
    ~RTC_pp();
signals:
    void finished();
    void kick_start_signal();
    void push_trigger(unsigned char *b,unsigned short len);

public slots:

    void kick_start_slot();
    void heartbeat_pulse();
    int  route_msg(QString s,scoap_packet_t &);
    int  process_incomming_pkt(scoap_packet_t &);
    int  device_ready(scoap_packet_t &);

private:

    unsigned short lTimer;
};

#endif
