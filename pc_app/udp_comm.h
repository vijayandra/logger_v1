#ifndef UDP_COMM_H
#define UDP_COMM_H

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include "coap_pdu.h"


class CoAPComm : public QObject
{
    Q_OBJECT

public:
    CoAPComm(QString ipAddrString);


    void setServerPort(int port);
    unsigned char in_data[2048];
    unsigned short len;
    int coap_client_read(unsigned char *ucbuff);
    unsigned char ubuffer[2048];
    unsigned short ubufflen;
    unsigned short icntr;
    unsigned short iResponse;

signals:
    void responseRcvd();
    void uart1_Get();
    void uart1_Put();

private slots:
    //void sendBroadcastDatagram();
    void readBroadcastDatagram();
    void hwPoked();
    int  test_read();
    int  test_write();

private:
    QTimer alarmTimer;
    //
    QUdpSocket *coapUDPSocket;
    QUdpSocket *hwListenPSocket;
    //QUdpSocket coapSocketRx;
    QHostAddress address;
    int serverPort;
};

#endif
