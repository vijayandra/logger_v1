#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_file.h"

#ifdef EMB_PLATFORM
#include "global_var.h"
#include "cscript.h"
#include "nfile_server.h"
//#include "file_server.h"
#endif


const scoap_endpoint_path_t path_line_io = {2, {"file","line"}};
const scoap_endpoint_path_t path_bin_io = {2, {"file","bin"}};

int ep_file_line_get(scoap_rw_buffer_t *scratch,
                        const scoap_packet_t *inpkt,
                        scoap_packet_t *outpkt,
                        uint8_t id_hi,
                        uint8_t id_lo)

{
    if(inpkt->payload.len>=sizeof(iNFileExchangeStruct))
    {
#ifdef EMB_PLATFORM
        memcpy(&io_fileunion.in_glue,inpkt->payload.p,sizeof(iNFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FIRMWR_EP_READ_LINE,1);
#endif
        ////////////////////
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

int ep_file_bin_get(scoap_rw_buffer_t *scratch,
                        const scoap_packet_t *inpkt,
                        scoap_packet_t *outpkt,
                        uint8_t id_hi,
                        uint8_t id_lo)

{
    if(inpkt->payload.len>=sizeof(iNFileExchangeStruct))
    {
#ifdef EMB_PLATFORM
        memcpy(&io_fileunion.in_glue,inpkt->payload.p,sizeof(iNFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FIRMWR_EP_READ_BIN,1);
#endif
        ////////////////////
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

int ep_file_line_put(scoap_rw_buffer_t *scratch,
                        const scoap_packet_t *inpkt,
                        scoap_packet_t *outpkt,
                        uint8_t id_hi,
                        uint8_t id_lo)

{
    if(inpkt->payload.len>=sizeof(iNFileExchangeStruct))
    {
#ifdef EMB_PLATFORM
        memcpy(&io_fileunion.in_glue,inpkt->payload.p,sizeof(iNFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FIRMWR_EP_WRITE_LINE,1);
#endif
        ////////////////////
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

int ep_file_bin_put(scoap_rw_buffer_t *scratch,
                        const scoap_packet_t *inpkt,
                        scoap_packet_t *outpkt,
                        uint8_t id_hi,
                        uint8_t id_lo)

{
    if(inpkt->payload.len>=sizeof(iNFileExchangeStruct))
    {
#ifdef EMB_PLATFORM
        memcpy(&io_fileunion.in_glue,inpkt->payload.p,sizeof(iNFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FIRMWR_EP_WRITE_BIN,1);
#endif
        ////////////////////
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

