#ifndef __EP_DEVICE_H
#define __EP_DEVICE_H

#define DEV_VERSION_URI    "<device-version>"
#define DEV_CAPABILITY_URI "<device-capability>"

extern const scoap_endpoint_path_t path_get_version;
extern const scoap_endpoint_path_t path_get_capability;

extern int ep_get_device(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_get_capability(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);


#endif
