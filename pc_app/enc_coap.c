#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "coap13.h"

const uint16_t rsplen=1500;
char rsp[1500];

int coap_pc_req(unsigned char *buff,uint8_t k,const char *uri,void *payload,unsigned short payloadLen)
{
#if 1
    coap_packet_t request[1];

    coap_init_message(request,COAP_TYPE_CON,k, 1290);
    //coap_init_message(request, COAP_TYPE_CON,COAP_POST, 2330);
    //printf("%04x %d>>>>>\n",2330,2330);

    coap_set_header_uri_path(request,uri);
    coap_set_payload(request, (uint8_t *)payload,payloadLen);
    return coap_serialize_message(request,buff);
#else
#define MSG_BUF_LEN 64
    uint8_t msg_send_buf[MSG_BUF_LEN];
    coap_pdu msg_send = {msg_send_buf, 0, 64};

    coap_init_pdu(&msg_send);
    //memset(msg_send, 0, msg_send_len);
    coap_set_version(&msg_send, COAP_V1);
    coap_set_type(&msg_send, CT_CON);
    coap_set_code(&msg_send, CC_GET); // or POST to write
    coap_set_mid(&msg_send, 1030);//message_id_counter++);
    coap_set_token(&msg_send, rand(), 2);
    coap_add_option(&msg_send, CON_URI_PATH, (uint8_t*)uri,strlen(uri));
    //coap_add_option(&msg_send, CON_URI_PATH, (uint8_t*)alias, strlen(alias));
    //coap_add_option(&msg_send, CON_URI_QUERY, (uint8_t*)cik, strlen(cik));
    //coap_set_payload14(&msg_send, payload,payloadLen);

    memcpy(buff,msg_send_buf,msg_send.len);
    coap_pretty_print(&msg_send);
    printf("msg len=%04x\n",msg_send.len);
    fflush(stdout);
    return msg_send.len;
    // to write, set payload:
#endif
}

#if 0
int coap_pc_req(void *p,const char *payload,unsigned short payloadLen)
{
    coap_packet_t request[1];

    if(!k)
        coap_init_message(request, COAP_TYPE_CON,COAP_GET, 1290);
    else
        coap_init_message(request, COAP_TYPE_CON,COAP_POST, 2330);
    printf("%04x %d>>>>>\n",2330,2330);

    coap_set_header_uri_path(request,uri);
    coap_set_payload(request, (uint8_t *)payload,payloadLen);
    coap_pretty_print(&msg_send);
    return coap_serialize_message(request,buff);
}
#endif


