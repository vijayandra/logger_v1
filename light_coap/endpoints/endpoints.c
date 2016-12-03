#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "srv_coap.h"
#include "ep_file.h"
#include "ep_nfile.h"
#include "ep_mem.h"
#include "ep_rtc.h"
#include "ep_7020.h"
#include "ep_cscript.h"
#include "ep_device.h"
#include "ep_cmds.h"
#include "ep_adc.h"
#include "ep_dac.h"
#include "ep_i2c.h"
#include "endpoints.h"

static char light = '0';

//const uint16_t rsplen = 1500;
//char rsp[1500] = "";
extern const uint16_t rsplen;
extern char rsp[1500];

void build_rsp(void);

void endpoint_setup(void)
{
    build_rsp();
}
//////////////////////////
static const scoap_endpoint_path_t path_well_known_core = {2, {".well-known", "core"}};

static int ep_get_well_known_core(scoap_rw_buffer_t *scratch,
                                  const scoap_packet_t *inpkt,
                                  scoap_packet_t *outpkt,
                                  uint8_t id_hi,
                                  uint8_t id_lo)
{
    return scoap_make_response(scratch,
                               outpkt,
                               (const uint8_t *)rsp,
                               strlen(rsp),
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CONTENT,
                               COAP_CONTENTTYPE_APPLICATION_LINKFORMAT);
}

//////////////////////////
static const scoap_endpoint_path_t path_light = {2, {"light","lm"}};
static int ep_get_light(scoap_rw_buffer_t *scratch,
                        const scoap_packet_t *inpkt,
                        scoap_packet_t *outpkt,
                        uint8_t id_hi,
                        uint8_t id_lo)
{
    return scoap_make_response(scratch,
                               outpkt,
                               (const uint8_t *)&light,
                               1,
                               id_hi,
                               id_lo,
                               &inpkt->tok,
                               COAP_RSPCODE_CONTENT,
                               COAP_CONTENTTYPE_TEXT_PLAIN);
}

//////////////////////////
static int ep_put_light(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    if (inpkt->payload.len == 0)
        return scoap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_TEXT_PLAIN);
    if (inpkt->payload.p[0] == '1')
    {
        light = '1';
        //printf("ON\n");
        return scoap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
    else
    {
        light = '0';
        //printf("OFF\n");
        return scoap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_TEXT_PLAIN);
    }
}

//////////////////////////
static const scoap_endpoint_path_t path_i2c_open = {3, {"device","i2c1","open"}};
static int ep_put_i2c_open(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    return scoap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_TEXT_PLAIN);
}

//////////////////////////
static const scoap_endpoint_path_t path_i2c_clk = {3, {"device","i2c1","clock"}};
static int ep_put_i2c_clk(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    return scoap_make_response(scratch, outpkt, (const uint8_t *)&light, 1, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_TEXT_PLAIN);
}
//////////////////////////

const scoap_endpoint_t endpoints[] =
{
    {COAP_METHOD_GET, ep_get_well_known_core ,&path_well_known_core, "ct=40"},
    {COAP_METHOD_GET, ep_get_light           ,&path_light,  "ct=0"},

    {COAP_METHOD_GET, ep_get_device         ,&path_get_version, NULL},
    {COAP_METHOD_GET, ep_get_capability      ,&path_get_capability, NULL},

#ifdef EMB_PLATFORM
    {COAP_METHOD_PUT, ep_put_rtc     ,&path_rtc, NULL},
    {COAP_METHOD_GET, ep_get_rtc     ,&path_rtc, NULL},

    {COAP_METHOD_GET,ep_format_sd           ,&path_sd_format,   NULL },
    {COAP_METHOD_PUT,ep_format_sd           ,&path_sd_format,   NULL },
    {COAP_METHOD_GET,ep_hw_reboot           ,&path_hw_reboot,   NULL },
    {COAP_METHOD_PUT,ep_hw_reboot           ,&path_hw_reboot,   NULL },

    {COAP_METHOD_GET,ep_get_temp            ,&path_temp,        NULL },
    {COAP_METHOD_GET,ep_get_humd            ,&path_humd,        NULL },

    {COAP_METHOD_POST,ep_post_mem            ,&path_mem,        NULL },

    {COAP_METHOD_GET ,ep_get_mem             ,&path_mem,        NULL },
    {COAP_METHOD_PUT ,ep_put_mem             ,&path_mem,        NULL },

    {COAP_METHOD_GET ,ep_get_cscript         ,&path_cscript,    NULL },
    {COAP_METHOD_PUT ,ep_put_cscript         ,&path_cscript,    NULL },

    {COAP_METHOD_POST,ep_post_mem_addr       ,&path_mem_addr,   NULL },
    {COAP_METHOD_GET ,ep_get_mem_addr        ,&path_mem_addr,   NULL },
    {COAP_METHOD_PUT ,ep_put_mem_addr        ,&path_mem_addr,   NULL },

    {COAP_METHOD_PUT, ep_put_light           ,&path_light,   NULL },
    {COAP_METHOD_GET, ep_put_i2c_open        ,&path_i2c_open,NULL },
    {COAP_METHOD_GET, ep_put_i2c_clk         ,&path_i2c_clk, NULL },


    {COAP_METHOD_GET,ep_file_line_get     ,&path_line_io,  NULL },
    {COAP_METHOD_PUT,ep_file_line_put     ,&path_line_io,  NULL },
    {COAP_METHOD_GET,ep_file_bin_get      ,&path_bin_io,  NULL },
    {COAP_METHOD_PUT,ep_file_bin_put      ,&path_bin_io,  NULL },


    {COAP_METHOD_GET,ep_get_adc     ,&path_adc,  NULL },
    {COAP_METHOD_PUT,ep_put_adc     ,&path_adc,  NULL },
    {COAP_METHOD_GET,ep_get_dac     ,&path_dac,  NULL },
    {COAP_METHOD_PUT,ep_put_dac     ,&path_dac,  NULL },



    {COAP_METHOD_GET,ep_open_file_get      ,&path_open_file,  NULL },
    {COAP_METHOD_PUT,ep_open_file_put      ,&path_open_file,  NULL },
    {COAP_METHOD_GET,ep_close_file_get     ,&path_close_file, NULL },
    {COAP_METHOD_PUT,ep_close_file_put     ,&path_close_file, NULL },
    {COAP_METHOD_GET,ep_read_file          ,&path_read_file,  NULL },
    {COAP_METHOD_PUT,ep_read_file          ,&path_read_file,  NULL },
    {COAP_METHOD_GET,ep_write_file         ,&path_write_file, NULL },
    {COAP_METHOD_PUT,ep_write_file         ,&path_write_file, NULL },
    {COAP_METHOD_PUT,ep_put_ptr_file       ,&path_ptr_file,   NULL },
    {COAP_METHOD_GET,ep_get_ptr_file       ,&path_ptr_file,   NULL },
#endif


    {(scoap_method_t)0,NULL                      , NULL         , NULL }
};

void build_rsp(void)
{
    uint16_t len = rsplen;
    const scoap_endpoint_t *ep = endpoints;
    int i;

    len--; // Null-terminated string

    while(NULL != ep->handler)
    {
        if (NULL == ep->core_attr)
        {
            ep++;
            continue;
        }

        if (0 < strlen(rsp))
        {
            strncat(rsp, ",", len);
            len--;
        }

        strncat(rsp, "<", len);
        len--;

        for (i = 0; i < ep->path->count; i++)
        {
            strncat(rsp, "/", len);
            len--;

            strncat(rsp, ep->path->elems[i], len);
            len -= strlen(ep->path->elems[i]);
        }

        strncat(rsp, ">;", len);
        len -= 2;

        strncat(rsp, ep->core_attr, len);
        len -= strlen(ep->core_attr);

        ep++;
    }
}

