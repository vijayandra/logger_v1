#include "options.h"
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include <QMutexLocker>
#include "file_nw.h"
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

using namespace std;

#define  C_STR(X)  ((string((const char *)X.toAscii())).c_str())
//#define DEBUG_FILE_RW

const char *uriNFileOpArrStr[20]=
{
    "<frd_line>",
    "<frd_bin>",
    "<fwr_line>",
    "<fwr_bin>",
    "<file_reset>"
};


int FileNw_class::route_msg(QString s,scoap_packet_t &pkt)
{
    unsigned short len;
    static int i=0;
    char uri[32];
#ifdef DEBUG_FILE_RW
    qDebug() << s;
#endif
    memset(uri,'\0',32);
    memcpy(uri,pkt.opts[0].buf.p,pkt.opts[0].buf.len);
    printf("))))))))))))))%s\n",uri);

#define  IS_URI_MATCH(X) (strncmp(X,(char *)pkt.opts[0].buf.p,strlen(X))==0)


    if(IS_URI_MATCH("<frd_line>"))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(iNFileExchangeStruct));
        fmutex.lock();
        response_index=0;
        fileNotSignaled.wakeAll();
        fmutex.unlock();
    }
    else if(IS_URI_MATCH("<frd_bin>"))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(iNFileExchangeStruct));
        fmutex.lock();
        response_index=1;
        fileNotSignaled.wakeAll();
        fmutex.unlock();
    }
    else if(IS_URI_MATCH("<fwr_line>"))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(iNFileExchangeStruct));
        fmutex.lock();
        response_index=2;
        fileNotSignaled.wakeAll();
        fmutex.unlock();
    }
    else if(IS_URI_MATCH("<fwr_bin>"))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(iNFileExchangeStruct));
        fmutex.lock();
        response_index=3;
        fileNotSignaled.wakeAll();
        fmutex.unlock();
    }
    else if(IS_URI_MATCH("<file_reset>"))
    {
        memcpy(&gluData,pkt.payload.p,sizeof(iNFileExchangeStruct));
        fmutex.lock();
        response_index=4;
        fileNotSignaled.wakeAll();
        fmutex.unlock();
    }

    return 0;
}

void FileNw_class::next_chunk_out_write_file()
{
}

void FileNw_class::heartbeat_pulse()
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
            //printf("delayed start for file activated\n");
            //fflush(stdout);
#endif
            i=1;
            //Q_EMIT kick_start_signal();
        }
    }
    lTimer++;
}

void FileNw_class::setFileName(QString finame)
{
    fileName=finame;
    argCnt++;
}

void FileNw_class::setDirection(bool dir)
{
    isGettingFile=dir;
    argCnt++;
}

int FileNw_class::device_ready(scoap_packet_t &pkt)
{
#ifdef DEBUG_FILE_RW
    printf("------------%s -device ready---------------\n",__FILE__);
#endif

    mdata.MemType=0;
    mdata.Off_l=0;
    mdata.Off_h=0;
    mdata.range=1000;
    lTimer=0;

    return 0;
}

#if 0
int FileNw_class::process_incomming_pkt(scoap_packet_t &pkt)
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
#endif

FileNw_class::FileNw_class(QObject *parent) : QThread(parent)
{
    m_flag=1;
    myfile=new QFile;
    lTimer=0;
    response_index=0xff;
    iRespRcvd=0;
    isGettingFile=false;
    argCnt=0;

    connect(this,SIGNAL(kick_start_signal()),     this, SLOT(kick_start_slot()));
    //connect(this,SIGNAL(signal_load_next_pkt()),  this, SLOT(next_chunk_out_write_file()));
    //connect(this,SIGNAL(request_read_next_pkt()), this, SLOT(next_chunk_in_file()));
    start();
}

FileNw_class::~FileNw_class()
{
}

void FileNw_class::next_line_in_file()
{
    unsigned short len;
    unsigned short isSucess=0;
    iNFileExchangeStruct   m;

    //QMutexLocker locker(&fmutex);


    printf(gluData.line_buffer);
    fflush(stdout);
    m.n1=0;
    m.n2=0;

    m.direction=0;
    m.fileTrfSize=MAX_TFR_SIZE;
    strcpy(m.filename,gluData.filename);
    len=coap_pc_req(buff,COAP_METHOD_GET,"file/line",&m,sizeof(iNFileExchangeStruct));

    if(gluData.fileOffset<gluData.fileLength)
    {
        myfile->setFileName(gluData.filename);
        if(myfile->open(QIODevice::WriteOnly | QIODevice::Append))
        {
            if(gluData.fileTrfSize)
            {
                myfile->write(gluData.line_buffer,gluData.fileTrfSize);
                myfile->flush();
            }
            myfile->close();
        }
        Q_EMIT push_trigger(buff,len);
    }
    else
    {
        printf("completed\r\n");
    }

}



void FileNw_class::next_bin_in_file()
{
    unsigned short len;
    unsigned short l;
    unsigned short isSucess=0;
    static unsigned short l2=0;
    iNFileExchangeStruct   m;

    //QMutexLocker locker(&fmutex);
    l=0;

    if(l2==0)
        //if(gluData.fileOffset>gluData.fileLength)
    {
        m.fileOffset=0;
        m.fileLength=0;
        m.fileTrfSize=MAX_TFR_SIZE;
        gluData.fileOffset=0;
        gluData.fileLength=0;
        gluData.fileTrfSize=0;
        l=1;
        l2=1;
    }

    //printf(gluData.line_buffer);

    m.direction=0;
    m.fileOffset+=gluData.fileTrfSize;
    m.fileTrfSize=MAX_TFR_SIZE;
    strcpy(m.filename,gluData.filename);
    len=coap_pc_req(buff,COAP_METHOD_GET,"file/bin",&m,sizeof(iNFileExchangeStruct));
    printf("BIN offset=%d len=%d\n",gluData.fileOffset,gluData.fileLength);

    if((gluData.fileOffset<gluData.fileLength) || (l))
    {
        if(!l)
        {
            myfile->setFileName(gluData.filename);
            if(myfile->open(QIODevice::WriteOnly | QIODevice::Append))
            {
                if(gluData.fileTrfSize)
                {
                    myfile->write(gluData.line_buffer,gluData.fileTrfSize);
                    myfile->flush();
                }
                myfile->close();
            }
        }
        Q_EMIT push_trigger(buff,len);
    }
    else
    {
        printf("completed\r\n");
    }
}

void FileNw_class::next_line_out_file()
{
    unsigned short len;
    unsigned short isSucess=0;
    iNFileExchangeStruct   m;

    //QMutexLocker locker(&fmutex);


    printf(gluData.line_buffer);
    fflush(stdout);
    m.n1=0;
    m.n2=0;

    m.direction=0;
    m.fileTrfSize=MAX_TFR_SIZE;
    strcpy(m.filename,gluData.filename);
    len=coap_pc_req(buff,COAP_METHOD_GET,"file/line",&m,sizeof(iNFileExchangeStruct));

    if(gluData.fileOffset<gluData.fileLength)
    {
        myfile->setFileName(gluData.filename);
        if(myfile->open(QIODevice::WriteOnly | QIODevice::Append))
        {
            if(gluData.fileTrfSize)
            {
                myfile->write(gluData.line_buffer,gluData.fileTrfSize);
                myfile->flush();
            }
            myfile->close();
        }
        Q_EMIT push_trigger(buff,len);
    }
    else
    {
        printf("completed\r\n");
    }

}

void FileNw_class::next_push_first_pkt_file()
{
    iNFileExchangeStruct   m;
    unsigned short len;

    if(myfile->isOpen())
    {
        if(_currPos<_fileSize)
        {
            strcpy(m.filename,gluData.filename);
            m.fileOffset  = _currPos;
            m.fileLength  = _fileSize;
            m.fileTrfSize = myfile->read(m.line_buffer,MAX_TFR_SIZE);
            _currPos += m.fileTrfSize;

            len=coap_pc_req(buff,COAP_METHOD_PUT,"file/bin",&m,sizeof(iNFileExchangeStruct));
            Q_EMIT push_trigger(buff,len);
            printf("sending first pkt %d %d %d\r\n",m.fileOffset,m.fileLength,m.fileTrfSize);
            fflush(stdout);
        }
        else
        {
            printf("file transfer completed\r\n");
            fflush(stdout);
        }
    }
}

void FileNw_class::next_bin_out_file()
{
    unsigned short len;
    unsigned short l;
    unsigned short isSucess=0;
    static unsigned short l2=0;
    iNFileExchangeStruct   m;

    //QMutexLocker locker(&fmutex);
    l=0;

    if(l2==0)
        //if(gluData.fileOffset>gluData.fileLength)
    {
        m.fileOffset=0;
        m.fileLength=0;
        m.fileTrfSize=MAX_TFR_SIZE;
        gluData.fileOffset=0;
        gluData.fileLength=0;
        gluData.fileTrfSize=0;
        l=1;
        l2=1;
    }

    //printf(gluData.line_buffer);

    m.direction=0;
    m.fileOffset+=gluData.fileTrfSize;
    m.fileTrfSize=MAX_TFR_SIZE;
    strcpy(m.filename,gluData.filename);
    len=coap_pc_req(buff,COAP_METHOD_GET,"file/bin",&m,sizeof(iNFileExchangeStruct));
    printf("BIN offset=%d len=%d\n",gluData.fileOffset,gluData.fileLength);

    if((gluData.fileOffset<gluData.fileLength) || (l))
    {
        if(!l)
        {
            myfile->setFileName(gluData.filename);
            if(myfile->open(QIODevice::WriteOnly | QIODevice::Append))
            {
                if(gluData.fileTrfSize)
                {
                    myfile->write(gluData.line_buffer,gluData.fileTrfSize);
                    myfile->flush();
                }
                myfile->close();
            }
        }
        Q_EMIT push_trigger(buff,len);
    }
    else
    {
        printf("completed\r\n");
    }
}


void FileNw_class::kick_start_slot()
{
    if(argCnt>=2)
    {
        isFirstPktFile=true;
        tokenID=0;
        if(isGettingFile)
        {
            unsigned short len;
            iNFileExchangeStruct   m;

            m.direction=0;
            m.fileOffset=0;
            m.fileTrfSize=0;
            m.fileLength=0;
            m.tokenID=tokenID;
            strcpy(m.filename,fileName.toStdString().c_str());

            myfile->setFileName(fileName);
            if(myfile->open(QIODevice::WriteOnly))
            {
                myfile->close();
            }

            m.n1=1;
            len=coap_pc_req(buff,COAP_METHOD_GET,"file/reset",&m,sizeof(iNFileExchangeStruct));
            Q_EMIT push_trigger(buff,len);
        }
        else
        {
            iNFileExchangeStruct   m;
            unsigned short len;

            _currPos  = 0;
            _fileSize = 0;
            strcpy(m.filename,fileName.toStdString().c_str());

            myfile->setFileName(m.filename);
            if(myfile->open(QIODevice::ReadOnly))
            {
                _currPos  = 0;
                _fileSize = myfile->size();
            }
            else
            {
                printf("file does not exists\r\n");
                fflush(stdout);
                return;
            }

            printf("file download starts %d\r\n",_fileSize);
            fflush(stdout);

            len=coap_pc_req(buff,COAP_METHOD_PUT,"file/reset",&m,sizeof(iNFileExchangeStruct));
            Q_EMIT push_trigger(buff,len);
        }
    }
}

void FileNw_class::run()
{
    while(1)
    {
        fmutex.lock();
        fileNotSignaled.wait(&fmutex);
        fmutex.unlock();

        if(response_index==0)
        {
            next_line_in_file();
        }
        else if(response_index==1)
        {
            next_bin_ep_in_file();
        }
        else if(response_index==2)
        {
            next_line_out_file();
        }
        else if(response_index==3)
        {
            next_push_first_pkt_file();
        }
        else if(response_index==4)
        {
            if(isGettingFile)
            {
                next_bin_ep_in_file();
                printf("next attempt to get file\r\n");
                fflush(stdout);
            }
            else
            {
                next_push_first_pkt_file();
            }
        }
    }
}


void FileNw_class::next_bin_ep_in_file()
{
    unsigned short len;
    unsigned short l;
    unsigned short isSucess=0;
    static unsigned short l2=0;
    iNFileExchangeStruct   m;

    //printf("BIN offset=%d chunk size=%d file len=%d\n",gluData.fileOffset,gluData.fileTrfSize,gluData.fileLength);
    if(gluData.fileLength)
    {
        printf("proress offset=%d <token ID=%d>\n",100*gluData.fileOffset/gluData.fileLength,tokenID);
        fflush(stdout);
    }

    if(isFirstPktFile)
    {
        isFirstPktFile=false;
        m.fileTrfSize=MAX_TFR_SIZE;
        m.tokenID=tokenID++;
        strcpy(m.filename,gluData.filename);
        len=coap_pc_req(buff,COAP_METHOD_GET,"file/bin",&m,sizeof(iNFileExchangeStruct));
        Q_EMIT push_trigger(buff,len);
        return;
    }

    if(gluData.fileOffset<gluData.fileLength)
    {
        myfile->setFileName(gluData.filename);
        if(myfile->open(QIODevice::WriteOnly | QIODevice::Append))
        {
            if(gluData.fileTrfSize)
            {
                myfile->write(gluData.line_buffer,gluData.fileTrfSize);
                myfile->flush();
            }

            myfile->close();

            m.fileTrfSize=MAX_TFR_SIZE;
            m.tokenID=tokenID++;
            strcpy(m.filename,gluData.filename);
            len=coap_pc_req(buff,COAP_METHOD_GET,"file/bin",&m,sizeof(iNFileExchangeStruct));
            Q_EMIT push_trigger(buff,len);
        }
    }
    else
    {
        printf("completed\r\n");
    }
}
