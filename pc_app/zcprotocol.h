/* version 1.2 */
#ifndef __Z_CPP_PROTOCOL_CPP_H
#define __Z_CPP_PROTOCOL_CP_H

#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QFile>
#include <QObject>
#include <QQueue>
#include <QMutexLocker>
#include <QTime>
#include <QTimer>
#include <stdio.h>

#include <stdio.h>
#include <string.h>

extern "C"
{
#include "options.h"
#include "io_uart.h"
#include "global_var.h"
}

#include "disc.h"

#define PROT_HEADER       (0x55)
#define Z_ATTMPT_TRY      (20)
#define Z_TIMEOUT         (200)
#define Z_INTERVAL        (20)

#define TYPE_CON   0
#define TYPE_NON   1
#define TYPE_ACK   2
#define TYPE_RST   3

typedef void (*callback_alarm)(int,int);

typedef enum Cmdtype
{
    normal_pkt=0,
    acknwg_pkt,
    invalid_pkt
} Cmdtype;


typedef struct PROT_Z
{
    unsigned short code;
    unsigned short type;
    unsigned short timeout;
    unsigned short lastSent;
    unsigned short com_error;

    unsigned short txCnt;
    unsigned short txLen;
    callback_alarm cb;

    unsigned short payloadlen;
    unsigned short crc;
    unsigned short mid;
    unsigned short len;
    unsigned char  payload[MAX_PAYLOAD];
} PROT_Z;

struct Out_In
{
    unsigned short static_mid;
    unsigned short out_count;
    unsigned short in_count;

    unsigned short isActive[MAX_ZMSG];
    unsigned short isWaitAck[MAX_ZMSG];
    unsigned short isTransOK[MAX_ZMSG];
    unsigned short isTsmitted[MAX_ZMSG];

    PROT_Z         outz[MAX_ZMSG];
};


class z_protocol: public QObject
{
    Q_OBJECT
private:

    volatile unsigned int currTime;
    struct Out_In _oi;

    QMutex         zmutex;
    QMutex         zmutex_r;

    unsigned char cztx_buff[MAX_ZMSG*8];
    unsigned char crx_buff[MAX_ZMSG*MAX_PAYLOAD];

    void mark_ack_rcvd(unsigned short mid,unsigned short crc,unsigned short len);


public:
    z_protocol(QObject *parent = 0);

    DiscBuff       *disc;
    unsigned char  z_inbuff[MAX_PAYLOAD];
    unsigned short z_post_mailbox(const void *msg,\
                                  unsigned short len,\
                                  unsigned short c_code,\
                                  callback_alarm cb);

    unsigned short z_read_mailbox(char *buff,short len);

    /* Post on z protocol */
    unsigned char  incomming_sorting_box(const void *ibuff,unsigned short len1);
    unsigned short z_read_trans(char *buff,short len);
    unsigned short z_call_me_1millisec(unsigned char *sbuff);

Q_SIGNALS:
    void zack(int,int);
public slots:
    void ms_tick();
};

#endif
