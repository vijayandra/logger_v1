#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_7020.h"
#include "shared_struct.h"

#ifdef EMB_PLATFORM
#include "global_var.h"
#include "cscript.h"
#endif

const scoap_endpoint_path_t path_humd = {1, {"humid"}};
const scoap_endpoint_path_t path_temp = {1, {"temp"}};


int ep_get_temp(scoap_rw_buffer_t    *scratch,
                const scoap_packet_t *inpkt,
                scoap_packet_t *outpkt,
                uint8_t id_hi,
                uint8_t id_lo)
{
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RTC_TEMP_URI);
#endif

    io_union.iTmpHum.humid=checkHumidity();
    io_union.iTmpHum.temp=getTemperature();


    return scoap_make_response(scratch,
                               outpkt,
                              (const uint8_t *) &io_union.iTmpHum,
                               sizeof(IW_TEMP_HUMIDITY),
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CHANGED,
                               COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM);
}


int ep_get_humd(scoap_rw_buffer_t *scratch,
                const scoap_packet_t *inpkt,
                scoap_packet_t *outpkt,
                uint8_t id_hi,
                uint8_t id_lo)
{
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RTC_HUMD_URI);
#endif
    io_union.iTmpHum.humid=checkHumidity();
    io_union.iTmpHum.temp=getTemperature();

    return scoap_make_response(scratch,
                               outpkt,
                               (const uint8_t *)&io_union.iTmpHum,
                               sizeof(IW_TEMP_HUMIDITY),
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CHANGED,
                               COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM);
}

