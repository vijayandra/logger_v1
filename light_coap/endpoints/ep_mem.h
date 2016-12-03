#ifndef __EP_MEM_S_H
#define __EP_MEM_S_H

#define RW_MEM_ADDR_URI "<memory-addr>"
#define RW_MEM_URI "<memory>"

extern const scoap_endpoint_path_t path_mem_addr;
extern const scoap_endpoint_path_t path_mem;

extern int ep_post_mem_addr(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_get_mem_addr(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_get_mem(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_post_mem(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);

extern int ep_put_mem(scoap_rw_buffer_t *scratch,
                      const scoap_packet_t *inpkt,
                      scoap_packet_t *outpkt,
                      uint8_t id_hi,
                      uint8_t id_lo);

extern int ep_put_mem_addr(scoap_rw_buffer_t    *scratch,
                           const scoap_packet_t *inpkt,
                           scoap_packet_t *outpkt,
                           uint8_t id_hi,
                           uint8_t id_lo);
#endif
