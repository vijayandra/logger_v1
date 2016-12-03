#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"


const scoap_endpoint_path_t path_uart_baud = {2, {"uart1","baud"}};
int ep_uart_baud(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_uart_stop = {2, {"uart1","stop"}};
int ep_uart_stop(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_uart_read = {2, {"uart1","read"}};
int ep_uart_read(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_uart_write = {2, {"uart1","write"}};
int ep_uart_write(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_uart_link = {2, {"uart1","link"}};
int ep_uart_link(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}


