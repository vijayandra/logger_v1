/* version 1.2 */
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
#include "ext_script.h"

extern "C"
{
#include "global_var.h"
#include "io_uart.h"
}


#include "disc.h"
#include "zcprotocol.h"

#define NO_MORE_DATA 0x1000
#define HIGH_BYTE(X) (0xff & ((X)>>8))
#define LOW_BYTE(X)  (0xff & (X))
#define BYTE(X)      (0xff & (X))

#define _RING_TX 0
#define _RING_RX 1

//class z_protocol
z_protocol::z_protocol(QObject *parent) : QObject(parent)
{
    unsigned char i;

    disc=new DiscBuff(this);

    _oi.static_mid = 0;

    _oi.out_count  = 0;
    _oi.in_count   = 0;

    vInitRing(_RING_TX,cztx_buff,MAX_ZMSG*8);
    vInitRing(_RING_RX,crx_buff,MAX_ZMSG*MAX_PAYLOAD);

    for(i=0; i<MAX_ZMSG; i++)
    {
        _oi.isActive[i]=0;
        _oi.isTsmitted[i]=0;
        _oi.isWaitAck[i]=0;
    }
}

void z_protocol::ms_tick()
{
    volatile short int i=0;
    QMutexLocker locker(&zmutex);

    for(i=0; i<MAX_ZMSG; i++)
    {
        if(_oi.isActive[i])
        {
            //printf("%s <%d> <%d>\n",__FUNCTION__,__LINE__,i); fflush(stdout);
            //if active then reduce timeout by one
            if(_oi.outz[i].timeout)
            {
                _oi.outz[i].timeout--;
            }

            //if last sent is set then decrement 1
            if(_oi.outz[i].lastSent)
            {
                _oi.outz[i].lastSent--;
            }

            /* if timeout expired then remove it from list */
            if(_oi.outz[i].timeout==0)
            {
                _oi.isActive[i]=0;
                //printf("time out tick=%d\n",currTime);
                //fflush(stdout);
                _oi.outz[i].com_error = 1;
                if(_oi.outz[i].cb != NULL)
                {
                    (_oi.outz[i].cb)(2,_oi.outz[i].mid);
                }
            }
        }
    }
    currTime++;
}

unsigned short z_protocol::z_call_me_1millisec(unsigned char *sbuff)
{
    unsigned short len;
    unsigned short retVal=0;
    static unsigned short index=0;
    short int i=0;

    QMutexLocker locker(&zmutex);

    if((_oi.isActive[index]) && (_oi.outz[index].lastSent==0))
    {
        //printf("%s <%d>\n",__FUNCTION__,__LINE__); fflush(stdout);
        memcpy(sbuff,_oi.outz[index].payload,_oi.outz[index].txLen);
        retVal=_oi.outz[index].txLen;
        //printf("loading message\n");
        //fflush(stdout);

        /* mark interval timeout */
        _oi.outz[index].lastSent=Z_INTERVAL;

        //_oi.isActive[index]=0;

        i=_oi.outz[index].txLen;

        if(_oi.outz[index].txCnt)
        {
            _oi.outz[index].txCnt--;
        }

        if(_oi.outz[index].txCnt==0)
        {
            _oi.isActive[index]=0;
            _oi.outz[index].com_error = 1;
            if(_oi.outz[index].cb != NULL)
            {
                (_oi.outz[index].cb)(1,_oi.outz[index].mid);
            }
            //printf("did not get response\n");
            //fflush(stdout);
        }
    }

    index++;
    if(index>(MAX_ZMSG-1))
    {
        index=0;
    }

    /* if there is nothing to be sent then send ack packets */
    if(retVal==0)
    {
        i=100;
        usRingRead(_RING_TX,sbuff,&i);
        retVal=i;
        return retVal;
    }

    return retVal;
}

unsigned short z_protocol::z_read_mailbox(char *buff,short len)
{
    currTime=0;
    QMutexLocker locker(&zmutex);
    usRingRead(_RING_RX,buff,&len);
    return len;
}

unsigned short z_protocol::z_read_trans(char *buff,short len)
{
    QMutexLocker locker(&zmutex);
    usRingRead(_RING_TX,buff,&len);
    return len;
}

void z_protocol::mark_ack_rcvd(unsigned short mid,unsigned short crc,unsigned short len)
{
    unsigned short i;
    QMutexLocker locker(&zmutex);

    for(i=0; i<MAX_ZMSG; i++)
    {
        if((_oi.isActive[i]      ) && \
                (_oi.outz[i].mid==mid ) && \
                (_oi.outz[i].crc==crc ) && \
                (_oi.outz[i].len==len))
        {
            _oi.isTsmitted[i]     = 0;
            _oi.isActive[i]       = 0;
            _oi.outz[i].com_error = 0;

            Q_EMIT zack(0,_oi.outz[i].mid);

            //printf("%s <%d>\n",__FUNCTION__,__LINE__);
            if(_oi.outz[i].cb!= NULL)
            {
                (_oi.outz[i].cb)(0,_oi.outz[i].mid);
                //printf("calling function");
                //fflush(stdout);
            }
        }
    }
}

unsigned short z_protocol::z_post_mailbox(const void *msg,unsigned short len,unsigned short c_code,callback_alarm cb)
{
    unsigned short j=0;
    unsigned short i=0;
    unsigned short k=0;
    unsigned short mid=0;
    unsigned char *tptr;
    unsigned char *dptr;
    unsigned short crc;

    QMutexLocker locker(&zmutex);

    for(i=0; i<MAX_ZMSG; i++)
    {
        if((_oi.isActive[i]==0))
        {
            //printf("arming <%d> endpong\n",i);
            //fflush(stdout);
            _oi.isActive[i]=0;
            _oi.isWaitAck[i]=0;

            /* increase msg id by 1 */
            _oi.static_mid++;

            mid= _oi.static_mid;

            /* these are trasmission properties */
            _oi.outz[i].code    = normal_pkt;
            _oi.outz[i].type    = 1;
            _oi.outz[i].timeout = Z_TIMEOUT;
            _oi.outz[i].txCnt   = Z_ATTMPT_TRY;
            _oi.outz[i].com_error = 0;
            _oi.outz[i].lastSent  = 0;

            /* calculate checksum */
            /* init buffer */

            tptr=(unsigned char *)msg;

            crc=0;
            for(j=0; j<len; j++) crc+=*tptr++;

            /* reinit as you used it already */
            tptr=(unsigned char *)msg;

            /* Now create z modem msg */
            //dptr=(unsigned char *)_oi.outz[i].payload;
            dptr=(unsigned char *)_oi.outz[i].payload;

            /* header */
            *dptr++=PROT_HEADER;
            *dptr++=normal_pkt;

            /* this is ack packet */
            *dptr++=HIGH_BYTE(_oi.static_mid);
            *dptr++=LOW_BYTE(_oi.static_mid);

            *dptr++=HIGH_BYTE(crc);
            *dptr++=LOW_BYTE(crc);

            len+=8;
            *dptr++=HIGH_BYTE(len);
            *dptr++=LOW_BYTE(len);
            /* end of ack pck */

            _oi.outz[i].txLen = len;
            //memcpy(dptr,tptr,len);
            tptr=(unsigned char *)msg;

            for(j=0; j<len; j++) *dptr++=*tptr++;

            dptr=(unsigned char *)_oi.outz[i].payload;

            _oi.outz[i].mid     = _oi.static_mid;
            _oi.outz[i].crc     = crc;
            _oi.outz[i].len     = len;

            _oi.outz[i].cb  = cb;

            /* mark slot used */
            _oi.isActive[i]=1;
            /* fill CRC,Len,ID for Ack, so rx thread can wait */

            /* increase out_count */
            _oi.out_count++;

            return mid;
        }
    }

    return mid;
}

unsigned char z_protocol::incomming_sorting_box(const void *inbuff,unsigned short len1)
{
    unsigned char *ptr1;
    uint8_t i;
    static unsigned char  ccSum;
    static unsigned char  cccSum;
    static unsigned short ch;
    static unsigned short rd;
    static unsigned short j;
    static unsigned short is_more_left;
    static unsigned short state=0;
    static unsigned short mid;
    static unsigned short last_mid=0xffff;
    static unsigned short crc;
    static unsigned short ccrc;
    static unsigned short len;
    static unsigned char  is_ack;

    ptr1=(unsigned char *)inbuff;

    is_more_left=1;
    //QMutexLocker locker(&zmutex_r);
    //QMutexLocker locker(&zmutex);
    fflush(stdout);

    do
    {
        if(len1)
        {
            rd=0xff & (*ptr1++);
            len1--;
        }
        else
        {
            rd=NO_MORE_DATA;
        }

        if(rd!=NO_MORE_DATA)
        {
            ch=rd & 0xff;

            switch(state)
            {
            case 0:
                if(PROT_HEADER==ch)
                {
                    state=1;
                }
                break;

            case 1:
                if(normal_pkt==ch)
                {
                    state=2;
                    mid=0;
                    crc=0;
                    ccrc=0;
                    len=0;
                    is_ack=0;
                }
                else if(acknwg_pkt==ch)
                {
                    state=2;
                    mid=0;
                    crc=0;
                    ccrc=0;
                    len=0;
                    is_ack=1;
                }
                else
                {
                    state=0;
                }
                break;

            case 2:
                mid=(ch <<8);
                state=3;

                break;

            case 3:
                mid |=ch;
                state=4;
                break;

            case 4:
                //emb_printf("-->MID=%04x\n",mid);
                crc=(ch <<8);
                state=5;

                break;

            case 5:
                crc|=ch;
                state=6;
                break;

            case 6:
                len=(ch <<8);
                state=7;

                break;

            case 7:
                len|=ch;
                state=8;
                ccrc=0;

                j=8;

                if(is_ack)
                {
                    state=0;
                    mark_ack_rcvd(mid,crc,len);
                }

                break;

            case 8:
                ccrc     +=ch;
                z_inbuff[j-8]=ch;
                j++;
                //emb_print_str(&ch,1);

                if((j==len) && (crc==ccrc))
                {
                    char zresponse_ptr[8];

                    state=0;
                    //emb_print_str("good packet\r\n",13);
                    /* time to make response pkt */
                    zresponse_ptr[0]=0x55;
                    zresponse_ptr[1]=acknwg_pkt;
                    zresponse_ptr[2]=HIGH_BYTE(mid);
                    zresponse_ptr[3]=LOW_BYTE(mid);
                    zresponse_ptr[4]=HIGH_BYTE(crc);
                    zresponse_ptr[5]=LOW_BYTE(crc);
                    zresponse_ptr[6]=HIGH_BYTE(len);
                    zresponse_ptr[7]=LOW_BYTE(len);
                    vRingWrite(_RING_TX,zresponse_ptr,8);

                    if(last_mid!=mid)
                    {
                        /* this is extracted message which was posted by remote */
                        vRingWrite(_RING_RX,z_inbuff,len-8);
                        if((len-8)>0)
                        {
                            disc->usPushDiscQ(z_inbuff,len-8);
                        }
                        //printf("---<LEN=%d 0x%04x>----\r\n",len-8,mid);
                        //fflush(stdout);
                    }
                    /* no payload */
                    /* transmit ack pkt */
                    return 1;
                }
                else if((j==len) && (crc!=ccrc))
                {
                    state=0;
                    //emb_print_str("good packet\r\n",13);
                    /* time to make response pkt */
                    //memset(zresponse_ptr,0x55,8);
                    /* no payload */
                    /* transmit ack pkt */
                    return 0;
                }

                break;
            default:
                break;
            }
        }
        else
        {
            is_more_left=0;
        }

    }
    while(is_more_left);
}

