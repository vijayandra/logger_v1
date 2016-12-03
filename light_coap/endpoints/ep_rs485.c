#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"


const scoap_endpoint_path_t path_rs485_baud = {2, {"rs485","baud"}};
int ep_rs485_baud(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_rs485_stop = {2, {"rs485","stop"}};
int ep_rs485_stop(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_rs485_read = {2, {"rs485","read"}};
int ep_rs485_read(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_rs485_write = {2, {"rs485","write"}};
int ep_rs485_write(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_rs485_link = {2, {"rs485","link"}};
int ep_rs485_link(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}


