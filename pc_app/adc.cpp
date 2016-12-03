#include "options.h"
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include "adc.h"
//#include "SmtpMime"
#ifdef ZSERIAL
#include "serial_cs.h"
#else
#include "lrn_io.h"
#endif
extern "C"
{
#include "enc_coap.h"
#include "ep_mem.h"
#include "ep_file.h"
}

int ADC_class::route_msg(QString s,scoap_packet_t &pkt)
{
    unsigned short i;
    static unsigned short j=0;
    memcpy(&gluData,pkt.payload.p,sizeof(ioFileExchangeStruct));
    for(i=0;i<MAX_ADC_DAC_DATA_IN_PKT;i++)
    {
        printf("%d,%d\n", gluData.ch1[i], gluData.ch2[i]);
    }

    printf("jcounter=%d\n",j++);
        fflush(stdout);
    return 0;
}

int ADC_class::process_incomming_pkt(scoap_packet_t &pkt)
{
    unsigned short i,len;

    return 0;
}

ADC_class::ADC_class(QObject *parent) : QThread(parent)
{
}

ADC_class::~ADC_class()
{
    //free(m_Ptr);
}

