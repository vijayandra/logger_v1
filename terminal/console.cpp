#include "options.h"
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include "console.h"
//#include "SmtpMime"
#ifdef ZSERIAL
#include "serial_cs.h"
#else
#include "lrn_io.h"
#endif

extern "C"
{
#include "srv_coap.h"
#include "enc_coap.h"
#include "ep_mem.h"
#include "ep_rtc.h"
#include "ep_file.h"
#include "ep_device.h"
#include "ep_7020.h"
}

#define  SCRATCH_URI "<scratch>"

extern const char *uriFileOpArrStr[20];
extern const char *uriNFileOpArrStr[20];

void Console::append(const QStringList &s)
{
    cmdlinearg = s;

    for (int i = 0; i < cmdlinearg.size(); ++i)
    {
        //qDebug() << cmdlinearg.at(i) << endl;
        if(cmdlinearg.at(i)=="put")
        {
            file_obj->setDirection(false);
        }
        else if(cmdlinearg.at(i)=="get")
        {
            file_obj->setDirection(true);
        }
        else if(cmdlinearg.at(i)=="boot")
        {
            isRebootReq=true;
        }
        else if(cmdlinearg.at(i)=="reboot")
        {
            isRebootReq=true;
        }
        else
        {
            file_obj->setFileName(cmdlinearg.at(i));
        }
    }
    fflush(stdout);
}

void Console::route_pkt(scoap_packet_t &pkt)
{
#define  IS_URI_MATCH(X) (strncmp(X,(const char *)uri,strlen(X))==0)

    char uri[32];
    unsigned char len;
    memset(uri,'\0',32);
    memcpy(uri,pkt.opts[0].buf.p,pkt.opts[0].buf.len);

#if 0
    printf("-----------------------<");
    printf(uri);
    printf(">--\n");
    fflush(stdout);
#endif

    for(len=0; len<5; len++)
    {
        if(IS_URI_MATCH(uriNFileOpArrStr[len]))
        {
            file_obj->route_msg(FILE_FATSD_DONE,pkt);
        }
    }

    if(IS_URI_MATCH(DEV_VERSION_URI))
    {
        file_obj->device_ready(pkt);
        /* start timer when device received */
        timerHeartBeat->start(1);
    }
    else if(IS_URI_MATCH(RW_MEM_ADDR_URI))
    {
        mem_obj->address_sent_ackd(pkt);
    }
    else if(IS_URI_MATCH(RTC_URI))
    {
        rtc_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(RTC_TEMP_URI))
    {
        sensor_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(RTC_HUMD_URI))
    {
        sensor_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(RW_MEM_URI))
    {
        //printf("------>in\n");
        //fflush(stdout);
        mem_obj->process_incomming_pkt(pkt);
    }
    else if(IS_URI_MATCH(RW_MEM_URI))
    {
    }
    else if(IS_URI_MATCH(FILE_FATSD_DONE))
    {
        file_obj->route_msg(FILE_FATSD_DONE,pkt);
    }
    else if(IS_URI_MATCH(FILE_OPEN_URI))
    {
        file_obj->route_msg(FILE_OPEN_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_CLOSE_URI))
    {
        file_obj->route_msg(FILE_CLOSE_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_WRITE_URI))
    {
        file_obj->route_msg(FILE_WRITE_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_READ_URI))
    {
        file_obj->route_msg(FILE_READ_URI,pkt);
    }
    else if(IS_URI_MATCH(FILE_POS_URI))
    {
        file_obj->route_msg(FILE_POS_URI,pkt);
    }
    else if(IS_URI_MATCH(SCRATCH_URI))
    {
        printf("scratch1 --->\n");
        fflush(stdout);
    }

#undef  IS_URI_MATCH
}


void Console::FoundDataLoggerHW()
{
    unsigned short len;
    /* device ping received, ask version info */
    len=coap_pc_req(buff,COAP_METHOD_GET,"device/version",NULL,0);
    p_lrn->push_msg(buff,len,1);
    printf("found hardware\r\n");

    if(isRebootReq)
    {
        len=coap_pc_req(buff,COAP_METHOD_PUT,"reboot",NULL,0);
        p_lrn->push_msg(buff,len,1);
    }

    fflush(stdout);
}

void Console::HeartBeatTimerSyncSlot()
{
    //printf("%s\n",__FUNCTION__);
    //fflush(stdout);
}

void Console::post_coap(unsigned char *cbf,unsigned short len)
{
    p_lrn->push_msg(cbf,len,1);
}

Console::Console(QObject *parent) : QObject(parent)
{
    downloadTime.start();
    lTimer=0;
    isRebootReq=false;


    for (int i = 0; i < cmdlinearg.size(); ++i)
    {
        qDebug() << cmdlinearg.at(i) << endl;
    }
    fflush(stdout);


#ifdef ZSERIAL
    p_lrn=new SERIAL_cs(0,this);
#else
    p_lrn=new LRN_io("10.38.180.185",5683,this);
#endif
    p_lrn->start();

    mem_obj =new MemRw_class(0,1000,this);
    file_obj=new FileNw_class(this);
    rtc_obj =new RTC_pp(this);
    sensor_obj=new SENSOR_pp(this);

    //lrn_tcp_c=new LrnTcpClient(this);
    //lrn_tcp_s=new LrnTcpServer(2200,this);

    //QTimer *timer = new QTimer(this);
    timerHeartBeat = new QTimer(this);

    connect(timerHeartBeat, SIGNAL(timeout()), this, SLOT(HeartBeatTimerSyncSlot()));
    connect(timerHeartBeat, SIGNAL(timeout()), this, SLOT(kick_start_slot()));
    connect(timerHeartBeat, SIGNAL(timeout()), mem_obj, SLOT(heartbeat_pulse()));
    connect(timerHeartBeat, SIGNAL(timeout()), file_obj, SLOT(heartbeat_pulse()));

    //connect(this, SIGNAL(kick_start_signal()),sensor_obj,SLOT(kick_start_slot()));
    connect(this, SIGNAL(kick_start_signal()),file_obj,SLOT(kick_start_slot()));

    connect(p_lrn, SIGNAL(hwPokeSignal()),this,SLOT(FoundDataLoggerHW()));

    connect(p_lrn, SIGNAL(got_valid_coap(scoap_packet_t &)),this,SLOT(route_pkt(scoap_packet_t &)));

    /* we feed got_valid_coap to load_next */
    /* if needed them mem_obj gets us back */
    connect(mem_obj, SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));
    connect(file_obj,SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));
    connect(rtc_obj,SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));
    connect(sensor_obj,SIGNAL(push_trigger(unsigned char *,unsigned short)),this,SLOT(post_coap(unsigned char *,unsigned short)));

    connect(p_lrn,SIGNAL(SIG_GUI_UPDATE(ioTxtGrpthExchStrct &)),this,SLOT(GUI_UPDATE(ioTxtGrpthExchStrct &)));


    //showProgress(34,200);
}

Console::~Console()
{
    fflush(stdout);
}


void Console::showProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    progressBar.setStatus(bytesReceived, bytesTotal);

    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024)
    {
        unit = "bytes/sec";
    }
    else if (speed < 1024*1024)
    {
        speed /= 1024;
        unit = "kB/s";
    }
    else
    {
        speed /= 1024*1024;
        unit = "MB/s";
    }

    progressBar.setMessage(QString::fromLatin1("%1 %2")
                           .arg(speed, 3, 'f', 1).arg(unit));
    progressBar.update();
}


void Console::heartbeat_pulse()
{
}

void Console::kick_start_slot()
{
    static unsigned char i=0;
    /* this serves as delayed activate system
     * where
     * delayed kickoff for timer */
    if(lTimer>100)
    {
        if(i==0)
        {
            //printf("kick start signal\n");
            //fflush(stdout);
            i=1;
            lTimer=0;
            Q_EMIT kick_start_signal();
        }
    }
    lTimer++;

}

void Console::GUI_UPDATE(ioTxtGrpthExchStrct &)
{
    // printf("run-->%s\n",__FUNCTION__);
    // fflush(stdout);
}
