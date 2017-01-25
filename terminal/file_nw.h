#ifndef __FILE_NW_H
#define __FILE_NW_H

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



class FileNw_class: public QThread
{
    Q_OBJECT
    void run();
    uint32_t response_index;
public:

    explicit FileNw_class(QObject *parent);
    ~FileNw_class();
    unsigned char buff[1288];
    char filereaddata[1288];


    void setDirection(bool);
    void setFileName(QString finame);

    QFile     *myfile;
    qint64    _currPos;
    qint64    _fileSize;
    bool      bool_isFileReadJustOpened;
    bool      bGetFile;
    QString   fileName;
    int       argCnt;
    bool      isGettingFile;
    bool      isFirstPktFile;
    unsigned short  tokenID;


signals:
    void signal_load_next_pkt();
    void request_read_next_pkt();

    void finished();
    void push_trigger(unsigned char *b,unsigned short len);
    void kick_start_signal();
    void signal_curr_state(int);
    void file_open_ok();
    void file_read_ok();
    void file_write_ok();

    void state_update(int ,int);


public slots:

    void next_chunk_out_write_file();
    void next_line_in_file();
    void next_bin_in_file();
    void next_bin_ep_in_file();
    void next_line_out_file();
    void next_bin_out_file();
    void next_push_first_pkt_file();


    void kick_start_slot();
    void heartbeat_pulse();
    int  route_msg(QString s,scoap_packet_t &);
    //int  process_incomming_pkt(scoap_packet_t &);
    int  device_ready(scoap_packet_t &);

private:
    QMutex         fmutex;
    QWaitCondition fileNotSignaled;
    QTime downloadTime;
    unsigned short m_tLen;
    unsigned short m_offs;
    unsigned short m_flag;
    MemData   mdata;
    unsigned char openMode;
    iNFileExchangeStruct gluData;

    unsigned char mRxBuffer[5000];
    unsigned short remaining_len;
    unsigned short curr_index;

    uint32_t       file_off;
    uint32_t       file_len;
    unsigned short lTimer;
    unsigned short lTimerResponseTimeout;
    unsigned short lMaxAttempts;

    unsigned short iRespRcvd;
    int fs_new_state;
    int fs_prev_state;
    int fs_curr_state;
};

#endif
