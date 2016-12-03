#include "lrn_tcp_thread.h"
#include "lrn_tcp_s.h"
extern "C"
{
#include "tcppkt.h"
}

#include <stdlib.h>

LrnTcpServer::LrnTcpServer(quint16 port,QObject *parent) : QTcpServer(parent)
{
    nport=port;
    tcpSocket=new QTcpSocket(this);
}

void LrnTcpServer::incomingConnection(int socketDescriptor)
{
#if 1
    if (!tcpSocket->setSocketDescriptor(socketDescriptor))
    {
        //emit error(tcpSocket->error());
        return;
    }
    QByteArray buf = tcpSocket->readAll();

    for(int i=0; i<buf.size(); i++)
    {
        //printf("%c",buf.at(i));
    }

    //printf("run-->%s %d\n",__FUNCTION__,buf.size());
    //memcpy(&iguiUpdate, buf.constData(),sizeof(ioTxtGrpthExchStrct));
    //

    if((buf.size()) && (is_good_tcp((unsigned char *)buf.constData())))
    {
        printf("good pkt %04x\r\n",_tpkt.mid);
        memcpy(&iguiUpdate, (buf.constData()+8),buf.size());
        tcpSocket->write(buf.constData(),8);
        Q_EMIT SIG_GUI_UPDATE(iguiUpdate);
    }
    fflush(stdout);


#else
    LrnTcpThread *thread = new LrnTcpThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
#endif
}
