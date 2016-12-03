#ifndef _LRN_TCP_THREAD_H
#define _LRN_TCP_THREAD_H

#include <QThread>
#include <QTcpSocket>

class LrnTcpThread : public QThread
{
    Q_OBJECT

public:
    LrnTcpThread(int socketDescriptor, QObject *parent);
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
};

#endif
