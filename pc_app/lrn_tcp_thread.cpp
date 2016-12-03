#include "lrn_tcp_thread.h"

#include <QtNetwork>

LrnTcpThread::LrnTcpThread(int socketDescriptor, QObject *parent) : QThread(parent), socketDescriptor(socketDescriptor)
{
}

void LrnTcpThread::run()
{
    QTcpSocket tcpSocket;

    if (!tcpSocket.setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket.error());
        return;
    }
    QByteArray buf = tcpSocket.readAll();

    for(int i=0; i<buf.size(); i++)
    {
        printf("%c",buf.at(i));
    }

    printf("run-->%s %d\n",__FUNCTION__,buf.size());
    fflush(stdout);
}
