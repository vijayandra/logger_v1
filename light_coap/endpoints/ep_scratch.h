#ifndef __EP_CSCRATCH_H
#define __EP_CSCRATCH_H

#define SCRATCH_URI "<scratch>"

extern const scoap_endpoint_path_t path_cscript;

int ep_put_scratch(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo);

int ep_get_scratch(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo);

#endif
