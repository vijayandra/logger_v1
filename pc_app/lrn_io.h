/* version 1.2 */
#ifndef _LRN_CS_H
#define _LRN_CS_H

#include <QObject>
#include <QUdpSocket>
#include <QMutexLocker>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QTimer>
#include "shared_struct.h"

#include <stdint.h>
#include "options.h"
//#include "cantcoap.h"
#include "zcprotocol.h"
extern "C"
{
#include "srv_coap.h"
#include "enc_coap.h"
#include "shared_struct.h"
}

class ParTask : public QObject
{
    Q_OBJECT
public:
    ParTask()
    {
    }

    ~ParTask()
    {
    }
public slots:
#if 0
    void doWork()
    {
        while(1)
        {
            printf("test task\n");
            fflush(stdout);
        }
    }
#endif

signals:
    void workFinished();
};



class LRN_io : public QThread
{
    Q_OBJECT

    QUdpSocket *broadCastSocket;
    QUdpSocket *client_socket;
    QUdpSocket *server_socket;


    bool mConnected;
    QString rem_server;
    quint16 rem_port;

    QMutex mMutex;
    QWaitCondition mWait;
    ParTask *sTask;

    QHostAddress  userAddr;
    quint16       userPort;

    QWaitCondition lrnNotSignaled;
    QMutex         cs_mutex;

    QMutex d1mutex;

    uint8_t call_exe();
    void run();

public:
    void reinit_client_addr(QString server, quint16 port);
    explicit LRN_io(QString server, quint16 port,QObject *parent);
    virtual ~LRN_io();
    void push_button_transmit();
    static void cb(int i,int mid);

    //CoapPDU *pdu;
    unsigned char mRxBuffer[2400];

    scoap_packet_t pkt;
    scoap_packet_t rsppkt;

    /* zmodem interface */
    z_protocol  *z;

    QString  addr_from_broadcast;
    bool reinit_done;

    //int z_transmit(uint8_t * buff, int len);
    int z_receive(uint8_t * buff, int buff_len, int timeout = 5000);

    unsigned short push_msg(const void *msg,unsigned short len,unsigned short c_code);
    //unsigned short pull_msg(void *ibf,unsigned short len1);

    void exTxThread();

Q_SIGNALS:
    void hwPokeSignal();
    void hwPokeSignalWithIP(QString);
    void zack(int,int);
    void got_valid_coap(scoap_packet_t &);
    void SIG_GUI_UPDATE(ioTxtGrpthExchStrct &);

public slots:
    void hwPokeAction();
    void ClintWriteResponse();
    void ServerHandlingIncomming();
    void ztimer_slot();
    void zack_ack_slot(int,int);
private:
    QTimer *ztimer;

};

class UDPconnectConnectException
{
public:
    UDPconnectConnectException() {}
};

#endif // UDPCONNECT_H
