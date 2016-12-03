#ifndef __EP_7020_H
#define __EP_7020_H

#define RTC_HUMD_URI "<humid>"
#define RTC_TEMP_URI "<temp>"

extern const scoap_endpoint_path_t path_humd;
extern const scoap_endpoint_path_t path_temp;

int ep_get_temp(scoap_rw_buffer_t    *scratch,
                const scoap_packet_t *inpkt,
                scoap_packet_t *outpkt,
                uint8_t id_hi,
                uint8_t id_lo);

int ep_get_humd(scoap_rw_buffer_t *scratch,
                const scoap_packet_t *inpkt,
                scoap_packet_t *outpkt,
                uint8_t id_hi,
                uint8_t id_lo);

#endif
