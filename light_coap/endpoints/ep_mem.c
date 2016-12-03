#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_mem.h"
#include "shared_struct.h"

#ifdef EMB_PLATFORM
#include "global_var.h"
#include "cscript.h"
#include "startthread.h"
#endif

static MemData md;
static unsigned char *ptr;



extern const uint16_t rsplen;
//extern char rsp[1500];

const scoap_endpoint_path_t path_mem_addr = {2, {"memory","addr"}};


int ep_post_mem_addr(scoap_rw_buffer_t    *scratch,
                     const scoap_packet_t *inpkt,
                     scoap_packet_t *outpkt,
                     uint8_t id_hi,
                     uint8_t id_lo)
{
    if(inpkt->payload.len>=sizeof(MemData))
    {
        memcpy(&md,inpkt->payload.p,sizeof(MemData));
    }

    if(md.MemType<10)
    {
        //ptr=GlbMemPtrTble[md.MemType];
        if(md.range>=GlbMemPtrTbleSize[md.MemType])
        {
            md.range=GlbMemPtrTbleSize[md.MemType];
        }
    }
    else
    {
        //ptr=GlbMemPtrTble[0];
        if(md.range>=GlbMemPtrTbleSize[0])
        {
            md.range=GlbMemPtrTbleSize[0];
        }
    }
    ptr=c_source_buffer;

#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RW_MEM_ADDR_URI);
#endif
    //emb_printf("<%d %d %d>\r\n",md.MemType,md.Off_l,md.range);


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


int ep_put_mem_addr(scoap_rw_buffer_t    *scratch,
                    const scoap_packet_t *inpkt,
                    scoap_packet_t *outpkt,
                    uint8_t id_hi,
                    uint8_t id_lo)
{
    if(inpkt->payload.len>=sizeof(MemData))
    {
        memcpy(&md,inpkt->payload.p,sizeof(MemData));
    }

    if(md.MemType<10)
    {
        //ptr=GlbMemPtrTble[md.MemType];
        if(md.range>=GlbMemPtrTbleSize[md.MemType])
        {
            md.range=GlbMemPtrTbleSize[md.MemType];
        }
    }
    else
    {
        //ptr=GlbMemPtrTble[0];
        if(md.range>=GlbMemPtrTbleSize[0])
        {
            md.range=GlbMemPtrTbleSize[0];
        }
    }
    ptr=c_source_buffer;

#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RW_MEM_ADDR_URI);
#endif
    //emb_printf("<%d %d %d>\r\n",md.MemType,md.Off_l,md.range);


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


int ep_get_mem_addr(scoap_rw_buffer_t *scratch,
                    const scoap_packet_t *inpkt,
                    scoap_packet_t *outpkt,
                    uint8_t id_hi,
                    uint8_t id_lo)
{

    //memcpy(inpkt->payload.p,&md,sizeof(MemData));
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RW_MEM_ADDR_URI);
#endif

    return scoap_make_response(scratch,
                               outpkt,
                               (const uint8_t *)&md,
                               sizeof(MemData),
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CHANGED,
                               COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_mem = {1, {"memory"}};

int ep_get_mem(scoap_rw_buffer_t *scratch,
               const scoap_packet_t *inpkt,
               scoap_packet_t *outpkt,
               uint8_t id_hi,
               uint8_t id_lo)
{

    //emb_printf("copied\n");
    memset(rsp,'\0',rsplen);
    endpoint_ptr=ptr+md.Off_l;
    //memcpy(rsp,c_source_buffer,1024);
    md.Off_l+=1024;
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RW_MEM_URI);
#endif


    return scoap_make_response(scratch,
                               outpkt,
                               (const uint8_t *)endpoint_ptr,
                               1024,
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CHANGED,
                               COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM);
}



int ep_post_mem(scoap_rw_buffer_t *scratch,
                const scoap_packet_t *inpkt,
                scoap_packet_t *outpkt,
                uint8_t id_hi,
                uint8_t id_lo)
{

    if(md.range>=(md.Off_l+inpkt->payload.len))
    {
        memcpy(ptr+md.Off_l,inpkt->payload.p,inpkt->payload.len);
        md.Off_l+=inpkt->payload.len;
    }
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RW_MEM_URI);
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

int ep_put_mem(scoap_rw_buffer_t *scratch,
               const scoap_packet_t *inpkt,
               scoap_packet_t *outpkt,
               uint8_t id_hi,
               uint8_t id_lo)
{

    if(md.range>=(md.Off_l+inpkt->payload.len))
    {
        memcpy(ptr+md.Off_l,inpkt->payload.p,inpkt->payload.len);
        md.Off_l+=inpkt->payload.len;
    }
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,RW_MEM_URI);
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

