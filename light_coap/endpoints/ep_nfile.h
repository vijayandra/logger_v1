#ifndef __EP_NFILE_H
#define __EP_NFILE_H

extern const char *uriFileOpArrStr[20];

#define FILE_FLRDBIN_URI  "<flrd-bin>"
#define FILE_FLWRBIN_URI  "<flwr-bin>"
#define FILE_FLRDLINE_URI "<flrd-line>"
#define FILE_FLWRLINE_URI "<flwr-line>"

extern const scoap_endpoint_path_t path_line_io;
extern const scoap_endpoint_path_t path_bin_io;


extern int ep_file_line_get(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_file_bin_get(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_file_line_put(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_file_bin_put(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);


#endif
