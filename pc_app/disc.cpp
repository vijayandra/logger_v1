#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "options.h"

extern "C"
{
#include "global_var.h"
#include "io_uart.h"
#define CIRCULAR_INC(X,MAX) X++;if(X>=MAX) X=0;
}


#include "disc.h"

//class disc
DiscBuff::DiscBuff(QObject *parent) : QObject(parent)
{
    unsigned short i;

    disQ.discr_Head = 0;
    disQ.discr_Tail = 0;
    disQ.discr_Len  = 0;

    for(i=0; i<DISCR_SIZE; i++)
    {
        //memset(disQ.cbuff,'\0',DISCR_CELL_SIZE);
        disQ.len[i] = 0;
    }
}

unsigned short DiscBuff::usIsNonEmpty(void)
{
    //QMutexLocker locker(&zmutex);
    return disQ.discr_Len;
}

unsigned short DiscBuff::usPushDiscQ(unsigned char *ch,unsigned short len)
{
    //QMutexLocker locker(&zmutex);
    if(disQ.discr_Len<DISCR_SIZE)
    {

        memcpy(disQ.G[disQ.discr_Head].buff,ch,len);
        disQ.len[disQ.discr_Head]=len;


        CIRCULAR_INC(disQ.discr_Head,DISCR_SIZE);
        disQ.discr_Len++;
        return 1;
    }
    return 0;
}

unsigned char DiscBuff::usPullDiscQ(unsigned char *ch,unsigned short *len)
{
    unsigned char i;
    i=0;
    //QMutexLocker locker(&zmutex);
    if(disQ.discr_Len)
    {
        *len=disQ.len[disQ.discr_Tail];
        memcpy(ch,disQ.G[disQ.discr_Tail].buff,*len);
        //*len=disQ.len[disQ.discr_Tail];

        CIRCULAR_INC(disQ.discr_Tail,DISCR_SIZE);
        disQ.discr_Len--;
        i=1;
    }
    return i;
}
