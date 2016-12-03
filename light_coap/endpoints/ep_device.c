#include "options.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "shared_struct.h"
#include "options.h"
#include "global_var.h"
#include "ep_device.h"

extern const uint16_t rsplen;
//extern char rsp[1500];

#ifdef EMB_PLATFORM
const char *devCap[]= {{"\n[VERSION]\n"},
    {__HW_VERSION__},
    {"\n[DEVICE]\n"},
    {__DEV_NAME__},
    {"\n[DATE]\n"},
    {__DATE__},
    {"\n[TIME]\n"},
    {__TIME__},
    {"\n[UART]"},
    {"\nUART_1"},
    {"\nUART_2"},
    {"\n[RS485]\n"},
    {"\nRS485_1"},
    {"\n[I2C]\n"},
    {"\nI2C_1"},
    {"[ID]\n"}
};
#endif

//{DEV_ID1},
//{DEV_ID2},
//{DEV_ID3},

const scoap_endpoint_path_t path_get_version = {2, {"device","version"}};
int ep_get_device(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    memset(rsp,'\0',rsplen);
    //emb_printf("%s %s %d <%d>\n",__FILE__,__FUNCTION__,__LINE__,sizeof(devCap));
#ifdef EMB_PLATFORM
    memcpy(rsp,*devCap,sizeof(devCap));
    //memcpy(rsp,"Vijayandra",10);//sizeof(devCap));

    sprintf(&rsp[sizeof(devCap)+0], "[%08x]",(DEV_ID1));
    sprintf(&rsp[sizeof(devCap)+10],"[%08x]",(DEV_ID2));
    sprintf(&rsp[sizeof(devCap)+20],"[%08x]",(DEV_ID3));

    memset(uri,'\0',32);
    strcpy(uri,DEV_VERSION_URI);
#endif

    //printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#ifdef DO_DEBUG
    emb_printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
    //return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
#ifdef EMB_PLATFORM
    return scoap_make_response(scratch, outpkt,(const uint8_t *)rsp,(sizeof(devCap))+30, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
#else
    return scoap_make_response(scratch, outpkt,(const uint8_t *)NULL,0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
#endif
}

const scoap_endpoint_path_t path_get_capability = {2, {"device","capability"}};
int ep_get_capability(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
#ifdef DO_DEBUG
    printf("%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
#endif
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,DEV_CAPABILITY_URI);
#endif
    return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
}
