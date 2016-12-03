#ifndef __EP_ADC_H
#define __EP_ADC_H

#define ADC_URI "<adc>"

extern const scoap_endpoint_path_t path_adc;

int ep_put_adc(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo);

int ep_get_adc(scoap_rw_buffer_t    *scratch,
                   const scoap_packet_t *inpkt,
                   scoap_packet_t *outpkt,
                   uint8_t id_hi,
                   uint8_t id_lo);

#endif
