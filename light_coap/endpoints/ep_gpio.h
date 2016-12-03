#ifndef __EP_GPIO_C
#define __EP_GPIO_C

extern const scoap_endpoint_path_t path_gpio_read;
extern const scoap_endpoint_path_t path_gpio_write;
extern int ep_gpio_read(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_gpio_writ(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);

#endif
