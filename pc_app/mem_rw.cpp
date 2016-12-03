#include "options.h"
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include "mem_rw.h"
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

int MemRw_class::route_msg(QString s,scoap_packet_t &pkt)
{

    return 0;
}



void MemRw_class::loadFile(QString sfile)
{
    QString fileName(sfile);
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly))
        {
            return;
        }

        QByteArray data = file.readAll();
        memcpy(c_code_data,data.data(),4095);

    }

}

void MemRw_class::slot_sendScriptC_Code(char *cBuff)
{
    unsigned short len;
    Q_EMIT comm_start();

    m.MemType=0;
    m.Off_l=0;
    m.Off_h=0;
    m.range=4095;
    remaining_len=4095;
    curr_mem_index=0;

    memcpy(c_code_data,cBuff,4095);

    len=coap_pc_req(buff,COAP_METHOD_PUT,"memory/addr",&m,sizeof(MemData));
    Q_EMIT push_trigger(buff,len);

    /* set diection of data flow to device */
    to_device();
}

void MemRw_class::heartbeat_pulse()
{
    static unsigned char i=0;
    /* this is delayed kickoff for timer */
    if(lTimer>100)
    {
        if(i==0)
        {
            i=1;
            //Q_EMIT kick_start_signal();
        }
    }
    lTimer++;
}

void MemRw_class::kick_start_slot()
{
    unsigned short len;

    m.MemType=0;
    m.Off_l=0;
    m.Off_h=0;
    m.range=2000;
    remaining_len=2000;
    curr_mem_index=0;

    printf("====KickStart Memory Read\n");
    fflush(stdout);

    len=coap_pc_req(buff,COAP_METHOD_PUT,"memory/addr",&m,sizeof(MemData));
    Q_EMIT push_trigger(buff,len);

    /* set diection of data flow to device */
    from_device();
    //to_device();

    /* device ping received, ask version info */
    //len=coap_pc_req(buff,1,"device/version",NULL,0);
    //p_lrn->push_msg(buff,len,1);
}

int MemRw_class::device_ready(scoap_packet_t &pkt)
{
    printf("-------------device ready---------------\n");
    fflush(stdout);

    mdata.MemType=0;
    mdata.Off_l=0;
    mdata.Off_h=0;
    mdata.range=1000;
    lTimer=0;

    return 0;
}

int MemRw_class::address_sent_ackd(scoap_packet_t &)
{
    unsigned short len;
    if(flag_dataDirection)
    {
        /* data going to device */
        len=coap_pc_req(buff,COAP_METHOD_PUT,"memory",&c_code_data[curr_mem_index],1024);
        curr_mem_index+=1024;
    }
    else
    {
        len=coap_pc_req(buff,COAP_METHOD_GET,"memory",NULL,0);
    }
    Q_EMIT push_trigger(buff,len);

    return 0;
}

int MemRw_class::process_incomming_pkt(scoap_packet_t &pkt)
{
    unsigned short i,len;
    //printf("====>%s\n",__FUNCTION__);
    //fflush(stdout);
    if(flag_dataDirection)
    {
        //printf("-%s %d\n",__FUNCTION__,__LINE__); fflush(stdout);
        /* data going to device,adjust pointer */
        if(curr_mem_index<m.range)
        {
            len=coap_pc_req(buff,COAP_METHOD_PUT,"memory",&c_code_data[curr_mem_index],1024);
            Q_EMIT push_trigger(buff,len);
            curr_mem_index+=1024;
        }
        else
        {
            Q_EMIT comm_end();
            //printf("comm complete\r\n"); fflush(stdout);
        }
    }
    else
    {
        //printf("-%s %d\n",__FUNCTION__,__LINE__); fflush(stdout);
        /* data comming from device */
        for(i=0; i<pkt.payload.len; i++)
        {
            if(curr_mem_index<sizeof(c_code_data))
            {
                c_code_data[curr_mem_index]=pkt.payload.p[i];
                //printf("<0x%02x>",c_code_data[curr_mem_index]);
                //printf("%c",c_code_data[curr_mem_index]);
                //if(i<30) printf("<0x%c>",pkt.payload.p[i]);
                //fflush(stdout);
                curr_mem_index++;
            }
        }
        if(curr_mem_index<remaining_len)
        {
            len=coap_pc_req(buff,COAP_METHOD_GET,"memory",NULL,0);
            Q_EMIT push_trigger(buff,len);
        }
        else
        {
            Q_EMIT comm_end();
            //printf("read completed \n"); fflush(stdout);
            //kick_start_slot();
        }
    }

    return 0;
}

void MemRw_class::retrigger(int offset,int len)
{
    m_flag=1;
    m_offs=offset;
    m_tLen=len;

    c_offset=0;
    c_len   =0;
}

void MemRw_class::load_next()
{
#if 0
    if(m_flag)
    {
        int len=0;
        char buffer[20];

        c_len=100;
        sprintf(buffer,"%d,%d",c_offset,c_len);
        len=coap_pc_req(buff,1,"memory/addr",buffer,strlen(buffer));
        Q_EMIT push_trigger(buff,len);
        //p_lrn->push_msg(buff,len,1);
    }
    printf("******************************\n");
    printf("******************************\n");
    printf("******************************\n");
    printf("******************************\n");
    printf("******************************\n");
    printf("******************************\n");
    printf("******************************\n");
#endif
    fflush(stdout);
}

MemRw_class::MemRw_class(quint16 offset,quint16 len,QObject *parent) : QThread(parent)
{
    unsigned short i;

    m_offs=offset;
    m_tLen=len;
    m_flag=1;
    flag_dataDirection=false;
    //m_Ptr=(unsigned char *)malloc(len);

    //for(i=0; i<2000; i++)c_code_data[i]=i;
    //memcpy(c_code_data,"VijayandraKumarSingh",20);
    //loadFile("mem_rw.cpp");

    connect(this,SIGNAL(kick_start_signal()), this, SLOT(kick_start_slot()));

    //printf("offset=0x%04x len=0x%4x\n",offset,len);
    //fflush(stdout);
}

MemRw_class::~MemRw_class()
{
    //free(m_Ptr);
}

void MemRw_class::to_device()
{
    flag_dataDirection=true;
}

void MemRw_class::from_device()
{
    flag_dataDirection=false;
}
