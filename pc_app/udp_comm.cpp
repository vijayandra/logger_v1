#include <QtNetwork>

#include "udp_comm.h"

//static const qint32 BroadcastInterval = 2000;
static const unsigned broadcastPort = 5683;

CoAPComm::CoAPComm(QString ipAddrString) : QObject()
{
    serverPort = 0;
    icntr=0;
    iResponse=0;
    printf("starting listerner \n");

    address.setAddress(ipAddrString);

    coapUDPSocket = new QUdpSocket(this);
    coapUDPSocket->bind(QHostAddress::Any,5683,QUdpSocket::ShareAddress| QUdpSocket::ReuseAddressHint);
    connect(coapUDPSocket, SIGNAL(readyRead()), this, SLOT(readBroadcastDatagram()));

    hwListenPSocket = new QUdpSocket(this);
    hwListenPSocket->bind(QHostAddress::Any,5684,QUdpSocket::ShareAddress| QUdpSocket::ReuseAddressHint);
    connect(hwListenPSocket, SIGNAL(readyRead()), this, SLOT(hwPoked()));


    //connect(this, SIGNAL(responseRcvd()), this, SLOT(test_write()));

    alarmTimer.setInterval(1);
    connect(&alarmTimer, SIGNAL(timeout()), this, SLOT(test_write()));
    alarmTimer.start();

    //connect(&alarmTimer, SIGNAL(timeout()), this, SLOT(sendBroadcastDatagram()));
}

void CoAPComm::setServerPort(int port)
{
    serverPort = port;
}

void CoAPComm::hwPoked()
{
    while (coapUDPSocket->hasPendingDatagrams())
    {
        QHostAddress senderIp;
        quint16 senderPort;
        QByteArray datagram;
        datagram.resize(coapUDPSocket->pendingDatagramSize());
        if (coapUDPSocket->readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort) == -1)
        {
            continue;
        }

        len=datagram.size();
        for(int i=0; i<len; i++)
        {
            //in_data[i]=datagram.at(i);
        }
    }

}

void CoAPComm::readBroadcastDatagram()
{
    fflush(stdout);
#if 0
    while (coapUDPSocket->hasPendingDatagrams())
    {
        QHostAddress senderIp;
        quint16 senderPort;
        QByteArray datagram;
        datagram.resize(coapUDPSocket->pendingDatagramSize());
        if (coapUDPSocket->readDatagram(datagram.data(), datagram.size(), &senderIp, &senderPort) == -1)
        {
            continue;
        }

        len=datagram.size();
        for(int i=0; i<len; i++)
        {
            in_data[i]=datagram.at(i);
        }
        test_read();
        iResponse++;
        emit responseRcvd();
        printf("iResponse=%d\n",iResponse);
    }
#else
    while (coapUDPSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(coapUDPSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        coapUDPSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        len=datagram.size();
        for(int i=0; i<len; i++)
        {
            in_data[i]=datagram.at(i);
        }
        test_read();

        //processTheDatagram(datagram);
    }
#endif
}

int CoAPComm::coap_client_read(unsigned char *ucbuff)
{
    memcpy(ucbuff,in_data,len);
    return len;
}

int CoAPComm::test_write()
{
    //printf("%s\n",__FUNCTION__);
    CoapPDU *pdu = new CoapPDU();

    pdu->setVersion(1);
    //pdu->setType(CoapPDU::COAP_CONFIRMABLE);
    pdu->setType(CoapPDU::COAP_NON_CONFIRMABLE);
    pdu->setCode(CoapPDU::COAP_GET);
    pdu->setToken((uint8_t*)"uart",4);
    pdu->setMessageID(icntr++);
    pdu->setURI((char*)"uart",4);
    pdu->addOption(CoapPDU::COAP_OPTION_CONTENT_FORMAT,1,(uint8_t*)")");

    //coap_client_write(pdu->getPDUPointer(),pdu->getPDULength());
    QByteArray   datagram((const char *)pdu->getPDUPointer(),pdu->getPDULength());
    coapUDPSocket->writeDatagram(datagram, address, 5683);
    coapUDPSocket->waitForBytesWritten();
    //delete pdu;
    //alarmTimer.start();

    return 0;
}

int CoAPComm::test_read()
{
    //alarmTimer.stop();
    ubufflen=coap_client_read(ubuffer);

    CoapPDU *recvPDU = new CoapPDU((uint8_t*)ubuffer,ubufflen);
    if(recvPDU->validate()!=1)
    {
        INFO("Malformed CoAP packet");
        return -1;
    }
    INFO("Valid CoAP PDU received");
    recvPDU->printHuman();

    return 0;
}
