/* version 1.2 */
#include <QDebug>
#include <QTimer>
#include <QMutexLocker>
#include <QHostInfo>

#include "lrn_io.h"
extern "C"
{
#include "srv_coap.h"
#include "enc_coap.h"
}


void LRN_io::cb(int i,int mid)
{
    if(i==1)
    {
        printf("MAX Retry Error\n");
        fflush(stdout);
    }
    else if(i==2)
    {
        printf("Timeout Error\n");
        fflush(stdout);
    }
    else if(i==0)
    {

    }
}

void LRN_io::zack_ack_slot(int i,int mid)
{
    //printf("--->bytes sent Result=%d <0x%04x\n",i,mid);
    //fflush(stdout);
}

LRN_io::LRN_io(QString server, quint16 port,QObject *parent) : QThread(parent)
{
    //mRxlen = 0;
    mConnected = false;
    reinit_done= false;

    //init_zprotocol();
    endpoint_setup();

    rem_server=server;
    rem_port  =port;

    z=new z_protocol(this);

    //sTask           = new ParTask();
    //QThread *thread = new QThread( );
    //sTask->moveToThread(thread);


    server_socket   = new QUdpSocket();
    client_socket   = new QUdpSocket();
    broadCastSocket = new QUdpSocket(this);

    ztimer          = new QTimer(this);

    broadCastSocket->bind(QHostAddress::Any,5555,QUdpSocket::ShareAddress| QUdpSocket::ReuseAddressHint);
    connect(broadCastSocket, SIGNAL(readyRead()), this, SLOT(hwPokeAction()));

    connect(z,SIGNAL(zack(int,int)),SIGNAL(zack(int,int)));
    connect(z,SIGNAL(zack(int,int)),this,SLOT(zack_ack_slot(int,int)));
    connect(ztimer, SIGNAL(timeout()),z, SLOT(ms_tick()));

#if 0
    connect( sTask, SIGNAL(workFinished()), thread, SLOT(quit()) );
    connect( thread, SIGNAL(started()),  this, SLOT(exec_pull()) );
    connect( thread, SIGNAL(finished()), sTask, SLOT(deleteLater()) );
    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );
#endif


    client_socket->socketOption(QAbstractSocket::KeepAliveOption);
    server_socket->socketOption(QAbstractSocket::KeepAliveOption);

    connect(ztimer, SIGNAL(timeout()), this, SLOT(ztimer_slot()));

    ztimer->start(1);

    if(!server_socket->bind(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server.";
    }
    else
    {
        //qDebug() << "Listening on port=" << port;
        connect(server_socket,SIGNAL(readyRead()),this,SLOT(ServerHandlingIncomming()));
    }

    connect(client_socket, SIGNAL(readyRead()), this, SLOT(ClintWriteResponse()));

    client_socket->connectToHost(server, port);

    //printf("port = %d \n",port);

    if(!client_socket->waitForConnected(5000))
    {
        throw UDPconnectConnectException();
    }

    if(client_socket->state() != QAbstractSocket::ConnectedState)
    {
        throw UDPconnectConnectException();
    }

    mConnected = true;

    //qDebug() << "Connected to host state: " << client_socket->state();
}

void LRN_io::ztimer_slot()
{
    cs_mutex.lock();
    lrnNotSignaled.wakeAll();
    cs_mutex.unlock();

    if(z->disc->usIsNonEmpty())
    {
        unsigned short len;
        unsigned char  buffer[1488];
        int n, rc;

        if(z->disc->usPullDiscQ(buffer,&len));
        {
            if (0 == (rc = scoap_parse(&pkt,buffer,len)))
            {
                Q_EMIT got_valid_coap(pkt);
            }
        }
    }

}

void LRN_io::reinit_client_addr(QString server, quint16 port)
{
    client_socket->disconnectFromHost();
    client_socket->connectToHost(server, port);
}

void LRN_io::ServerHandlingIncomming()
{
    QHostAddress senderIp;
    quint16 senderPort;
    int n, rc;
    int l=0;
    static unsigned short l1=0;

    QByteArray datagram;
    qint64 dataSize;

    //server_socket->waitForReadyRead();

    dataSize = server_socket->pendingDatagramSize();
    datagram.resize(dataSize);

    if(server_socket->readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort))
    {
        //pull_msg(mRxbuffer,dataSize);
#if 1
        //memcpy(&iguiUpdate, buf.constData(),sizeof(ioTxtGrpthExchStrct));
        z->incomming_sorting_box(datagram.constData(),datagram.size());
#if 0
        z->incomming_sorting_box(mRxBuffer,dataSize);
        if(z->disc->usIsNonEmpty())
        {
            unsigned short len;
            unsigned char  buffer[1488];
            if(z->disc->usPullDiscQ(buffer,&len));
            {
                if (0 == (rc = scoap_parse(&pkt,buffer,len)))
                {
                    Q_EMIT got_valid_coap(pkt);
                }
            }
        }
#endif
#else
        for(int i=0; i<datagram.size(); i++)
        {
            mRxBuffer[i]=datagram.at(i);
        }
        if(z->incomming_sorting_box(mRxBuffer,dataSize))
        {
            //printf("len=%d\n",dataSize-8);
            if (0 == (rc = scoap_parse(&pkt,z->z_inbuff,dataSize-8)))
            {
                Q_EMIT got_valid_coap(pkt);
            }
        }
#endif

    }
}

int LRN_io::z_receive(uint8_t * buff, int buff_len, int timeout)
{
    if(!mConnected)
        return -1;

    int rxLen = -1;
    return rxLen;
}

void LRN_io::ClintWriteResponse()
{
    client_socket->waitForReadyRead();
}

void LRN_io::exTxThread()
{
    push_button_transmit();
}

LRN_io::~LRN_io()
{
    client_socket->close();
    server_socket->close();

    if(client_socket)
    {
        client_socket->disconnect();
        delete client_socket;
    }

    if(server_socket)
    {
        server_socket->disconnect();
        delete server_socket;
    }
}

void LRN_io::push_button_transmit()
{
#if 0
    cs_mutex.lock();
    //script_thread.icurr_script=0;
    lrnNotSignaled.wakeAll();
    cs_mutex.unlock();
#endif
}

unsigned short LRN_io::push_msg(const void *msg,unsigned short len,unsigned short c_code)
{
    unsigned short len1=0;

    /* zmodem interface */
    //z->z_post_mailbox("Vijayandra",10,1,&cb);
    z->z_post_mailbox(msg,len,1,&cb);
    usleep(200);

    return len1;
}


void LRN_io::run()
{
    while(1)
    {
        cs_mutex.lock();
        lrnNotSignaled.wait(&cs_mutex);
        cs_mutex.unlock();

        call_exe();
    }
}

void LRN_io::hwPokeAction()
{
    QHostAddress senderIp;
    quint16 senderPort;
    int n, rc;
    int l=0;

    QByteArray datagram;
    qint64 dataSize;

    dataSize = broadCastSocket->pendingDatagramSize();
    datagram.resize(dataSize);

    if(broadCastSocket->readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort))
    {
        for(int i=0; i<datagram.size(); i++)
        {
            mRxBuffer[i]=datagram.at(i);
        }

        if (0 != (rc = scoap_parse(&pkt,mRxBuffer,datagram.size())))
        {
        }
        else
        {
            if(!reinit_done)
            {
                QString s=senderIp.toString();
                addr_from_broadcast=s;

                //printf("=====>device version string match\n");
                //fflush(stdout);
                //scoap_handle_req(&scratch_buf, &pkt, &rsppkt);
                Q_EMIT hwPokeSignal();
                Q_EMIT hwPokeSignalWithIP(s);

                if(reinit_done==false)
                {
                    reinit_done=true;
                    reinit_client_addr(s,5683);
                }
            }
        }
    }
}

uint8_t LRN_io::call_exe()
{
    unsigned short i=0;
    short int len;
    char tbuff[4095];
    unsigned char *dptr;
    uint8_t  retVal=MAX_ZMSG;

    //while(_oi.out_count)
    QMutexLocker locker(&d1mutex);


    /* zmodem interface */
    memset(tbuff,'\0',4095);
    len=z->z_call_me_1millisec((unsigned char *)tbuff);

    if(len)
    {
        if(client_socket->state()!=QUdpSocket::ConnectedState)
        {
            client_socket->connectToHost(rem_server, rem_port);
            client_socket->waitForConnected(1000);
        }

        if(client_socket->state()==QUdpSocket::ConnectedState)
        {
            client_socket->write((const char *)tbuff,len);
            client_socket->waitForBytesWritten();
        }
        //printf("%s %d <%d> %s\n",__FUNCTION__,__LINE__,len,(const char *)tbuff);
        //printf("==========>%s %d <%d>\n",__FUNCTION__,__LINE__,len);
        //fflush(stdout);
    }

    return retVal;
}
