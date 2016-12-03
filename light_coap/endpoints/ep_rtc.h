#ifndef __EP_RTC_H
#define __EP_RTC_H

#define RTC_URI "<rtc>"

extern const scoap_endpoint_path_t path_rtc;

int ep_put_rtc(scoap_rw_buffer_t    *scratch,
               const scoap_packet_t *inpkt,
               scoap_packet_t *outpkt,
               uint8_t id_hi,
               uint8_t id_lo);

int ep_get_rtc(scoap_rw_buffer_t *scratch,
               const scoap_packet_t *inpkt,
               scoap_packet_t *outpkt,
               uint8_t id_hi,
               uint8_t id_lo);

#endif
