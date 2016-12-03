#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_file.h"
#include "ep_cmds.h"

#ifdef EMB_PLATFORM
#include "global_var.h"
#include "cscript.h"
#endif

const scoap_endpoint_path_t path_hw_reboot = {1, {"reboot"}};

int ep_hw_reboot(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    osEvent event;
#ifdef EMB_PLATFORM
    memset(uri,'\0',32);
    strcpy(uri,FILE_REBOOT_URI);
#endif
#ifdef EMB_PLATFORM
    emb_printf("Reboot command issued\r\n");
    osDelay(500);
    //wdg_activate(500);
    while(1) HAL_NVIC_SystemReset();
#endif

    return scoap_make_response(scratch,
                               outpkt,
                               (const uint8_t *)endpoint_ptr,
                               sizeof(ioFileExchangeStruct),
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CHANGED,
                               COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM);

}


