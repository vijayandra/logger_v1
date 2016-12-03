#ifndef _LRN_TCP_SERVERS_H
#define _LRN_TCP_SERVERS_H

#include <QStringList>
#include <QTcpServer>
#include "shared_struct.h"

class LrnTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit LrnTcpServer(quint16 port,QObject *parent=0);
    quint16 nport;
    QTcpSocket *tcpSocket;
    ioTxtGrpthExchStrct iguiUpdate;

signals:
    void SIG_GUI_UPDATE(ioTxtGrpthExchStrct &);

protected:
    void incomingConnection(int socketDescriptor);

private:
    QStringList fortunes;
};

#endif
