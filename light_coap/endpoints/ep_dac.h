#ifndef __EP_DAC_H
#define __EP_DAC_H

#define DAC_URI "<dac>"

extern const scoap_endpoint_path_t path_dac;

int ep_put_dac(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo);

int ep_get_dac(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo);

#endif
