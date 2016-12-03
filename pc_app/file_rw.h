#ifndef __FILE_RW_H
#define __FILE_RW_H

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



class FileRw_class: public QThread
{
    Q_OBJECT
public:
    explicit FileRw_class(QObject *parent);
    ~FileRw_class();
    unsigned char buff[1288];
    QFile     *myfile;
    qint64    endPos;
    qint64    currPos;
signals:
    void may_load_next();
    void finished();
    void push_trigger(unsigned char *b,unsigned short len);
    void kick_start_signal();
    void signal_curr_state(int);
    void file_open_ok();
    void file_read_ok();
    void file_write_ok();

    void state_update(int ,int);


public slots:

    void process_curr_state(int);
    void analyze_state(int ,int);
    void next_pkt_send();
    void next_pkt_save();
    void kick_start_slot();
    void load_next();
    void heartbeat_pulse();
    int  route_msg(QString s,scoap_packet_t &);
    int  address_sent_ackd(scoap_packet_t &);
    int  process_incomming_pkt(scoap_packet_t &);
    int  device_ready(scoap_packet_t &);
    void retrigger(int,int);

    void pullFile(const QString &fileName);
    void pushFile(const QString &fileName);

private:
    QTime downloadTime;
    unsigned short m_tLen;
    unsigned short m_offs;
    unsigned short m_flag;
    MemData   mdata;
    unsigned char openMode;
    ioFileExchangeStruct gluData;

    unsigned char mRxBuffer[5000];
    unsigned short remaining_len;
    unsigned short curr_index;

    unsigned short c_offset;
    unsigned short c_len;
    unsigned short lTimer;

    unsigned short iRespRcvd;
    int fs_new_state;
    int fs_prev_state;
    int fs_curr_state;
};

#endif
