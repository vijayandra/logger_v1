/* version 1.2 */
#ifndef __Z_DISC_CPP_PROTOCOL_CPP_H
#define __Z_DISC_CPP_PROTOCOL_CPP_H

#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QFile>
#include <QObject>
#include <QQueue>
#include <QMutexLocker>
#include <QTime>
#include <QTimer>
#include <stdio.h>

#include <stdio.h>
#include <string.h>

extern "C"
{
#include "options.h"
#include "global_var.h"
#include "io_uart.h"
}

#include "shared_struct.h"

#define DISCR_CELL_SIZE     1288
#define DISCR_SIZE     3

struct GBuff
{
    unsigned char  buff[DISCR_CELL_SIZE];
};

struct DisrMsgQ
{
    struct   GBuff G[DISCR_SIZE];
    unsigned short len[DISCR_SIZE];
    unsigned short discr_Head;
    unsigned short discr_Tail;
    unsigned short discr_Len;
};



class DiscBuff: public QObject
{
    Q_OBJECT
private:

    QMutex         zmutex;

public:
    DiscBuff(QObject *parent = 0);

    struct DisrMsgQ disQ;

    unsigned short usPushDiscQ(unsigned char *ch,unsigned short len);
    unsigned char  usPullDiscQ(unsigned char *ch,unsigned short *len);
    unsigned short usIsNonEmpty(void);

};

#endif
