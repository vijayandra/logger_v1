#ifndef __EP_CMDS_H
#define __EP_CMDS_H


#define FILE_REBOOT_URI "<reboot>"

extern const scoap_endpoint_path_t path_hw_reboot;

extern int ep_hw_reboot(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);

#endif
