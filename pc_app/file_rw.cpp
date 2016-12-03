#include "options.h"
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include "file_rw.h"
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

static const char *omyStr[100]=
{
    "old_fs_SERVER_READY",
    "old_fsOPEN___R___File",
    "old_fsOPEN___W___File",
    "old_fsREAD_BIN___File",
    "old_fsWRITE_BIN__File",
    "old_fsREAD_LINE__File",
    "old_fsWRITE_LINE_File",
    "old_fsCLOSE______File"
};

static const char *myStr[100]=
{
    "fs_SERVER_READY",
    "fsREAD_LINE__File",
    "fsWRITE_LINE_File",
    "fsCLOSE______File"
};

void FileRw_class::process_curr_state(int f_tmp_state)
{

    printf("--------------------------->process curr=%d\r\n",f_tmp_state);
    fflush(stdout);
    switch(f_tmp_state)
    {
    case fs_SERVER_READY:
        printf("file closed and file ready\n");
        break;
    case fsREAD_BIN___File:
        break;
    case fsWRITE_BIN__File:
        printf("file write ok\n");
        next_pkt_send();
        break;
    case fsCLOSE______File:
        printf("close file\n");
        break;
    default:
        break;
    }

    fflush(stdout);
}

void FileRw_class::analyze_state(int fs_new_state,int fs_prev_state)
{
    printf("%s %s \r\n",__FILE__,__FUNCTION__);

    fs_curr_state=(int)fs_new_state;

    printf("<%d> <%d>\r\n",fs_prev_state,fs_curr_state);

    if(fs_prev_state<7);
    {
        printf("---------->%d\n",fs_prev_state);
    }
    process_curr_state(fs_curr_state);
    fflush(stdout);

#if 0
    switch(fs_prev_state)
    {
    case fs_SERVER_READY:
        break;
    case fsREAD_BIN___File:
        break;
    case fsWRITE_BIN__File:

        break;
    case fsCLOSE______File:
        break;
    default:
        break;
    }

    if(fs_new_state<7);
    {
        printf("------->>>%d\n",fs_new_state);
        fflush(stdout);
    }

    //process_curr_state

    fs_curr_state=(int)fs_new_state;


    switch(fs_new_state)
    {
    case fs_SERVER_READY:
        break;
    case fsWRITE_BIN__File:
        break;
    case fsCLOSE______File:
        break;
    default:
        break;
    }

    Q_EMIT signal_curr_state((int)fs_curr_state);
#endif
}

int FileRw_class::route_msg(QString s,scoap_packet_t &pkt)
{
    unsigned short len;
#ifdef DEBUG_FILE_RW
    qDebug() << s;
#endif

    if(IS_URI_MATCH(FILE_FATSD_DONE))
    {
        printf("------------> FATSD\n");
        fflush(stdout);
        memcpy(&gluData,pkt.payload.p,sizeof(ioFileExchangeStruct));

        fs_new_state  = gluData.new_state;
        fs_prev_state = gluData.prev_state;

        Q_EMIT state_update(gluData.prev_state,gluData.new_state);
    }

#if 0
    else if(IS_URI_MATCH(FILE_OPEN_URI))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(ioFileExchangeStruct));
        if(gluData.error==IW_FILE_SUCCESS)
        {
#ifdef DEBUG_FILE_RW
            printf("%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
#endif
            fflush(stdout);
            //printf("command successful\n");
            if(openMode)
            {
#ifdef DEBUG_FILE_RW
                printf("%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
#endif
                fflush(stdout);
                Q_EMIT file_open_ok();
            }
            else
            {
#ifdef DEBUG_FILE_RW
                printf("%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
#endif
                fflush(stdout);
                /* this is to Transferred */
                //Q_EMIT file_open_ok();
                gluData.len=MAX_TFR_SIZE;
                /*this is write file mode */
                len=coap_pc_req(buff,COAP_METHOD_GET,"file/Transferred",&gluData,sizeof(ioFileExchangeStruct));
                Q_EMIT push_trigger(buff,len);
            }
        }
        else
        {
            printf("failed\n");
        }
    }
    else if(IS_URI_MATCH(FILE_CLOSE_URI))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(ioFileExchangeStruct));

        if(gluData.error==IW_FILE_SUCCESS)
        {
#ifdef DEBUG_FILE_RW
            printf("command successful\n");
#endif
        }
    }
    else if(IS_URI_MATCH(FILE_WRITE_URI))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(ioFileExchangeStruct));
        if(gluData.error==IW_FILE_SUCCESS)
        {
            Q_EMIT file_write_ok();
            //printf("command successful\n");
        }
    }
    else if(IS_URI_MATCH(FILE_READ_URI))
    {
#ifdef DEBUG_FILE_RW
        printf("%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
        fflush(stdout);
#endif
        memcpy(&gluData,pkt.payload.p,sizeof(ioFileExchangeStruct));
#ifdef DEBUG_FILE_RW
        printf("Transferred bytes=%d\n",gluData.Transferred);
        printf("Transferred bytes= %02x %02x %02x %02x %02x \n", gluData.data_buffer[0], gluData.data_buffer[1], gluData.data_buffer[2], gluData.data_buffer[3], gluData.data_buffer[4], gluData.data_buffer[5]);
        printf("Transferred bytes=%c%c%c%c%c%c\n",gluData.data_buffer[0], gluData.data_buffer[1], gluData.data_buffer[2], gluData.data_buffer[3], gluData.data_buffer[4], gluData.data_buffer[5]);
        printf("%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
        fflush(stdout);
#endif
        if(gluData.error==IW_FILE_SUCCESS)
        {
#ifdef DEBUG_FILE_RW
            printf("%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
            fflush(stdout);
#endif
            //printf("file Transferred ok command successful\n");
            Q_EMIT file_read_ok();
        }
    }
    else if(IS_URI_MATCH(FILE_POS_URI))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(ioFileExchangeStruct));
        if(gluData.error==IW_FILE_SUCCESS)
        {
#ifdef DEBUG_FILE_RW
            printf("command successful\n");
#endif
        }
    }
#endif
    fflush(stdout);

    return 0;
}

void FileRw_class::next_pkt_save()
{
    unsigned short len;

    if(gluData.Transferred==0)
    {
        myfile->close();
#ifdef DEBUG_FILE_RW
        printf("File Transferred done %s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
        fflush(stdout);
#endif
        len=coap_pc_req(buff,COAP_METHOD_GET,"file/close",&gluData,sizeof(ioFileExchangeStruct));
        Q_EMIT push_trigger(buff,len);
    }
    else
    {
        len=gluData.Transferred;
        currPos+=len;

        printf("currPos=%d\n",currPos);

#ifdef DEBUG_FILE_RW
        printf("File Transferred done %s %s %d %d\n",__FILE__,__FUNCTION__,__LINE__,len);
        fflush(stdout);
#endif
        if(len>MAX_TFR_SIZE) len=0;
        //for(len=0;len<gluData.Transferred;len++) printf("%c",gluData.line_buffer[len]);
        fflush(stdout);

        myfile->write(gluData.line_buffer,gluData.Transferred);
#ifdef DEBUG_FILE_RW
        printf("%s\n",gluData.line_buffer);
        fflush(stdout);
#endif
        gluData.len=MAX_TFR_SIZE;

        len=coap_pc_req(buff,COAP_METHOD_GET,"file/read",&gluData,sizeof(ioFileExchangeStruct));
        Q_EMIT push_trigger(buff,len);
    }

}

void FileRw_class::next_pkt_send()
{
    unsigned short len;
    qint64 l;
    ioFileExchangeStruct   m;

    m.len=myfile->read(m.line_buffer,MAX_TFR_SIZE);
    currPos+=m.len;
    printf("progress=%d\n",100*currPos/endPos);
    fflush(stdout);

#ifdef DEBUG_FILE_RW
    printf("%s %s %d <%d>\n",__FILE__,__FUNCTION__,__LINE__,myfile->pos());
    fflush(stdout);
#endif

    if(m.len==0)
    {
        /* Sending LAST CLOSE */
        /*this is write file mode */
        printf("Sending last CLOSE REQ\n");
        fflush(stdout);
        len=coap_pc_req(buff,COAP_METHOD_PUT,"file/close",&m,sizeof(ioFileExchangeStruct));
        Q_EMIT push_trigger(buff,len);
    }
    else
    {
        /*this is write file mode */
        len=coap_pc_req(buff,COAP_METHOD_PUT,"file/write",&m,sizeof(ioFileExchangeStruct));
        Q_EMIT push_trigger(buff,len);
    }
}

void FileRw_class::heartbeat_pulse()
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
            //Q_EMIT kick_start_signal();
        }
    }
    lTimer++;
}


int FileRw_class::device_ready(scoap_packet_t &pkt)
{
#ifdef DEBUG_FILE_RW
    printf("------------%s -device ready---------------\n",__FILE__);
    fflush(stdout);
#endif

    mdata.MemType=0;
    mdata.Off_l=0;
    mdata.Off_h=0;
    mdata.range=1000;
    lTimer=0;

    return 0;
}

int FileRw_class::address_sent_ackd(scoap_packet_t &)
{
    unsigned short len;
#ifdef DEBUG_FILE_RW
    printf("-------------address sent acked--------------\n");
    fflush(stdout);
#endif
    len=coap_pc_req(buff,COAP_METHOD_GET,"memory",NULL,0);
    Q_EMIT push_trigger(buff,len);

    return 0;
}

int FileRw_class::process_incomming_pkt(scoap_packet_t &pkt)
{
    unsigned short i,len;
    for(i=0; i<pkt.payload.len; i++)
    {
        if(curr_index<sizeof(mRxBuffer))
        {
            mRxBuffer[curr_index]=pkt.payload.p[i];
            //printf("<0x%02x>",mRxBuffer[curr_index]);
            printf("%c",mRxBuffer[curr_index]);
            //if(i<30) printf("<0x%c>",pkt.payload.p[i]);
            fflush(stdout);
            curr_index++;
        }
    }
    if(curr_index<remaining_len)
    {
        len=coap_pc_req(buff,COAP_METHOD_GET,"memory",NULL,0);
        Q_EMIT push_trigger(buff,len);
    }
    else
    {
#ifdef DEBUG_FILE_RW
        printf("read completed \n");
#endif
        fflush(stdout);
    }



    return 0;
}

void FileRw_class::retrigger(int offset,int len)
{
    m_flag=1;
    m_offs=offset;
    m_tLen=len;

    c_offset=0;
    c_len   =0;
}

void FileRw_class::load_next()
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

FileRw_class::FileRw_class(QObject *parent) : QThread(parent)
{
    m_flag=1;
    myfile=new QFile;
    lTimer=0;
    iRespRcvd=0;

    connect(this,SIGNAL(kick_start_signal()), this, SLOT(kick_start_slot()));
    connect(this,SIGNAL(state_update(int,int)),this, SLOT(analyze_state(int,int)));

    //connect(this,SIGNAL(signal_curr_state(int)),this, SLOT(process_curr_state(int)));

    //connect(this,SIGNAL(file_open_ok()),      this, SLOT(next_pkt_send()));
    //connect(this,SIGNAL(file_write_ok()),     this, SLOT(next_pkt_send()));
    //connect(this,SIGNAL(file_read_ok()),      this, SLOT(next_pkt_save()));

    //printf("offset=0x%04x len=0x%4x\n",offset,len);
    //fflush(stdout);
}

FileRw_class::~FileRw_class()
{
}


void FileRw_class::pullFile(const QString &fileName)
{
    unsigned short len;
    ioFileExchangeStruct   m;

    /* Data will be comming in so create a file */

    myfile->setFileName(fileName);
    if(!myfile->open(QFile::WriteOnly))
    {
#ifdef DEBUG_FILE_RW
        printf("Error:file exists %s \n",__FUNCTION__);
#endif
    }

    memset(m.line_buffer,'\0',MAX_TFR_SIZE);
    strcpy(m.line_buffer,fileName.toStdString().c_str());
#ifdef DEBUG_FILE_RW
    printf("%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
    fflush(stdout);
#endif

    openMode=0;
    len=coap_pc_req(buff,COAP_METHOD_GET,"file/open",&m,sizeof(ioFileExchangeStruct));
    Q_EMIT push_trigger(buff,len);
}

void FileRw_class::pushFile(const QString &fileName)
{
    unsigned short len;
    ioFileExchangeStruct   m;

    myfile->setFileName(fileName);

    if (!myfile->open(QFile::ReadOnly))
    {
#ifdef DEBUG_FILE_RW
        printf("Error:file exists %s \n",__FUNCTION__);
#endif
        printf("file does not exisit on your drive\n");
        printf("please copy first\n");
        fflush(stdout);
        return;
    }
    endPos=myfile->size();
    printf("file size=%d\n",endPos);
    fflush(stdout);

    strcpy(m.line_buffer,fileName.toStdString().c_str());
#ifdef DEBUG_FILE_RW
    printf("%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
    fflush(stdout);
#endif
    openMode=1; // write mode=1
    len=coap_pc_req(buff,COAP_METHOD_PUT,"file/open",&m,sizeof(ioFileExchangeStruct));
    Q_EMIT push_trigger(buff,len);
}

void FileRw_class::kick_start_slot()
{
#if 0
    unsigned short len;
    ioFileExchangeStruct   m;

    m.fop=FL_WFILE_NAME;
    strcpy(m.filename,"autoexec.c");

    openMode=0;
    if(openMode==1)
    {
        len=coap_pc_req(buff,COAP_METHOD_PUT,"file/open",&m,sizeof(ioFileExchangeStruct));
    }
    else
    {
        len=coap_pc_req(buff,COAP_METHOD_GET,"file/open",&m,sizeof(ioFileExchangeStruct));
    }
    Q_EMIT push_trigger(buff,len);

    /* device ping received, ask version info */
    //len=coap_pc_req(buff,1,"device/version",NULL,0);
    //p_lrn->push_msg(buff,len,1);
#endif
    endPos=0;
    currPos=0;
    //printf("testing taking place\n");
    //fflush(stdout);
    //pullFile("autoexec.ini");
    printf("---->starting file push\n");
    pushFile("autoexec.c");
    fflush(stdout);
}
