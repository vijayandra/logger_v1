#ifndef __TFTPC_H
#define __TFTPC_H

#include <QDebug>
#include <QWidget>
#include <QTextEdit>
#include <QProcess>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QList>
#include <QLabel>
#include <QUdpSocket>
#include "options.h"

class QTFTPWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QTFTPWidget(QString localAddressString = QString(), int localPort = -1,
                         QString remoteAddressString = QString(), int remotePort = -1,
                         QWidget *parent = 0);
    ~QTFTPWidget();

    bool putByteArray(QString filename, QByteArray transmittingFile);
    bool getByteArray(QString filename, QByteArray *requestedFile);

    inline QString errorString()
    {
        return(lastErrorString);
    }

    QString remoteAddressString();
    QString localAddressString();
    int remotePortNumber();
    int localPortNumber();

public slots:
    inline void onSetLocalAddress(QString address)
    {
        localAddressSuppliedByUser=address;
    }
    inline void onSetLocalPort(int port)
    {
        localPortSuppliedByUser=port;
    }
    inline void onSetRemoteAddress(QString address)
    {
        remoteAddressSuppliedByUser=address;
    }
    inline void onSetRemotePort(int port)
    {
        remotePortSuppliedByUser=port;
    }

private:
    QString localAddressSuppliedByUser, remoteAddressSuppliedByUser;
    int localPortSuppliedByUser, remotePortSuppliedByUser;

    QString lastErrorString;
    QUdpSocket *socket;
    QComboBox *localAddressComboBox;
    QSpinBox *localPortSpinBox;
    QLineEdit *remoteAddressLineEdit;
    QSpinBox *remotePortSpinBox;

    bool bindSocket();
    QByteArray getFilePacket(QString filename);
    QByteArray putFilePacket(QString filename);
};
#endif
