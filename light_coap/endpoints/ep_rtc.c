#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_rtc.h"
#include "shared_struct.h"

#ifdef EMB_PLATFORM
#include "global_var.h"
#include "cscript.h"
#endif

const scoap_endpoint_path_t path_rtc = {1, {"rtc"}};

int ep_put_rtc(scoap_rw_buffer_t    *scratch,
               const scoap_packet_t *inpkt,
               scoap_packet_t *outpkt,
               uint8_t id_hi,
               uint8_t id_lo)
{
    IW_CDATE_CTIME *iDateTime;

#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RTC_URI);
#endif
    if(inpkt->payload.len>=sizeof(IW_CDATE_CTIME))
    {
        memcpy(&iDateTime,inpkt->payload.p,sizeof(IW_CDATE_CTIME));
#ifdef EMB_PLATFORM
        //SetDateTime(&iDateTime.cDate,&iDateTime.cTime);
#endif
    }


    return scoap_make_response(scratch,
                               outpkt,
                               NULL,
                               0,
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CHANGED,
                               COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM);
}


int ep_get_rtc(scoap_rw_buffer_t *scratch,
               const scoap_packet_t *inpkt,
               scoap_packet_t *outpkt,
               uint8_t id_hi,
               uint8_t id_lo)
{
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RTC_URI);
#endif
#ifdef EMB_PLATFORM
    memset(&io_union.iDateTime,0xff,sizeof(IW_CDATE_CTIME));
    GetDateTime(&io_union.iDateTime.cDate,&io_union.iDateTime.cTime);
#endif

    return scoap_make_response(scratch,
                               outpkt,
                              (const uint8_t *) &io_union.iDateTime,
                               sizeof(IW_CDATE_CTIME),
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CHANGED,
                               COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM);
}

