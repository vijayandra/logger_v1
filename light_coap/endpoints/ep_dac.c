#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_dac.h"
#include "shared_struct.h"

#ifdef EMB_PLATFORM
#include "global_var.h"
#include "cscript.h"
#endif

const scoap_endpoint_path_t path_dac = {1, {"dac"}};

int ep_put_dac(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo)
{

#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,DAC_URI);
#endif
    return scoap_make_response(scratch,
                               outpkt,
                               NULL,
                               0,
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_BAD_REQUEST,
                               COAP_CONTENTTYPE_TEXT_PLAIN);
}


int ep_get_dac(scoap_rw_buffer_t *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo)
{
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,DAC_URI);
#endif

    return scoap_make_response(scratch,
                               outpkt,
                               NULL,
                               0,
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CHANGED,
                               COAP_CONTENTTYPE_TEXT_PLAIN);
}

