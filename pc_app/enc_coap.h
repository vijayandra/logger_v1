#ifndef __ENC_COAP_H
#define __ENC_COAP_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int coap_get_uri(void *packet,char **path);
int coap_pc_req(unsigned char *buff,uint8_t k,const char *uri,void *payload,unsigned short payloadLen);
#endif
