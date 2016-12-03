#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"


const scoap_endpoint_path_t path_i2c_read = {2, {"i2c","read"}};
int ep_i2c_read(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_i2c_write = {2, {"i2c","write"}};
int ep_i2c_write(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_i2c_start = {2, {"i2c","start"}};
int ep_i2c_start(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_i2c_restart = {2, {"i2c","restart"}};
int ep_i2c_restart(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_i2c_stop = {2, {"i2c","stop"}};
int ep_i2c_stop(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}

const scoap_endpoint_path_t path_i2c_speed = {2, {"i2c","speed"}};
int ep_i2c_speed(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
#if 0
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}
