#include "options.h"
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include "rtc_pp.h"
//#include "SmtpMime"
#ifdef ZSERIAL
#include "serial_cs.h"
#else
#include "lrn_io.h"
#endif
extern "C"
{
#include "enc_coap.h"
#include "ep_mem.h"
#include "ep_file.h"
}

//#define DEBUG_FILE_RW
#define  IS_URI_MATCH(X) ((strncmp(X,(char *)pkt.opts[0].buf.p,pkt.opts[0].buf.len))==0)

int RTC_pp::route_msg(QString s,scoap_packet_t &pkt)
{
    unsigned short len;
#ifdef DEBUG_FILE_RW
    qDebug() << s;
#endif

    if(IS_URI_MATCH(FILE_OPEN_URI))
    {
    }
    fflush(stdout);

    return 0;
}

void RTC_pp::heartbeat_pulse()
{
    static unsigned char i=0;
    /* this serves as delayed activate system
     * where
     * delayed kickoff for timer */
    if(lTimer>100)
    {
        if(i==0)
        {
#ifdef DEBUG_FILE_RW
            printf("delayed start for file activated\n");
            fflush(stdout);
#endif
            i=1;
            Q_EMIT kick_start_signal();
        }
    }
    lTimer++;
}


int RTC_pp::device_ready(scoap_packet_t &pkt)
{
#ifdef DEBUG_FILE_RW
    printf("------------%s -device ready---------------\n",__FILE__);
    fflush(stdout);
#endif
    printf("--RTC-------%s -device ready---------------\n",__FILE__);
    fflush(stdout);

    lTimer=0;

    return 0;
}

int RTC_pp::process_incomming_pkt(scoap_packet_t &pkt)
{
    unsigned short i,len;
    IW_CDATE_CTIME id;
    if(pkt.payload.len>=sizeof(IW_CDATE_CTIME));
    {
        memcpy(&id,pkt.payload.p,sizeof(IW_CDATE_CTIME));
        printf("year=%d month=%d date=%d\r\n",id.cDate.Month ,id.cDate.Date ,id.cDate.Year);
        printf("hh=%d mm=%d ss=%d\r\n"       ,id.cTime.Hours,id.cTime.Minutes,id.cTime.Seconds);
        fflush(stdout);
    }


    return 0;
}

RTC_pp::RTC_pp(QObject *parent) : QObject(parent)
{
    lTimer=0;

    connect(this,SIGNAL(kick_start_signal()), this, SLOT(kick_start_slot()));

    //printf("offset=0x%04x len=0x%4x\n",offset,len);
    //fflush(stdout);
}

RTC_pp::~RTC_pp()
{
}


void RTC_pp::kick_start_slot()
{
    unsigned short len;
    IW_CDATE_CTIME _cd;


    _cd.cDate.Month=0x1;
    _cd.cDate.Date=0x2;
    _cd.cDate.Year=0x4;

    _cd.cTime.Hours=0x5;
    _cd.cTime.Minutes=0x7;
    _cd.cTime.Seconds=0x8;


    len=coap_pc_req(buff,COAP_METHOD_GET,"rtc",&_cd,sizeof(IW_CDATE_CTIME));
    Q_EMIT push_trigger(buff,len);

    printf("====>testing taking place\n");
    fflush(stdout);
}
