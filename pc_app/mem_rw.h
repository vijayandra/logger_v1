#ifndef __RW_MEMORY_H
#define __RW_MEMORY_H

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


class MemRw_class: public QThread
{
    Q_OBJECT
public:
    explicit MemRw_class(quint16 offset,quint16 len,QObject *parent);
    ~MemRw_class();
    unsigned char buff[1288];
    MemData        m;
signals:
    void may_load_next();
    void finished();
    void push_trigger(unsigned char *b,unsigned short len);
    void kick_start_signal();
    void comm_start();
    void comm_end();



public slots:

    int route_msg(QString s,scoap_packet_t &pkt);
    void kick_start_slot();
    void load_next();
    void heartbeat_pulse();
    int  address_sent_ackd(scoap_packet_t &);
    int  process_incomming_pkt(scoap_packet_t &);
    int  device_ready(scoap_packet_t &);
    void retrigger(int,int);
    void to_device();
    void from_device();
    void slot_sendScriptC_Code(char *);

private:
    QTime downloadTime;
    unsigned char *m_Ptr;
    unsigned short m_tLen;
    unsigned short m_offs;
    unsigned short m_flag;
    bool flag_dataDirection;
    MemData   mdata;

    char c_code_data[4095];
    unsigned char mRxBuffer[5000];
    unsigned short remaining_len;
    unsigned short curr_mem_index;

    unsigned short c_offset;
    unsigned short c_len;
    unsigned short lTimer;

    void loadFile(QString sfile);

};

#endif
