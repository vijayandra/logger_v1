#ifndef __SCRATCH_HUB_H
#define __SCRATCH_HUB_H

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


class SCRATCH_pp: public QObject
{
    Q_OBJECT
public:
    explicit SCRATCH_pp(QObject *parent);
    ioTxtGrpthExchStrct  iGuiUpdate;
    ~SCRATCH_pp();
signals:
    void SIG_SCRATCH1(ioTxtGrpthExchStrct &);
    void SIG_SCRATCH2(ioTxtGrpthExchStrct &);
    void SIG_SCRATCH3(ioTxtGrpthExchStrct &);
    void SIG_RS485(ioTxtGrpthExchStrct &);
    void SIG_UART2(ioTxtGrpthExchStrct &);
    void SIG_UART3(ioTxtGrpthExchStrct &);
    void SIG_UART23(ioTxtGrpthExchStrct &);

    void kick_start_signal();
    void push_trigger(unsigned char *b,unsigned short len);

public slots:

    void heartbeat_pulse();
    int  route_msg(QString s,scoap_packet_t &);
    int  process_incomming_pkt(scoap_packet_t &);
    int  device_ready(scoap_packet_t &);

private:

    unsigned short lTimer;
};

#endif
