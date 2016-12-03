#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_file.h"

#ifdef EMB_PLATFORM
#include "global_var.h"
#include "cscript.h"
//#include "file_server.h"
#endif


const scoap_endpoint_path_t path_open_file = {2, {"file","open"}};
const scoap_endpoint_path_t path_sd_format = {1, {"sdformat"}};

int ep_format_sd(scoap_rw_buffer_t *scratch,
                 const scoap_packet_t *inpkt,
                 scoap_packet_t *outpkt,
                 uint8_t id_hi,
                 uint8_t id_lo)
{
    osEvent event;
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_FORMAT_URI);
#endif
#ifdef EMB_PLATFORM
    formatSDCard();
    emb_printf("format command issued\r\n");
    setOwnderFileServer(user_fsCoAP);
#endif

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


int ep_open_file_get(scoap_rw_buffer_t *scratch,
                     const scoap_packet_t *inpkt,
                     scoap_packet_t *outpkt,
                     uint8_t id_hi,
                     uint8_t id_lo)
{
    osEvent event;
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_OPEN_URI);
#endif
#ifdef EMB_PLATFORM
    if(inpkt->payload.len>=sizeof(ioFileExchangeStruct))
    {
        setOwnderFileServer(user_fsCoAP);
        ////////////////////
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FL_RFILE_NAME,1);

        //event=osMessageGet(ifile_resQ,500);

        if(event.status == osEventMessage)
        {
            io_fileunion.io_glue.error=event.value.v;
        }
        else
        {
            io_fileunion.io_glue.error=IW_FILE_ERROR;
        }

        endpoint_ptr=(unsigned char *)&io_fileunion.io_glue;
        ////////////////////
    }
#endif

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

int ep_open_file_put(scoap_rw_buffer_t *scratch,
                     const scoap_packet_t *inpkt,
                     scoap_packet_t *outpkt,
                     uint8_t id_hi,
                     uint8_t id_lo)
{
    osEvent event;
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
#ifdef EMB_PLATFORM
    //emb_printf("%s %s %d %d %d\n",__FILE__,__FUNCTION__,__LINE__,inpkt->payload.len,sizeof(ioFileExchangeStruct));
    memset(uri,'\0',32);
    strcpy(uri,FILE_OPEN_URI);
#endif
#ifdef EMB_PLATFORM
    if(inpkt->payload.len>=sizeof(ioFileExchangeStruct))
    {
        setOwnderFileServer(user_fsCoAP);
        ////////////////////
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FL_WFILE_NAME,1);

        //event=osMessageGet(ifile_resQ,500);

        if(event.status == osEventMessage)
        {
            io_fileunion.io_glue.error=event.value.v;
        }
        else
        {
            io_fileunion.io_glue.error=IW_FILE_ERROR;
        }

        endpoint_ptr=(unsigned char *)&io_fileunion.io_glue;
        ////////////////////
    }
#endif

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

const scoap_endpoint_path_t path_close_file = {2, {"file","close"}};

int ep_close_file_get(scoap_rw_buffer_t *scratch,
                      const scoap_packet_t *inpkt,
                      scoap_packet_t *outpkt,
                      uint8_t id_hi,
                      uint8_t id_lo)
{
    osEvent event;
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_CLOSE_URI);
#endif
#ifdef EMB_PLATFORM
    if(inpkt->payload.len>=sizeof(ioFileExchangeStruct))
    {
        setOwnderFileServer(user_fsCoAP);
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        ////////////////////
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FL_RCLOSE_FILE,1);

        //event=osMessageGet(ifile_resQ,500);

        if(event.status == osEventMessage)
        {
            io_fileunion.io_glue.error=event.value.v;
        }
        else
        {
            io_fileunion.io_glue.error=IW_FILE_ERROR;
        }

        endpoint_ptr=(unsigned char *)&io_fileunion.io_glue;
        ////////////////////
    }
#endif
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

int ep_close_file_put(scoap_rw_buffer_t *scratch,
                      const scoap_packet_t *inpkt,
                      scoap_packet_t *outpkt,
                      uint8_t id_hi,
                      uint8_t id_lo)
{
    osEvent event;
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_CLOSE_URI);
#endif
#ifdef EMB_PLATFORM
    if(inpkt->payload.len>=sizeof(ioFileExchangeStruct))
    {
        setOwnderFileServer(user_fsCoAP);
        ////////////////////
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FL_WCLOSE_FILE,1);

        //event=osMessageGet(ifile_resQ,500);

        if(event.status == osEventMessage)
        {
            io_fileunion.io_glue.error=event.value.v;
        }
        else
        {
            io_fileunion.io_glue.error=IW_FILE_ERROR;
        }

        endpoint_ptr=(unsigned char *)&io_fileunion.io_glue;
        ////////////////////
    }
#endif
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

const scoap_endpoint_path_t path_write_file = {2, {"file","write"}};

int ep_write_file(scoap_rw_buffer_t *scratch,
                  const scoap_packet_t *inpkt,
                  scoap_packet_t *outpkt,
                  uint8_t id_hi,
                  uint8_t id_lo)
{
    osEvent event;
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_WRITE_URI);
#endif
#ifdef EMB_PLATFORM
    if(inpkt->payload.len>=sizeof(ioFileExchangeStruct))
    {
        setOwnderFileServer(user_fsCoAP);
        ////////////////////
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FL_WRITE_BIN,1);

        //event=osMessageGet(ifile_resQ,500);

        if(event.status == osEventMessage)
        {
            io_fileunion.io_glue.error=event.value.v;
        }
        else
        {
            io_fileunion.io_glue.error=IW_FILE_ERROR;
        }

        endpoint_ptr=(unsigned char *)&io_fileunion.io_glue;
        ////////////////////
    }
#endif
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

const scoap_endpoint_path_t path_read_file = {2, {"file","read"}};


int ep_read_file(scoap_rw_buffer_t *scratch,
                 const scoap_packet_t *inpkt,
                 scoap_packet_t *outpkt,
                 uint8_t id_hi,
                 uint8_t id_lo)
{
    osEvent event;
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_READ_URI);
#endif
#ifdef EMB_PLATFORM
    if(inpkt->payload.len>=sizeof(ioFileExchangeStruct))
    {
        setOwnderFileServer(user_fsCoAP);
        ////////////////////
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FL_READ_BIN,1);

        //event=osMessageGet(ifile_resQ,500);

        if(event.status == osEventMessage)
        {
            io_fileunion.io_glue.error=event.value.v;
        }
        else
        {
            io_fileunion.io_glue.error=IW_FILE_ERROR;
        }

        endpoint_ptr=(unsigned char *)&io_fileunion.io_glue;
        ////////////////////
    }
#endif
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

const scoap_endpoint_path_t path_ptr_file = {2, {"file","pos"}};

int ep_put_ptr_file(scoap_rw_buffer_t *scratch,
                    const scoap_packet_t *inpkt,
                    scoap_packet_t *outpkt,
                    uint8_t id_hi,
                    uint8_t id_lo)
{
    osEvent event;
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_POS_URI);
#endif
#ifdef EMB_PLATFORM
    if(inpkt->payload.len>=sizeof(ioFileExchangeStruct))
    {
        setOwnderFileServer(user_fsCoAP);
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        ////////////////////
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FL_GET_OFFSET,1);

        //event=osMessageGet(ifile_resQ,500);

        if(event.status == osEventMessage)
        {
            io_fileunion.io_glue.error=event.value.v;
        }
        else
        {
            io_fileunion.io_glue.error=IW_FILE_ERROR;
        }

        endpoint_ptr=(unsigned char *)&io_fileunion.io_glue;
        ////////////////////
    }
#endif
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


int ep_get_ptr_file(scoap_rw_buffer_t *scratch,
                    const scoap_packet_t *inpkt,
                    scoap_packet_t *outpkt,
                    uint8_t id_hi,
                    uint8_t id_lo)
{
    osEvent event;
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_POS_URI);
#endif
#ifdef EMB_PLATFORM
    if(inpkt->payload.len>=sizeof(ioFileExchangeStruct))
    {
        setOwnderFileServer(user_fsCoAP);
        ////////////////////
        memcpy(&io_fileunion.io_glue,inpkt->payload.p,sizeof(ioFileExchangeStruct));
        osMessageGet(ifile_resQ,0);
        osMessageGet(ifile_cmdQ,0); /* make sure Qis empty */
        osMessagePut(ifile_cmdQ,FL_SET_OFFSET,1);

        //event=osMessageGet(ifile_resQ,500);

        if(event.status == osEventMessage)
        {
            io_fileunion.io_glue.error=event.value.v;
        }
        else
        {
            io_fileunion.io_glue.error=IW_FILE_ERROR;
        }

        endpoint_ptr=(unsigned char *)&io_fileunion.io_glue;
        ////////////////////
    }
#endif
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
