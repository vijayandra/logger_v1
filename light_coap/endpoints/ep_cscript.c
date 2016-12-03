#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_cscript.h"
#include "shared_struct.h"

#ifdef EMB_PLATFORM
#include "global_var.h"
#include "cscript.h"
#endif

const scoap_endpoint_path_t path_cscript = {1, {"cscript"}};

int ep_put_cscript(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo)
{

#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,SCRIPT_URI);
#endif


    /* clear command buttons */
#if 0
    osMessageGet(ifile_resQ,0);
    osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
    osMessagePut(ifile_cmdQ,FL_RELOAD_CSCRIPT,1);
    osMessageGet(ifile_resQ,500);
#endif
    osMessagePut(iscript_cmdQ,0,0);

    //osMessagePut(iscript_cmdQ,0,1);
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


int ep_get_cscript(scoap_rw_buffer_t *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo)
{
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,SCRIPT_URI);
#endif

    /* clear command buttons */
    osMessageGet(iscript_cmdQ,0);
    /*Run Script without loading */
    osMessagePut(iscript_cmdQ,1,1);

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

