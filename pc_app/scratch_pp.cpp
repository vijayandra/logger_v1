#include "options.h"
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <stdio.h>
#include "scratch_pp.h"
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

//#define DEBUG_FILE_RW
#define  IS_URI_MATCH(X) ((strncmp(X,(char *)pkt.opts[0].buf.p,pkt.opts[0].buf.len))==0)

int SCRATCH_pp::route_msg(QString s,scoap_packet_t &pkt)
{
    unsigned short len;
#ifdef DEBUG_FILE_RW
    qDebug() << s;
#endif

    if(IS_URI_MATCH(FILE_OPEN_URI))
    {
    }
    fflush(stdout);

    return 0;
}

int SCRATCH_pp::process_incomming_pkt(scoap_packet_t &pkt)
{
    unsigned short i,len;

    if(pkt.payload.len>0)
    {
        memcpy(&iGuiUpdate,pkt.payload.p,pkt.payload.len);

        switch(iGuiUpdate.guiDest.tWin)
        {
        case IW_SCRATCH1:

            Q_EMIT SIG_SCRATCH1(iGuiUpdate);

            break;

        case IW_SCRATCH2:

            Q_EMIT SIG_SCRATCH2(iGuiUpdate);

            break;

        case IW_SCRATCH3:
            Q_EMIT SIG_SCRATCH3(iGuiUpdate);

            break;

        case IW_RS485:
            Q_EMIT SIG_RS485(iGuiUpdate);

            break;

        case IW_UART2:
            Q_EMIT SIG_UART2(iGuiUpdate);

            break;

        case IW_UART3:
            Q_EMIT SIG_UART3(iGuiUpdate);

            break;

        case IW_UART23:
            Q_EMIT SIG_UART23(iGuiUpdate);

            break;

        default:
            break;

        }

        printf("colTxt=%d\n" ,iGuiUpdate.guiDest.colTxt);
        printf("fontTxt=%d\n",iGuiUpdate.guiDest.fontTxt);
        printf("win=%d\n"    ,iGuiUpdate.guiDest.tWin);
        printf("pInfo=%d\n"  ,iGuiUpdate.guiDest.pInfo);
        printf("CmdTxt=%d\n" ,iGuiUpdate.guiDest.cmdTxt);
        printf("LenTxt=%d\n" ,iGuiUpdate.guiDest.lenTxt);
        printf("String= 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n" ,iGuiUpdate.hex_data_buffer[0] ,iGuiUpdate.hex_data_buffer[1] ,iGuiUpdate.hex_data_buffer[2] ,iGuiUpdate.hex_data_buffer[3] ,iGuiUpdate.hex_data_buffer[4]);

        fflush(stdout);
    }

    return 0;
}

void SCRATCH_pp::heartbeat_pulse()
{
    static unsigned char i=0;
    /* this serves as delayed activate system
     * where
     * delayed kickoff for timer */
    lTimer++;
}


int SCRATCH_pp::device_ready(scoap_packet_t &pkt)
{
#ifdef DEBUG_FILE_RW
    printf("------------%s -device ready---------------\n",__FILE__);
    fflush(stdout);
#endif
    printf("--RTC-------%s -device ready---------------\n",__FILE__);
    fflush(stdout);

    lTimer=0;

    return 0;
}


SCRATCH_pp::SCRATCH_pp(QObject *parent) : QObject(parent)
{
    lTimer=0;
}

SCRATCH_pp::~SCRATCH_pp()
{
}
