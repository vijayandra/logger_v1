#ifndef __EP_CSCRIPT_H
#define __EP_CSCRIPT_H

#define SCRIPT_URI "<cscript>"

extern const scoap_endpoint_path_t path_cscript;

int ep_put_cscript(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo);

int ep_get_cscript(scoap_rw_buffer_t *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo);

#endif
